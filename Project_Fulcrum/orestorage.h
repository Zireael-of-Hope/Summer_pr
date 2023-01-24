#ifndef ORESTORAGE_H
#define ORESTORAGE_H

#include "storage.h"

class OreStorage : public Storage
{
public:
    OreStorage();
    ~OreStorage() {};

private:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // ORESTORAGE_H
