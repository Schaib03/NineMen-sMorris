#include "pausemenu.h"

PauseMenu::PauseMenu(QWidget *parent)
    : QDialog(parent)
{

    backButton = new QPushButton("back");
    resumeButton = new QPushButton("resume");
    restartButton = new QPushButton("restart");
    saveButton = new QPushButton("save");
    loadButton = new QPushButton("load");

    layout = new QVBoxLayout(this);
    layout->addWidget(backButton);
    layout->addWidget(resumeButton);
    layout->addWidget(restartButton);
    layout->addWidget(saveButton);
    layout->addWidget(loadButton);
    connect(backButton, SIGNAL (clicked()), this, SLOT (backToMainMenu()));
    connect(resumeButton, SIGNAL (clicked()), this, SLOT (resumeGame()));
    connect(restartButton, SIGNAL (clicked()), this, SLOT (restartGame()));
    connect(saveButton, SIGNAL (clicked()), this, SLOT (saveGame()));
    connect(loadButton, SIGNAL (clicked()), this, SLOT (loadGame()));
}

void PauseMenu::restartGame()
{
    emit restartButtonClicked();
}

void PauseMenu::resumeGame()
{
    emit resumeButtonClicked();
}

void PauseMenu::saveGame()
{
    emit saveButtonClicked();
}

void PauseMenu::loadGame()
{
    emit loadButtonClicked();
}

void PauseMenu::backToMainMenu()
{
    emit backButtonClicked();
}

PauseMenu::~PauseMenu()
{
    qDebug("pause menu destroyed\n");
}
