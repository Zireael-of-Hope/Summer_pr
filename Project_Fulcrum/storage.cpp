#include "storage.h"

Storage::Storage()
{
    quantityOfResources = 0;
}

bool Storage::GetResources(int howMuchResources)
{
    quantityOfResources += howMuchResources;
    if (quantityOfResources >= 1500)
    {
        quantityOfResources = 0;
        prepareGeometryChange();
        return true;
    }
    else
    {
        prepareGeometryChange();
        return false;
    }
}


