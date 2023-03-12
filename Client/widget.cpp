#include <QFileDialog>
#include <QBuffer>
#include "widget.h"
#include "ui_widget.h"
#include "ConnectionDialog.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    m_Socket = new QTcpSocket(this);

    connect(m_Socket, &QTcpSocket::disconnected, m_Socket, &QTcpSocket::deleteLater);

    connect(m_Socket, &QTcpSocket::readyRead, this, &Widget::slot_ready );

    m_blockSize = 0;
    m_img = new QImage();
}

Widget::~Widget()
{
    delete ui;
    delete m_img;
}

void Widget::slot_ready()
{
    QDataStream in(m_Socket);
    in.setVersion(QDataStream::Qt_6_2);

    if (in.status() == QDataStream::Ok) {
        while (true) {
            if (m_blockSize == 0) {
                if (m_Socket -> bytesAvailable() < 2)
                    break;
                in >> m_blockSize;
            }
            if (m_Socket -> bytesAvailable() < m_blockSize)
                break;
            QString _str;
            in >> _str;
            m_blockSize = 0;
            ui->textEdit->append(_str);
        }
    }
    else {
        qDebug() << "DataStream error";
    }
}

void Widget::on_send_clicked()
{
    QString _mess(ui->nickname->text() + ": " + ui->message->text());

    QByteArray _ba;
    QBuffer _buffer(&_ba);
    _buffer.open(QIODevice::WriteOnly);
    m_img->save(&_buffer, "PNG");

    QByteArray m_data;
    QDataStream out(&m_data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_2);

    out << (quint64)0;
    out << _mess;
    out << _ba;
    out.device() -> seek(0);
    out << quint64( m_data.size() - sizeof (quint64) );

    qDebug() << m_Socket->write(m_data);
    ui->message->clear();
}

void Widget::on_bind_clicked()
{
    ConnectionDialog _d(this);
    if (_d.exec() == QDialog::Rejected){
        return;
    }
    m_Socket->connectToHost(_d.hostNmae(), _d.port());
}

void Widget::on_file_clicked()
{
    QString _path(QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("Выбор дирректории"), "/home"));
    m_img->load(_path);
}

