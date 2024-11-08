#ifndef DATA_H
#define DATA_H

#include <QString>
#include <QFile>

enum DataType
{
    Message,
    Info,
    Login,
    Registration
};

struct Data
{
    inline Data(const QString& text = "", const DataType type = Message)
        : text(text), type(type) {}

    Data& operator+(const QString& oth);

    QString text;
    DataType type;
};
