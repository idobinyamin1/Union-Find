
// Created by liran on 07/05/2021.
//

#ifndef DATA_STRUCTURE_ravl_H
#define DATA_STRUCTURE_ravl_H
#include "node.h"
template <class T>
class ravl
{
public:
    node<T> *root;

    node<T> *smallest_leaf;

    explicit ravl() : root(nullptr), smallest_leaf(nullptr){};

    ~ravl()
    {
    }

    node<T> *insert(T data)
    {
        if (root == nullptr)
        {
            root = new node<T>(data, nullptr, nullptr, nullptr);

            update_smallest();
            return root;
        }

        node<T> *data_in_tree = find(data);
        if (data_in_tree != nullptr)
        {
            return data_in_tree;
        }
        node<T> *new_vertex = root->insert(data);

        root = root->get_root(); // updating new root if needed
        update_smallest();
        return new_vertex;
    }

    void update_smallest()
    {
        if (root == nullptr)
        {
            smallest_leaf = nullptr;
            return;
        }
        smallest_leaf = root;
        while (smallest_leaf->left != nullptr)
        {
            smallest_leaf = smallest_leaf->left;
        }
    }

    /**
     * removes node<T> and update tree
     * @param node<T> - pointer to node<T> to remove
     */
    void remove(T data)
    {

        node<T> *to_remove = root->find(data);

        if (to_remove)
        {

            root = to_remove->remove_specific_node();

            root = root->get_root();
            update_smallest();
        }
    }

    /**
     *  find in tree by data
     * @tparam ValueType
     * @param value
     * @return pointer to node<T> or nullptr if not found
     */

    node<T> *find(T data)
    {
        if (root)
        {
            return root->find(data);
        }
        return nullptr;
    }
    /**
     *search_in_tree by value in the data itself
     * @tparam ValueType
     * @param value
     * @return  pointer to node<T> or nullptr if not found
     */

    // template <typename Func>
    // void inorder(Func func)
    // {
    //     if (root)
    //     {
    //         root->inorder(func);
    //     }
    // }

    void delete_tree()
    {

        root->delete_tree();
        root = nullptr;
    }

    node<T> *select(int k)
    {

        if (root == nullptr)
        {
            return nullptr;
        }
        if (root->rank > k)
        {
            return nullptr;
        }
        return root->select(k);
    }
};
template<class T>
void merge(node<T> **array1, node<T> **array2, node<T> **out, int size1, int size2)
{

    int i = 0;

    int j = 0;

    int k = 0;

    while (i < size1 && j < size2)
    {
        if (array1[i]->data < array2[j]->data)
        {
            out[k] = array1[i];
            i++;
        }
        else
        {
            out[k] = array2[j];
            j++;
        }
        k++;
    }

    while (i < size1)
    {
        out[k] = array1[i];
        i++;
        k++;
    }

    while (j < size2)
    {
        out[k] = array2[j];
        j++;
        k++;
    }
}
int log2(int arr)
{
    int to_return = 0;
    int base = 1;
    while (base <= arr)
    {
        base *= 2;
        to_return++;
    }
    return to_return - 1;
}
template<class T>
node<T> *Build_Sub_Tree(node<T> **array, int begin, int end,node<T> *parent=nullptr)
{

    if (begin > end)
    {

        return nullptr;
    }

    int mid = (begin + end) / 2;

    array[mid]->rank = 1;
 array[mid]->height = 0;

int l_height=0;
int r_height=0;

   
    array[mid]->parent = parent;
    array[mid]->left = Build_Sub_Tree(array, begin, mid - 1,array[mid]);
    array[mid]->right = Build_Sub_Tree(array, mid + 1, end, array[mid]);


   if (array[mid]->left != nullptr)
    {
        l_height = array[mid]->left->height;
    }
    if (array[mid]->right != nullptr)
    {
        r_height = array[mid]->right->height;
    }
        if (array[mid]->right == nullptr && array[mid]->left == nullptr)
    {
       array[mid]->height=0;
    }
    else{
        if(l_height>r_height)
        {
            array[mid]->height=l_height+1;
        }
        else{
            array[mid]->height=r_height+1;
        }
    }

    if (array[mid]->left != nullptr)
    {
        array[mid]->rank += array[mid]->left->rank;
    }
    if (array[mid]->right != nullptr)
    {
        array[mid]->rank += array[mid]->right->rank;
    }

    return array[mid];
}
template <class T>
void unite_trees(ravl<T> &t1, ravl<T> &t2)
{

    
    if(t2.root==nullptr)
    {
        return;
    }
      if(t1.root==nullptr)
    {
        t1.root=t2.root;
        t2.root=nullptr;
        return;
    }
    node<T> *r1 = t1.root;
    node<T> *r2 = t2.root;

   
    int t1_size = r1->rank;
    int t2_size = r2->rank;

    node<T> *r1_i = r1;
    node<T> *r2_i = r2;
    while (r1_i->left)
    {
        r1_i = r1_i->left;
    }
    while (r2_i->left)
    {
        r2_i = r2_i->left;
    }
    node<T> **array1 = new node<T> *[t1_size];
    node<T> **array2 = new node<T> *[t2_size];

    for (int i = 0; i < t1_size; i++)
    {

        array1[i] = r1_i;
        r1_i = r1_i->FindNextInOrder(r1_i);
    }
    for (int i = 0; i < t2_size; i++)
    {

        array2[i] = r2_i;
        r2_i = r2_i->FindNextInOrder(r2_i);
    }
    node<T> **array3 = new node<T> *[t2_size + t1_size];
    merge(array1, array2, array3, t1_size, t2_size);
    delete[] array1;
    delete[] array2;

    t1.root = Build_Sub_Tree(array3,  0, t2_size + t1_size - 1);
    t2.root = nullptr;
    t1.update_smallest();
    t2.update_smallest();
       delete[] array3;
     
}
#endif //DATA_STRUCTURE_ravl_H
