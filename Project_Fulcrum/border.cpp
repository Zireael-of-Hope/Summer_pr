#include "border.h"

Border::Border(BorderSide borderSide) : QObject(), QGraphicsItem()
{
    border = borderSide;

    switch (border)
    {
    case BorderSide::BOTTOM_BORDER:
        setPos(-670, 400);
        break;
    case BorderSide::TOP_BORDER:
        setPos(-670, -420);
        break;
    case BorderSide::LEFT_BORDER:
        setPos(-670, -420);
        break;
    case BorderSide::RIGHT_BORDER:
        setPos(650, -420);
        break;
    }
}

QRectF Border::boundingRect() const
{
    switch (border)
    {
    case BorderSide::BOTTOM_BORDER:
    case BorderSide::TOP_BORDER:
        return QRectF(0,0, 1340, 20);
        break;
    case BorderSide::LEFT_BORDER:
    case BorderSide::RIGHT_BORDER:
        return QRectF(0,0, 20, 840);
        break;
    }

}

void Border::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rec = boundingRect();
    QBrush brush;
    brush.setColor(Qt::gray);
    brush.setStyle(Qt::SolidPattern);

    painter->fillRect(rec, brush);
    painter->drawRect(rec);
}
