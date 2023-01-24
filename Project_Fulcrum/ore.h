#ifndef ORE_H
#define ORE_H

#include "collectibleobject.h"

enum class OreColor
{
    GOLDEN,
    IRON,
    COPPER
};

class Ore : public CollectibleObject
{
public:
    Ore(OreColor oreColor, int pointsToCollect);
    ~Ore() {};

protected:
    OreColor oreColor;

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // ORE_H
