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
}

Widget::~Widget()
{
}

