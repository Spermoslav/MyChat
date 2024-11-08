#include "data.h"

Data &Data::operator+(const QString &oth) {
    text += oth;
    return *this;
}
