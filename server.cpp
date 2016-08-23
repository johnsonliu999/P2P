#include "server.h"
#include "processthread.h"

#include <QTcpServer>
#include <QTcpSocket>

Server::Server(QObject *parent) : QObject(parent),
    m_pTcpServer(new QTcpServer(this))
{
    if (!m_pTcpServer->listen(QHostAddress::Any, PORT)) {
        qDebug() << "Listen error :" << m_pTcpServer->errorString();
        return;
    }

    qDebug() << "Server started at" << m_pTcpServer->serverAddress().toString() << ":" << m_pTcpServer->serverPort();
    connect(m_pTcpServer, &QTcpServer::acceptError, this, &Server::on_acceptError);
    connect(m_pTcpServer, &QTcpServer::newConnection, this, &Server::on_newConnection);

}

void Server::on_acceptError(QAbstractSocket::SocketError error)
{
    qDebug() << "Accept error :" << m_pTcpServer->errorString();
}

void Server::on_newConnection()
{
    auto pSocket = m_pTcpServer->nextPendingConnection();
    qDebug() << "Connect :" << pSocket->peerAddress().toString();

    auto p_proThread = new ProcessThread(pSocket, this);
    pSocket->setParent(nullptr);
    pSocket->moveToThread(p_proThread);

    p_proThread->start();
}
