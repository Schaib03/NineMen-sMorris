#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QGraphicsScene>
#include <QHBoxLayout>
#include "gameboard.h"

class GameWidget : public QWidget
{
    Q_OBJECT

    public:
        GameWidget(QWidget *parent = nullptr);
        ~GameWidget();
        void showBoard();
        void hideBoard();
    private:
        QPushButton *pauseButton;
        GameBoard *gameBoard;
        QGraphicsScene *scene;
        QHBoxLayout *layout;
};

#endif // GAMEWIDGET_H
