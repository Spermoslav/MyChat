#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent),
      chatBrowser(new QTextBrowser),
      messageEdit(new QLineEdit),
      messageSendPB(new QPushButton("send message")),
      mainLay(new QVBoxLayout(this))
{
    mainLay->addWidget(chatBrowser);
    mainLay->addWidget(messageEdit);
    mainLay->addWidget(messageSendPB);

    chatBrowser->setStyleSheet("background-color: rgb(" + QString(CHATBROWSER_COLOR) + ");");

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
    messageEdit->clear();
}
