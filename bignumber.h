#ifndef BIGNUMBER_H
#define BIGNUMBER_H

#include <QString>
#include <vector>

typedef unsigned int quint;
typedef unsigned long long ulonglong;

#define SIZE_OF_POINTER sizeof( * void )

template <typename T>
void invert_string( T & tmp );
bool mod2( const QString & );
void div2( const QString & incomeNumber );

class bigNumber
{
    std::vector<ulonglong> arr;
    bool Negative = false;
public:
    bigNumber(){
        arr.push_back( 0 );
    }
    bigNumber( const QString & income );

    bigNumber & operator+( const bigNumber & other );
    bigNumber & operator=( const bigNumber & other );
    bool operator->*( const bigNumber & other );//thats MOD operator >
    bool operator>( const bigNumber & other );

    friend bool operator==( const bigNumber & left, const bigNumber & right );
    friend std::ostream & operator<<( std::ostream &out, const bigNumber & number );

    ulonglong getSize() const;
    bool isNegative() const;
    bool isPositive() const;

    void setNegative();
    void setPositive();
};


bool mod2( const QString & incomeNumber ) {
    int last = incomeNumber.length() - 1;
    if ( incomeNumber[last].isNumber() ) {
        if ( incomeNumber[last].digitValue() == 1 ||
             incomeNumber[last].digitValue() == 3 ||
             incomeNumber[last].digitValue() == 5 ||
             incomeNumber[last].digitValue() == 7 ||
             incomeNumber[last].digitValue() == 9 ) {
            return true;
        } else {
            return false;
        }
    }
}

void div2( QString & incomeNumber ) {
    int last = incomeNumber.length() - 1;
    bool isOverloaded = false;
    for (int i = last; i >= 0; ++i) {
        switch (incomeNumber[i].digitValue()) {
            case 9 :  {
                    if (isOverloaded) {
                        incomeNumber[i] = '9';
                        isOverloaded = true;
                        break;
                    } else {
                        incomeNumber[i] = '4';
                        isOverloaded = true;
                        break;
                    }
            }

            case 8 :  {
                    if (isOverloaded) {
                        incomeNumber[i] = '9';
                        isOverloaded = false;
                        break;
                    } else {
                        incomeNumber[i] = '4';
                        isOverloaded = false;
                        break;
                    }
            }

            case 7 :  {
                    if (isOverloaded) {
                        incomeNumber[i] = '8';
                        isOverloaded = true;
                        break;
                    } else {
                        incomeNumber[i] = '3';
                        isOverloaded = true;
                        break;
                    }
            }

            case 6 :  {
                    if (isOverloaded) {
                        incomeNumber[i] = '8';
                        isOverloaded = false;
                        break;
                    } else {
                        incomeNumber[i] = '3';
                        isOverloaded = false;
                        break;
                    }
            }

            case 5 :  {
                    if (isOverloaded) {
                        incomeNumber[i] = '7';
                        isOverloaded = true;
                        break;
                    } else {
                        incomeNumber[i] = '2';
                        isOverloaded = true;
                        break;
                    }
            }

            case 4 :  {
                    if (isOverloaded) {
                        incomeNumber[i] = '7';
                        isOverloaded = false;
                        break;
                    } else {
                        incomeNumber[i] = '2';
                        isOverloaded = false;
                        break;
                    }
            }

            case 3 :  {
                    if (isOverloaded) {
                        incomeNumber[i] = '6';
                        isOverloaded = true;
                        break;
                    } else {
                        incomeNumber[i] = '1';
                        isOverloaded = true;
                        break;
                    }
            }

            case 2 :  {
                    if (isOverloaded) {
                        incomeNumber[i] = '6';
                        isOverloaded = false;
                        break;
                    } else {
                        incomeNumber[i] = '1';
                        isOverloaded = false;
                        break;
                    }
            }

            case 1 :  {
                    if (isOverloaded) {
                        incomeNumber[i] = '5';
                        isOverloaded = true;
                        break;
                    } else {
                        incomeNumber[i] = '0';
                        isOverloaded = true;
                        break;
                    }
            }

            case 0 :  {
                    if (isOverloaded) {
                        incomeNumber[i] = '5';
                        isOverloaded = false;
                        break;
                    } else {
                        incomeNumber[i] = '0';
                        isOverloaded = true;
                        break;
                    }
            }
        }
    }
}

template <typename T>
void invert_string( T & tmp ) {
    int size = tmp.length();
    QChar tmpChar;
    for ( int i = 0; i < size / 2; ++i ) {
        tmpChar = tmp[i];
        tmp[i] = tmp[size - i - 1];
        tmp[size - i - 1] = tmpChar;
    }
}

#endif // BIGNUMBER_H
