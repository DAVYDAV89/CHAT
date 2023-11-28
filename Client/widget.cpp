#include <QFileDialog>
#include <QMessageBox>
#include <QBuffer>
#include "widget.h"
#include "ConnectionDialog.h"
#include "ui_widget.h"

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

    m_label = new QLabel;
    m_label->setWindowFlags( Qt::Dialog | Qt::Popup );

}

Widget::~Widget()
{
    delete ui;
    delete m_img;
    delete m_label;
}

void Widget::slot_ready()
{
    QDataStream _in(m_Socket);
    _in.setVersion(QDataStream::Qt_5_15);
    if (_in.status() == QDataStream::Ok) {
        for(;;){
            if (m_blockSize == 0) {
                if (m_Socket->bytesAvailable() < 2)
                    break;
                _in >> m_blockSize;
            }
            if (m_Socket->bytesAvailable() < m_blockSize)
                break;

            QString _str;
            QByteArray _data;

            _in >> _str;
            _in >> _data;

            m_blockSize = 0;

            if (_data.size() > 0) {
                m_label->clear();

                QBuffer _buffer(&_data);
                m_img->loadFromData(_data,"PNG");
                m_img->save(&_buffer, "PNG");

                QMessageBox msgBox;
                msgBox.setWindowFlags( Qt::Dialog | Qt::Popup );
                msgBox.setText("Image received!");
                msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
                msgBox.setIcon(QMessageBox::Question);
                msgBox.setDefaultButton(QMessageBox::Ok);
                int res = msgBox.exec();
                if (res == QMessageBox::Ok) {

                    m_label->setPixmap(QPixmap::fromImage(*m_img));
                    openImg();
                }
            }
            ui->textEdit->append(_str);
            m_img->load("");
            break;
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
    out.setVersion(QDataStream::Qt_5_15);

    out << quint64(0);
    out << _mess;
    out << _ba;
    out.device() -> seek(0);
    out << quint64( m_data.size() - sizeof (quint64) );

    m_Socket->write(m_data);
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
    m_img->load(QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("Выбор дирректории"), "/home"));
}

void Widget::openImg()
{
    if (!m_label->isHidden())
        m_label -> close();
    m_label->show();
}
