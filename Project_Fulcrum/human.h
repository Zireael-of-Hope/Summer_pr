#ifndef HUMAN_H
#define HUMAN_H

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QObject>
#include "food.h"
#include "obstacle.h"
#include "foodstorage.h"
#include "orestorage.h"
#include <cmath>

class Human : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    Human(FoodStorage* foodStorage, OreStorage* oreStorage);
    ~Human() {};

    void collectFood(int howMuchFood);
    void collectOre(int howMuchOre);
    void checkForCollision();
    void DoCollision();
    void DoCollision(WhatSideCollisionIsFrom sideOFCollision);
    void unloadPackageOfFood();
    void unloadPackageOfOre();
    void turnToNeededStorage(Storage* storage);
    QPointF getLocation() {return location;}
    void UnloadEverything();
    int GetPackageOfFood() {return packageOfFood;}
    int GetPackageOfOre() {return packageOfOre;}

    int packageOfFood; // from 0 to 100
    int packageOfOre; // from 0 to 100

protected:
    int startX;
    int startY;
    qreal angle;
    qreal speed;
    QPointF location;
    bool itemIsCollidingOnSpawn; // check if item has a place to spawn
    bool isMovingToStorage;
    bool isMovingToStorageNotFull;
    FoodStorage* localFoodStorage;
    OreStorage* localOreStorage;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

public slots:
    void advance(int phase);

signals:
    void signalCheckItem(QGraphicsItem *item, Human *humanSender, int foodRequest, int oreRequest, bool isMovingToStorage);
    void signalDebug(int a, int b, int c);
};



#endif // HUMAN_H
