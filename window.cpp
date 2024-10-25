#include "window.h"

#include <QApplication>

Window::Window(QWidget *parent): QMainWindow(parent)
{
    // Set size of the window
    setFixedSize(800, 450);

    scene = new QGraphicsScene(this);
    QBrush redBrush(Qt::red);
    QBrush blueBrush(Qt::blue);
    QPen blackPen(Qt::black);
    blackPen.setWidth(3);

    cell = scene->addEllipse(10, 10, 20, 20, blackPen, redBrush);

}
