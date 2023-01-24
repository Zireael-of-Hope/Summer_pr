#ifndef FOODSTORAGE_H
#define FOODSTORAGE_H

#include "storage.h"

class FoodStorage : public Storage
{
public:
    FoodStorage();
    ~FoodStorage() {};

private:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // FOODSTORAGE_H
