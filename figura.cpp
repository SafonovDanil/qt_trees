#include "figura.h"
#include<math.h>
#include <QTranslator>
#include<QString>

void Figura::move(float Alpha, QPainter *Painter)
{
    dx = halflen * cos(Alpha);
    dy = halflen * sin(Alpha);
    draw(Painter);
}
void MyLine::draw(QPainter *Painter)
{
    Painter->drawLine(x + dx, y + dy, x - dx, y - dy);
}
void MyRect::draw(QPainter *Painter)
{
    Painter->drawLine(x + dx, y + dy, x + dy, y - dx);
    Painter->drawLine(x + dy, y - dx, x - dx, y - dy);
    Painter->drawLine(x - dx, y - dy, x - dy, y + dx);
    Painter->drawLine(x - dy, y + dx, x + dx, y + dy);

    //Тут просто примеры работы с некоторыми графическими примитивами

    /*https://doc.qt.io/qt-5/qpainter.html*/

    QFont font = Painter->font();
    font.setPixelSize(48);
    Painter->setFont(font);

    QRectF rectangle(15.0, 45.0, 80.0, 60.0);
    Painter->drawRoundedRect(rectangle, 20.0, 15.0);

    rectangle = QRect(50, 50, 100, 50);
    QRect boundingRect;
    Painter->drawText(rectangle, 0, "Hello", nullptr);


    QPen pen = Painter->pen();
    pen.setStyle(Qt::DotLine);
    Painter->setPen(pen);
    Painter->drawRect(boundingRect.adjusted(0, 0, -pen.width(), -pen.width()));

    pen.setStyle(Qt::DashLine);
    Painter->setPen(pen);
    Painter->drawRect(rectangle.adjusted(0, 0, -pen.width(), -pen.width()));
}
