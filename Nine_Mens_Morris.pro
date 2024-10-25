TEMPLATE = app
TARGET = Nine_Mens_Morris
QT = core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += main.cpp \
    confirmationdialog.cpp \
    game.cpp \
    gameboard.cpp \
    gamecard.cpp \
    gamewidget.cpp \
    historywidget.cpp \
    init.cpp \
    mainconfig.cpp \
    mainmenuwidget.cpp \
    mainwindow.cpp \
    move.cpp \
    pausemenu.cpp \
    player.cpp \
    playmenu.cpp \
    settingswidget.cpp \
    state.cpp \
    INIReader.cpp \
    ini.c

HEADERS += \
    confirmationdialog.h \
    game.h \
    gameboard.h \
    gamecard.h \
    gamewidget.h \
    historywidget.h \
    init.hpp \
    mainconfig.h \
    mainmenuwidget.h \
    mainwindow.h \
    move.h \
    pausemenu.h \
    player.h \
    playmenu.h \
    settingswidget.h \
    state.h \
    INIReader.h

FORMS += \
    mainwindow.ui
