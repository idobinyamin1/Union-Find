//uf
#ifndef DATA_STRUCTURE_uf
#define DATA_STRUCTURE_uf

#include "ravl.h"
#include "sells.h"
#include "id.h"

typedef enum
{
    SUCCESS_uf = 0,
    FAILURE_uf = -1,
    ALLOCATION_ERROR_uf = -2,
    INVALID_INPUT_uf = -3
} StatusType_uf;
struct ufnode
{
    int id;
    int rank;
    ufnode *parent;
    ravl<id_data> id_tree;
    ravl<sells_data> sells_tree;

    ufnode(int id_)
    {
        parent = nullptr;
        id = id_;
        rank = 1;
        id_tree.root = nullptr;
        sells_tree.root = nullptr;
    }
};
class uf
{
public:
    int numSets;

    int numElts;
    int array_size;
    int array_used;
    int num_of_agencies;

    ufnode **nodes;

    uf() : numSets(0), numElts(0), array_size(1), array_used(0), num_of_agencies(0)
    {
        nodes = new ufnode *[1];

        nodes[0] = nullptr;
    }
    // uf(int num) : numSets(0), numElts(0)

    ~uf()
    {
        for (int i = 0; i < array_used; i++)
        {
            ufnode *iterator = nodes[i];

            if (iterator->id_tree.root != nullptr)
            {
                iterator->id_tree.root->delete_tree();
                iterator->id_tree.root = nullptr;
            }

            if (iterator->sells_tree.root != nullptr)
            {
                iterator->sells_tree.root->delete_tree();

                iterator->sells_tree.root = nullptr;
            }
            delete iterator;
        }
        delete[] nodes;
    }
    StatusType_uf Union(int set1, int set2)
    {
        ufnode *set1_rep = Find(set1);
        ufnode *set2_rep = Find(set2);
        if (set1_rep == nullptr || set2_rep == nullptr)
        {
            return FAILURE_uf;
        }

        if (set1_rep->id == set2_rep->id)
        {
            return SUCCESS_uf;
        }

        if (set1_rep->rank < set2_rep->rank)
        {
            set1_rep->parent = set2_rep;
            unite_trees(set2_rep->id_tree, set1_rep->id_tree);
            unite_trees(set2_rep->sells_tree, set1_rep->sells_tree);
       


        }
        else if (set1_rep->rank > set2_rep->rank)
        {
            set2_rep->parent = set1_rep;
            unite_trees(set1_rep->id_tree, set2_rep->id_tree);
            unite_trees(set1_rep->sells_tree, set2_rep->sells_tree);
                   

        }
        else
        {
            set2_rep->parent = set1_rep;
            unite_trees(set1_rep->id_tree, set2_rep->id_tree);
            unite_trees(set1_rep->sells_tree, set2_rep->sells_tree);
            set1_rep->rank += 1;
        
              



        }

        --numSets;
        return SUCCESS_uf;
    }

    ufnode *Find(int id)
    {
        if (id+1>array_used ||nodes[id] == nullptr)
        {
            return nullptr;
        }
        ufnode *root = nodes[id];

        //find root
        while (root->parent != nullptr)
            root = root->parent;

        // compress to root
        ufnode *i = nodes[id];
        while (i != root)
        {
            ufnode *parent = i->parent;
            i->parent = root;
            i = parent;
        }

        return root;
    }
    //uf(const uf &b);
    //uf &operator=(const uf &d);

    StatusType_uf AddSet()
    {
        if (array_used == array_size)
        {
            ufnode **temp_array = new ufnode *[array_size * 2];
            if (temp_array == nullptr)
            {
                return ALLOCATION_ERROR_uf;
            }

            for (int i = 0; i < array_size; i++)
            {
                temp_array[i] = nodes[i];
            }
            for (int i = array_size; i < 2 * array_size; i++)
            {
                temp_array[i] = nullptr;
            }
            delete[] nodes;
            nodes = new ufnode *[array_size * 2];
            if (nodes == nullptr)
            {
                delete[] temp_array;
                return ALLOCATION_ERROR_uf;
            }

            for (int i = 0; i < array_size * 2; i++)
            {
                nodes[i] = temp_array[i];
            }
            delete[] temp_array;
            array_size = (array_size * 2);
        }

        nodes[num_of_agencies] = new ufnode(num_of_agencies);
        if (nodes[num_of_agencies] == nullptr)
        {
            return ALLOCATION_ERROR_uf;
        }

        array_used++;
        num_of_agencies++;
        return SUCCESS_uf;
    }
    //int NumElements() const;
    //int NumSets() const;
};

#endif