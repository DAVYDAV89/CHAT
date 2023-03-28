#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QImage>
#include <QLabel>


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

    Ui::Widget *ui;
    QTcpSocket *m_Socket;

    QImage *m_img;
    QLabel *m_label;
    quint64 m_blockSize;

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void slot_ready();
    void on_send_clicked();
    void on_bind_clicked();

    void on_file_clicked();

private:
    void openImg();
};
#endif // WIDGET_H
