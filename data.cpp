#include "data.h"

#include "timer.h"
#include <QDebug>

void Data::generateColorsForTheGame(const QColor &firstPlayerColor,
                                    const QColor &secondPlayerColor,
                                    size_t colorsNumber)
{
    colorsForGame.push_back(firstPlayerColor);
    colorsForGame.push_back(secondPlayerColor);
    size_t counter = 0;
    while (colorsForGame.size() != colorsNumber)
    {
        if (counter != constValues.size() - 1)
        {
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
}

void Data::createCustomColors(QColor firstPlayerColor,
                              QColor secondPlayerColor, int numberOfCells)
{
    int nesting = 1;
    for (; numberOfCells > 0; numberOfCells -= nesting, ++nesting);

    qDebug() << "nesting == " << --nesting;
    int nestingColumn = nesting;
    for (int row = 0; row < nesting; ++row)
    {
        for (int column = 0; column < nestingColumn; ++column)
        {
            m_data[row][column] = { firstPlayerColor, Owner::FIRST_PLAYER };
            m_data[m_data.size() - 1 - row]
                    [m_data[m_data.size() - 1 - row].size() - 1 - column]
                    = { secondPlayerColor, Owner::SECOND_PLAYER };
        }
        --nestingColumn;
    }
}

void Data::loadData(int rows, int columns, QColor firstPlayerColor,
                    QColor secondPlayerColor, size_t colorsNumber,
                    int numberOfStartingCells)
{
    timer t;
    t.start();

    generateColorsForTheGame(firstPlayerColor, secondPlayerColor, colorsNumber);
    srand(time(NULL));

    m_data.resize(rows);
    for (int row = 0; row < rows; ++row)
    {
        for (int column = 0; column < columns; ++column)
        {
            m_data[column].reserve(columns);

            auto val = rand() % colorsForGame.size();
            QColor tempColor = colorsForGame.at(val);
            m_data[row].push_back({tempColor, Owner::IS_FREE });
        }
    }

    createCustomColors(firstPlayerColor,secondPlayerColor, numberOfStartingCells);
}

const std::vector<std::vector<Field> > &Data::data() const noexcept
{
    return m_data;
}

Data::~Data()
{
    colorsForGame.clear();
    m_data.clear();
}
