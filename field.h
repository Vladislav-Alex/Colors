#ifndef FIELD_H
#define FIELD_H

#include <QColor>

/**
 * @brief Enum to indicate who owns the field
 */
enum Owner
{
    FIRST_PLAYER,
    SECOND_PLAYER,
    IS_FREE
};

/**
 * @brief The struct contains the color of the field and its owner
 */
struct Field
{
    QColor color;
    Owner owner;
};

#endif
