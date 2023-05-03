#ifndef APPCORE_H
#define APPCORE_H

#include <QObject>
#include <QTcpSocket>
#include <QtWidgets/QLabel>

class AppCore : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString _message WRITE setMessage)

    QTcpSocket *m_Socket;

    QImage *m_img;
    quint64 m_blockSize;

    QString m_message;
    QLabel* m_label;

public:

    explicit AppCore(QObject *parent = nullptr);
    ~AppCore();

signals:
    void addMessage(QString _message);

private:
    void setMessage(QString _str) {
        if (m_message == _str)
            return;

        m_message = _str;
    }

private slots:
    void slot_ready();

public slots:
    void on_send_clicked();
    void on_bind_clicked();
};

#endif // APPCORE_H
