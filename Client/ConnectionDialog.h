#ifndef CONNECTIONDIALOG_H
#define CONNECTIONDIALOG_H

#include <QDialog>

namespace Ui {
class ConnectionDialog;
}

class ConnectionDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ConnectionDialog(QWidget *parent = nullptr);
    ~ConnectionDialog();
    QString hostNmae() const;
    quint16 port() const;
private slots:
    void on_ok_clicked();
    void on_cancel_clicked();
private:
    Ui::ConnectionDialog *ui;
    QString mHostName;
    quint16 mPort;
};

inline QString ConnectionDialog::hostNmae() const
{
    return mHostName;
}

inline quint16 ConnectionDialog::port() const
{
    return mPort;
}
#endif // CONNECTIONDIALOG_H
