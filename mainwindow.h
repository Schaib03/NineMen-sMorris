#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore>
#include <QtGui>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QVBoxLayout>
#include <QStackedWidget>
#include "game.h"
#include "player.h"
#include "gamewidget.h"
#include "mainmenuwidget.h"
#include "historywidget.h"
#include "settingswidget.h"
#include "pausemenu.h"
#include "confirmationdialog.h"
#include "playmenu.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:

        explicit MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

        void resizeEvent(QResizeEvent *);
        void fitGraphicsViewToWindow();

    private:
        QStackedWidget *stackedWidget;
        QGraphicsScene *scene;
        QVBoxLayout *layout;
        GameBoard *gameWidget;
        MainMenuWidget *mainMenuWidget;
        HistoryWidget *historyWidget;
        SettingsWidget *settingsWidget;
        PauseMenu *pauseMenu;
        ConfirmationDialog *restartDialog;
        ConfirmationDialog *quitDialog;
        PlayMenu *playMenu;

    public slots:
        void goToPlayMenu();
        void startGame(GameMode, int, int);
        void pauseGame();
        void quitGamePrompt();
        void goToHistory();
        void goToSettings();
        void backToMainMenu();
        void restartGamePrompt();
        void restartGame();
        void resumeGame();
        void loadGame(QString);
        void saveGame();

    signals:
        void restartConfirmed();
        void quitConfirmed();
};

#endif // MAINWINDOW_H
