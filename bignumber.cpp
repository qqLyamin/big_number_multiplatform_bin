#include "bignumber.h"
#include <QDebug>

bigNumber::bigNumber(const QString & income)
{
    bool isValid = true;
    //is valid checking
    if (income[0] == '0' || (income[0] == '-' && income[1] == '0')) isValid = false;
    if (isValid && income[0] == '-') this->setNegative();
    if (isValid) {
        for (int i = 0; i < income.length(); ++i) {
            if (!income[i].isNumber()) {
                isValid = false;
                if (i == 0 && income[0] == '-') isValid = true;
            }
        }
    }

    if (isValid) {
        for (int i = 0; i < income.length(); ++i) {

        }
    }
}

bigNumber & bigNumber::operator+(const bigNumber & other)
{
    int saturation = 0;
    int negativeSaturation = 0;
    short maxSize;
    bool isNegativeAnswer = false;
    maxSize = arr.size() > other.arr.size() ? arr.size() : other.arr.size();

    if (this->isPositive() && other.isPositive()) {
        for ( int i = 0 ; i < maxSize; ++i ) {
            short tmp = arr[i];
            this->arr[i] = (arr[i] + other.arr[i] + saturation) % 10000;
            saturation = (tmp + other.arr[i] + saturation) / 10000;
            isNegativeAnswer = false;
        }
    }

    if (this->isNegative() && other.isNegative()) {
        for ( int i = 0 ; i < maxSize; ++i ) {
            short tmp = arr[i];
            this->arr[i] = (arr[i] + other.arr[i] + saturation) % 10000;
            saturation = (tmp + other.arr[i] + saturation) / 10000;
            isNegativeAnswer = true;
        }
    }

    if (this->isPositive() && other.isNegative()) {
        bigNumber tmp = other;
        for ( int i = 0 ; i < maxSize; ++i ) {
            if (*this ->* tmp) { //вычитаем всегда ИЗ arr[i]
                if (arr[i] > tmp.arr[i]) { //eсли мы больше ВЫЧИТАЕМОГО
                    arr[i] = arr[i] - tmp.arr[i];
                } else if (arr[i] == tmp.arr[i]) {
                    arr[i] = 0;
                } else if (tmp.arr[i] > arr[i]) { //Если армия врага больше нашей
                    arr[i] = arr[i] + 10000 - tmp.arr[i];
                    tmp.arr[i + 1] += 1;
                }
            } else { //вычитаем всегда ИЗ tmp
                if (tmp.arr[i] > arr[i]) { //eсли мы больше ВЫЧИТАЕМОГО
                    arr[i] = tmp.arr[i] - arr[i];
                } else if (arr[i] == tmp.arr[i]) {
                    arr[i] = 0;
                } else if (tmp.arr[i] > arr[i]) { //Если армия врага больше нашей
                    arr[i] = tmp.arr[i] + 10000 - arr[i];
                    arr[i + 1] += 1;
                }
                isNegativeAnswer = true;
            }
        }
    }

    if (this->isNegative() && other.isPositive()) {
        bigNumber tmp = other;
        for ( int i = 0 ; i < maxSize; ++i ) {
            if (*this ->* tmp) { //вычитаем всегда ИЗ arr[i]
                if (arr[i] > tmp.arr[i]) { //eсли мы больше ВЫЧИТАЕМОГО
                    arr[i] = arr[i] - tmp.arr[i];
                } else if (arr[i] == tmp.arr[i]) {
                    arr[i] = 0;
                } else if (tmp.arr[i] > arr[i]) { //Если армия врага больше нашей
                    arr[i] = arr[i] + 10000 - tmp.arr[i];
                    tmp.arr[i + 1] += 1;
                }
                isNegativeAnswer = true;
            } else { //вычитаем всегда ИЗ tmp
                if (tmp.arr[i] > arr[i]) { //eсли мы больше ВЫЧИТАЕМОГО
                    arr[i] = tmp.arr[i] - arr[i];
                } else if (arr[i] == tmp.arr[i]) {
                    arr[i] = 0;
                } else if (arr[i] > tmp.arr[i]) { //Если армия врага больше нашей
                    arr[i] = tmp.arr[i] + 10000 - arr[i];
                    arr[i + 1] += 1;
                }
            }
        }
    }

    if (this->arr.size() == 1 && this->arr[0] == 0) isNegativeAnswer = false;

    if (isNegativeAnswer) {
        this->setNegative();
    } else {
        this->setPositive();
    }

    return * this;
}

bigNumber & bigNumber::operator=(const bigNumber & other)
{
    Negative = other.Negative;
    for (ulonglong i = 0; i < other.arr.size(); ++i) {
        arr.push_back(other.arr[i]);
    }
    return * this;
}

bool bigNumber::operator->*(const bigNumber & other)//thats MOD operator >
{
    if (this->arr.size() == other.arr.size()) {
        for (ulonglong i = arr.size(); i > 0; --i) {
            if (this->arr[i - 1] == other.arr[i - 1]) continue;
            return this->arr[i - 1] > other.arr[i - 1];
        }
        return false;
    } else {
        return this->arr.size() > other.arr.size();
    }
}

bool bigNumber::operator>(const bigNumber &other)
{

    if (this->arr.size() > other.arr.size() && this->isPositive() && other.isPositive()) return true;
    if (this->arr.size() > other.arr.size() && this->isNegative() && other.isPositive()) return false;
    if (this->arr.size() < other.arr.size() && this->isPositive() && other.isPositive()) return false;
    if (this->arr.size() < other.arr.size() && this->isPositive() && other.isNegative()) return true;


    if (this->arr.size() == other.arr.size() && this->isNegative() && other.isNegative()) {
        if (this->arr[arr.size() - 1] > other.arr[arr.size() - 1])
            return false;
        return true;
    }

    if (this->arr.size() == other.arr.size() && this->isPositive() && other.isPositive()) {
        if (this->arr[arr.size() - 1] > other.arr[arr.size() - 1])
            return true;
        return false;
    }
}

ulonglong bigNumber::getSize() const
{
    return arr.size();
}

bool bigNumber::isNegative() const
{
    return Negative;
}

bool bigNumber::isPositive() const
{
    return !Negative;
}

void bigNumber::setNegative()
{
    this->Negative = true;
}

void bigNumber::setPositive()
{
    this->Negative = false;
}

std::ostream& operator<< (std::ostream &out, const bigNumber & number) {
    if (number.isNegative()) out << "-";
    out << number.arr[number.arr.size() - 1];
    for (int i = number.arr.size() - 2; i >= 0; --i) {
        if (number.arr[i] < 1000) {
            out << "0";
        }
        if (number.arr[i] < 100) {
            out << "0";
        }
        if (number.arr[i] < 10) {
            out << "0";
        }
        out << number.arr[i];
    }
    return out;
}

bool operator==(const bigNumber &left, const bigNumber &right)
{
    if (left.arr.size() == right.arr.size()) {
        for (int i = 0; i < right.arr.size(); ++i) {
            if (left.arr[i] != right.arr[i]) return false;
        }
    } else {
        return false;
    }

    return (left.isPositive() && right.isPositive()) || (left.isNegative() && right.isNegative());
}
