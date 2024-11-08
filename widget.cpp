#include "widget.h"
#include "clientsocket.h"
#include "auth.h"
#include "data.h"

#include <QDir>

Widget::Widget(QWidget *parent)
    : QWidget(parent),
      chatBrowser(new QTextBrowser),
      messageEdit(new QLineEdit),
      messageSendPB(new QPushButton("send message")),
      mainLay(new QVBoxLayout(this)),
      clientSocket(new ClientSocket(this, "178.68.247.57", 1234))
{
    mainLay->addWidget(chatBrowser);
    mainLay->addWidget(messageEdit);
    mainLay->addWidget(messageSendPB);

    chatBrowser->setStyleSheet("background-color: rgb(" + QString(CHATBROWSER_COLOR) + ");");
    chatBrowser->setFontPointSize(14);

    messageSendPB->setStyleSheet("background-color: rgb(" + QString(MESSAGESENDPB_COLOR_NORMAL) + ");");
    connect(messageSendPB, &QPushButton::released, this, &Widget::messageSendPBReleased);
    connect(messageSendPB, &QPushButton::pressed, this, &Widget::messageSendPBPressed);
    QDir d = QDir::current();
    d.mkdir("Data");

#ifndef AUTH_HIDE
    #ifdef AUTH_SHOW
        auth = new EnterAccount(this);
    #else
        if(readAccLog() == "") {
            auth = new EnterAccount(this);
        }
        else {
            nickName = readAccLog();
            chatBrowserAppendInfoAll(nickName + " подключился");
     }
    #endif
#endif
}

Widget::~Widget()
{
}

void Widget::authSucces(const Data &accData)
{
    auto dataSplit = accMessageSplit(accData.text);
    writeAccLog(dataSplit.first);
    nickName = dataSplit.first;

    auth->hide();

    if(accData.type == Login) {
        chatBrowserAppendInfoAll(dataSplit.first + " подключился");
    }
    else {
        chatBrowserAppendInfoAll(dataSplit.first + " зарегался");
    }
}

void Widget::messageSendPBPressed()
{
    messageSendPB->setStyleSheet("background-color: rgb(" + QString(MESSAGESENDPB_COLOR_TAP) + ");");
    if(messageEdit->text().size() != 0)
        clientSocket->sendToServer(nickName + ' ' + messageEdit->text());

    messageEdit->clear();
}
void Widget::sendAuthAccount(const Data &accData)
    { clientSocket->sendToServer(accData); }

void Widget::authFault(const Data &accData)
    { auth->authFault(accData); }

void Widget::chatBrowserAppendInfoAll(const QString &text)
    { clientSocket->sendToServer(Data(text, Info)); }
