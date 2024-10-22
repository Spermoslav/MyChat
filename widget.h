#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTextBrowser>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    QTextBrowser* chatBrowser;
    QLineEdit* messageEdit;
    QPushButton* messageSendPB;
    QVBoxLayout* mainLay;

};
#endif // WIDGET_H
