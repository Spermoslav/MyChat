#ifndef AUTH_H
#define AUTH_H

#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QResizeEvent>
#include <QKeyEvent>

#include "widget.h"
#include "data.h"

#define EA_REGPB_TEXT             "Зарегевтрироваться"
#define EA_LOGINPB_TEXT           "Войти"

#define AUTH_NN_NOTFOUND_TEXT     "Такого аккаунта не существует"
#define AUTH_NN_EXIST_TEXT        "Такой аккаунт уже существует"
#define AUTH_NN_WRONG_TEXT        "Неправильный ник"
#define AUTH_PASS_WRONG_TEXT      "Пароль не верный"

#define LOGIN_INFONNLABEL_TEXT    "Введи свой никнейм:"
#define LOGIN_INFOPASSLABEL_TEXT  "Введи пароль:"
#define LOGIN_SUBMITPB_TEXT       "Войти"

#define REG_INFONNLABEL_TEXT      "Введи свой ник 2-14 символов без пробелов"
#define REG_INFOPASSLABEL_TEXT    "Введи свой пароль 4-20 символов без пробелов"
#define REG_SUBMITPB_TEXT         "Зарегаться"

#define REG_NICKNAME_MINS  2
#define REG_NICKNAME_MAXS  14
#define REG_PASSWORD_MINS  4
#define REG_PASSWORD_MAXS  20


enum NicknameErrorType {
    NotFound,
    Exist,
    Wrong
};


class Auth;

class EnterAccount : public QGroupBox
{
    Q_OBJECT
public:
    EnterAccount(Widget* parent);

    void authFault(const Data& message);
    void tryAuthAccount(const Data& accData);

private slots:
    void resizeEvent(QResizeEvent* e) override;

    void regSubmitPBClicked();
    void loginSubmitPBClicked();

private:
    Widget* parent;

    Auth* auth{nullptr};

    QPushButton* regSubmitPB;
    QPushButton* loginSubmitPB;
};

class Auth : public QGroupBox
{
    Q_OBJECT
public:
    explicit Auth(EnterAccount* parent);

    virtual void nicknameFault(NicknameErrorType t = Wrong) = 0;

private slots:
    void resizeEvent(QResizeEvent* e) override;
    void keyPressEvent(QKeyEvent* e) override;

    virtual void submitPBReleased() = 0;
    virtual void submitPBPressed()  = 0;

    inline void backPBClicked() { hide(); }

protected:
    EnterAccount* parent;

    QLabel* infoNickNameL;
    QLabel* infoPasswordL;

    QLineEdit* editNickNameLE;
    QLineEdit* editPasswordLE;

    QPushButton* submitPB;
    QPushButton* backPB;
};

class Reg : public Auth
{
    Q_OBJECT
public:
    explicit Reg(EnterAccount* parent);

    void nicknameFault(NicknameErrorType t = Wrong) override;

private slots:
    void submitPBReleased() override;
    void submitPBPressed()  override;
};

class LogIn : public Auth
{
    Q_OBJECT
public:
    explicit LogIn(EnterAccount* parent);

    void wrongPassword();
    void nicknameFault(NicknameErrorType t = Wrong) override;

private slots:
    void submitPBReleased() override;
    void submitPBPressed()  override;
};

#endif // AUTH_H
