#ifndef PROCESSTHREAD_H
#define PROCESSTHREAD_H

#include <QThread>
#include <QAbstractSocket>
#include <QMutex>
#include <QHostAddress>


class QTcpSocket;
class Server;

class ProcessThread : public QThread
{
    Q_OBJECT

    enum {
        LOG_IN,
        LOG_OUT,
        LOOK_UP
    };

public:
    ProcessThread(QTcpSocket *pSocket, QObject *parent = 0);

private:
    QTcpSocket *m_pSocket;
    QHostAddress m_addr;
    QMutex m_mutex;

    Server *m_pServer;

public slots:


private slots:
    void on_readyRead();
    void on_disconnected();
    void on_error(QAbstractSocket::SocketError error);
};

#endif // PROCESSTHREAD_H
