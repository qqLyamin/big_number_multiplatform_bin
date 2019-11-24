#include "bignumber.h"
#include <QDebug>
#include <iostream>

bool even( const QString & incomeNumber ) {
    int last = incomeNumber.length() - 1;
    if ( incomeNumber[last].isNumber() ) {
        if ( incomeNumber[last].digitValue() == 1 ||
             incomeNumber[last].digitValue() == 3 ||
             incomeNumber[last].digitValue() == 5 ||
             incomeNumber[last].digitValue() == 7 ||
             incomeNumber[last].digitValue() == 9 ) {
            return false;
        } else {
            return true;
        }
    }
}

QString divide( const QString & incomeNumber ) {
    int last = incomeNumber.length();
    QString incomeCopy = incomeNumber;
    QString devide = "";
    QString answer = "";
    bool isOverloaded = false;

    for (int i = 0; i < last; ++i) {
        int a = incomeCopy[i].digitValue();
        if (devide.length() < 2) {
            devide += (char)(a + 48);
        }
        if (devide.toInt() == 0 && a == 0) {
            answer += (char)(48);
            devide = "";
            continue;
        }
        if (devide.toInt() >= 2) {
            answer += (char)(devide.toInt() / 2 + 48);
            if (devide.toInt() % 2 != 0) {
                devide = "1";
            } else {
                devide = "";
            }
        } else {
            if (answer != "") {
                answer += "0";
            }
        }
    }

    return answer;
}

bigNumber::bigNumber(const QString & income)
{
    bool isValid = true;
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
    QString incomeCopy = income;
    if (isValid && this->isNegative()) incomeCopy.remove(0, 1);

    QString tmp = "";
    QString divideTmp = "";
    if (isValid) {
        int i = 0;
        while (incomeCopy.length() > 1 || (incomeCopy[0] != 1 || incomeCopy[0] != 0)) {
            if (i == SIZE_OF_POINTER * 8) {
                invert_string(tmp);
                arr.push_back(tmp);
                i = 0;
                tmp = "";
            }
            if (even(incomeCopy)) {
                tmp += "0";
                incomeCopy = divide(incomeCopy);
            } else {
                tmp += "1";
                incomeCopy[incomeCopy.length() - 1] = (char)((incomeCopy[incomeCopy.length() - 1].digitValue() - 1) + 48);
                incomeCopy = divide(incomeCopy);
            }
            if (incomeCopy.length() == 1 && incomeCopy[0] == 48) break;
            i++;
        }
        invert_string(tmp);
        arr.push_back(tmp);
    }
}


//bigNumber & bigNumber::operator+(const bigNumber & other)
//{
//    int saturation = 0;
//    int negativeSaturation = 0;
//    short maxSize;
//    bool isNegativeAnswer = false;
//    maxSize = arr.size() > other.arr.size() ? arr.size() : other.arr.size();

//    if (this->isPositive() && other.isPositive()) {
//        for ( int i = 0 ; i < maxSize; ++i ) {
//            short tmp = arr[i];
//            this->arr[i] = (arr[i] + other.arr[i] + saturation) % 10000;
//            saturation = (tmp + other.arr[i] + saturation) / 10000;
//            isNegativeAnswer = false;
//        }
//    }

//    if (this->isNegative() && other.isNegative()) {
//        for ( int i = 0 ; i < maxSize; ++i ) {
//            short tmp = arr[i];
//            this->arr[i] = (arr[i] + other.arr[i] + saturation) % 10000;
//            saturation = (tmp + other.arr[i] + saturation) / 10000;
//            isNegativeAnswer = true;
//        }
//    }

//    if (this->isPositive() && other.isNegative()) {
//        bigNumber tmp = other;
//        for ( int i = 0 ; i < maxSize; ++i ) {
//            if (*this ->* tmp) { //вычитаем всегда ИЗ arr[i]
//                if (arr[i] > tmp.arr[i]) { //eсли мы больше ВЫЧИТАЕМОГО
//                    arr[i] = arr[i] - tmp.arr[i];
//                } else if (arr[i] == tmp.arr[i]) {
//                    arr[i] = 0;
//                } else if (tmp.arr[i] > arr[i]) { //Если армия врага больше нашей
//                    arr[i] = arr[i] + 10000 - tmp.arr[i];
//                    tmp.arr[i + 1] += 1;
//                }
//            } else { //вычитаем всегда ИЗ tmp
//                if (tmp.arr[i] > arr[i]) { //eсли мы больше ВЫЧИТАЕМОГО
//                    arr[i] = tmp.arr[i] - arr[i];
//                } else if (arr[i] == tmp.arr[i]) {
//                    arr[i] = 0;
//                } else if (tmp.arr[i] > arr[i]) { //Если армия врага больше нашей
//                    arr[i] = tmp.arr[i] + 10000 - arr[i];
//                    arr[i + 1] += 1;
//                }
//                isNegativeAnswer = true;
//            }
//        }
//    }

