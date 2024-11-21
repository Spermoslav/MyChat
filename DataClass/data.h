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

void clearAccInfo();
void clearAdress();

void writeAccInfo(const QString& nick, const QString &pass);
void writeAdress(const QString& ip, const QString& port);

using InfoPair = std::optional<std::pair<QString, QString>>;

[[nodiscard]] InfoPair readAccInfo();
[[nodiscard]] InfoPair readAdress();

[[nodiscard]] std::pair<QString, QString> accMessageSplit(const QString &accData);

#endif // DATA_H
