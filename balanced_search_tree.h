#ifndef BALANCED_SEARCH_TREE_H
#define BALANCED_SEARCH_TREE_H

#include "search_tree.h"
#include <algorithm>
#include <stack>


template<class type> class balanced_search_tree :public search_tree<type>
{
protected:
    class balanced_node : public search_tree<type>::node //наследуем узел, тк в него нужно добавить баланс
    {
    public:
        balanced_node(type&);

        balanced_node(balanced_node&);

        balanced_node& operator = (balanced_node&);

        int balance;
    };

    bool AddTo(type&, balanced_node*&);
    balanced_node* L_turn(balanced_node*); //однократный поворот налево
    balanced_node* R_turn(balanced_node*); //направо
    balanced_node* LR_turn(balanced_node*);//двукратный LR
    balanced_node* RL_turn(balanced_node*);//RL
public:

    balanced_search_tree();
    balanced_search_tree(balanced_search_tree<type>&);
    balanced_search_tree(type* arr, int n);
    balanced_search_tree(type&);

    balanced_search_tree<type>& operator = (balanced_search_tree<type>&);

    bool AddNode(type&);
    bool DelNode(type&);


};


template<class type> balanced_search_tree<type>::balanced_node::balanced_node(type& inf):search_tree<type>::node(inf, 0)
{
    balance = 0;
}

template<class type> balanced_search_tree<type>::balanced_node::balanced_node(balanced_node& obj):basic_tree<type>::node(obj)
{
    balance = obj.balance;
}

template<class type> typename balanced_search_tree<type>::balanced_node& balanced_search_tree<type>::balanced_node::operator = (balanced_node& obj)
{
    balance = obj.balance;
    balanced_node::data = obj.data;
    if (obj.lt)
    {
        if (balanced_node::lt)
            *balanced_node::lt = *(obj.lt);
        else
            balanced_node::lt = new balanced_node(*static_cast<balanced_node*>(obj.lt)); //cast - преобразование типов в новых стандартах. Static - статический тип в статический.
    }
    else
        if (balanced_node::lt)
        {
            delete balanced_node::lt;
            balanced_node::lt = nullptr;
        }

    if (obj.rt)
    {
        if (balanced_node::rt)
            *balanced_node::rt = *(obj.rt);
        else
            balanced_node::rt = new balanced_node(*static_cast<balanced_node*>(obj.rt));
    }
    else
        if (balanced_node::rt)
        {
            delete balanced_node::rt;
            balanced_node::rt = nullptr;
        }

    return *this;
}

// balanced_search_tree

template<class type> balanced_search_tree<type>::balanced_search_tree()
{
    balanced_search_tree::root = nullptr;
}

template<class type> balanced_search_tree<type>::balanced_search_tree(type& inf)
{
    balanced_search_tree::root = new balanced_node(inf);
}

template<class type> balanced_search_tree<type>::balanced_search_tree(balanced_search_tree<type>& obj)
{
    balanced_search_tree::root = new balanced_node(obj.root);
}

template<class type> balanced_search_tree<type>::balanced_search_tree(type* arr, int n)
{
    if(arr)
        for (int i = 0; i < n; i++)
            AddNode(arr[i]);
    else
        balanced_search_tree::root = nullptr;
}

template<class type> balanced_search_tree<type>& balanced_search_tree<type>::operator = (balanced_search_tree<type>& obj)
{
    if (obj.root)
    {
        if (balanced_search_tree::root)
            *static_cast<balanced_node*> (balanced_search_tree::root) = *((balanced_node*)obj.root);
        else
            balanced_search_tree::root = new balanced_node(*((balanced_node*)obj.root));
    }
    else
        if (balanced_search_tree::root)
        {
            delete balanced_search_tree::root;
            balanced_search_tree::root = nullptr;
        }
    return *this;
}

template<class type> bool balanced_search_tree<type>::AddNode(type& inf)
{
    AddTo(inf, (balanced_node*&)balanced_search_tree::root);

    return false;
}

