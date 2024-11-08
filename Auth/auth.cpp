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


Auth::Auth(EnterAccount *parent)
    : QGroupBox(parent),
      parent(parent),
      infoNickNameL(new QLabel(this)),
      infoPasswordL(new QLabel(this)),
      editNickNameLE(new QLineEdit(this)),
      editPasswordLE(new QLineEdit(this)),
      submitPB(new QPushButton(this)),
      backPB(new QPushButton("Назад", this))
{
    infoNickNameL->setAlignment(Qt::AlignCenter);
    infoNickNameL->setFont(QFont(infoNickNameL->font().family(), 10));

    infoPasswordL->setAlignment(Qt::AlignCenter);
    infoPasswordL->setFont(QFont(infoNickNameL->font().family(), 10));

    connect(submitPB, &QPushButton::released, this, &Auth::submitPBReleased);
    connect(submitPB, &QPushButton::pressed,  this, &Auth::submitPBPressed);
    connect(backPB,   &QPushButton::clicked,  this, &Auth::backPBClicked);

    setFocus();
}

void Auth::resizeEvent(QResizeEvent *e)
{
    Q_UNUSED(e)
    infoNickNameL->setGeometry(width() * 0.05, height() * 0.3, width() * 0.9, height() * 0.1);
    editNickNameLE->setGeometry(width() * 0.05, height() * 0.41, width() * 0.9, height() * 0.05);
    infoPasswordL->setGeometry(width() * 0.05, height() * 0.5, width() * 0.9, height() * 0.1);
    editPasswordLE->setGeometry(width() * 0.05, height() * 0.61, width() * 0.9, height() * 0.05);
    submitPB->setGeometry(width() * 0.05, height() * 0.7, width() * 0.9, height() * 0.05);
    backPB->setGeometry(width() * 0, height() * 0, width() * 0.2, height() * 0.05);
}

void Auth::keyPressEvent(QKeyEvent *e)
{
    Q_UNUSED(e)
    if(e->key() == Qt::Key_Enter || e->key() == Qt::Key_Return)
        submitPBReleased();
}


Reg::Reg(EnterAccount *parent)
    : Auth(parent)
{
    infoNickNameL->setText(REG_INFONNLABEL_TEXT);
    infoPasswordL->setText(REG_INFOPASSLABEL_TEXT);
    submitPB->setText(REG_SUBMITPB_TEXT);
}

void Reg::nicknameFault(NicknameErrorType t)
{
    if(t == Wrong) {
        infoNickNameL->setText(AUTH_NN_WRONG_TEXT);
    }
    else {
        infoNickNameL->setText(AUTH_NN_EXIST_TEXT);
    }
}

void Reg::submitPBReleased()
{
    QString nick = editNickNameLE->text();
    QString pass = editPasswordLE->text();

    if(nick.size() >= REG_NICKNAME_MINS && nick.size() <= REG_NICKNAME_MAXS && nick.indexOf(' ') == -1) {
        if(pass.size() >= REG_PASSWORD_MINS && pass.size() <= REG_PASSWORD_MAXS && pass.indexOf(' ') == -1) {
            parent->tryAuthAccount(Data(nick + ' ' + pass, Registration));
        }
        else {
            infoPasswordL->setText(AUTH_PASS_WRONG_TEXT);
        }
    }
    else {
        nicknameFault();
    }
}

void Reg::submitPBPressed()
{
    qDebug() << __FUNCTION__;
}


LogIn::LogIn(EnterAccount *parent)
    : Auth(parent)
{
    infoNickNameL->setText(LOGIN_INFONNLABEL_TEXT);
    infoPasswordL->setText(LOGIN_INFOPASSLABEL_TEXT);
    submitPB->setText(LOGIN_SUBMITPB_TEXT);
}

void LogIn::submitPBReleased()
{
    QString nick = editNickNameLE->text();
    QString pass = editPasswordLE->text();
    qDebug() << __FUNCTION__;
    if(nick.size() >= REG_NICKNAME_MINS && nick.size() <= REG_NICKNAME_MAXS && nick.indexOf(' ') == -1) {
        if(pass.size() >= REG_PASSWORD_MINS && pass.size() <= REG_PASSWORD_MAXS && pass.indexOf(' ') == -1) {
            parent->tryAuthAccount(Data(nick + ' ' + pass, Login));
        }
        else {
            infoPasswordL->setText(AUTH_PASS_WRONG_TEXT);
        }
    }
    else {
        nicknameFault();
    }
}

void LogIn::wrongPassword()
    { infoPasswordL->setText(AUTH_PASS_WRONG_TEXT); }

void LogIn::nicknameFault(NicknameErrorType t)
    { infoNickNameL->setText(AUTH_NN_NOTFOUND_TEXT); }

void LogIn::submitPBPressed()
{
    qDebug() << __FUNCTION__;
}
