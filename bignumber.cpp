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

    QString tmp = "";
    QString divideTmp = "";
    if (isValid) {
        int i = 0;
        while (incomeCopy.length() > 1 || (incomeCopy[0] != 1 || incomeCopy[0] != 0)) {
            if (i == SIZE_OF_POINTER * 8) {
                invert_string(tmp);
                arrStrBinary.push_back(tmp);
                ulonglong temp = fromBinToDecimal(tmp);
                arr.push_back(temp);
                i = 0;
                tmp = "";
            }
            if (even(incomeCopy)) {
                tmp += "0";
                incomeCopy = divide(incomeCopy);
            } else {
                tmp += "1";
                incomeCopy[incomeCopy.length() - 1] = static_cast<char>(((incomeCopy[incomeCopy.length() - 1].digitValue() - 1) + 48));
                incomeCopy = divide(incomeCopy);
            }
            if (incomeCopy.length() == 1 && incomeCopy[0] == 48) break;
            i++;
        }
        invert_string(tmp);
        arrStrBinary.push_back(tmp);
        ulonglong temp = fromBinToDecimal(tmp);
        arr.push_back(temp);
    } else {
        Trash = true;
        arr.push_back(0);
        arrStrBinary.push_back("0");
        Negative = false;
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
    ulonglong saturation = 0;
    ulonglong negativeSaturation = 0;
    quint maxSize;
    bigNumber otherCopy = other;

    bool isNegativeAnswer = false;
    maxSize = arr.size() > other.arr.size() ? arr.size() : other.arr.size();

    if (this->isPositive() && other.isPositive()) {
        for ( quint i = 0 ; i < maxSize; ++i ) {
            int step = 1;
            ulonglong tmp = 0;
            while (step < 20) {
                ulonglong degree = static_cast<ulonglong>(pow(10, step));
                ulonglong iter = ((arr[i] % degree - arr[i] % (degree / 10)) + (other.arr[i] % degree - other.arr[i] % (degree / 10))) / (degree / 10);

                if (iter > 9) {
                    if (step == 19 && iter % 10 == 0) {
                        saturation = 1; break;
                    }
                    tmp += iter % 10 * (degree / 10) + saturation * (degree / 10);
                    saturation = 1;
                } else {
                    tmp += iter * (degree / 10) + saturation * (degree / 10);
                    saturation = 0;
                }
                step++;
            }
            this->arr[i] = tmp;
        }
        isNegativeAnswer = false;
    }

    if (this->isNegative() && other.isNegative()) {
        for ( quint i = 0 ; i < maxSize; ++i ) {
            int step = 1;
            ulonglong tmp = 0;
            while (step < 20) {
                ulonglong degree = static_cast<ulonglong>(pow(10, step));
                ulonglong iter = ((arr[i] % degree - arr[i] % (degree / 10)) + (other.arr[i] % degree - other.arr[i] % (degree / 10))) / (degree / 10);

                if (iter > 9) {
                    if (step == 19 && iter % 10 == 0) {
                        saturation = 1; break;
                    }
                    tmp += iter % 10 * (degree / 10) + saturation * (degree / 10);
                    saturation = 1;
                } else {
                    tmp += iter * (degree / 10) + saturation * (degree / 10);
                    saturation = 0;
                }
                step++;
            }
            this->arr[i] = tmp;
        }
        isNegativeAnswer = true;
    }

    if (this->isPositive() && other.isNegative()) {
        int step = 1;
        ulonglong tmp = 0;
        if (*this ->* otherCopy) {
            for ( quint i = 0 ; i < maxSize; ++i ) {
                if (arr[i] < otherCopy.arr[i]) {
                    if (SIZE_OF_POINTER == 4) {
                        tmp = 4294967294 - otherCopy.arr[i] + arr[i] + 1;
                    }
                    if (SIZE_OF_POINTER == 8) {
                        tmp = 18446744073709551614 - otherCopy.arr[i] + arr[i] + 1;
                    }
                    arr[i + 1] -= 1;
                }

                if (arr[i] > otherCopy.arr[i]) {
                    tmp = arr[i] - otherCopy.arr[i];
                }

                if (arr[i] == otherCopy.arr[i]) {
                    tmp = 0;
                }
                this->arr[i] = tmp;
            }
            isNegativeAnswer = false;
        } else if (otherCopy &= *this) {
            isNegativeAnswer = false;
            this->arr.clear();
            this->arr.push_back(0);
        } else {
            for ( quint i = 0 ; i < maxSize; ++i ) {
                if (arr[i] > otherCopy.arr[i]) {
                    if (SIZE_OF_POINTER == 4) {
                        tmp = 4294967294 - arr[i] + otherCopy.arr[i] + 1;
                    }
                    if (SIZE_OF_POINTER == 8) {
                        tmp = 18446744073709551614 - arr[i] + otherCopy.arr[i] + 1;
                    }
                    otherCopy.arr[i + 1] -= 1;
                }

                if (arr[i] < otherCopy.arr[i]) {
                    tmp = otherCopy.arr[i] - arr[i];
                }

                if (arr[i] == otherCopy.arr[i]) {
                    tmp = 0;
                }
                this->arr[i] = tmp;
            }
            isNegativeAnswer = true;
        }
    }


    if (this->isNegative() && other.isPositive()) {
            int step = 1;
            ulonglong tmp = 0;
            if (*this ->* otherCopy) {
                for ( quint i = 0 ; i < maxSize; ++i ) {
                    if (arr[i] < otherCopy.arr[i]) {
                        if (SIZE_OF_POINTER == 4) {
                            tmp = 4294967294 - otherCopy.arr[i] + arr[i] + 1;
                        }
                        if (SIZE_OF_POINTER == 8) {
                            tmp = 18446744073709551614 - otherCopy.arr[i] + arr[i] + 1;
                        }
                        arr[i + 1] -= 1;
                    }

                    if (arr[i] > otherCopy.arr[i]) {
                        tmp = arr[i] - otherCopy.arr[i];
                    }

                    if (arr[i] == otherCopy.arr[i]) {
                        tmp = 0;
                    }
                    this->arr[i] = tmp;
                }
                isNegativeAnswer = true;
            } else if (otherCopy &= *this) {
                isNegativeAnswer = false;
                this->arr.clear();
                this->arr.push_back(0);
            } else {
                for ( quint i = 0 ; i < maxSize; ++i ) {
                    if (arr[i] > otherCopy.arr[i]) {
                        if (SIZE_OF_POINTER == 4) {
                            tmp = 4294967294 - arr[i] + otherCopy.arr[i] + 1;
                        }
                        if (SIZE_OF_POINTER == 8) {
                            tmp = 18446744073709551614 - arr[i] + otherCopy.arr[i] + 1;
                        }
                        otherCopy.arr[i + 1] -= 1;
                    }

                    if (arr[i] < otherCopy.arr[i]) {
                        tmp = otherCopy.arr[i] - arr[i];
                    }

                    if (arr[i] == otherCopy.arr[i]) {
                        tmp = 0;
                    }
                    this->arr[i] = tmp;
                }
                isNegativeAnswer = false;
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
    if (left.Negative != right.Negative) return false;
    if (left.arr.size() != right.arr.size()) return false;

    for (int i = left.arr.size() - 1; i >= 0; --i) {
        if (left.arr[i] != right.arr[i]) {
            return false;
        }
    }

    return true;
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
