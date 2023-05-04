#include "appcore.h"
#include <QBuffer>
#include <QDataStream>
#include <QDebug>

AppCore::AppCore(QObject *parent)
    : QObject{parent}
{
    m_Socket = new QTcpSocket(this);
    m_Socket->connectToHost("localhost", 3333);

    connect(m_Socket, &QTcpSocket::disconnected, m_Socket, &QTcpSocket::deleteLater);
    connect(m_Socket, &QTcpSocket::readyRead, this, &AppCore::slot_ready );

    m_blockSize = 0;
}

AppCore::~AppCore()
{
    delete m_Socket;
}

void AppCore::slot_ready()
{
    QDataStream _in(m_Socket);
    _in.setVersion(QDataStream::Qt_5_9);
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
            _in >> _str;

            m_blockSize = 0;
//            qDebug() << "_str: " << _str;

            emit addMessage(_str);
            break;
        }
    }
    else {
        qDebug() << "DataStream error";
    }
}

void AppCore::on_send_clicked()
{
    QByteArray _data;
    QDataStream out(&_data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_9);

    out << quint64(0);
    out << m_message;
    out.device() -> seek(0);
    out << quint64( _data.size() - sizeof (quint64) );

    qDebug() << m_Socket->write(_data);
}

void AppCore::on_bind_clicked()
{
    qDebug() << __PRETTY_FUNCTION__;
}
