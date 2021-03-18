#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QTextCodec>
#include <QRadioButton>
#include <QLabel>
#include <QFrame>
#include <QLineEdit>
#include <QCheckBox>
#include <QRect>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QSplitter>
#include "area.h"


class MainWindow : public QMainWindow //за основу взял проект ForPaintBasic, который вы предоставили как пример
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

  void clear_tree();

protected:
    //QTextCodec *codec;
    Area *area;  // область отображения рисунка



private slots:
    void RadioChaoticClick(); //данные слоты будут переключать указатель на нужный тип дерева
    void RadioSearchClick();    //который будет отрисовываться
    void RadioBalancedClick();

    void ButtonAddOnClick(); //следущие слоты будут вызывать функции всех 3 типов деревьев
    void ButtonDelOnClick();
    void ButtonFindOnClick();
    void ButtonCreateOnClick();
    void ButtonClearOnClick();

private:

    QPushButton *btn;
    QPushButton *countBtn;
    QGroupBox *groupBoxS;
    QVBoxLayout *layStart;
    QLineEdit *countEdit;
    QLabel *countLabel;
    QGroupBox *groupBoxA;
    QGroupBox *groupBoxB;
    QGroupBox *groupBoxC;
    QGroupBox *groupBoxD ;
    QSplitter *splitter;
    QVBoxLayout *layOptions;
    QRadioButton *radioChaotic;
    QRadioButton *radioSearch;
    QRadioButton *radioBalanced;
    QVBoxLayout *layProcessing;
    QLineEdit *valueEdit;
    QLabel *valueLabel;
    QPushButton *addBtn;
    QPushButton *delBtn;
    QPushButton *fndBtn;
    QPushButton *clrBtn;
    QSizePolicy qq;
    QVBoxLayout *layTree;
    QVBoxLayout *layoutPicture;

};
#endif // MAINWINDOW_H
