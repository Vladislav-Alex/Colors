#ifndef DATA_H
#define DATA_H

#include <time.h>

#include "field.h"

/**
 * @brief The class for storing data
 */
class Data
{
public:
    /**
     * @brief Method for starting initialization of the playing field
     * @param rows The number of lines in the game board
     * @param columns The number of columns in the game board
     * @param firstPlayerColor The first player color
     * @param secondPlayerColor The second player color
     * @param colorsNumber The number of colors chosen by the player
     * that will be present in the game
     */
    void loadData(int rows, int columns, QColor firstPlayerColor,
                  QColor secondPlayerColor, size_t colorsNumber);

    /**
     * @brief getter
     * @return m_data
     */
    const std::vector<std::vector<Field> > &data() const noexcept;
    ~Data();

    /** Data store */
    std::vector<std::vector<Field>> m_data;
private:
    /** Colors that will be in the game */
    std::vector <QColor> colorsForGame;

    /** Color options that can be in the game */
    const std::vector<QColor> constValues = {  QColor(Qt::darkMagenta),
                                               QColor(Qt::darkBlue),
                                               QColor(Qt::green),
                                               QColor(Qt::yellow),
                                               QColor(Qt::red),
                                               QColor(Qt::blue),
                                               QColor(Qt::darkRed),
                                               QColor(Qt::cyan),
                                               QColor(Qt::black),
                                               QColor(Qt::white) };

    /**
     * @brief generateColorsForTheGame Generating a set of colors for the game
     * by input parameters
     */
    void generateColorsForTheGame(const QColor &firstPlayerColor,
                                  const QColor &secondPlayerColor,
                                  size_t colorsNumber);
    void createCustomColors(QColor firstPlayerColor, QColor secondPlayerColor);
};

#endif // DATA_H
