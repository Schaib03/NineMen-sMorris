#include "confirmationdialog.h"

ConfirmationDialog::ConfirmationDialog(QWidget *parent, DialogMessage m)
    : QWidget(parent)
{
    confirmButton = new QPushButton(m.action);
    cancelButton = new QPushButton("Cancel");
    question = new QLabel(this);
    question->setText(m.question);
    question->setGeometry(0,0,600,200);
    question->setWordWrap(true);
    layout = new QVBoxLayout(this);
    layout->addWidget(confirmButton);
    layout->addWidget(cancelButton);
    connect(confirmButton, SIGNAL (clicked()), this, SLOT (confirmAction()));
    connect(cancelButton, SIGNAL (clicked()), this, SLOT (cancelAction()));
}

ConfirmationDialog::~ConfirmationDialog()
{
    qDebug() << "confirmation dialog destroyed\n";
}

void ConfirmationDialog::confirmAction()
{
    emit confirmButtonClicked();
}

void ConfirmationDialog::cancelAction()
{
    emit cancelButtonClicked();
}
