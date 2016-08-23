#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QAbstractSocket>

class QTcpServer;

class Server : public QObject
{
    Q_OBJECT

    friend class ProcessThread;
    enum {
        PORT = 1234,
    };

public:
    explicit Server(QObject *parent = 0);

private:
    QTcpServer* m_pTcpServer;
    QMultiMap<QString, QString> m_file_ip_map;
    QStringList m_ip_list;

signals:

public slots:

private slots:
    void on_acceptError(QAbstractSocket::SocketError error);
    void on_newConnection();

};

#endif // SERVER_H
