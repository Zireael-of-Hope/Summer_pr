#ifndef FOOD_H
#define FOOD_H

#include "collectibleobject.h"

enum class FoodColor
{
    GREEN,
    RED,
    YELLOW
};

class Food : public CollectibleObject
{
public:
    Food(FoodColor foodColor, int pointsToCollect);
    ~Food() {};

protected:
    FoodColor foodColor;
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // FOOD_H
