#include "gamewidget.h"

GameWidget::GameWidget(QWidget *parent)
    : QWidget(parent)
{
    // scene = new QGraphicsScene(this);
    layout = new QHBoxLayout(this);
    gameBoard = new GameBoard(this);
    gameBoard->hide();
    scene->addWidget(pauseButton);
    // scene->addWidget(gameBoard);
    layout->addWidget(gameBoard);
    layout->addWidget(pauseButton);
    setLayout(layout);
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);
    // setStyleSheet("background-color: magenta");
    // gameBoard->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    // setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

GameWidget::~GameWidget()
{
    return;
}

void GameWidget::showBoard()
{
    gameBoard->show();
    pauseButton->show();
}

void GameWidget::hideBoard()
{
    gameBoard->hide();
}
