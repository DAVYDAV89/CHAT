#include "ConnectionDialog.h"
#include "ui_ConnectionDialog.h"

ConnectionDialog::ConnectionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectionDialog)
{
    ui->setupUi(this);
}

ConnectionDialog::~ConnectionDialog()
{
    delete ui;
}

void ConnectionDialog::on_ok_clicked()
{
    mHostName = ui->hostName->text();
    mPort = ui->port->value();
    accept();
}

void ConnectionDialog::on_cancel_clicked()
{
    reject();
}
