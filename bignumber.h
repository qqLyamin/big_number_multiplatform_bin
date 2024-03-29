#ifndef BIGNUMBER_H
#define BIGNUMBER_H

#include <QString>
#include <vector>

typedef unsigned int quint;
typedef unsigned long long ulonglong;

#define SIZE_OF_POINTER sizeof(void*)
#define MAX_INT 4294967295
#define MAX_ULONGLONG 18446744073709551615

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

class bigNumber
{
    std::vector<ulonglong> arr;
    std::vector<QString> arrStrBinary; //это можно спокойно удалить - не будет вывода, складывать будет по-прежнему
    bool Negative = false;
    bool Trash = false;
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
    friend bool operator&=( const bigNumber & left, const bigNumber & right ); //thats MOD operator ==
    friend std::ostream & operator<<( std::ostream &out, const bigNumber & number );
    quint getSize() const;
    bool isNegative() const;
    bool isPositive() const;
    bool isTrash() const;

    void setNegative();
    void setPositive();
};



#endif // BIGNUMBER_H
