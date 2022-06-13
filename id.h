#ifndef DATA_STRUCTURE_id
#define DATA_STRUCTURE_id

#include "sells.h"
class id_data
{
public:
    int id;
    node<sells_data> *sells_p;
    id_data(int id) : id(id), sells_p(nullptr)
    {
    }
    bool operator<(id_data &b)
    {
        if (id < b.id)
        {
            return true;
        }
        return false;
    }
    bool operator>(id_data &b)
    {
        return (b.id < id);
    }
    bool operator==(id_data &b)
    {
        return (!(b.id < id)) && (!(id < b.id));
    }
       void print()
    {
        std::cout<<"["<<id<<"]";
    }
};

#endif