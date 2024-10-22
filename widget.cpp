#include "widget.h"
#include "clientsocket.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent),
      chatBrowser(new QTextBrowser),
      messageEdit(new QLineEdit),
      messageSendPB(new QPushButton("send message")),
      mainLay(new QVBoxLayout(this)),
      clientSocket(new ClientSocket("78.81.157.245", 1234))
{
    mainLay->addWidget(chatBrowser);
    mainLay->addWidget(messageEdit);
    mainLay->addWidget(messageSendPB);

    chatBrowser->setStyleSheet("background-color: rgb(" + QString(CHATBROWSER_COLOR) + ");");
    chatBrowser->setFontPointSize(14);

    messageSendPB->setStyleSheet("background-color: rgb(" + QString(MESSAGESENDPB_COLOR_NORMAL) + ");");
    connect(messageSendPB, &QPushButton::released, this, &Widget::messageSendPBReleased);
    connect(messageSendPB, &QPushButton::pressed, this, &Widget::messageSendPBPressed);
}

Widget::~Widget()
{
}

void Widget::messageSendPBReleased()
{
    messageSendPB->setStyleSheet("background-color: rgb(" + QString(MESSAGESENDPB_COLOR_NORMAL) + ");");

}

void Widget::messageSendPBPressed()
{
    messageSendPB->setStyleSheet("background-color: rgb(" + QString(MESSAGESENDPB_COLOR_TAP) + ");");
    if(messageEdit->text().size() != 0)
        chatBrowser->append(messageEdit->text());

    messageEdit->clear();
}
