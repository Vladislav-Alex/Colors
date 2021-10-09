#include "data.h"

void Data::generateColorsForTheGame(const QColor &firstPlayerColor, const QColor &secondPlayerColor, size_t colorsNumber)
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

void Data::loadData(int rows, int columns, QColor firstPlayerColor,
                    QColor secondPlayerColor, size_t colorsNumber)
{
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
            switch (row) {
            case 0:
                switch (column) {
                case 0:
                case 1:
                    m_data[row][column] = { firstPlayerColor, Owner::FIRST_PLAYER };
                    break;
                }
                break;
            case 1:
                switch (column) {
                case 0:
                    m_data[row][column] = { firstPlayerColor, Owner::FIRST_PLAYER };
                    break;
                }
                break;
            }
            if (row == rows - 1 || row == rows - 2)
            {
                if (column == columns - 1 || column == columns - 2)
                    m_data[row][column] = { secondPlayerColor, Owner::SECOND_PLAYER };
            }
        }
    }
}

const std::vector<std::vector<Field> > &Data::data() const noexcept
{
    return m_data;
}
