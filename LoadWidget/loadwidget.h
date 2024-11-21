#ifndef LOADWIDGET_H
#define LOADWIDGET_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QTimer>

#define LW_LOADING_TEXT "Loading"

class LoadWidget : public QLabel
{
    Q_OBJECT
public:
    explicit LoadWidget(QWidget* parent = nullptr, quint8 opacity = 90);

    void activate();
    void stop();

private slots:
    void timeOut();

private:
    QTimer* loadT;
    quint8 dotsCount{0};
};

#endif // LOADWIDGET_H
