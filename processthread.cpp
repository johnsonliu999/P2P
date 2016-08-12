#include "processthread.h"

#include <QTcpSocket>
#include <QDataStream>
#include <QHostAddress>

ProcessThread::ProcessThread(QTcpSocket *pSocket, QObject *parent)
    : QThread(parent),
      m_pSocket(pSocket)
{
    connect(this, &ProcessThread::finished, this, &ProcessThread::deleteLater);
    connect(pSocket, &QTcpSocket::readyRead, this, &ProcessThread::on_readyRead);
}

void ProcessThread::on_readyRead()
{
    m_pSocket->waitForReadyRead();

    QDataStream in(m_pSocket);
    quint8 flag;
    in >> flag;

    qDebug() << m_pSocket->peerAddress().toString();

    switch (flag) {
    case LOG_IN:
        qDebug() << "log in";
        break;
    case LOG_OUT:
        qDebug() << "log out";
        break;
    case LOOK_UP:
        qDebug() << "look up";
        break;
    }
}
