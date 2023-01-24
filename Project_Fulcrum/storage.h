#ifndef STORAGE_H
#define STORAGE_H

#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QObject>

class Storage : public QObject, public QGraphicsItem
{
public:
    Storage();
    ~Storage() {};
    bool GetResources(int howMuchResources); // returns true if storage is full
    void MakeEmpty() { prepareGeometryChange(); quantityOfResources = 0; };

protected:
    int quantityOfResources; // from 0 to 1500
    int startX;
    int startY;

    virtual QRectF boundingRect() const = 0;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) = 0;
};

#endif // STORAGE_H
