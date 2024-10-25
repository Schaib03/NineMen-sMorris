#ifndef CONFIRMATIONDIALOG_H
#define CONFIRMATIONDIALOG_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QDebug>
#include <QString>

using DialogMessage = struct dm
{
    QString question;
    QString action;
};

const DialogMessage QUIT_MESSAGE = {"Do you really want to quit?", "Quit"};
const DialogMessage RESTART_MESSAGE = {"Do you really want to restart? \nUnsaved progress will be lost", "Restart"};
const DialogMessage DELETE_MESSAGE = {"Do you really want to delete this savegame?", "Delete"};

class ConfirmationDialog : public QWidget
{
    Q_OBJECT

    public:
        ConfirmationDialog(QWidget *parent = nullptr, DialogMessage = RESTART_MESSAGE);
        ~ConfirmationDialog();

    private:
        QPushButton *confirmButton;
        QPushButton *cancelButton;
        QLabel *question;
        QVBoxLayout *layout;

    signals:
        void cancelButtonClicked();
        void confirmButtonClicked();

    public slots:
        void cancelAction();
        void confirmAction();
};

#endif // CONFIRMATIONDIALOG_H
