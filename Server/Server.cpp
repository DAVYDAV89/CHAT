#include "Server.h"
#include <QDataStream>
#include <QDebug>

Server::Server()
{
    if (listen(QHostAddress::Any, 3333)) {
        qDebug() << "start";
    }
    else {
        qDebug() << "error";
    }
    m_blockSize = 0;
}

Server::~Server()
{
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    m_socket = new QTcpSocket;
    m_socket -> setSocketDescriptor(socketDescriptor);

    connect(m_socket, &QTcpSocket::readyRead, this, &Server::slotReadyRead);
    connect(m_socket, &QTcpSocket::disconnected, m_socket, &Server::deleteLater);

    m_Sockets.push_back(m_socket);
    qDebug() << "client connected " << socketDescriptor;
}

void Server::slotReadyRead()
{
    m_socket = static_cast<QTcpSocket*>(sender());

    QDataStream _in(m_socket);
    _in.setVersion(QDataStream::Qt_5_9);
    if (_in.status() == QDataStream::Ok) {
        for(;;){
            if (m_blockSize == 0) {
                if (m_socket->bytesAvailable() < 2)
                    break;
                _in >> m_blockSize;
            }
            if (m_socket->bytesAvailable() < m_blockSize)
                break;

            QString _str;
            _in >> _str;

            m_blockSize = 0;

            sendToClient(_str);
            break;
        }
    }
}

void Server::sendToClient(QString _mess)
{
    QByteArray _data;
    QDataStream out(&_data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_9);

    out << quint64(0);
    out << _mess;
    out.device() -> seek(0);
    out << quint64( _data.size() - sizeof (quint64) );

    for (const auto &el : m_Sockets )
        el->write(_data);

}
