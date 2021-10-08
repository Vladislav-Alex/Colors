#include "gameboard.h"
#include <algorithm>
#include <random>
#include <time.h>

#include "music.h"

GameBoard::GameBoard(int nRows, int nColumns, QObject* pobj)
    : QAbstractTableModel(pobj), m_nRows(nRows) , m_nColumns(nColumns),
      m_state(FIRST_PLAYER), color(QColor(Qt::green)), m_firstPlayerAccount(0), m_secondPlayerAccount(0)
{
    m_playersAccount = { m_firstPlayerAccount, m_secondPlayerAccount };

    m_pRecorder = new MoveRecorder();
}

GameBoard::~GameBoard()
{
//    dataClass->hash().clear();
    delete m;
}

QVariant GameBoard::data(const QModelIndex& index, int nRole) const
{
    if (!index.isValid() || !dataReadyForWork()) {
        return QVariant();
    }
    switch (nRole) {
    case Qt::DisplayRole:
    case Qt::EditRole:
    case MyRoles::COLOR_ROLE:
        return m_pDataClass->hash().value(index).color;

    case MyRoles::OWNER_ROLE:
        return m_pDataClass->hash().value(index).owner;
    }
    return QVariant();
}

bool GameBoard::setData(const QModelIndex& index, const QVariant& value, int nRole)
{
    if (!dataReadyForWork())
        return false;
    if (nRole == Qt::EditRole) {
        QColor temp = m_pDataClass->hash()[index].color;
        m_pDataClass->m_hash[index].color = color;
        ++m_playersAccount.at(m_state);

        m_firstPlayerAccount = m_playersAccount.at(0);
        m_secondPlayerAccount = m_playersAccount.at(1);
        emit accountChanged();

        switch (value.toInt()) {
        case WhoseMove::FIRST_PLAYER:
            m_pDataClass->m_hash[index].owner = Owner::FIRST_PLAYER;
            break;
        case WhoseMove::SECOND_PLAYER:
            m_pDataClass->m_hash[index].owner = Owner::SECOND_PLAYER;
            break;
        }
        emit animation(temp, m_pDataClass->hash()[index].color);
        emit dataChanged(index, index);
        return true;
    }
    else if (nRole == MyRoles::COLOR_ROLE)
    {
        m_pDataClass->m_hash[index] = { value.value<QColor>(), Owner::IS_FREE};
        emit dataChanged(index, index);

        return true;
    }
    return false;
}

void GameBoard::stepDown()
{
    if (m_pRecorder->size() == 0)
        return;
    const std::vector<Recorder> &temp = m_pRecorder->pop();
    //qDebug() << "m_pRecorder->.size()"<< m_pRecorder->size();
    if (temp.size() != 0)
    {
        switch (m_state) {
        case WhoseMove::FIRST_PLAYER:
            color = m_playersColors.at(1);
                        qDebug() << "change from " << m_state;
            m_state = WhoseMove::SECOND_PLAYER;
                        qDebug() << "change to " << m_state;
            emit playerChanged();
            break;
        case WhoseMove::SECOND_PLAYER:
            color = m_playersColors.at(0);
                        qDebug() << "change from " << m_state;
            m_state = WhoseMove::FIRST_PLAYER;
                        qDebug() << "change to " << m_state;
            emit playerChanged();
            break;
        }

        for (auto item : temp)
        {
            qDebug() << "temp.size()"<< temp.size();
            QModelIndex tempIndex = index(static_cast<int>(item.point.x), static_cast<int>(item.point.y));
            setData(tempIndex, item.field.color, MyRoles::COLOR_ROLE);
            --m_playersAccount.at(m_state);
        }

//        ++m_playersAccount.at(m_state);
        m_firstPlayerAccount = m_playersAccount.at(0);
        m_secondPlayerAccount = m_playersAccount.at(1);
        emit accountChanged();
    }
//
//    for (auto item : pretendent)
//
}

QHash <int,QByteArray> GameBoard::roleNames() const
{
    return { { MyRoles::COLOR_ROLE, "display" },
             { MyRoles::OWNER_ROLE, "owner" },
    };
}

Qt::ItemFlags GameBoard::flags(const QModelIndex& index) const
{
    Qt::ItemFlags flags = QAbstractTableModel::flags(index);
    return index.isValid() ? (flags | Qt::ItemIsEditable) : flags;
}

int GameBoard::nColumns() const
{
    return m_nColumns;
}

int GameBoard::nRows() const
{
    return m_nRows;
}

bool GameBoard::helper(int x, int y) // the method for check that one of four adjacent cells belongs to the player
{
    for (int i = -1; i <= 1; i += 2)
    {
        QModelIndex tempIndex = index(x, y + i);
        if (tempIndex.isValid() && m_pDataClass->hash()[tempIndex].owner
                                   == static_cast<Owner>(m_state))
            return true;

        tempIndex = index(x + i, y);
        if (tempIndex.isValid() && m_pDataClass->hash()[tempIndex].owner
                                   == static_cast<Owner>(m_state))
            return true;
    }
    return false;
}

QList<QModelIndex> GameBoard::forCheck(int x, int y)
{
    QList<QModelIndex> temp;
    for (int i = -1; i <= 1; i += 2)
    {
        QModelIndex tempIndex = index(x, y + i);
        if (tempIndex.isValid() && (m_pDataClass->hash()[tempIndex].owner
                                     == Owner::IS_FREE || isFirstEntering))
            temp.append(tempIndex);

        tempIndex = index(x + i, y);
        if (tempIndex.isValid() && (m_pDataClass->hash()[tempIndex].owner
                                    == Owner::IS_FREE || isFirstEntering))
            temp.append(tempIndex);
    }
    return temp;
}

