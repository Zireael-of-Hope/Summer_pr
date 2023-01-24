#include "collectibleobject.h"
CollectibleObject::CollectibleObject()
    : QObject(), QGraphicsItem()
{
    srand(time(0));
    startX = (rand() % (600)) * ((rand()%2 == 1)?1:-1);
    startY = (rand() % (400)) * ((rand()%2 == 1)?1:-1);
}

bool CollectibleObject::getCollected(int &howMuchToCollect_ref)
{
    if (howMuchToCollect_ref >= pointsToCollect)
    {
        howMuchToCollect_ref = pointsToCollect;
        pointsToCollect = 0;
        prepareGeometryChange();
        return true;
    } else
    {
        pointsToCollect = pointsToCollect - howMuchToCollect_ref;
        prepareGeometryChange();
        return false;
    }
}

void CollectibleObject::checkForCollision()
{
    do {
       if(scene()->collidingItems(this).isEmpty())
        {
         itemIsCollidingOnSpawn = false;
        }
        else {
           itemIsCollidingOnSpawn = true;          
           startX = (rand() % (600)) * ((rand()%2 == 1)?1:-1);
           startY = (rand() % (400)) * ((rand()%2 == 1)?1:-1);
           setPos(startX, startY);
        }
    } while(itemIsCollidingOnSpawn);
}



