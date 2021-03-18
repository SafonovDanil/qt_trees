#ifndef AREA_H
#define AREA_H


#include <QWidget>
#include <QPainter>
#include <QMainWindow>
#include "figura.h"
#include "chaotic_tree.h"
#include "basic_tree.h"
#include "search_tree.h"
#include "balanced_search_tree.h"

class MainWindow;

class Area : public QWidget
{
    friend MainWindow;      //друг, чтобы главное окно видело деревья
    basic_tree<int> **ptrTree;                 //все три типа дерева всегда находятся в памяти
    chaotic_tree<int> *chaoticTree;            //методы класса будут вызываться у каждого объекта
    search_tree<int> *searchTree;              //отрисовываться будет дерево, на которое указывает ptrTree
    balanced_search_tree<int> *balancedTree;
public:
    QPen myPen;

    Area(QWidget *parent = nullptr);
    ~Area();
    void setTree(basic_tree<int> *);
    void DrawTree(QPen &tmpPen);

protected:
    void drawTreeRecursively(QPainter *, basic_tree<int>::node *, int, int, int);
    // обработчики событий
    void paintEvent(QPaintEvent *event);

};

#endif // AREA_H
