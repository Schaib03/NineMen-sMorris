#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>


class Window : public QMainWindow
{
    Q_OBJECT
    public:
        explicit Window(QWidget *parent = nullptr);
    private:
        QGraphicsView *view;
        QGraphicsScene *scene;
        QGraphicsEllipseItem *cell;
        QGraphicsRectItem *board;


};

#endif // WINDOW_H
