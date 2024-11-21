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
    explicit ClientSocket(Widget* widget, const QString& ip, uint port);

    void sendToServer(const Data &ms);

private slots:
    void readMessage();
    void socketError(QAbstractSocket::SocketError err);

private:
    Widget* widget;

    QTcpSocket *socket;
    QByteArray data;
    quint16 nextBlockSize{0};

};

#endif // CLIENTSOCKET_H
