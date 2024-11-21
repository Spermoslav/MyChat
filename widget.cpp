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
      logOutPB(new QPushButton("выйти из аккаунта")),
      mainLay(new QVBoxLayout(this)),
      clientSocket(new ClientSocket(this))
{
    mainLay->addWidget(chatBrowser);
    mainLay->addWidget(messageEdit);
    mainLay->addWidget(messageSendPB);
    mainLay->addWidget(logOutPB);

    chatBrowser->setStyleSheet("background-color: rgb(" + QString(CHATBROWSER_COLOR) + ");");
    chatBrowser->setFontPointSize(14);

    messageSendPB->setStyleSheet("background-color: rgb(" + QString(MESSAGESENDPB_COLOR_NORMAL) + ");");

    connect(messageSendPB, &QPushButton::released, this, &Widget::messageSendPBReleased);
    connect(messageSendPB, &QPushButton::pressed, this, &Widget::messageSendPBPressed);
    connect(logOutPB, &QPushButton::clicked, this, &Widget::logOutPBClicked);
    connect(clientSocket, &ClientSocket::connectionFault, this, &Widget::socketError);
    connect(clientSocket, &ClientSocket::socketConnected, this, &Widget::socketConnected);

    QDir d = QDir::current();
    d.mkdir("Data");

    InfoPair ap = readAdress();
    InfoPair aN = readAccInfo();

    if(ap == std::nullopt) {
        if(aN == std::nullopt) {
            auth = new EnterAccount(this);
        }
        else {
            clientSocket->sendToServer(Data((*aN).first + ' ' + (*aN).second, Login));
        }

        cm = new ConnectionMenu(static_cast<QWidget*> (this), clientSocket->socket);
    }
    else {
        clientSocket->connectSocket((*ap).first, (*ap).second.toInt());
        waitConnectionLW = new LoadWidget(this);
        waitConnectionLW->setAlignment(Qt::AlignCenter);
        waitConnectionLW->setFont(QFont(waitConnectionLW->font().family(), 15));

        if(aN == std::nullopt) {
            auth = new EnterAccount(this);
        }
        else {
            clientSocket->sendToServer(Data((*aN).first + ' ' + (*aN).second, Login));
        }
    }
}

Widget::~Widget()
{
}

void Widget::authSucces(const Data &accData)
{
    auto dataSplit = accMessageSplit(accData.text);
    writeAccInfo(dataSplit.first, dataSplit.second);
    nickName = dataSplit.first;

    if(auth) auth->hide();

    if(accData.type == Login) {
        chatBrowserAppendInfoAll(dataSplit.first + " подключился");
    }
    else {
        chatBrowserAppendInfoAll(dataSplit.first + " зарегался");
    }
}

void Widget::authFault(const Data &accData)
{
    if(auth) auth->authFault(accData);
    else {
        auth = new EnterAccount(this);
        auth->resize(size());
        auth->show();
    }
}

void Widget::messageSendPBPressed()
{
    messageSendPB->setStyleSheet("background-color: rgb(" + QString(MESSAGESENDPB_COLOR_TAP) + ");");
    if(messageEdit->text().size() != 0)
        clientSocket->sendToServer(nickName + ' ' + messageEdit->text());

    messageEdit->clear();
}

void Widget::logOutPBClicked()
{
    clearAccInfo();

    if(auth) {
        auth->show();
    }
    else {
        auth = new EnterAccount(this);
        auth->resize(size());
        auth->show();
    }
}

void Widget::resizeEvent(QResizeEvent *e)
{
    if(auth) {
        auth->resize(size());
    }
    if(cm) {
        cm->resize(size());
    }
    if(waitConnectionLW) {
        waitConnectionLW->resize(size());
    }
}

void Widget::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Enter || e->key() == Qt::Key_Return)
        messageSendPBPressed();
}

void Widget::socketConnected()
{
    if(waitConnectionLW) {
        waitConnectionLW->stop();
        delete waitConnectionLW;
    }
}

void Widget::socketError(const QString& err)
{
    if(auth) {
        auth->show();
    }
    else {
        auth = new EnterAccount(this);
        auth->resize(size());
    }
    if(cm) {
        cm->show();
    }
    else {
        cm = new ConnectionMenu(this, clientSocket->socket);
        cm->resize(size());
        cm->writeError(err);
    }
}

void Widget::sendAuthAccount(const Data &accData)
    { clientSocket->sendToServer(accData); }

void Widget::chatBrowserAppendInfoAll(const QString &text)
    { clientSocket->sendToServer(Data(text, Info)); }

void Widget::messageSendPBReleased()
    { messageSendPB->setStyleSheet("background-color: rgb(" + QString(MESSAGESENDPB_COLOR_NORMAL) + ");"); }
