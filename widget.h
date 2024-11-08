#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTextBrowser>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTime>
#include <QResizeEvent>
#include <QKeyEvent>
#include <QString>

#include "data.h"

#define MESSAGESENDPB_COLOR_NORMAL "200, 200, 200"
#define MESSAGESENDPB_COLOR_TAP    "150, 150, 150"
#define CHATBROWSER_COLOR "224, 255, 255"

//#define DEBUG
#ifdef DEBUG
//    #define AUTH_HIDE
    #ifndef AUTH_HIDE
        #define AUTH_SHOW
    #endif
#endif

class ClientSocket;
class EnterAccount;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void sendAuthAccount(const Data& accData);

    void authFault(const Data& accData);
    void authSucces(const Data &accData);

    void chatBrowserAppendInfoAll(const QString& text);
    inline void chatBrowserAppendInfo(const QString& text)
                    { chatBrowser->append(QTime::currentTime().toString() + " " + text); }

private slots:
    void messageSendPBReleased();
    void messageSendPBPressed();

private:
    QTextBrowser* chatBrowser;
    QLineEdit* messageEdit;
    QPushButton* messageSendPB;
    QVBoxLayout* mainLay;

    ClientSocket* clientSocket;

};
#endif // WIDGET_H
