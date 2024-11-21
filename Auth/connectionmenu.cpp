#include "connectionmenu.h"
#include "data.h"

ConnectionMenu::ConnectionMenu(QWidget *parent, QTcpSocket* socket)
    : QGroupBox(parent),
      parent(parent),
      ipInfoL(new QLabel(CM_INFO_TEXT, this)),
      ipLE(new QLineEdit(this)),
      portLE(new QLineEdit(this)),
      submitPB(new QPushButton("Ок", this)),
      lw(new LoadWidget(this)),
      socket(socket)
{
    ipLE->setText(CM_IPLE_TEXT);
    portLE->setText(CM_PORTLE_TEXT);

    lw->hide();
    lw->setAlignment(Qt::AlignCenter);
    lw->setFont(QFont(lw->font().family(), 15));

    connect(submitPB, &QPushButton::clicked, this, &ConnectionMenu::submitPBClicked);
    connect(socket, &QTcpSocket::errorOccurred, this, &ConnectionMenu::socketError);
    connect(socket, &QTcpSocket::connected, this, &ConnectionMenu::socketConnected);
}

void ConnectionMenu::resizeEvent(QResizeEvent *e)
{
    ipInfoL->setGeometry(width() * 0.1, height() * 0.25, width() * 0.8, height() * 0.1);
    ipLE->setGeometry(width() * 0.1, height() * 0.4, width() * 0.8, height() * 0.1);
    portLE->setGeometry(width() * 0.1, height() * 0.55, width() * 0.8, height() * 0.1);
    submitPB->setGeometry(width() * 0.1, height() * 0.7, width() * 0.8, height() * 0.1);
    lw->resize(size());
}

void ConnectionMenu::keyPressEvent(QKeyEvent *e)
{
    Q_UNUSED(e)
    if(e->key() == Qt::Key_Enter || e->key() == Qt::Key_Return)
        submitPBClicked();
}

void ConnectionMenu::submitPBClicked()
{
    if(!ipIsValid()) {
        writeError("Wrong ip adress");
    }
    else if (!portIsValid()){
        writeError("Wrong port");
    }
    else {
        lw->activate();
        socket->connectToHost(ipLE->text(), portLE->text().toInt());
    }
}

void ConnectionMenu::socketConnected()
{
    lw->stop();
    hide();
    writeAdress(ipLE->text(), portLE->text());
}

void ConnectionMenu::socketError(QAbstractSocket::SocketError err)
{
    Q_UNUSED(err)
    writeError(socket->errorString());
    lw->stop();
}

bool ConnectionMenu::ipIsValid()
{
    QString ip = ipLE->text();
    if(ip.size() < 7) return false;

    qint8 dotCount = 0;
    quint8 afterDotNCount = 0;
    bool waitN = true;

    for(qsizetype i = 0; i < ip.size(); ++i) {
        if(waitN) {
            if(ip[i] >= '0' && ip[i] <= '9') {
                waitN = false;
                ++afterDotNCount;
            }
            else return false;
        }
        else {
            if(ip[i] == '.') {
                if(dotCount < 3) {
                    waitN = true;
                    ++dotCount;
                    afterDotNCount = 0;
                }
                else return false;
            }
            else if (ip[i] >= '0' && ip[i] <= '9') {
                if(afterDotNCount < 3) {
                    ++afterDotNCount;
                }
                else return false;
            }
            else return false;
        }
    }
    return true;
}

bool ConnectionMenu::portIsValid()
{
    QString port = portLE->text();
    if(port.size() > 6 || port.size() == 0) return false;
    for(qsizetype i = 0; i < port.size(); ++i) {
        if (port[i] < '0' || port[i] > '9') {
            return false;
        }
    }
    return true;
}
