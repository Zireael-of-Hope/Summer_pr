#include "human.h"

Human::Human(FoodStorage* foodStorage, OreStorage* oreStorage)
    : QObject(), QGraphicsItem()
{
    setFlag(this->ItemIsMovable);
    srand(time(0));

    //random start rotation
    angle = (rand() % 360);
    setRotation(angle);

    //set the speed
    speed = 1;

    //randon start position

    srand(time(0));
    startX = (rand() % (670)) * ((rand()%2 == 1)?1:-1);
    startY = (rand() % (420)) * ((rand()%2 == 1)?1:-1);

    setPos(startX, startY);

    packageOfFood = 0;
    packageOfOre = 0;

    this->localFoodStorage = foodStorage;
    this->localOreStorage = oreStorage;

    isMovingToStorage = false;
}

void Human::collectFood(int howMuchFood)
{
    packageOfFood += howMuchFood;

    if (packageOfFood >= 100)
    {
        packageOfFood = 100;
        isMovingToStorage = true;
        turnToNeededStorage(localFoodStorage);
    }

    if (isMovingToStorageNotFull == true)
        turnToNeededStorage(localFoodStorage);
}

void Human::collectOre(int howMuchOre)
{
    packageOfOre += howMuchOre;

    if (packageOfOre >= 100)
    {
        packageOfOre = 100;
        isMovingToStorage = true;
        turnToNeededStorage(localOreStorage);
    }

    if (isMovingToStorageNotFull == true)
        turnToNeededStorage(localOreStorage);
}

QRectF Human::boundingRect() const
{
    return QRectF(-10, -10, 20, 20);
}

void Human::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rec = boundingRect();
    QBrush brush(Qt::gray);

    painter->fillRect(rec, brush);
    painter->drawRect(rec);

    QRectF lineRec_food(-10, 5, (int) packageOfFood/10, 5);
    brush.setColor(Qt::green);
    painter->setPen(Qt::NoPen);
    brush.setStyle(Qt::SolidPattern);
    painter->fillRect(lineRec_food, brush);

    QRectF lineRec_ore(0, 5, (int) packageOfOre/10, 5);
    brush.setColor(Qt::blue);
    painter->setPen(Qt::NoPen);
    brush.setStyle(Qt::SolidPattern);
    painter->fillRect(lineRec_ore, brush);
}

void Human::unloadPackageOfFood()
{
    packageOfFood = 0;
    isMovingToStorage = false;
    isMovingToStorageNotFull = false;
}

void Human::unloadPackageOfOre()
{
    packageOfOre = 0;
    isMovingToStorage = false;
    isMovingToStorageNotFull = false;
}

void Human::turnToNeededStorage(Storage *storage)
{
    bool isStorageFound = false;
    int locAngle = 0;
    do {
        QList<QGraphicsItem *> foundItems = scene()->items(QPolygonF()
        << mapToScene(0, 0) << mapToScene(-1, -1700) << mapToScene(1, -1700));
        foreach (QGraphicsItem *item, foundItems)
        {
            if (item == storage)
                isStorageFound = true;
            else {
                setRotation(locAngle + 1);
                locAngle = locAngle + 1;
            }
        }
    } while (!isStorageFound);
}

void Human::UnloadEverything()
{
    if (!isMovingToStorage)
    {
        if (packageOfFood != 0)
            {
                turnToNeededStorage(localFoodStorage);
                isMovingToStorage = true;
                isMovingToStorageNotFull = true;
            }
            else  if (packageOfOre != 0 )
            {
                turnToNeededStorage(localOreStorage);
                isMovingToStorage = true;
                isMovingToStorageNotFull = true;
            }
    }
}

void Human::advance(int phase)
{
    if(!phase) return;  
    setPos(mapToParent(0, -(speed)));
    location = this->pos();

    QList<QGraphicsItem *> foundItems = scene()->items(QPolygonF()
    << mapToScene(0, 0) << mapToScene(-20, -20) << mapToScene(20, -20));
    foreach (QGraphicsItem *item, foundItems)
    {
        if (item == this)
            continue;
        emit signalCheckItem(item, this, 100 - packageOfFood, 100 - packageOfOre, isMovingToStorage);
    }
}

void Human::checkForCollision()
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

void Human::DoCollision(WhatSideCollisionIsFrom sideOfCollision)
{   
    if (isMovingToStorage)
    {
        collectFood(0);
        collectOre(0);
    }
        else
    switch(sideOfCollision)
    {
    case WhatSideCollisionIsFrom::TOP:
        if (angle > 180)
            angle = angle + (270 - angle) * 2;
        else angle = angle - (angle - 90) * 2;
        setRotation(angle);
        break;
    case WhatSideCollisionIsFrom::BOTTOM:
        if (angle > 180)
            angle = angle - (angle - 270) * 2;
        else angle = angle + (90 - angle) * 2;
        setRotation(angle);
        break;
    case WhatSideCollisionIsFrom::RIGHT:
        if (angle > 90 && angle < 270)
            angle = angle - (angle - 180) * 2;
        else angle = 0 + (360 - angle);
        setRotation(angle);
        break;
    case WhatSideCollisionIsFrom::LEFT:
        if (angle > 90 && angle < 270)
            angle = angle + (180 - angle) * 2;
        else angle = 270 + (90 - angle);
        setRotation(angle);
        break;
    }
}

void Human::DoCollision()
{
    angle = (rand() % (180)) * ((rand()%2 == 1)?1:-1);
    setRotation(angle);
}



