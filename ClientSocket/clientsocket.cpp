#include "clientsocket.h"

ClientSocket::ClientSocket(Widget *widget, const QString &ip, uint port) :
    widget(widget),
    socket(new QTcpSocket(this))
{
    connect(socket, &QTcpSocket::readyRead, this, &ClientSocket::readMessage);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
    connect(socket, &QTcpSocket::errorOccurred, this, &ClientSocket::socketError);
    socket->connectToHost(ip, port);
    socket->waitForConnected();
}

void ClientSocket::readMessage()
{
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_6_2);
    if(in.status() == QDataStream::Ok) {
        for(;;) {
            if(nextBlockSize == 0) {
                if(socket->bytesAvailable() < 2)
                    break;

                in >> nextBlockSize;
            }

            if(socket->bytesAvailable() < nextBlockSize)
                break;

            QString str;
            in >> str;
            nextBlockSize = 0;
            widget->chatBrowserAppend(str);
        }
    }
    else {

    }
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

void ClientSocket::socketError(QAbstractSocket::SocketError err)
{
    Q_UNUSED(err)
    widget->chatBrowserAppend(socket->errorString());
}
