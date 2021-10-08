#include "data.h"

Data::Data(QAbstractTableModel& model, int nRows, int nColumns,
           QColor firstPlayer, QColor secondPlayer, QObject* pobj)
{
}

void Data::loadData(QAbstractTableModel &model, int nRows, int nColumns, QColor firstPlayer, QColor secondPlayer, size_t colorsNumber)
{
    colorsForGame.push_back(firstPlayer);
    colorsForGame.push_back(secondPlayer);
    size_t counter = 0;
    while (colorsForGame.size() != colorsNumber)
    {
        if (counter != constValues.size() - 1)
        {
//            qDebug() << "here";
            QColor temp = constValues.at(counter++);
            for (const QColor &item : colorsForGame)
            {
                if (item == temp)
                    continue;
            }
            colorsForGame.push_back(temp);
        }
        else
            counter = 0;
    }

    srand(time(NULL));
    for (int i = 0; i < nRows; ++i)
        for (int j = 0; j < nColumns; ++j)
        {
            QModelIndex tempIndex = model.index(i, j);

            auto val = rand() % colorsForGame.size();
            QColor tempColor = colorsForGame.at(val);
            m_hash[tempIndex] = { tempColor, Owner::IS_FREE };
            switch (tempIndex.row()) {
            case 0:
                switch (tempIndex.column()) {
                case 0:
                case 1:
                    m_hash[tempIndex] = { firstPlayer, Owner::FIRST_PLAYER };
                    break;
                }
                break;
            case 1:
                switch (tempIndex.column()) {
                case 0:
                    m_hash[tempIndex] = { firstPlayer, Owner::FIRST_PLAYER };
                    break;
                }
                break;
            }
            if (tempIndex.row() == nRows - 1 || tempIndex.row() == nRows - 2)
            {
                if (tempIndex.column() == nColumns - 1 || tempIndex.column() == nColumns - 2)
                    m_hash[tempIndex] = { secondPlayer, Owner::SECOND_PLAYER };
            }
            emit model.dataChanged(tempIndex, tempIndex);
        }
}

const QHash<QModelIndex, Field> &Data::hash() const
{
    return m_hash;
}
