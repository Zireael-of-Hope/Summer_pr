#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QObject>

enum class ObstacleColor
{
    ROCK,
    WOOD
};

enum class WhatSideCollisionIsFrom
{
    TOP,
    BOTTOM,
    RIGHT,
    LEFT
};

class Obstacle : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    Obstacle(ObstacleColor obstacleColor, int width, int height);
    ~Obstacle() {};
    void checkForCollision();
    WhatSideCollisionIsFrom getSideOfCollision(QPointF collidedItemLocation);

protected:
    ObstacleColor obstacleColor;
    bool itemIsCollidingOnSpawn; // check if item has a place to spawn
    int width;
    int height;
    int startX;
    int startY;
    QPointF location;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // OBSTACLE_H
