#ifndef BASIC_TREE_H
#define BASIC_TREE_H

class Area;

template <class type> class basic_tree
{
    friend Area;


protected:

    class node
    {
    public:
        type data;
        node *lt, *rt;
        /*
        //node(type&) - ошибка неоднозначности вызова (скорее всего случай <type> == node)
        node(type&, int); //второй аргумент - хардкод
        */

        //ошибку вызывал ниже закомментированный конструктор, он был объявлен, но не было описания, первые аргументы совпадали, вызывалась неоднозначность
        node(type&);
        node(node&);
        //node(type& inf, node*plt = nullptr, node*prt = nullptr);
        node& operator = (node& obj);
    };

    static int height(node*);
    node* getRoot();
    void ClearTree(basic_tree::node*&root);
    node *Parents(type, node *);         // возвращает РОДИТЕЛЯ

    node* root;
    node* iterator;

public:
    basic_tree();
    basic_tree(basic_tree<type>& obj);
    basic_tree(type&);
    basic_tree& operator = (basic_tree& obj);
    bool isEmpty();
    int Height();
    void Clear();

    virtual bool AddNode(type&)=0;
    virtual bool DelNode(type&)=0;
    virtual bool FindNode(type&)=0;
    virtual bool getData(type& inf);
    virtual ~basic_tree();

};


template<class type> basic_tree<type>::node::node(type& inf)
{
    data = inf;
    rt = lt = nullptr;
}

template<class type> basic_tree<type>::node::node(node& obj)
{
    data = obj.data;
    rt = lt = nullptr;
    if(obj.lt)
        lt = new node(*(obj.lt));
    if(obj.rt)
        rt = new node(*(obj.rt));
}


template<class type> typename basic_tree<type>::node& basic_tree<type>::node::operator=(node& obj)
{
    data = obj.data;
    if(obj.lt)
    {
        if(lt)
        {
            delete lt;
            *lt = *(obj.lt);
        }
        else
            lt = new node(*(obj.lt));
    }
    else
        if(lt)
        {
            delete lt;
            lt = nullptr;
        }
    if(obj.rt)
    {
        if(rt)
        {
            delete rt;
            *rt = *(obj.rt);
        }
        else
            rt = new node(*(obj.rt));
    }
    else
        if(rt)
        {
            delete rt;
            rt = nullptr;
        }
    return *this;
}


template<class type> basic_tree<type>::basic_tree()
{
    root = nullptr;
    iterator = nullptr;
}

template<class type> basic_tree<type>::basic_tree(basic_tree<type>&obj)
{
    root = new node(obj.root);
    iterator = root;
}

template<class type> basic_tree<type>::basic_tree(type& inf)
{
    root = new node(inf);
    iterator = root;
}

template<class type> basic_tree<type>::~basic_tree()
{
    ClearTree(root);
    delete root;
    root = iterator = nullptr;
}

template<class type> bool basic_tree<type>::isEmpty()
{
    if(root)
        return true;
    else
        return false;
}

template<class type> int basic_tree<type>::Height()
{
    return height(this->root);
}

template<class type> void basic_tree<type>::Clear()
{
    ClearTree(root);
}


template<class type> bool basic_tree<type>::getData(type& inf)
{
    if (iterator)
    {
        inf = iterator->data;
        return true;
    }
    return false;
}

template<class type> void basic_tree<type>::ClearTree(basic_tree::node *& ptr)
{
    if (ptr)
    {

        ClearTree(ptr->lt);
        ClearTree(ptr->rt);
        delete ptr;
        ptr = nullptr;
    }
}

template<class type> int basic_tree<type>::height(node *nd)
{
    if (nd)
    {
        return (max(height(nd->lt), height(nd->rt)) + 1);
    }
    return 0;
}

template<class type> typename basic_tree<type>::node *basic_tree<type>::Parents(type key, typename basic_tree<type>::node *R)
{
    typename basic_tree<type>::node *tmp = nullptr;
    if (R->lt && R->lt->data == key) {
        return R;
    }
    if (R->lt) {
        tmp = Parents(key, R->lt);
    }
    if (tmp) {
        return tmp;
    }
    if (R->rt && R->rt->data == key) {
        return R;
    }
    if (R->rt) {
        return (Parents(key, R->rt));
    }
    return tmp;
}

template<class type> typename basic_tree<type>::node* basic_tree<type>::getRoot()
{
    return root;
}

#endif // BASIC_TREE_H
