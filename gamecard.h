#ifndef GAMECARD_H
#define GAMECARD_H

#include <string>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QGroupBox>
#include <QLabel>

class GameCard : public QWidget
{
    Q_OBJECT

    public:
        explicit GameCard(QString fileName, QWidget *parent = nullptr);
        ~GameCard();
    private:
        QVBoxLayout *mainLayout;
        QLabel *label;
        QHBoxLayout *buttonLayout;
        QGroupBox *buttonGroup;
        QPushButton *deleteButton;
        QPushButton *actionButton;
    signals:
        void deleteButtonClicked(QString);
        void actionButtonClicked(QString);
    public slots:
        void deleteGame();
        void continueGame();
};

#endif // GAMECARD_H
