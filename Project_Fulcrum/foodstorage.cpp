#include "foodstorage.h"

FoodStorage::FoodStorage()
{
    startX = -640;
    startY = -390;

    setPos(startX,startY);
}

QRectF FoodStorage::boundingRect() const
{
    return QRectF(0, 0, 150, 165);
}

void FoodStorage::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rec = boundingRect();
    painter->drawRect(rec);

    QBrush brush_1;
    brush_1.setColor(Qt::gray);
    QRectF LeftWall(0, 0, 15, 150);
    painter->setPen(Qt::NoPen);
    brush_1.setStyle(Qt::SolidPattern);
    painter->fillRect(LeftWall, brush_1);

    QBrush brush_2;
    brush_2.setColor(Qt::gray);
    QRectF RightWall(135, 0, 15, 150);
    painter->setPen(Qt::NoPen);
    brush_2.setStyle(Qt::SolidPattern);
    painter->fillRect(RightWall, brush_2);

    QBrush brush_3;
    brush_3.setColor(Qt::gray);
    QRectF BottomWall(0, 150, 150, 15);
    painter->setPen(Qt::NoPen);
    brush_3.setStyle(Qt::SolidPattern);
    painter->fillRect(BottomWall, brush_3);

    QBrush brush_4;
    brush_4.setColor(Qt::green);
    QRectF Resource(15, 150 - (int) quantityOfResources/10, 120, (int) quantityOfResources/10); // width height
    painter->setPen(Qt::NoPen);
    brush_4.setStyle(Qt::SolidPattern);
    painter->fillRect(Resource, brush_4);
}
