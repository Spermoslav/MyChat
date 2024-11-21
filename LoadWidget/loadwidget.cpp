#include "loadwidget.h"

LoadWidget::LoadWidget(QWidget *parent, quint8 opacity)
    : QLabel(LW_LOADING_TEXT, parent),
      loadT(new QTimer(this))
{
    setStyleSheet("background-color: rgba(0, 0, 0, " + QString::number(opacity) + ");");

    loadT->setInterval(1000);
    connect(loadT, &QTimer::timeout, this, &LoadWidget::timeOut);
}

void LoadWidget::activate()
{
    show();
    loadT->start();
}

void LoadWidget::stop()
{
    loadT->stop();
    hide();
}

void LoadWidget::timeOut()
{
    if(dotsCount == 5){
        setText(LW_LOADING_TEXT);
        dotsCount = 0;
    }
    else {
        setText(text() + '.');
        dotsCount++;
    }
}