template<class type> bool balanced_search_tree<type>::AddTo(type& inf, balanced_node*& root)
{
    if (root)
    {
        if (root->data > inf)
        {
            if (AddTo(inf, reinterpret_cast<balanced_node*&>(root->lt))) // reinterpret cast - использовал для приведения указателей
                root->balance--;
            else
                return false;
        }
        else
            if (AddTo(inf, reinterpret_cast<balanced_node*&>(root->rt)))
                root->balance++;
            else
                return false;

        if((root->balance) ==  0)
            return false;
        else
            if((root->balance) == 2)
        {
            if (((balanced_node*)(root->rt))->balance == 1)
                root = L_turn(root);
            else
                root = RL_turn(root);
            return false;
        }
            else
                if((root->balance) == -2)
        {
            if (static_cast<balanced_node*>(root->lt)->balance == -1)
                root = R_turn(root);
            else
                root = LR_turn(root);

            return false;
        }

    }
    else
        root = new balanced_node(inf);
    return true;
}

template<class type> bool balanced_search_tree<type>::DelNode(type& inf)
{
    std::stack<balanced_node**> need_to_balance; //стек с вершинами, в который изменится баланс
    need_to_balance.push(nullptr);
    balanced_node *delete_node = nullptr; //удаляемый узел
    balanced_node **parent_node = nullptr;//родитель удаляемой, двойной указатель для использования в поворотах
    balanced_node *replace_node = nullptr;//замещающий узел
    balanced_node **ptr = nullptr;//указатель для пересчета баланса
    balanced_node *ptr_child = nullptr;//для проверки баланса в потомках
    balanced_node *rep_parent_node = nullptr;//родитель замещающей

    parent_node = reinterpret_cast<balanced_node**>(&(search_tree<type>::root));
    delete_node = static_cast<balanced_node*>(balanced_search_tree<type>::root);

    while (delete_node && delete_node->data != inf) //поиск удаляемой вершины, добавление пути в стек
    {
        need_to_balance.push(parent_node);
        if (delete_node->data > inf)
        {
            parent_node = reinterpret_cast<balanced_node **>(&(delete_node->lt));
            delete_node = static_cast<balanced_node *>(delete_node->lt);
        }
        else
        {
            parent_node = reinterpret_cast<balanced_node **>(&(delete_node->rt));
            delete_node = static_cast<balanced_node *>(delete_node->rt);
        }
    }
    if (delete_node) //ищем замещающей вершины и ее родителя
    {
        if (!delete_node->lt)
        {
            replace_node = static_cast<balanced_node *>(delete_node->rt);
            ptr_child = delete_node;
        }
        else
            if (!delete_node->rt)
            {
                replace_node = static_cast<balanced_node *>(delete_node->lt);
                ptr_child = delete_node;
            }
            else
            {
                rep_parent_node = delete_node;
                replace_node = static_cast<balanced_node *>(delete_node->lt);
                need_to_balance.push(&delete_node);
                while (replace_node->rt)
                {
                    rep_parent_node = replace_node;
                    replace_node = static_cast<balanced_node *>(replace_node->rt);

                    need_to_balance.push(&rep_parent_node);
                }

                replace_node->rt = delete_node->rt;

                ptr_child = replace_node;
            }


//блок с пересчетом баланса
        bool balanced = false;
        ptr = need_to_balance.top();
        need_to_balance.pop();
        while (!need_to_balance.empty() && !balanced)//до тех пока дерево не станет сбалансированным, либо если баланс не "испортился"
        {
            if ((*ptr)->lt == ptr_child)
                (*ptr)->balance++;
            else
                (*ptr)->balance--;

            if(((*ptr)->balance) ==0) //повороты не нужны, просто считаем баланс
            {
                ptr_child = *ptr;
                ptr = need_to_balance.top();
                need_to_balance.pop();
            }
            else
                if ((*ptr)->balance ==2) //баланс > |1|, нужна корректировка поворотами
            {
                if (static_cast<balanced_node *>((*ptr)->rt)->balance == 0) //проверяем правого потомка
                {
                    *ptr = L_turn(*ptr); //если баланс 0, левый поворот
                    balanced = true;
                }
                else
                {
                    if (static_cast<balanced_node *>((*ptr)->rt)->balance == 1)
                    {
                        *ptr = L_turn(*ptr); //если 1, левый поворот и пересчет баланса
                        ptr_child = *ptr;
                        ptr = need_to_balance.top();
                        need_to_balance.pop();
                    }
                    else //если знак баланса родителя и потомка отличаются, нужен двукратный поворот
                    {
                        *ptr = RL_turn(*ptr);
                        ptr_child = *ptr;
                        ptr = need_to_balance.top();
                        need_to_balance.pop();
                    }
                }
                }
            else if(((*ptr)->balance)==-2) //аналогично с другим знаком
            {
                if ((static_cast<balanced_node *>((*ptr)->lt))->balance == 0)
                {
                    *ptr = R_turn(*ptr);
                    balanced = true;
                }
                else
                    if ((static_cast<balanced_node *>((*ptr)->lt))->balance == -1)
                    {
                        *ptr = R_turn(*ptr);
                        ptr_child = *ptr;
                        ptr = need_to_balance.top();
                        need_to_balance.pop();
                    }
                    else
                    {
                        *ptr = LR_turn(*ptr);
                        ptr_child = *ptr;
                        ptr = need_to_balance.top();
                        need_to_balance.pop();
                    }

            }
           else
                balanced = true;

            }

//балансировка проведена, настраиваем связи
        if (rep_parent_node && rep_parent_node != delete_node)
        {
            rep_parent_node->rt = replace_node->lt;
            replace_node->lt = delete_node->lt;
        }

        *parent_node = replace_node;
        delete_node->lt = delete_node->rt = nullptr;
        delete delete_node;
        return true;
    }

    return false;
}

