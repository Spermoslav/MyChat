#include "auth.h"

EnterAccount::EnterAccount(Widget *parent)
    : QGroupBox(parent),
      parent(parent),
      regSubmitPB(new QPushButton(EA_REGPB_TEXT, this)),
      loginSubmitPB(new QPushButton(EA_LOGINPB_TEXT, this))
{
    connect(regSubmitPB,   &QPushButton::clicked, this, &EnterAccount::regSubmitPBClicked);
    connect(loginSubmitPB, &QPushButton::clicked, this, &EnterAccount::loginSubmitPBClicked);
}

void EnterAccount::authFault(const Data &message)
{
    if(message.type == Registration) {
        auth->nicknameFault(Exist);
    }
    else if(message.type == Login) {
        if(message.text == "n")
            auth->nicknameFault(NotFound);

        else if (message.text == "p")
            static_cast<LogIn*> (auth)->wrongPassword();

        else
            qDebug() << __FUNCTION__ << " Message не обработан";
    }
}

void EnterAccount::resizeEvent(QResizeEvent *e)
{
    if(auth) {
        auth->resize(size());
    }
    else {
        regSubmitPB->setGeometry(width() * 0.05, height() * 0.35, width() * 0.9, height() * 0.1);
        loginSubmitPB->setGeometry(width() * 0.05, height() * 0.5, width() * 0.9, height() * 0.1);
    }
}

void EnterAccount::regSubmitPBClicked()
{
    if(!auth) auth = new Reg(this);
    else {
        delete auth;
        auth = new Reg(this);
    }
    auth->show();
    auth->resize(size());
}

void EnterAccount::loginSubmitPBClicked()
{
    if(!auth) auth = new LogIn(this);
    else {
        delete auth;
        auth = new LogIn(this);
    }
    auth->show();
    auth->resize(size());
}

void EnterAccount::tryAuthAccount(const Data &accData)
    {   parent->sendAuthAccount(accData);   }
