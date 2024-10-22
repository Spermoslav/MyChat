#include "clientsocket.h"

ClientSocket::ClientSocket(const QString &ip, uint port)
{
    connect(socket, &QTcpSocket::readyRead, this, &ClientSocket::readMessage);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
    connect(socket, &QTcpSocket::errorOccurred, this, &ClientSocket::socketError);
    socket->connectToHost(ip, port);
    socket->waitForConnected();
}

void ClientSocket::sendToServer(const QString &str)
{
    data.clear();
    QDataStream out(&data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_2);
    out << quint16(0) << str;
    out.device()->seek(0);
    out << quint16(data.size() - sizeof(quint16));
    socket->write(data);
}
}
