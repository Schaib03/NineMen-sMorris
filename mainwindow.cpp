#include "mainwindow.h"
#include <iostream>
#include <QApplication>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // scene = new QGraphicsScene(this);
    historyWidget = new HistoryWidget(this);
    gameWidget = new GameBoard(this);
    mainMenuWidget = new MainMenuWidget(this);
    settingsWidget = new SettingsWidget(this);
    pauseMenu = new PauseMenu(this);
    playMenu = new PlayMenu(this);
    restartDialog = new ConfirmationDialog(this, RESTART_MESSAGE);
    quitDialog = new ConfirmationDialog(this, QUIT_MESSAGE);
    stackedWidget = new QStackedWidget(this);
    stackedWidget->addWidget(historyWidget);
    stackedWidget->addWidget(mainMenuWidget);
    stackedWidget->addWidget(settingsWidget);
    stackedWidget->addWidget(gameWidget);
    stackedWidget->addWidget(pauseMenu);
    stackedWidget->addWidget(restartDialog);
    stackedWidget->addWidget(quitDialog);
    stackedWidget->addWidget(playMenu);
    stackedWidget->setCurrentWidget(mainMenuWidget);
    setCentralWidget(stackedWidget);
    stackedWidget->layout()->setContentsMargins(0,0,0,0);
    qDebug() << "MainWindow created\n";

    // connect button to corresponding actions
    connect(mainMenuWidget, SIGNAL (startButtonClicked()), this, SLOT (goToPlayMenu()));
    connect(mainMenuWidget, SIGNAL (historyButtonClicked()), this, SLOT (goToHistory()));
    connect(mainMenuWidget, SIGNAL (quitButtonClicked()), this, SLOT (quitGamePrompt()));
    connect(mainMenuWidget, SIGNAL (settingsButtonClicked()), this, SLOT (goToSettings()));


    connect(settingsWidget, SIGNAL (backButtonClicked()), this, SLOT (backToMainMenu()));

    connect(historyWidget, SIGNAL (backButtonClicked()), this, SLOT (backToMainMenu()));
    connect(historyWidget, SIGNAL (loadRequest(QString)), this, SLOT (loadGame(QString)));


    connect(gameWidget, SIGNAL (pauseButtonClicked()), this, SLOT (pauseGame()));

    connect(playMenu, SIGNAL (startButtonClicked(GameMode,int,int)), this, SLOT (startGame(GameMode,int,int)));
    connect(playMenu, SIGNAL (backButtonClicked()), this, SLOT (backToMainMenu()));

    connect(pauseMenu, SIGNAL (backButtonClicked()), this, SLOT (backToMainMenu()));
    connect(pauseMenu, SIGNAL (resumeButtonClicked()), this, SLOT (resumeGame()));
    connect(pauseMenu, SIGNAL (saveButtonClicked()), this, SLOT (saveGame()));
    // connect(pauseMenu, SIGNAL (loadButtonClicked()), this, SLOT (loadGame()));
    connect(pauseMenu, SIGNAL (restartButtonClicked()), this, SLOT (restartGamePrompt()));

    connect(restartDialog, SIGNAL (confirmButtonClicked()), this, SLOT (restartGame()));
    connect(quitDialog, SIGNAL (confirmButtonClicked()), QApplication::instance(), SLOT (quit()));

    connect(restartDialog, SIGNAL (cancelButtonClicked()), this, SLOT (pauseGame()));
    connect(quitDialog, SIGNAL (cancelButtonClicked()), this, SLOT (backToMainMenu()));
}


MainWindow::~MainWindow()
{
    // delete ui;
}


void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    fitGraphicsViewToWindow();
}

void MainWindow::restartGamePrompt()
{
    stackedWidget->setCurrentWidget(restartDialog);
}

void MainWindow::quitGamePrompt()
{
    stackedWidget->setCurrentWidget(quitDialog);
}

void MainWindow::restartGame()
{
    gameWidget->reinitialize();
    stackedWidget->setCurrentWidget(gameWidget);
}

void MainWindow::fitGraphicsViewToWindow()
{
    // Get the size of the main window
    QSize size = this->size();

    // Adjust the geometry of the graphicsView to fill the entire window
    // gameWidget->setGeometry(0, 0, size.width(), size.height());
    // mainMenuWidget->setGeometry(0, 0, size.width(), size.height());
    // historyWidget->setGeometry(0, 0, size.width(), size.height());
    // settingsWidget->setGeometry(0, 0, size.width(), size.height());
}

void MainWindow::goToPlayMenu()
{
    stackedWidget->setCurrentWidget(playMenu);
}

void MainWindow::startGame(GameMode m, int d, int f)
{
    gameWidget->setGameSettings(m, d, f);
    stackedWidget->setCurrentWidget(gameWidget);
}

void MainWindow::loadGame(QString s)
{
    gameWidget->loadGame(s);
    stackedWidget->setCurrentWidget(gameWidget);
    qDebug() << "game should load now";
}

void MainWindow::saveGame()
{
    gameWidget->saveGame();
    historyWidget->saveGame();
    stackedWidget->setCurrentWidget(historyWidget);
}

void MainWindow::resumeGame()
{
    stackedWidget->setCurrentWidget(gameWidget);
}

void MainWindow::pauseGame()
{
    stackedWidget->setCurrentWidget(pauseMenu);
}

void MainWindow::goToHistory()
{
    stackedWidget->setCurrentWidget(historyWidget);
}

void MainWindow::goToSettings()
{
    stackedWidget->setCurrentWidget(settingsWidget);
}

void MainWindow::backToMainMenu()
{
    gameWidget->reinitialize();
    stackedWidget->setCurrentWidget(mainMenuWidget);
}
