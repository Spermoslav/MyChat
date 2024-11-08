#include "data.h"

Data &Data::operator+(const QString &oth) {
    text += oth;
    return *this;
}

void writeAccLog(const QString &nick) {
    QFile dataF("Data/clientdata.cfg");
    dataF.open(QIODevice::WriteOnly | QIODevice::Text);
    dataF.write(QString(nick).toLocal8Bit());
}

QString readAccLog() {
    QFile dataF("Data/clientdata.cfg");
    dataF.open(QIODevice::ReadOnly | QIODevice::Text);
    return QString::fromLocal8Bit(dataF.readAll());
}

void clearAccLog() {
    QFile dataF("Data/clientdata.cfg");
    dataF.open(QIODevice::WriteOnly | QIODevice::Text);
    dataF.write("");
    dataF.close();
}

std::pair<QString, QString> accMessageSplit(const QString &accData)
{
    if(accData.indexOf(' ') == -1) return std::pair<QString, QString> (accData, "-1");

    QString nick = "";
    QString mess = "";
    qsizetype i = 0;

    while(accData[i] != ' ') {
        nick += accData[i];
        ++i;
    }

    ++i;
    while(i != accData.size()) {
        mess += accData[i];
        ++i;
    }

    return std::pair<QString, QString> (nick, mess);
}
