#include "mainmenuwidget.h"

MainMenuWidget::MainMenuWidget(QWidget *parent)
    : QWidget(parent)
{
    startButton = new QPushButton("Play");
    quitButton = new QPushButton("Quit");
    historyButton = new QPushButton("History");
    settingsButton = new QPushButton("Settings");
    buttonGroup = new QVBoxLayout(this);
    buttonGroup->addWidget(startButton);
    buttonGroup->addWidget(settingsButton);
    buttonGroup->addWidget(historyButton);
    buttonGroup->addWidget(quitButton);
    setLayout(buttonGroup);
    qDebug() << "main menu created\n";
    connect(startButton, SIGNAL (clicked()), this, SLOT (startGame()));
    connect(historyButton, SIGNAL (clicked()), this, SLOT (goToHistory()));
    connect(settingsButton, SIGNAL (clicked()), this, SLOT (goToSettings()));
    connect(quitButton, SIGNAL (clicked()), this, SLOT (quitGame()));
}

MainMenuWidget::~MainMenuWidget()
{
    delete startButton;
    delete quitButton;
    delete historyButton;
    delete settingsButton;
    delete buttonGroup;
}

void MainMenuWidget::startGame()
{
    emit startButtonClicked();
}

void MainMenuWidget::quitGame()
{
    emit quitButtonClicked();
}

void MainMenuWidget::goToHistory()
{
    emit historyButtonClicked();
}

void MainMenuWidget::goToSettings()
{
    emit settingsButtonClicked();
}
