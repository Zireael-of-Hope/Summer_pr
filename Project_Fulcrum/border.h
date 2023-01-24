#ifndef BORDER_H
#define BORDER_H

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QObject>

enum class BorderSide
{
    LEFT_BORDER,
    RIGHT_BORDER,
    TOP_BORDER,
    BOTTOM_BORDER
};

class Border : public QObject, public QGraphicsItem
{
public:
    Border(BorderSide borderSide);
    ~Border() {};

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    BorderSide border;
};

#endif // BORDER_H
