#include "data.h"
#include <QDebug>

Data &Data::operator+(const QString &oth) {
    text += oth;
    return *this;
}

void writeAccInfo(const QString &nick, const QString& pass) {
    QFile dataF("Data/clientdata.cfg");
    dataF.open(QIODevice::ReadOnly | QIODevice::Text);
    QStringList sl = QString::fromLocal8Bit(dataF.readAll()).split(' ');

    dataF.close();
    dataF.open(QIODevice::WriteOnly | QIODevice::Text);

    if(sl.size() == 1) {
        dataF.write(QString(nick + ' ' + pass + ' ').toLocal8Bit());
    }
    else if(sl.size() == 3) {
        dataF.write(QString(nick + ' ' + pass + ' ' + sl[1] + ' ' + sl[2]).toLocal8Bit());
    }
    else if(sl.size() == 4) {
        dataF.write(QString(nick + ' ' + pass + ' ' + sl[2] + ' ' + sl[3]).toLocal8Bit());
    }
    else {
        qDebug() << __FUNCTION__ << "sl.size > 2";
    }
    dataF.flush();
}

void writeAdress(const QString &ip, const QString &port)
{
    QFile dataF("Data/clientdata.cfg");
    dataF.open(QIODevice::ReadOnly | QIODevice::Text);
    QStringList sl = QString::fromLocal8Bit(dataF.readAll()).split(' ');

    dataF.close();
    dataF.open(QIODevice::WriteOnly | QIODevice::Text);

    if(sl.size() < 4) {
        dataF.write(QString(' ' + ip + ' ' + port).toLocal8Bit());
    }
    else if(sl.size() == 4) {
        dataF.write(QString(sl[0] + ' ' + sl[1] + ' ' + ip + ' ' + port).toLocal8Bit());
    }
    else {
        qDebug() << __FUNCTION__ << "sl.size > 2";
    }
    dataF.flush();
}

InfoPair readAccInfo() {
    QFile dataF("Data/clientdata.cfg");
    dataF.open(QIODevice::ReadOnly | QIODevice::Text);
    QStringList sl = QString::fromLocal8Bit(dataF.readAll()).split(' ');

    if(sl[0] == "") return std::nullopt;

    return InfoPair({sl[0], sl[1]});
}

InfoPair readAdress()
{
    QFile dataF("Data/clientdata.cfg");
    dataF.open(QIODevice::ReadOnly | QIODevice::Text);
    QStringList sl = QString::fromLocal8Bit(dataF.readAll()).split(' ');

    if (sl.size() < 4) return std::nullopt;
    return InfoPair({sl[2], sl[3]});
}

void clearAccInfo()
{
    QFile dataF("Data/clientdata.cfg");
    dataF.open(QIODevice::ReadOnly | QIODevice::Text);
    QStringList sl = QString::fromLocal8Bit(dataF.readAll()).split(' ');

    dataF.close();
    if(sl[0] == "") return;

    dataF.open(QIODevice::WriteOnly | QIODevice::Text);

    if(sl.size() == 2) {
        dataF.write("");
    }
    else {
        dataF.write(QString(' ' + sl[2] + ' ' + sl[3]).toLocal8Bit());
    }
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

void clearAdress()
{
    QFile dataF("Data/clientdata.cfg");
    dataF.open(QIODevice::ReadOnly | QIODevice::Text);
    QStringList sl = QString::fromLocal8Bit(dataF.readAll()).split(' ');

    dataF.close();
    if(sl.size() == 1) return;

    dataF.open(QIODevice::WriteOnly | QIODevice::Text);

    dataF.write(QString(sl[0] + ' ' + sl[1]).toLocal8Bit());

    dataF.close();
}