//    if (this->isNegative() && other.isPositive()) {
//        bigNumber tmp = other;
//        for ( int i = 0 ; i < maxSize; ++i ) {
//            if (*this ->* tmp) { //вычитаем всегда ИЗ arr[i]
//                if (arr[i] > tmp.arr[i]) { //eсли мы больше ВЫЧИТАЕМОГО
//                    arr[i] = arr[i] - tmp.arr[i];
//                } else if (arr[i] == tmp.arr[i]) {
//                    arr[i] = 0;
//                } else if (tmp.arr[i] > arr[i]) { //Если армия врага больше нашей
//                    arr[i] = arr[i] + 10000 - tmp.arr[i];
//                    tmp.arr[i + 1] += 1;
//                }
//                isNegativeAnswer = true;
//            } else { //вычитаем всегда ИЗ tmp
//                if (tmp.arr[i] > arr[i]) { //eсли мы больше ВЫЧИТАЕМОГО
//                    arr[i] = tmp.arr[i] - arr[i];
//                } else if (arr[i] == tmp.arr[i]) {
//                    arr[i] = 0;
//                } else if (arr[i] > tmp.arr[i]) { //Если армия врага больше нашей
//                    arr[i] = tmp.arr[i] + 10000 - arr[i];
//                    arr[i + 1] += 1;
//                }
//            }
//        }
//    }

//    if (this->arr.size() == 1 && this->arr[0] == 0) isNegativeAnswer = false;

//    if (isNegativeAnswer) {
//        this->setNegative();
//    } else {
//        this->setPositive();
//    }

//    return * this;
//}

bigNumber & bigNumber::operator=(const bigNumber & other)
{
    Negative = other.Negative;
    arr[0] = other.arr[0];
    for (int i = 1; i < other.arr.size(); ++i) {
        arr.push_back(other.arr[i]);
    }
    return * this;
}

bool bigNumber::operator->*(const bigNumber & other)//thats MOD operator >
{
    if (this->arr.size() == other.arr.size()) {
        for (int i = arr.size(); i > 0; --i) {
            if (i == arr.size() && this->arr[i].length() > other.arr[i].length()) return true;
            if (i == arr.size() && this->arr[i].length() < other.arr[i].length()) return false;

            if (this->arr[i].length() == other.arr[i].length()) {
                for (int j = arr[i].length() - 1; j >= 0; --j) {
                    if (arr[i][j] == other.arr[i][j]) continue;
                    if (arr[i][j] > other.arr[i][j]) return true;
                    if (arr[i][j] < other.arr[i][j]) return false;
                }
            }
        }
        return false;
    } else {
        return this->arr.size() > other.arr.size();
    }
}

bool bigNumber::operator>(const bigNumber &other)
{
    if (this->arr.size() > other.arr.size() && this->isPositive() && other.isPositive()) return true;
    if (this->arr.size() < other.arr.size() && this->isPositive() && other.isPositive()) return false;
    if (this->arr.size() > other.arr.size() && this->isNegative() && other.isNegative()) return false;
    if (this->arr.size() < other.arr.size() && this->isNegative() && other.isNegative()) return true;

    if (this->isNegative() && other.isPositive()) return false;
    if (this->isPositive() && other.isNegative()) return true;


    if (this->arr.size() == other.arr.size() && this->isNegative() && other.isNegative()) {
        for (int i = arr.size(); i >= 0; --i) {
            if (i == arr.size() && this->arr[0].length() > other.arr[0].length()) return false;
            if (i == arr.size() && this->arr[0].length() < other.arr[0].length()) return true;

            if (this->arr[0].length() == other.arr[0].length()) {
                for (int j = 0; j < arr[i].length(); ++j) {
                    if (this->arr[i][j] == this->arr[i][j]) continue;
                    if (this->arr[i][j] > this->arr[i][j]) return false;
                    if (this->arr[i][j] < this->arr[i][j]) return true;
                }
            }
        }
    }

    if (this->arr.size() == other.arr.size() && this->isPositive() && other.isPositive()) {
        for (int i = arr.size() - 1; i >= 0; --i) {
            if (i == arr.size() && this->arr[0].length() > other.arr[0].length()) return true;
            if (i == arr.size() && this->arr[0].length() < other.arr[0].length()) return false;

            if (this->arr[0].length() == other.arr[0].length()) {
                for (int j = 0; j < arr[i].length(); ++j) {
                    if (this->arr[i][j] == this->arr[i][j]) continue;
                    if (this->arr[i][j] > this->arr[i][j]) return true;
                    if (this->arr[i][j] < this->arr[i][j]) return false;
                }
            }
        }
    }
}

quint bigNumber::getSize() const
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

std::ostream& operator<< (std::ostream &OU, const bigNumber & number){
    if (number.isNegative()) OU << "-";
    for (int i = number.arr.size() - 1; i >= 0; --i) {
        for (int j = 0; j < number.arr[i].length(); ++j) {
            OU << (number.arr[i])[j].toLatin1();
        }
    }
    return OU;
}

bool operator==(const bigNumber &left, const bigNumber &right)
{
    if (left.Negative != right.Negative) return false;
    if (left.arr.size() != right.arr.size()) return false;

    for (int i = left.arr.size() - 1; i >= 0; --i) {
        if (i == 0 && left.arr[i].length() != right.arr[i].length()) return false;

        for (int j = 0; j < left.arr[i].length() - 1; ++j) {
            if (left.arr[i][j] != left.arr[i][j]) return false;
        }
    }

    return true;
}
