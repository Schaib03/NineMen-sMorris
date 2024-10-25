#include "gamecard.h"

GameCard::GameCard(QString fileName, QWidget *parent)
    : QWidget(parent)
{
    mainLayout = new QVBoxLayout(this);
    label = new QLabel(this);
    label->setText(fileName);
    buttonLayout = new QHBoxLayout(this);
    buttonGroup = new QGroupBox(this);
    deleteButton = new QPushButton("delete");
    actionButton = new QPushButton("continue");
    buttonLayout->addWidget(deleteButton);
    buttonLayout->addWidget(actionButton);
    buttonGroup->setLayout(buttonLayout);
    mainLayout->addWidget(label);
    mainLayout->addWidget(buttonGroup);
    setLayout(mainLayout);
    setFixedSize(500, 200);
    connect(deleteButton, SIGNAL (clicked()), this, SLOT (deleteGame()));
    connect(actionButton, SIGNAL (clicked()), this, SLOT (continueGame()));
}

void GameCard::deleteGame()
{
    emit deleteButtonClicked(label->text());
}

void GameCard::continueGame()
{
    emit actionButtonClicked(label->text());
}

GameCard::~GameCard()
{
    qDebug() << "gamecard destroyed";
}