template<class type> typename balanced_search_tree<type>::balanced_node* balanced_search_tree<type>::L_turn(balanced_node* ptr)
{
    //левый поворот относительно ptr
    balanced_node *rep = static_cast<balanced_node *>(ptr->rt);//замещающая вершина
    ptr->rt = static_cast<balanced_node *>(rep->lt);
    rep->lt = ptr;
    if (ptr->rt && !ptr->lt)//пересчет баланса
    {
        ptr->balance = 1;
        rep->balance = -1;
    }
    else
    {
        ptr->balance = 0;
        rep->balance = 0;
    }
    return rep;
}

template<class type> typename balanced_search_tree<type>::balanced_node* balanced_search_tree<type>::R_turn(balanced_node* ptr)
{ //аналогично правый поворот
    balanced_node *rep = static_cast<balanced_node *>(ptr->lt);
    ptr->lt = static_cast<balanced_node *>(rep->rt);
    rep->rt = ptr;

    if (ptr->lt && !ptr->rt)
    {
        ptr->balance = -1;
        rep->balance = 1;
    }
    else
    {
        ptr->balance = 0;
        rep->balance = 0;
    }
    return rep;
}

template<class type> typename balanced_search_tree<type>::balanced_node* balanced_search_tree<type>::LR_turn(balanced_node* ptr)
{
    balanced_node *s, *p; //обозначение вершин с лекций
    s = static_cast<balanced_node *>(ptr->lt);
    p = static_cast<balanced_node *>(s->rt);

    s->rt = static_cast<balanced_node *>(p->lt);
    p->lt = s;

    ptr->lt = p->rt;
    p->rt = ptr;

    ptr->balance = s->balance = 0;
    if (p->balance == -1)
        ptr->balance = 1;
    if (p->balance == 1)
        s->balance = -1;

    p->balance = 0;

    return p;
}

template<class type> typename balanced_search_tree<type>::balanced_node* balanced_search_tree<type>::RL_turn(balanced_node* ptr)
{
    balanced_node *s, *p;
    s = static_cast<balanced_node *>(ptr->rt);
    p = static_cast<balanced_node *>(s->lt);

    s->lt = p->rt;
    p->rt = s;

    ptr->rt = p->lt;
    p->lt = ptr;

    ptr->balance = s->balance = 0;
    if (p->balance == -1)
        s->balance = 1;
    if (p->balance == 1)
        ptr->balance = -1;

    p->balance = 0;

    return p;
}


#endif // BALANCED_SEARCH_TREE_H
