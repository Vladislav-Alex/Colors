#ifndef DATA_H
#define DATA_H

#include <QObject>
#include <QAbstractTableModel>
#include <QColor>

#include "field.h"

class Data
{
//    Q_OBJECT
public:
    static constexpr size_t defaultPuzzleDimension = 10;
//    static constexpr size_t colorCount {6};

    Data(QAbstractTableModel &model, int nRows = defaultPuzzleDimension, int nColumns = defaultPuzzleDimension,
         QColor firstPlayer = QColor(Qt::red), QColor secondPlayer = QColor(Qt::blue), QObject* pobj = 0);

    void loadData(QAbstractTableModel &model, int nRows, int nColumns,
                  QColor firstPlayer, QColor secondPlayer, size_t colorsNumber);
    const QHash<QModelIndex, Field> &hash() const;

    QHash<QModelIndex, Field> m_hash;
private:

    std::vector <QColor> colorsForGame;

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
};

#endif // DATA_H
