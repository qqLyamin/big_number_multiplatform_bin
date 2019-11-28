#include "bignumber.h"
#include <QDebug>
#include <iostream>
#include <math.h>


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

void divide( QString & incomeNumber ) {
    int last = incomeNumber.length();
    QString devide = "";
    QString answer = "";
    bool isOverloaded = false;

    for (int i = 0; i < last; ++i) {
        int a = incomeNumber[i].digitValue();
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

    incomeNumber = answer;
}

ulonglong fromBinToDecimal( const QString & incomeNumber ) {
    ulonglong value = 0;

    int degree = incomeNumber.length() - 1;
    for (int i = 0; i <= degree; ++i) {
        if (incomeNumber[i] == '1') {
            value += pow(2, degree - i);
        }
    }
    return value;
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

    QString binaryRow = "";
    while (incomeCopy != '0') {
        int i = 0;
        while (i < SIZE_OF_POINTER * 8) {

            if (even(incomeCopy)) {
                binaryRow += "0";
                divide(incomeCopy);
            } else {
                binaryRow += "1";
                incomeCopy[incomeCopy.length() - 1] = static_cast<char>(((incomeCopy[incomeCopy.length() - 1].digitValue() - 1) + 48));
                divide(incomeCopy);
            }
            if (incomeCopy == '0') break;
            i++;
        }

        arr.push_back(fromBinToDecimal(binaryRow));
        binaryRow = "";
    }
}

bigNumber & bigNumber::operator+(const bigNumber & other)
{
    if (this->isTrash() || other.isTrash()) {
        if (other.isTrash() && !this->isTrash()) return *this;
        if (!other.isTrash() && this->isTrash()) {
            this->arr = other.arr;
            this->Trash = other.Trash;
            this->Negative = other.Negative;
            this->arrStrBinary = other.arrStrBinary;
        }
        if (other.isTrash() && this->isTrash()) {
            this->arr.clear();
            this->arr.push_back(0);
            this->Negative = false;
            this->Trash = Negative;
            this->arrStrBinary.clear();
            this->arrStrBinary.push_back("0");
        }
    }

    //negative or positive answer
    if (this->isPositive() && other.isNegative()) {
        if (*this > other || (*this &= other)) {
            // do nothing
        } else {
            this->setNegative();
        }
    }
    if (this->isNegative() && other.isPositive()) {
        if (*this > other || (*this &= other)) {
            // do nothing
        } else {
            this->setPositive();
        }
    }

    int overloaded = 0;
    int i = 0;

    while (arr[i] != 0 && other.arr[i] != 0) {
        if (this->isPositive() == other.isPositive()) { //если номера одного знака, то нам плевать какой больше

            if (SIZE_OF_POINTER == 4) {

                unsigned long THIS;
                if (i < arr.size()) {
                    THIS = arr[i];
                } else {
                    THIS = 0;
                }

                unsigned long OTHER;
                if (i < other.arr.size()) {
                    OTHER = other.arr[i];
                } else {
                    OTHER = 0;
                }

                if (MAX_INT - THIS > OTHER) {

                    if (i <= arr.size()) {
                        if (overloaded) {
                            arr[i] = THIS + OTHER + 1;
                            overloaded = 0;
                        } else {
                            arr[i] = THIS + OTHER;
                        }
                    } else {
                        if (overloaded) {
                            arr.push_back(THIS + OTHER + 1);
                            overloaded = 0;
                        } else {
                            arr.push_back(THIS + OTHER);
                        }
                    }
                } else if (MAX_INT - THIS == OTHER && !overloaded) {
                    if (i <= arr.size()) {
                        arr[i] = MAX_INT;
                    } else {
                        arr.push_back(MAX_INT);
                    }
                } else {
                    if (i <= arr.size()) {
                        if (other.arr.size() > i) {
                            arr[i] = OTHER - (MAX_INT - THIS) - 1;
                            overloaded = 1;
                        } else {
                            arr[i] = OTHER - (MAX_INT - THIS);
                            overloaded = 1;
                        }
                    } else {
                        arr.push_back(OTHER - (MAX_INT - THIS) - 1);
                        overloaded = 1;
                    }
                }

            } else if (SIZE_OF_POINTER == 8) {

                if (MAX_ULONGLONG - arr[i] > other.arr[i]) {
                    if (overloaded) {
                        arr[i] = arr[i] + other.arr[i] + 1;
                        overloaded = 0;
                    } else {
                        arr[i] = arr[i] + other.arr[i];
                    }
                } else if (MAX_ULONGLONG - arr[i] == other.arr[i]) {
                    arr[i] = MAX_ULONGLONG;
                } else {
                    arr[i] = other.arr[i] - (MAX_ULONGLONG - arr[i]) - 1;
                    overloaded = 1;
                }

            }

            i++;
            continue;

        }

        if (*this ->* other) { //выясняем какой больше по модулю

            if (arr[i] > other.arr[i]) {
                arr[i] = arr[i] - other.arr[i];
            } else if (arr[i] == other.arr[i]) {
                arr[i] = 0;
            } else {
                arr[i + 1] -= 1;
                if (SIZE_OF_POINTER == 4) {
                    arr[i] = MAX_INT - other.arr[i] + arr[i];
                } else if (SIZE_OF_POINTER == 8) {
                    arr[i] = MAX_ULONGLONG - other.arr[i] + arr[i];
                }
            }

        } else if (*this == other) {

            this->arr.clear();
            this->arr.push_back(0);
            this->setPositive();
            this->arrStrBinary.clear();
            this->arrStrBinary.push_back("0");

        } else { // если other больше по модулю

            bigNumber otherCopy = other;
            if (otherCopy.arr[i] > arr[i]) {
                arr[i] = otherCopy.arr[i] - arr[i];
            } else if (otherCopy.arr[i] == arr[i]) {
                arr[i] = 0;
            } else {
                otherCopy.arr[i + 1] -= 1;
                if (SIZE_OF_POINTER == 4) {
                    arr[i] = MAX_INT - arr[i] + otherCopy.arr[i];
                } else if (SIZE_OF_POINTER == 8) {
                    arr[i] = MAX_ULONGLONG - arr[i] + otherCopy.arr[i] ;
                }
            }

        }
        i++;
    }

    if (overloaded) arr.push_back(1);
    return * this;
}

bigNumber & bigNumber::operator=(const bigNumber & other)
{
    Negative = other.Negative;
    this->arr = other.arr;
    return * this;
}

bool bigNumber::operator->*(const bigNumber & other)//thats MOD operator >
{
    if (this->arr.size() == other.arr.size()) {
        for (quint i = arr.size(); i > 0; --i) {
            if ( arr[i - 1] != other.arr[i - 1] ) {
                return arr[i - 1] > other.arr[i - 1];
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
        for (quint i = arr.size() - 1; i >= 0; --i) {
            if (arr[i] != other.arr[i]) {
                return arr[i] < other.arr[i];
            }
        }
    }

    if (this->arr.size() == other.arr.size() && this->isPositive() && other.isPositive()) {
        for (quint i = arr.size() - 1; i >= 0; --i) {
            if (arr[i] != other.arr[i]) {
                return arr[i] > other.arr[i];
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

bool bigNumber::isTrash() const
{
    return Trash;
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
        for (int j = 0; j < number.arrStrBinary[i].length(); ++j) {
            OU << (number.arrStrBinary[i])[j].toLatin1();
        }
    }
    return OU;
}

bool operator==(const bigNumber &left, const bigNumber &right)
{
    //decimal ==
    if (left.Negative != right.Negative) return false;
    if (left.arr.size() != right.arr.size()) return false;

    for (int i = left.arr.size() - 1; i >= 0; --i) {
        if (left.arr[i] != right.arr[i]) {
            return false;
        }
    }

    return true;

    //binary test
//    if (left.Negative != right.Negative) return false;
//    if (left.arr.size() != right.arr.size()) return false;
//    QString leftStr = "";
//    QString rightStr = "";
//    for (int i = left.arrStrBinary.size() - 1; i >= 0; --i) {
//        if (left.arr[i] != right.arr[i]) {
//            return false;
//        }
//    }
//    return true;
}

bool operator&=(const bigNumber &left, const bigNumber &right)
{
    if (left.arr.size() != right.arr.size()) return false;

    for (int i = left.arr.size() - 1; i >= 0; --i) {
        if (left.arr[i] != right.arr[i]) {
            return false;
        }
    }

    return true;
}
