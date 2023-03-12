#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QImage>


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

    Ui::Widget *ui;

    QTcpSocket *m_Socket;


    quint16 m_blockSize;

    QImage *m_img;


public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void slot_ready();
    void on_send_clicked();
    void on_bind_clicked();


    void on_file_clicked();

private:
};
#endif // WIDGET_H
