#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <QTcpSocket>
#include "widget.h"
#include "data.h"

class ClientSocket : public QObject
{
    friend class Widget;
    Q_OBJECT
public:
    explicit ClientSocket(Widget* widget);

    void sendToServer(const Data &ms);

    inline void connectSocket(const QString& ip, uint port) noexcept {
        socket->connectToHost(ip, port);
    }

private slots:
    void readMessage();
    void socketError(QAbstractSocket::SocketError err);
    void socketDisconnected();

signals:
    void connectionFault(const QString &err);
    void socketConnected();

private:
    Widget* widget;

    QTcpSocket *socket;
    QByteArray data;
    quint16 nextBlockSize{0};

};

#endif // CLIENTSOCKET_H
