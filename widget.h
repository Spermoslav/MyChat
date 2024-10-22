#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTextBrowser>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

#define MESSAGESENDPB_COLOR_NORMAL "200, 200, 200"
#define MESSAGESENDPB_COLOR_TAP    "150, 150, 150"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void messageSendPBReleased();
    void messageSendPBPressed();

private:
    QTextBrowser* chatBrowser;
    QLineEdit* messageEdit;
    QPushButton* messageSendPB;
    QVBoxLayout* mainLay;

};
#endif // WIDGET_H
