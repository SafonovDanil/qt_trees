#ifndef SEARCH_TREE_H
#define SEARCH_TREE_H

#include "basic_tree.h"
#include <algorithm>



template<class type> class search_tree :public basic_tree<type>
{
public:

    search_tree();
    search_tree(search_tree<type>&);
    search_tree(type&);
    search_tree(type*, int);

    search_tree<type>& operator = (search_tree<type>&);

    virtual bool AddNode(type&);
    virtual bool DelNode(type&);
    virtual bool FindNode(type&);

private:


    typename search_tree<type>::node** SearchNode(type&, typename search_tree<type>::node*&);
};

template<class type> search_tree<type>::search_tree(): search_tree<type>::basic_tree()
{
}

template<class type> search_tree<type>::search_tree(search_tree& obj): search_tree<type>::basic_tree(obj)
{
}

template<class type> search_tree<type>::search_tree(type& inf) : search_tree<type>::basic_tree(inf)
{
}

template<class type> search_tree<type>::search_tree(type* arr, int n)
{
    basic_tree<type>::root = nullptr;
    if (arr)
    {
        for (int i = 0; i < n; i++)
            AddNode(arr[i]);
    }
}

template<class type> search_tree<type>& search_tree<type>::operator = (search_tree<type>& obj)
{
    if (obj.root)
    {
        if (basic_tree<type>::root)
            *basic_tree<type>::root = *(obj.root);
        else
            basic_tree<type>::root = new typename search_tree<type>::node(*(obj.root));
    }
    else
        if (basic_tree<type>::root)
        {
            delete basic_tree<type>::root;
            basic_tree<type>::root = nullptr;
        }

    return *this;
}

template<class type> bool search_tree<type>::AddNode(type& inf)
{
    typename search_tree<type>::node** ptr = &(basic_tree<type>::root);
    while (*ptr)
    {
        if ((*ptr)->data > inf)
            ptr = &((*ptr)->lt);
        else
            ptr = &((*ptr)->rt);
    }
    *ptr = new typename search_tree<type>::node(inf, 0);
    if(*ptr)
        return true;
    return false;
}

template<class type> bool search_tree<type>::DelNode(type& inf)
{
    typename search_tree<type>::node *ptr, **parent_ptr, *replace_ptr;
    ptr = nullptr;
    replace_ptr = nullptr;
    parent_ptr = SearchNode(inf, ptr);
    if (ptr)   //проверяем есть ли только правый потомок/только левый/есть оба
    {
        if (!ptr->lt)
            replace_ptr = ptr->rt;
        else
            if (!ptr->rt)
                replace_ptr = ptr->lt;
            else
            {
                typename search_tree<type>::node *rep_parent_ptr = ptr;
                replace_ptr = ptr->lt;
                while (replace_ptr->rt) //ищем узел для замены (в левом поддереве самый правый узел)
                {
                    rep_parent_ptr = replace_ptr;
                    replace_ptr = replace_ptr->rt;
                }
                if (ptr != rep_parent_ptr)//если удаляемый не сын замещаемого, то переобозначаем указатели
                {
                    rep_parent_ptr->rt = replace_ptr->lt;
                    replace_ptr->lt = ptr->lt;
                }
                replace_ptr->rt = ptr->rt;
            }
        *parent_ptr = replace_ptr;
        ptr->lt = ptr->rt = nullptr;
        delete ptr;
        return true;
    }
    return false;
}


template<class type> bool search_tree<type>::FindNode(type& inf)
{
    typename search_tree<type>::node* ptr = basic_tree<type>::root;

    while (ptr && ptr->data != inf)
    {
        if (ptr->data > inf)
            ptr = ptr->lt;
        else
            ptr = ptr->rt;
    }

    if (!ptr)
        return false;
    return true;
}


//функция поиска узла + родителя, разбирали на практике
template<class type> typename search_tree<type>::node** search_tree<type>::SearchNode(type& inf, typename search_tree<type>::node*& found_node)
{
    typename search_tree<type>::node** parent_node = &(basic_tree<type>::root);
    found_node = basic_tree<type>::root;
    while(found_node && found_node->data != inf)
    {
        if (found_node->data > inf)
        {
            parent_node = &(found_node->lt);
            found_node = found_node->lt;
        }
        else
        {
            parent_node = &(found_node->rt);
            found_node = found_node->rt;
        }
    }

    if (!found_node)
        parent_node = nullptr;

    return parent_node;
}


#endif // SEARCH_TREE_H
