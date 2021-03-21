#include "mainwindow.h"
#include<QVBoxLayout>
#include <QSplitter>
#include<QGroupBox>
#include<QRadioButton>
#include<QStatusBar>
#include<QLineEdit>
#include<QLabel>
#include<QApplication>
#include <QRandomGenerator>
#include <QString>
#include <iostream>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    countBtn = new QPushButton(tr("Create"), this);
    groupBoxS = new QGroupBox(this);
    layStart = new QVBoxLayout(this);
    countEdit = new QLineEdit(this);
    countEdit->setText("0");

    //countEdit->setMaximumWidth(150);

    countLabel = new QLabel("&Count:", this);
    countLabel->setBuddy(countEdit);

    layStart->addWidget(countLabel, 1, Qt::AlignLeft);
    layStart->addWidget(countEdit);//, 0, Qt::AlignRight);
    layStart->addWidget(countBtn);
    layStart->addStretch(10);
    groupBoxS->setLayout(layStart);



    groupBoxA = new QGroupBox(tr(""));

    groupBoxB = new QGroupBox(tr("Options"));

    groupBoxC = new QGroupBox(tr("Processing"));
    groupBoxD = new QGroupBox(tr("Visualization"));

    this->setGeometry(100, 100, 1000, 600);
    this->setStatusBar(new QStatusBar(this));
    this->statusBar()->showMessage("Choosen Tree: ");
    splitter = new QSplitter(parent);

    layOptions = new QVBoxLayout(this);

    radioChaotic = new QRadioButton(tr("&Chaotic Tree"), this);
    radioSearch = new QRadioButton(tr("Search tree"), this);
    radioBalanced = new QRadioButton(tr("Balanced Tree"), this);
    radioChaotic->setChecked(true);

    layOptions->addWidget(radioChaotic, 1, Qt::AlignLeft);
    layOptions->addWidget(radioSearch, 1, Qt::AlignLeft);
    layOptions->addWidget(radioBalanced, 1, Qt::AlignLeft);
    layOptions->addStretch(1);
    groupBoxB->setLayout(layOptions);

    layProcessing = new QVBoxLayout(this);
    valueEdit = new QLineEdit(this);
    valueLabel = new QLabel("Value Of Node:", this);
    valueEdit->setText("0");
    countLabel->setBuddy(valueEdit);

    addBtn = new QPushButton(tr("Add"), this);
    delBtn = new QPushButton(tr("Remove"), this);
    fndBtn = new QPushButton(tr("Find"), this);
    clrBtn = new QPushButton(tr("Clear"), this);

    layProcessing->addWidget(valueLabel, 1, Qt::AlignLeft);
    layProcessing->addWidget(valueEdit);//, 0, Qt::AlignRight);
    layProcessing->addWidget(addBtn);
    layProcessing->addWidget(delBtn);
    layProcessing->addWidget(fndBtn);
    layProcessing->addWidget(clrBtn);
    layProcessing->addStretch(1);
    groupBoxC->setLayout(layProcessing);


    qq.setHorizontalStretch(2);
    qq.setVerticalStretch(3);
    groupBoxB->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    groupBoxC->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    layTree = new QVBoxLayout(this);


    layTree->addWidget(groupBoxS);
    layTree->addWidget(groupBoxB);
    layTree->addWidget(groupBoxC);

    groupBoxA->setLayout(layTree);

    //codec = QTextCodec::codecForName("Windows-1251");
    //this->setWindowTitle(codec->toUnicode("Event handling"));
    area = new Area(this);

    //Инициализируем карандаш
    area->myPen.setWidth(2);
    area->myPen.setColor(Qt::red);

    //btn = new QPushButton(codec->toUnicode("Close"), this);
    btn = new QPushButton(this);
    layoutPicture = new QVBoxLayout(this);
    layoutPicture->addWidget(area);
    layoutPicture->addWidget(btn);

    connect(btn, SIGNAL(clicked(bool)), this, SLOT(this->close()));

    connect(btn, &QPushButton::clicked, qApp, &QApplication::quit);
    groupBoxD->setLayout(layoutPicture);


    ///---------------------------
    groupBoxA->setMinimumWidth(80);
    groupBoxA->setMaximumWidth(150);
    splitter->addWidget(groupBoxD);
    splitter->addWidget(groupBoxA);

    setCentralWidget(splitter);
    connect(radioChaotic, &QRadioButton::toggled, this, &MainWindow::RadioChaoticClick);
    connect(radioSearch, &QRadioButton::toggled, this, &MainWindow::RadioSearchClick);
    connect(radioBalanced, &QRadioButton::toggled, this, &MainWindow::RadioBalancedClick);
    //---------------------------------------------------
    connect(addBtn, &QPushButton::clicked, this,  &MainWindow::ButtonAddOnClick);
    connect(delBtn, &QPushButton::clicked, this,  &MainWindow::ButtonDelOnClick);
    connect(fndBtn, &QPushButton::clicked, this,  &MainWindow::ButtonFindOnClick);
    connect(clrBtn, &QPushButton::clicked, this,  &MainWindow::ButtonClearOnClick);
    connect(countBtn, &QPushButton::clicked, this,  &MainWindow::ButtonCreateOnClick);


}

