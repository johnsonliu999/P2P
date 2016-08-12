#ifndef PROCESSTHREAD_H
#define PROCESSTHREAD_H

#include <QThread>

class QTcpSocket;

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

public slots:


private slots:
    void on_readyRead();

};

#endif // PROCESSTHREAD_H
