#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include <QDialog>
#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

class PauseMenu : public QDialog
{
    Q_OBJECT
    public:
        PauseMenu(QWidget *parent = nullptr);
        ~PauseMenu();
    private:
        QVBoxLayout *layout;
        QPushButton *backButton;
        QPushButton *restartButton;
        QPushButton *resumeButton;
        QPushButton *saveButton;
        QPushButton *loadButton;
    signals:
        void backButtonClicked();
        void restartButtonClicked();
        void resumeButtonClicked();
        void saveButtonClicked();
        void loadButtonClicked();
    public slots:
        void restartGame();
        void backToMainMenu();
        void resumeGame();
        void saveGame();
        void loadGame();
};

#endif // PAUSEMENU_H