MainWindow::~MainWindow()
{

}

void MainWindow::RadioChaoticClick()
{
 //   if (checked)
  //  {
       area->ptrTree = reinterpret_cast<basic_tree<int>**>(&(area->chaoticTree));
       emit update();

        this->statusBar()->showMessage("Choosen Tree: Chaotic");

 //   }
  //  else
  //  {
  //      this->statusBar()->showMessage("Choosen Tree: SomeRadioButton is NOT checkekd");
  //  }

}
void MainWindow::RadioSearchClick()
{
   // if (checked)
   // {
        area->ptrTree = reinterpret_cast<basic_tree<int>**>(&(area->searchTree));
        emit update();
        this->statusBar()->showMessage("Choosen Tree: Search");

  //  }
  //  else
  //  {
  //      this->statusBar()->showMessage("Choosen Tree: SomeRadioButton is NOT checkekd");
   // }

}
void MainWindow::RadioBalancedClick()
{
 //   if (checked)
 //   {
        area->ptrTree = reinterpret_cast<basic_tree<int>**>(&(area->balancedTree));
        emit update();
        this->statusBar()->showMessage("Choosen Tree: Balanced");

  //  }
  //  else
//    {
  //      this->statusBar()->showMessage("Choosen Tree: SomeRadioButton is NOT checkekd");
 //   }

}


void MainWindow::ButtonAddOnClick()
{
    if(!(this->valueEdit->text().isEmpty()))
    {
        int value = 0;
        value = valueEdit->text().toInt();
        //QString elem = valueEdit->text();
        //qint16 value = elem.toInt();
        //std::cout << value;
        area->chaoticTree->AddNode(value);
        area->searchTree->AddNode(value);
        area->balancedTree->AddNode(value);
    }
    QPen tmpPen;
    tmpPen.setWidth(2);
    tmpPen.setColor(Qt::black);
    area->needToFind = false;
    //area->DrawTree(tmpPen);
    //Обновляем виджет что бы дерево перерисовалось.
    area->update();
}
void MainWindow::ButtonDelOnClick()
{
    if(!(this->valueEdit->text().isEmpty()))
    {
        int value = valueEdit->text().toInt();

        //emit delete_value(value);
        area->chaoticTree->DelNode(value);
        area->searchTree->DelNode(value);
        area->balancedTree->DelNode(value);
    }
    QPen tmpPen;
    tmpPen.setWidth(2);
    tmpPen.setColor(Qt::black);
    area->needToFind = false;
    //area->DrawTree(tmpPen);
    //Обновляем виджет что бы дерево перерисовалось.
    area->update();
}

void MainWindow::ButtonFindOnClick()
{
    if(!(this->valueEdit->text().isEmpty()))
    {
        area->toFind = valueEdit->text().toInt();
        area->needToFind = true;
    QPen tmpPen;
    tmpPen.setWidth(2);    
    //tmpPen.setColor(Qt::red);
    //
    //Обновляем виджет что бы дерево перерисовалось.
    //area->DrawTree(tmpPen);
    //area->drawFindNode(tmpPen);
    tmpPen.setColor(Qt::red);
    area->update();
    //area->needToFind = false;
    }
}

void MainWindow::ButtonCreateOnClick()
{
    QPen tmpPen;
    tmpPen.setWidth(2);
    tmpPen.setColor(Qt::black);
    int count = countEdit->text().toInt();
    QRandomGenerator generator;
    area->chaoticTree->Clear();
    area->searchTree->Clear();
    area->balancedTree->Clear();
    // герерируем значение, записываем в файл и добавляем в дерево
    for(int i = 0; i < count; i++)
    {
        int gen = generator.bounded(100);
        area->chaoticTree->AddNode(gen);
        area->searchTree->AddNode(gen);
        area->balancedTree->AddNode(gen);
    }

    //area->DrawTree(tmpPen);
    //Обновляем виджет что бы дерево перерисовалось.
    area->needToFind = false;
    area->update();


}

void MainWindow::ButtonClearOnClick()
{
    QPen tmpPen;
    tmpPen.setWidth(2);
    tmpPen.setColor(Qt::black);
    area->chaoticTree->Clear();
    area->searchTree->Clear();
    area->balancedTree->Clear();
    //area->DrawTree(tmpPen);
    area->needToFind = false;
    //Обновляем виджет что бы дерево перерисовалось.
    area->update();
}


//}




