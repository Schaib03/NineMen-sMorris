#ifndef MAINMENUWIDGET_H
#define MAINMENUWIDGET_H

#include <QObject>
#include <QtCore>
#include <QWidget>
#include <QPushButton>
#include <QMouseEvent>
#include <QVBoxLayout>

class MainMenuWidget : public QWidget
{
    Q_OBJECT

    public:
        explicit MainMenuWidget(QWidget *parent = nullptr);
        ~MainMenuWidget();
    private:
        QVBoxLayout *buttonGroup;
        QPushButton *startButton;
        QPushButton *quitButton;
        QPushButton *historyButton;
        QPushButton *settingsButton;
    signals:
        void startButtonClicked();
        void quitButtonClicked();
        void historyButtonClicked();
        void settingsButtonClicked();
    public slots:
        void startGame();
        void quitGame();
        void goToSettings();
        void goToHistory();

};

#endif // MAINMENUWIDGET_H