void GameBoard::takeAll(const QModelIndex &index, bool isFirstEntering)
{
    int find = pretendent.indexOf(index);

    if (find == -1 && m_pDataClass->hash()[index].color == m_playersColors.at(m_state))
    {
        if (!isFirstEntering)
            pretendent.append(index);
        QList<QModelIndex> test = forCheck(index.row(), index.column());
        for (const QModelIndex& item : test) takeAll(item, false);
    }
}


void GameBoard::commit(int row, int column)
{
    vectorToReverse.clear();
    if (!dataReadyForWork())
        return;
    QModelIndex tempIndex = index(row, column);

    if (!tempIndex.isValid() || m_pDataClass->hash()[tempIndex].owner != Owner::IS_FREE || !helper(row, column))
        return;

    pretendent.clear();
    Recorder rec = {{tempIndex.row(), tempIndex.column()}, m_pDataClass->m_hash[tempIndex]};
//    vectorToReverse.append({{tempIndex.row(), tempIndex.column()}, m_pDataClass->m_hash[tempIndex]});

    setData(tempIndex, m_state, Qt::EditRole);
    takeAll(tempIndex, true);
    if (pretendent.count() > 0)
    {
//        --m_playersAccount.at(m_state);
        changeFieldOwner();
    }
    vectorToReverse.push_back(rec);
    m_pRecorder->push(vectorToReverse);

    switch (m_state) {
    case WhoseMove::FIRST_PLAYER:
        color = m_playersColors.at(1);
        m_state = WhoseMove::SECOND_PLAYER;
        emit playerChanged();
        break;
    case WhoseMove::SECOND_PLAYER:
        color = m_playersColors.at(0);
        m_state = WhoseMove::FIRST_PLAYER;
        emit playerChanged();
        break;
    }

    for (auto item : m_pDataClass->hash().keys())
    {
        if (m_pDataClass->hash()[item].owner == Owner::IS_FREE)
        {
            QModelIndex temp1 = index(item.row() - 1, item.column());
            if (temp1.isValid() && m_pDataClass->hash()[temp1].owner == m_state)
            {
                qDebug() << "+";
                return;
            }
            QModelIndex temp2 = index(item.row() + 1, item.column());
            if (temp2.isValid() && m_pDataClass->hash()[temp2].owner == m_state)
            {
                qDebug() << "+";
                return;
            }
            QModelIndex temp3 = index(item.row(), item.column() - 1);
            if (temp3.isValid() && m_pDataClass->hash()[temp3].owner == m_state)
            {
                qDebug() << "+";
                return;
            }
            QModelIndex temp4 = index(item.row(), item.column() + 1);
            if (temp4.isValid() && m_pDataClass->hash()[temp4].owner == m_state)
            {
                qDebug() << "+";
                return;
            }
        }
        else
            continue;
    }
    qDebug() << "over";
    emit someSignal();
}

void GameBoard::test(int size, QColor colorPlayer1, QColor colorPlayer2, int numberOfColors)
{
    qDebug() << "color" << color;
    m_playersColors.push_back(colorPlayer1);
    m_playersColors.push_back(colorPlayer2);
    color = m_playersColors.at(0);
    m_pDataClass = new Data(*this, size, size);

    beginInsertRows(QModelIndex(), 0, size - 1);
        m_nRows = size;
    endInsertRows();

    beginInsertColumns(QModelIndex(), 0, size - 1);
        m_nColumns = size;
    endInsertColumns();
    m_pDataClass->loadData(*this, size, size, colorPlayer1, colorPlayer2, numberOfColors);
    emit dataReady();


    m = new Music;
    takeAll(index(0, 0), true);
    if (pretendent.count() > 0)
        changeFieldOwner();
    pretendent.clear();
    vectorToReverse.clear();
    m_state = WhoseMove::SECOND_PLAYER;
    color = m_playersColors.at(WhoseMove::SECOND_PLAYER);
    takeAll(index(size - 1, size - 1), true);
    if (pretendent.count() > 0)
        changeFieldOwner();
    pretendent.clear();
    vectorToReverse.clear();
    m_state = WhoseMove::FIRST_PLAYER;
    color = m_playersColors.at(WhoseMove::FIRST_PLAYER);
    isFirstEntering = false;

    emit dataChanged(index(0, 0), index(size - 1, size - 1));
}

bool GameBoard::dataReadyForWork() const
{
    return m_pDataClass;
}

void GameBoard::changeFieldOwner()
{
    for (const QModelIndex& item : pretendent)
    {
        vectorToReverse.push_back({{item.row(), item.column()}, m_pDataClass->m_hash[item]});
        setData(item, m_state, Qt::EditRole);
    }
    qDebug() << "vectorToReverse.size()" << vectorToReverse.size();
}

int GameBoard::secondPlayerAccount() const
{
    return m_secondPlayerAccount;
}

int GameBoard::state() const
{
    return static_cast<int>(m_state);
}

int GameBoard::firstPlayerAccount() const
{
    return m_firstPlayerAccount;
}

int GameBoard::rowCount(const QModelIndex&) const
{
    if (dataReadyForWork())
        return m_nRows;
    else
        return defaultPuzzleDimension;

}
// -----------------------------------------------------------------
int GameBoard::columnCount(const QModelIndex&) const
{
    if (dataReadyForWork())
        return m_nColumns;
    else
        return defaultPuzzleDimension;
}
