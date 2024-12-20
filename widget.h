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
#include "connectionmenu.h"
#include "loadwidget.h"

#define MESSAGESENDPB_COLOR_NORMAL "200, 200, 200"
#define MESSAGESENDPB_COLOR_TAP    "150, 150, 150"
#define CHATBROWSER_COLOR "224, 255, 255"

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

    inline void chatBrowserAppend(const QString& nick, const QString& text)
                    { chatBrowser->append(QTime::currentTime().toString() + " " + nick + ": " + text); }

    inline void chatBrowserAppendInfo(const QString& text)
                    { chatBrowser->append(QTime::currentTime().toString() + " " + text); }

private slots:
    void messageSendPBReleased();
    void messageSendPBPressed();
    void logOutPBClicked();
    void resizeEvent(QResizeEvent* e) override;

    void keyPressEvent(QKeyEvent* e) override;

    void socketConnected();
    void socketError(const QString &err);

private:  
    QTextBrowser* chatBrowser;

    QLineEdit* messageEdit;

    QPushButton* messageSendPB;
    QPushButton* logOutPB;

    QVBoxLayout* mainLay;

    ClientSocket* clientSocket;

    QString nickName = "not";

    EnterAccount* auth{nullptr};

    ConnectionMenu* cm{nullptr};

    LoadWidget* waitConnectionLW{nullptr};
};
#endif // WIDGET_H
