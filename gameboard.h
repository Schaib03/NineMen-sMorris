#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QObject>
#include <QtCore>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QPushButton>
#include <QTimer>
#include "game.h"
#include "player.h"

class GameBoard : public QGraphicsView
{
    Q_OBJECT

    public:
        explicit GameBoard(QWidget *parent = nullptr);
        // void startGame();
        // void stopGame();
        void createGameObjects();
        void mousePressEvent(QMouseEvent *) override;
        void gameOver();
        void applyAIMove();
        void reinitialize();
        void setGameSettings(GameMode, int, int);
        void loadGame(QString);
        void saveGame();
        ~GameBoard();
    private:
        QGraphicsScene *scene;
        QPushButton *pauseButton;
        QGraphicsEllipseItem *cells[3][8];
        QGraphicsEllipseItem *slot[3][8];
        QGraphicsRectItem *board;
        QGraphicsRectItem *outlines[3];
        QGraphicsLineItem *lines[4];
        unsigned int slotRadius;
        unsigned int cellRadius;
        QBrush darkWoodBrush;
        QBrush noBrush;
        QPen blackPen;
        QPen noPen;
        Cell playerColor;
        Game g;
        HumanPlayer me;
        AIPlayer ai;
        Move m;
        GameMode gameMode; // PvP or PvAI
        int difficulty;
        bool awaitRemove;
        bool awaitSlide;
    signals:
        void pauseButtonClicked();
    public slots:
        void pauseGame();
};

#endif // GAMEBOARD_H
