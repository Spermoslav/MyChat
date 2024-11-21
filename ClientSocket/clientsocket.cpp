#include "clientsocket.h"

ClientSocket::ClientSocket(Widget *widget) :
    widget(widget),
    socket(new QTcpSocket(this))
{
    connect(socket, &QTcpSocket::readyRead, this, &ClientSocket::readMessage);
    connect(socket, &QTcpSocket::connected, this, &ClientSocket::socketConnected);
    connect(socket, &QTcpSocket::disconnected, this, &ClientSocket::socketDisconnected);
    connect(socket, &QTcpSocket::errorOccurred, this, &ClientSocket::socketError);
}

void ClientSocket::readMessage()
{
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_6_2);
    if(in.status() == QDataStream::Ok) {

        if(nextBlockSize == 0) {
            if(socket->bytesAvailable() < 2)
                return;

            in >> nextBlockSize;
        }

        if(socket->bytesAvailable() < nextBlockSize)
            return;

        nextBlockSize = 0;

        Data d;
        in >> d.type;
        in >> d.text;

        switch (d.type) {
        case Message: {
            auto ms = accMessageSplit(d.text);
                widget->chatBrowserAppend(ms.first, ms.second);
            }
            break;

        case Info:
            widget->chatBrowserAppendInfo(d.text);
            break;

        case Login:
            if(d.text == "n") {
                widget->authFault(d);
            }
            else if(d.text == "p") {
                widget->authFault(d);
            }
            else {
                widget->authSucces(d);
            }
            break;

        case Registration:
            qDebug() << d.text;
            if(d.text == "e") {
                widget->authFault(Data("e", Registration));
            }
            else {
                widget->authSucces(d);
            }
            break;
        }
    }
    else {

    }
}

void ClientSocket::sendToServer(const Data &ms)
{
    data.clear();

    QDataStream out(&data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_2);

    out << quint16(0);
    out << ms.type;
    out << ms.text;
    out.device()->seek(0);
    out << quint16(data.size() - sizeof(quint16));

    socket->write(data);
}

void ClientSocket::socketError(QAbstractSocket::SocketError err)
{
    connectionFault(socket->errorString());
}

void ClientSocket::socketDisconnected()
{
    connectionFault("Соединение потеряно");
}
