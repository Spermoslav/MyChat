#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <QTcpSocket>

class ClientSocket : public QObject
{
    Q_OBJECT
public:
    explicit ClientSocket(const QString& ip, uint port);

private slots:
    void readMessage();
    void sendToServer(const QString& str);
    void socketError(QAbstractSocket::SocketError err);

private:
    QTcpSocket *socket;
    QByteArray data;
    quint16 nextBlockSize{0};

};

#endif // CLIENTSOCKET_H
