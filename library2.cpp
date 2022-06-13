#include "library2.h"

#include "cm.h"
void *Init()
{

    auto *DS = new cm();

    return (void *)DS;
}

StatusType AddAgency(void *DS)
{
    if (DS == nullptr)
    {
        return INVALID_INPUT;
    }
    return ((cm *)DS)->AddAgency();
}
StatusType SellCar(void *DS, int agencyID, int typeID, int k)
{

    if (DS == nullptr)
    {
        return INVALID_INPUT;
    }

    return ((cm *)DS)->SellCar(agencyID, typeID, k);
}


StatusType UniteAgencies(void *DS, int agencyID1, int agencyID2)
{

    if (DS == nullptr)
    {
        return INVALID_INPUT;
    }
     return ((cm *) DS)->UniteAgencies( agencyID1, agencyID2);
}

StatusType GetIthSoldType(void *DS, int agencyID, int i, int *res)
{

    if (DS == nullptr)
    {
        return INVALID_INPUT;
    }

    return ((cm *) DS)->GetIthSoldType( agencyID,  i,  res);
}

void Quit(void **DS)
{

    ((cm *)(*DS))->Quit();

*DS=nullptr;
       return;
}