#include "settingswidget.h"
#include "init.hpp"
SettingsWidget::SettingsWidget(QWidget *parent)
    : QWidget(parent)
{

    languageButton = new QPushButton("English");
    soundSlider = new QSlider(Qt::Horizontal);
    soundSlider->setRange(0,100);
    soundSlider->setValue(mainConfig.getSound());
    layout = new QVBoxLayout(this);
    layout->addWidget(languageButton);
    layout->addWidget(soundSlider);
    backButton = new QPushButton("back");
    layout->addWidget(backButton);
    setLayout(layout);
    connect(backButton, SIGNAL (clicked()), this, SLOT (backToMainMenu()));
    connect(soundSlider, SIGNAL (valueChanged(int)), this, SLOT (updateSound(int)));
}

void SettingsWidget::backToMainMenu()
{
    emit backButtonClicked();
}

void SettingsWidget::updateSound(int s)
{
    mainConfig.setSound(s);
}

SettingsWidget::~SettingsWidget()
{
    qDebug() << "settings widget deleted";
}
