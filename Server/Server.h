#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>
#include <QLabel>
#include <QBuffer>


class Server
        : public QTcpServer
{
    Q_OBJECT

    QTcpSocket              *m_socket;
    QVector<QTcpSocket*>    m_Sockets;

    quint64 m_blockSize;
    QLabel  *m_label;

public:
    Server();
    ~Server();

protected:
    void incomingConnection(qintptr);

private:
    void sendToClient(QString _mess);

private slots:
    void slotReadyRead();
    void openImg();



};

#endif // SERVER_H
