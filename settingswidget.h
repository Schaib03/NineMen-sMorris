#ifndef SETTINGSWIDGET_H
#define SETTINGSWIDGET_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QButtonGroup>
#include <QSlider>
#include <QHBoxLayout>

class SettingsWidget : public QWidget
{
    Q_OBJECT

    public:
        SettingsWidget(QWidget *parent = nullptr);
        ~SettingsWidget();
    private:
        QVBoxLayout *layout;
        QPushButton *backButton;
        QSlider *soundSlider;
        QPushButton *languageButton;
    signals:
        void backButtonClicked();
    public slots:
        void backToMainMenu();
        void updateSound(int);
};

#endif // SETTINGSWIDGET_H
