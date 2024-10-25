#include "playmenu.h"

PlayMenu::PlayMenu(QWidget *parent)
    : QWidget(parent)
{
    // difficulty components
    pvpRadio = new QRadioButton("Player vs Player");
    pvaiRadio = new QRadioButton("Player vs AI");
    gameModeGroup = new QButtonGroup(this);
    gameModeBox = new QGroupBox(this);
    gameModelayout = new QHBoxLayout(this);
    gameModelayout->addWidget(pvpRadio);
    gameModelayout->addWidget(pvaiRadio);
    gameModeBox->setLayout(gameModelayout);
    gameModeGroup->addButton(pvpRadio, 1);
    gameModeGroup->addButton(pvaiRadio, 2);
    pvpRadio->setChecked(true);

    // starting player components
    playerFirstRadio = new QRadioButton("Player first");
    aiFirstRadio = new QRadioButton("AI first");
    randomRadio = new QRadioButton("Randomized");
    firstPlayerGroup = new QButtonGroup(this);
    firstPlayerBox = new QGroupBox(this);
    firstPlayerlayout = new QHBoxLayout(this);
    firstPlayerlayout->addWidget(playerFirstRadio);
    firstPlayerlayout->addWidget(aiFirstRadio);
    firstPlayerlayout->addWidget(randomRadio);
    firstPlayerBox->setLayout(firstPlayerlayout);
    firstPlayerGroup->addButton(playerFirstRadio, 1);
    firstPlayerGroup->addButton(aiFirstRadio, 2);
    firstPlayerGroup->addButton(randomRadio, 3);
    playerFirstRadio->setChecked(true);

    difficultySlider = new QSlider(Qt::Horizontal);
    difficultySlider->setRange(1, 3);
    backButton = new QPushButton("back");
    startButton = new QPushButton("Start");
    mainlayout = new QVBoxLayout(this);
    mainlayout->addWidget(gameModeBox);
    mainlayout->addWidget(firstPlayerBox);
    mainlayout->addWidget(difficultySlider);
    mainlayout->addWidget(startButton);
    mainlayout->addWidget(backButton);
    setLayout(mainlayout);
    connect(backButton, SIGNAL (clicked()), this, SLOT (backToMainMenu()));
    connect(startButton, SIGNAL (clicked()), this, SLOT (startGame()));
}

PlayMenu::~PlayMenu()
{
    qDebug() << "playmenu destroyed";
}

void PlayMenu::backToMainMenu()
{
    emit backButtonClicked();
}

void PlayMenu::startGame()
{
    QAbstractButton *gmButton = gameModeGroup->checkedButton();
    QAbstractButton *pfButton = firstPlayerGroup->checkedButton();
    GameMode m = (gameModeGroup->id(gmButton) == 1) ? PvP : PvAI;
    qDebug() << "diff is" << difficultySlider->value();
    emit startButtonClicked(m, difficultySlider->value(), firstPlayerGroup->id(pfButton));
}




