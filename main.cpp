#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.resize(350, 650);
    w.setStyleSheet("background-color: rgb(0, 191, 255);"
                    "border: 1px solid black;"
                    "border-radius: 4px;");
    w.show();
    return a.exec();
}
