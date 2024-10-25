#ifndef PLAYMENU_H
#define PLAYMENU_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QButtonGroup>
#include <QSlider>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QRadioButton>
#include <QButtonGroup>
#include "init.hpp"

class PlayMenu: public QWidget
{
    Q_OBJECT

    public:
        PlayMenu(QWidget *parent = nullptr);
        ~PlayMenu();

    private:
        QVBoxLayout *mainlayout;
        QSlider *difficultySlider;
        QPushButton *startButton;
        QPushButton *backButton;

        // difficulty components
        QGroupBox *gameModeBox;
        QRadioButton *pvpRadio;
        QRadioButton *pvaiRadio;
        QButtonGroup *gameModeGroup;
        QHBoxLayout *gameModelayout;

        // first player components
        QGroupBox *firstPlayerBox;
        QRadioButton *playerFirstRadio;
        QRadioButton *aiFirstRadio;
        QRadioButton *randomRadio;
        QButtonGroup *firstPlayerGroup;
        QHBoxLayout *firstPlayerlayout;

    signals:
        void backButtonClicked();
        void startButtonClicked(GameMode, int, int);
    public slots:
        void backToMainMenu();
        void startGame();
};

#endif // PLAYMENU_H
