#ifndef HISTORYWIDGET_H
#define HISTORYWIDGET_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QMap>
#include "gamecard.h"
#include "init.hpp"


class HistoryWidget : public QWidget
{
    Q_OBJECT

    public:
        HistoryWidget(QWidget *parent = nullptr);
        ~HistoryWidget();
        void saveGame();
    private:
        QVBoxLayout *cardLayout;
        QScrollArea *scrollArea;
        QWidget *containerWidget;
        QVBoxLayout *mainLayout;
        QPushButton *backButton;
        QMap<QString, GameCard*> gameCardMap;
    signals:
        void backButtonClicked();
        void loadRequest(QString);
    public slots:
        void backToMainMenu();
        void deleteGame(QString);
        void continueGame(QString);


};

#endif // HISTORYWIDGET_H
