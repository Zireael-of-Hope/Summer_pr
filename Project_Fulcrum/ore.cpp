#include "ore.h"

Ore::Ore(OreColor oreColor, int pointsToCollect = 180)
{
    this->oreColor = oreColor;
    if (pointsToCollect > 300)
       this->pointsToCollect = 300;
    else if (pointsToCollect < 1)
            this->pointsToCollect = 1;
         else this->pointsToCollect = pointsToCollect;

    setFlag(this->ItemIsMovable);
    setPos(startX, startY);
}

QRectF Ore::boundingRect() const
{
    if (pointsToCollect < 300)
        if (pointsToCollect < 200)
            if (pointsToCollect < 100)
                if (pointsToCollect < 50)
                    if (pointsToCollect < 20)
                        if (pointsToCollect == 0)
                            return QRectF(0,0,0,0);
                        else return QRectF(0,0,10,10);
                    else return QRectF(0,0,25,25);
                else return QRectF(0,0,40,40);
            else return QRectF(0,0,60,60);
        else return QRectF(0,0,80,80);
    else return QRectF(0,0,100,100);
}

void Ore::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rec = boundingRect();
    QBrush brush;
    switch(oreColor)
    {
    case OreColor::GOLDEN:
        brush.setColor(QColorConstants::Svg::gold);
        brush.setStyle(Qt::SolidPattern);
        break;
    case OreColor::IRON:
        brush.setColor(QColor(89, 89, 89));
        brush.setStyle(Qt::SolidPattern);
        break;
    case OreColor::COPPER:
        brush.setColor(QColor(94, 98, 58));
        brush.setStyle(Qt::SolidPattern);
        break;
    }

    painter->fillRect(rec, brush);
    painter->drawRect(rec);
}
