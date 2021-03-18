#ifndef CHAOTIC_TREE_H
#define CHAOTIC_TREE_H

#include "basic_tree.h"
#include <algorithm>
#include <random>
#include <QRandomGenerator>
#include <stack>

template<class type> class chaotic_tree: public basic_tree<type>
{
protected:
    void addTo(typename basic_tree<type>::node *, typename basic_tree<type>::node *);
public:
    chaotic_tree();
    chaotic_tree(chaotic_tree<type>&);
    chaotic_tree(type&);
    chaotic_tree(type*, int);
    chaotic_tree<type>& operator = (chaotic_tree<type>&);
    virtual bool AddNode(type&);
    virtual bool DelNode(type&);
    bool FindNode(type&);
};

template<class type> chaotic_tree<type>::chaotic_tree(): chaotic_tree<type>::basic_tree()
{}

template<class type> chaotic_tree<type>::chaotic_tree(chaotic_tree& obj):chaotic_tree<type>::basic_tree(obj)
{}

template<class type> chaotic_tree<type>::chaotic_tree(type& inf):chaotic_tree<type>::basic_tree(inf)
{}

template<class type> chaotic_tree<type>::chaotic_tree(type*arr, int n)
{
    if(arr)
    {
        for(int i = 0; i < n; i++)
            addTo(arr[i]);
    }
}

template<class type> void chaotic_tree<type>::addTo(typename basic_tree<type>::node *R, typename basic_tree<type>::node *N)
{
    QRandomGenerator generator;
    if (generator.bounded(100) % 2) {
        if (R->rt) {
            addTo(R->rt, N);
        } else {
            R->rt = N;
        }
    }
    else {
        if (R->lt) {
            addTo(R->lt, N);
        } else {
            R->lt = N;
        }
    }
}

template<class type>chaotic_tree<type>& chaotic_tree<type>::operator = (chaotic_tree<type>& obj)
{
    if(obj.root)
    {
        if(basic_tree<type>::root)
            *basic_tree<type>::root=*(obj.root);
        else
            basic_tree<type>::root=new typename chaotic_tree<type>::node(*(obj.root));
    }
    else
        if(basic_tree<type>::root)
        {
            delete basic_tree<type>::root;
            basic_tree<type>::root = nullptr;
        }
    return *this;
}

template<class type> bool chaotic_tree<type>::AddNode(type &inf)
{
    typename basic_tree<type>::node** ptr = &(basic_tree<type>::root);
    while(*ptr)
    {
    if(rand()% 2)
        ptr = &((*ptr)->lt);
    else
        ptr = &((*ptr)->rt);
    }
    (*ptr)  = new typename chaotic_tree<type>::node(inf, 0);
    if(*ptr)
        return true;
    return false;
}

template<class type> bool chaotic_tree<type>::DelNode(type &inf)
{
    if(chaotic_tree<type>::root)
    {
        typename chaotic_tree<type>::node** ptrNode = &(chaotic_tree<type>::root);
        std::stack<typename chaotic_tree<type>::node **> buf_nodes;
        buf_nodes.push(nullptr);

        while(ptrNode && (*ptrNode)->data != inf)
        {
            if ((*ptrNode)->rt) {
                buf_nodes.push(&((*ptrNode)->rt));
            }

            if ((*ptrNode)->lt) {
                ptrNode = &((*ptrNode)->lt);
            } else {
                ptrNode = buf_nodes.top();
                buf_nodes.pop();
            }
        }

        if(ptrNode)
        {
            typename chaotic_tree<type>::node *ptr_lt = nullptr, *ptr_rt = nullptr;

            if((*ptrNode)->lt)
                ptr_lt = (*ptrNode)->lt;
            if((*ptrNode)->rt)
            {
                if(ptr_lt)
                    ptr_rt = (*ptrNode)->rt;
                else
                    ptr_lt = (*ptrNode)->rt;
            }

            delete (*ptrNode);
            (*ptrNode) = ptr_lt;

            if(ptr_rt)
            {
                typename chaotic_tree<type>::node** ptr= &(chaotic_tree<type>::root);
                while(*ptr)
                {
                    if(rand()%2)
                        ptr = &((*ptr)->lt);
                    else
                        ptr = &((*ptr)->rt);
                }
                (*ptr) = ptr_rt;
            }

            return true;
        }
    }
    return false;
}

template<class type> bool chaotic_tree<type>::FindNode(type& inf)
{
    typename chaotic_tree<type>::node* ptr = basic_tree<type>::root;

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


#endif // CHAOTIC_TREE_H
