#ifndef CONNECTIONMENU_H
#define CONNECTIONMENU_H

#include <QObject>
#include <QWidget>
#include <QGroupBox>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QResizeEvent>
#include <QKeyEvent>
#include <QTcpSocket>
#include <QTimer>

#include "loadwidget.h"

#define CM_INFO_TEXT    "Введите адрес сервера"
#define CM_IPLE_TEXT    "ip"
#define CM_PORTLE_TEXT  "port"

class ConnectionMenu : public QGroupBox
{
    Q_OBJECT
public:
    ConnectionMenu(QWidget* parent, QTcpSocket* socket);

    inline void writeError(const QString& text) {
        ipInfoL->setText("Ошибка: " + text);
    }

private slots:
    void resizeEvent(QResizeEvent* e) override;
    void keyPressEvent(QKeyEvent* e)  override;

    void submitPBClicked();

    void socketConnected();
    void socketError(QAbstractSocket::SocketError err);

private:
    [[nodiscard]] bool ipIsValid();
    [[nodiscard]] bool portIsValid();

    QWidget* parent;

    QLabel*  ipInfoL;
    QLineEdit* ipLE;
    QLineEdit* portLE;
    QPushButton* submitPB;

    QTcpSocket* socket;

    LoadWidget* lw;
};

#endif // CONNECTIONMENU_H
