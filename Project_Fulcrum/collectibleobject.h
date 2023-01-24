#ifndef COLLECTIBLEOBJECT_H
#define COLLECTIBLEOBJECT_H

#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QObject>

enum class TypeOfFacedObject
{
    FOOD,
    ORE,
    OBSTACLE
};

class CollectibleObject : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    CollectibleObject();
    ~CollectibleObject() {};
    bool getCollected(int &howMuchToCollect_ref); // value of collected food will be returned in <howMuchToCollect>
                                              // true if object is depleted
    void checkForCollision();

protected:
    int startX;
    int startY;
    int pointsToCollect; // from 1 to 300
    bool itemIsCollidingOnSpawn; // check if item has a place to spawn

    virtual QRectF boundingRect() const = 0;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) = 0;
};

#endif // COLLECTIBLEOBJECT_H
