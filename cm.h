#include "library2.h"
#include "uf.h"


class cm{
public:
uf uf1;

cm():uf1()
{}



StatusType AddAgency()
{
  
    return static_cast<StatusType>(uf1.AddSet() );
    
}
StatusType SellCar( int agencyID, int typeID, int k)
{
    
   
  
   
   
    if(k<=0 ||agencyID<0)
    {
        return INVALID_INPUT;
    }
    
    ufnode * agency_root=uf1.Find(agencyID);

    if(agency_root==nullptr)
    {
        return FAILURE;
    }

   node<id_data>* car_type=agency_root->id_tree.find(typeID);



   if(car_type!=nullptr )
   {
       sells_data old_data (typeID,car_type->data.sells_p->data.sells) ;
       agency_root->sells_tree.remove(old_data);
       old_data.sells+=k;
      
      
       car_type->data.sells_p=agency_root->sells_tree.insert(old_data);
       if(car_type->data.sells_p==nullptr)
       {
           return ALLOCATION_ERROR;
       }
       
       return SUCCESS;
   }

   
   sells_data new_data(typeID,k);
  
    node<id_data>* new_node  =agency_root-> id_tree.insert(typeID);
      if(new_node==nullptr)
       {
           return ALLOCATION_ERROR;
       }


    new_node->data.sells_p=agency_root->sells_tree.insert(new_data);

    
return SUCCESS;
}

StatusType UniteAgencies( int agencyID1, int agencyID2)
{
   if(agencyID1<0||agencyID2<0)
   {
       return INVALID_INPUT;
   }
   
    return static_cast<StatusType>(uf1.Union(agencyID1,agencyID2));
}

StatusType GetIthSoldType( int agencyID, int i, int* res)
{
       if(agencyID<0||res==nullptr||i<0)
   {
       return INVALID_INPUT;
   }
  ufnode* agency_root= uf1.Find(agencyID);
  
  
  if(agency_root==nullptr||agency_root->id_tree.root==nullptr||(i) > (agency_root->id_tree.root->rank-1 ))
  {
      return FAILURE;
  }
  *res=agency_root->sells_tree.root->select(i)->data.id;
  return SUCCESS;
  

}
void Quit()
{
    

delete this;
   
  return;


}

};