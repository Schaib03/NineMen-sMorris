#include "historywidget.h"
#include <QDirIterator>
#include <QLabel>
#include <QFile>

HistoryWidget::HistoryWidget(QWidget *parent)
    : QWidget(parent)
{
    containerWidget = new QWidget(this);
    cardLayout = new QVBoxLayout(containerWidget);
    mainLayout = new QVBoxLayout(this);
    scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    qDebug() << "History Widget created\n";
    QString currentPath = QDir::currentPath();
    qDebug() << "Current Working Directory: " << currentPath;
    QDir dir("../../savegames");
    QStringList files = dir.entryList(QDir::Files);
    for (const auto& file : files)
    {
        qDebug() << file;
        GameCard *gc = new GameCard(file);
        gameCardMap.insert(file, gc);
        cardLayout->addWidget(gameCardMap.value(file));
        connect(gc, SIGNAL (deleteButtonClicked(QString)), this, SLOT (deleteGame(QString)));
        connect(gc, SIGNAL (actionButtonClicked(QString)), this, SLOT (continueGame(QString)));
    };
    scrollArea->setWidget(containerWidget);
    mainLayout->addWidget(scrollArea);
    backButton = new QPushButton("back");
    mainLayout->addWidget(backButton);
    setLayout(mainLayout);
    connect(backButton, SIGNAL (clicked()), this, SLOT (backToMainMenu()));
}


void HistoryWidget::backToMainMenu()
{
    emit backButtonClicked();
}


void HistoryWidget::continueGame(QString s)
{
    emit loadRequest(s);
    qDebug() << "load request emitted";
}

void HistoryWidget::deleteGame(QString f)
{
    cardLayout->removeWidget(gameCardMap.value(f));
    delete gameCardMap.value(f);
    gameCardMap.remove(f);
    f.prepend("../../savegames/");
    if (QFile::remove(f))
    {
        qDebug() << "El file removed";
    }
    else
    {
        qDebug() << "Error removing file";
    };
}

void HistoryWidget::saveGame()
{
    QString fileName = "../../savegames/savegame_";
    fileName.append(std::to_string(mainConfig.getSaveCount()));
    fileName.append(".txt");
    GameCard *gc = new GameCard(fileName.mid(16));
    gameCardMap.insert(fileName.mid(16), gc);
    cardLayout->addWidget(gc);
    connect(gc, SIGNAL (deleteButtonClicked(QString)), this, SLOT (deleteGame(QString)));
    connect(gc, SIGNAL (actionButtonClicked(QString)), this, SLOT (continueGame(QString)));
}

HistoryWidget::~HistoryWidget()
{
    qDebug() << "Object deleted\n";
}
