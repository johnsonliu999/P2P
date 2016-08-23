#include "processthread.h"
#include "server.h"

#include <QTcpSocket>
#include <QDataStream>
#include <QHostAddress>

ProcessThread::ProcessThread(QTcpSocket *pSocket, QObject *parent)
    : QThread(parent),
      m_pSocket(pSocket),
      m_addr(pSocket->peerAddress()),
      m_pServer((Server *)this->parent())
{
    m_pSocket->setParent(this);
    connect(this, &ProcessThread::finished, this, &ProcessThread::deleteLater);
    connect(m_pSocket, &QTcpSocket::readyRead, this, &ProcessThread::on_readyRead);
    connect(m_pSocket, &QTcpSocket::disconnected, this, &ProcessThread::on_disconnected);

    qRegisterMetaType<QAbstractSocket::SocketError>("QAbstractSocket::SocketError");
    connect(m_pSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(on_error(QAbstractSocket::SocketError)));
}

void ProcessThread::on_readyRead()
{
    qDebug() << "on_readyRead";

    qDebug() << m_pSocket->bytesAvailable();

    QDataStream in(m_pSocket);
    quint8 flag;
    in >> flag;

    qDebug() << m_pSocket->peerAddress().toString();

    switch (flag) {
    case LOG_IN:
    {
        qDebug() << m_addr.toString() << "log in";

        m_mutex.lock();
        m_pServer->m_ip_list << m_addr.toString();
        m_mutex.unlock();

        QStringList fileList;
        in >> fileList;

        m_mutex.lock();
        foreach (auto &file, fileList) {
            m_pServer->m_file_ip_map.insert(file, m_addr.toString());
        }
        m_mutex.unlock();

        break;
    }
    case LOG_OUT:
        qDebug() << m_addr.toString() << "log out";
        m_mutex.lock();
        m_pServer->m_ip_list.removeAll(m_addr.toString());
        m_mutex.unlock();
        break;
    case LOOK_UP:
        qDebug() << m_addr.toString() << "look up";
        break;
    }
}

void ProcessThread::on_disconnected()
{
    qDebug() << m_addr.toString() <<  " disconnected";
}

void ProcessThread::on_error(QAbstractSocket::SocketError error)
{
    qDebug() << m_addr.toString() <<  " error :" << m_pSocket->errorString();
}
