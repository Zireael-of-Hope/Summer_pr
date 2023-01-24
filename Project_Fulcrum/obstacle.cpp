#include "obstacle.h"

Obstacle::Obstacle(ObstacleColor obstacleColor, int width, int height) : QObject(), QGraphicsItem()
{
    this->obstacleColor = obstacleColor;
    this->width = width;
    this->height = height;
    setFlag(this->ItemIsMovable);

    srand(time(0));
    startX = (rand() % (600)) * ((rand()%2 == 1)?1:-1);
    startY = (rand() % (400)) * ((rand()%2 == 1)?1:-1);
}

QRectF Obstacle::boundingRect() const
{
    return QRectF(0, 0, this->width, this->height);
}

void Obstacle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rec = boundingRect();
    QBrush brush;
    switch(obstacleColor)
    {
    case ObstacleColor::ROCK:
        brush.setColor(QColor(157, 157, 157));
        brush.setStyle(Qt::SolidPattern);
        break;
    case ObstacleColor::WOOD:
        brush.setColor(QColor(72, 64, 39));
        brush.setStyle(Qt::SolidPattern);
        break;
    }

    painter->fillRect(rec, brush);
    painter->drawRect(rec);
}

void Obstacle::checkForCollision()
{
    do {
       if(scene()->collidingItems(this).isEmpty())
        {
         itemIsCollidingOnSpawn = false;
        }
        else {
           itemIsCollidingOnSpawn = true;
           startX = (rand() % (670)) * ((rand()%2 == 1)?1:-1);
           startY = (rand() % (420)) * ((rand()%2 == 1)?1:-1);
           setPos(startX, startY);
        }
    } while(itemIsCollidingOnSpawn);
}

WhatSideCollisionIsFrom Obstacle::getSideOfCollision(QPointF collidedItemLocation)
{
    location = this->pos();
    if (collidedItemLocation.y() > location.y())
        if (collidedItemLocation.x() > location.x())
            if (collidedItemLocation.x() < location.x() + width)
                return WhatSideCollisionIsFrom::BOTTOM;
            else return WhatSideCollisionIsFrom::RIGHT;
        else return WhatSideCollisionIsFrom::LEFT;
    else return WhatSideCollisionIsFrom::TOP;
}

