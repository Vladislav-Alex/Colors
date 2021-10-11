#include "gameboard.h"
#include <algorithm>
#include <random>
#include <time.h>

#include "music.h"

GameBoard::GameBoard(QObject* pobj)
    : QAbstractTableModel(pobj), m_state(FIRST_PLAYER),
      m_firstPlayerAccount(0), m_secondPlayerAccount(0)
{
    m_pRecorder = new MoveRecorder();
}

void GameBoard::restart()
{
//    delete m_pRecorder;
    m_firstPlayerAccount = 0;
    m_secondPlayerAccount = 0;
    m_playersAccount.clear();
    isFirstEntering = true;

    delete m_pDataClass;
}

GameBoard::~GameBoard()
{
    restart();
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
        return m_pDataClass->data()[index.row()][index.column()].color;

    case MyRoles::OWNER_ROLE:
        return m_pDataClass->data()[index.row()][index.column()].owner;
    }
    return QVariant();
}

bool GameBoard::setData(const QModelIndex& index, const QVariant& value, int nRole)
{
    if (!dataReadyForWork())
        return false;
    if (nRole == Qt::EditRole) {
//        QColor temp = m_pDataClass->data()[index.row()][index.column()].color;
        m_pDataClass->m_data[index.row()][index.column()].color = color;
        ++m_playersAccount.at(m_state);

        m_firstPlayerAccount = m_playersAccount.at(0);
        m_secondPlayerAccount = m_playersAccount.at(1);
        emit accountChanged();

        switch (value.toInt()) {
        case WhoseMove::FIRST_PLAYER:
            m_pDataClass->m_data[index.row()][index.column()].owner = Owner::FIRST_PLAYER;
            break;
        case WhoseMove::SECOND_PLAYER:
            m_pDataClass->m_data[index.row()][index.column()].owner = Owner::SECOND_PLAYER;
            break;
        }
        emit dataChanged(index, index);
        return true;
    }
    else if (nRole == MyRoles::COLOR_ROLE)
    {
        m_pDataClass->m_data[index.row()][index.column()] = { value.value<QColor>(), Owner::IS_FREE};
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
        m_firstPlayerAccount = m_playersAccount.at(0);
        m_secondPlayerAccount = m_playersAccount.at(1);
        emit accountChanged();
    }
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

bool GameBoard::helper(int x, int y) // the method for check that one of four adjacent cells belongs to the player
{
    for (int i = -1; i <= 1; i += 2)
    {
        QModelIndex tempIndex = index(x, y + i);
        if (tempIndex.isValid() && m_pDataClass->data()[tempIndex.row()][tempIndex.column()].owner
                                   == static_cast<Owner>(m_state))
            return true;

        tempIndex = index(x + i, y);
        if (tempIndex.isValid() && m_pDataClass->data()[tempIndex.row()][tempIndex.column()].owner
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
        if (tempIndex.isValid() && (m_pDataClass->data()[tempIndex.row()][tempIndex.column()].owner
                                     == Owner::IS_FREE || isFirstEntering))
            temp.append(tempIndex);

        tempIndex = index(x + i, y);
        if (tempIndex.isValid() && (m_pDataClass->data()[tempIndex.row()][tempIndex.column()].owner
                                    == Owner::IS_FREE || isFirstEntering))
            temp.append(tempIndex);
    }
    return temp;
}

void GameBoard::takeAll(const QModelIndex &index, bool isFirstEntering)
{
    int find = pretendent.indexOf(index);

    if (find == -1 && m_pDataClass->data()[index.row()][index.column()].color == m_playersColors.at(m_state))
    {
        if (!isFirstEntering)
            pretendent.append(index);
        QList<QModelIndex> test = forCheck(index.row(), index.column());
        for (const QModelIndex& item : test) takeAll(item, false);
    }
}


void GameBoard::endOfTheGame()
{
    timer t;
    t.start();
    for (int row = 0; row < m_nRows; ++row)
    {
        for (int column = 0; column < m_nColumns; ++column)
        {
            if (m_pDataClass->data()[row][column].owner == Owner::IS_FREE)
            {
                if ((row - 1) >= 0 && m_pDataClass->data()[row - 1][column].owner == static_cast<Owner>(m_state))
                {
                    return;
                }
                if ((row + 1) < m_nRows && m_pDataClass->data()[row + 1][column].owner == static_cast<Owner>(m_state))
                {
                    return;
                }
                if ((column - 1) >= 0 && m_pDataClass->data()[row][column - 1].owner == static_cast<Owner>(m_state))
                {
                    return;
                }
                if ((column + 1) < m_nColumns && m_pDataClass->data()[row][column + 1].owner == static_cast<Owner>(m_state))
                {
                    return;
                }
            }
            else
            {
                t.stop();
                qDebug() << "Finished data " << t.ms() << "ms";
                continue;
            }
        }
        t.stop();
        qDebug() << "Finished data " << t.ms() << "ms";
    }
    emit gameEndSignal();
}

void GameBoard::commit(int row, int column)
{
    vectorToReverse.clear();
    if (!dataReadyForWork())
        return;
    QModelIndex tempIndex = index(row, column);

    if (!tempIndex.isValid() || m_pDataClass->data()[tempIndex.row()][tempIndex.column()].owner != Owner::IS_FREE || !helper(row, column))
        return;

    pretendent.clear();
    Recorder rec = {{tempIndex.row(), tempIndex.column()}, m_pDataClass->m_data[tempIndex.row()][tempIndex.column()]};

    setData(tempIndex, m_state, Qt::EditRole);
    takeAll(tempIndex, true);
    if (pretendent.count() > 0)
    {
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

    endOfTheGame();
}

void GameBoard::addingAreasToPlayerTerritories(size_t row, size_t column, WhoseMove move)
{
    takeAll(index(row, column), true);
    if (pretendent.count() > 0)
        changeFieldOwner();
    pretendent.clear();
    vectorToReverse.clear();
    m_state = move;
    color = m_playersColors.at(m_state);
}

void GameBoard::boardCreation(int size, QColor colorPlayer1, QColor colorPlayer2, int numberOfColors)
{
    timer t;
    t.start();

    restart();
    m_playersAccount = { m_firstPlayerAccount, m_secondPlayerAccount };

    m_pDataClass = new Data();

    beginInsertRows(QModelIndex(), 0, size - 1);
        m_nRows = size;
    endInsertRows();
    beginInsertColumns(QModelIndex(), 0, size - 1);
        m_nColumns = size;
    endInsertColumns();

    m_pDataClass->loadData(size, size, colorPlayer1, colorPlayer2, numberOfColors);

    m_playersColors.clear();

    m_playersColors.push_back(colorPlayer1);
    m_playersColors.push_back(colorPlayer2);
    color = m_playersColors.at(0);
    m_state = WhoseMove::FIRST_PLAYER;

    emit dataReady();

    addingAreasToPlayerTerritories(0, 0, WhoseMove::SECOND_PLAYER);
    addingAreasToPlayerTerritories(size - 1, size - 1, WhoseMove::FIRST_PLAYER);

    isFirstEntering = false;
    t.stop();
    qDebug() << "Finished initializing arrays in " << t.ms() << "ms";
}

void GameBoard::changeFieldOwner()
{
    for (const QModelIndex& item : pretendent)
    {
        vectorToReverse.push_back({{item.row(), item.column()}, m_pDataClass->m_data[item.row()][item.column()]});
        setData(item, m_state, Qt::EditRole);
    }
    qDebug() << "vectorToReverse.size()" << vectorToReverse.size();
}

bool GameBoard::dataReadyForWork() const
{
    return m_pDataClass;
}

int GameBoard::state() const
{
    return static_cast<int>(m_state);
}

int GameBoard::firstPlayerAccount() const
{
    return m_firstPlayerAccount;
}

int GameBoard::secondPlayerAccount() const
{
    return m_secondPlayerAccount;
}

int GameBoard::rowCount(const QModelIndex&) const
{
    if (dataReadyForWork())
        return m_nRows;
    else
        return defaultPuzzleDimension;

}

int GameBoard::columnCount(const QModelIndex&) const
{
    if (dataReadyForWork())
        return m_nColumns;
    else
        return defaultPuzzleDimension;
}
