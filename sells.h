#ifndef DATA_STRUCTURE_sells
#define DATA_STRUCTURE_sells

class sells_data
{
   public:
    int id;
    int sells;

    sells_data(int id, int sells) : id(id), sells(sells)
    {
    }
    bool operator<(sells_data &b)
    {
        if (sells < b.sells || (sells == b.sells && id < b.id))
        {
            return true;
        }
        return false;
    }
   friend bool operator>(sells_data &a,sells_data b)
   {
        return (b < a);
    
   }
  
    friend bool operator==(sells_data &a,sells_data &b)
    {
        return (!(b < a)) && (!(a < b)  );
    }
    void print()
    {
        std::cout<<sells;
    }
};
 

#endif