#include <QtTest/QTest>
#include <QString>
#include <iostream>

#include "bignumber.h"
#include "bisumms.h"

class bigNumberTrying : public QObject
{
    Q_OBJECT

private slots:

    //POSITIVE:
    void positiveSameNumbers();
    void ulongPlusOne();
    void positiveSameNumbersBig();
    void positiveDifferentNumbers();
    void positiveDifferentNumbersSwitched();

    //POSITIVE + NEGATIVE:
    void positiveNegative();
    void negativePositive();

    void positiveNegativeSwitched();
    void negativePositiveSwitched();

    void positiveNegativeSame();
    void negativePositiveSame();

    //TWO NEGATIVE:
    void negativeNegative();
    void negativeNegativeSwitched();
    void negativeSameNumbersBig();
    void negativeDifferentNumbersBig();
    void negativeNegativeSame();

    //TRASH WITH NORMAL:
    void trashPlusNormal();
    void normalPlusTrash();
    void trashPlusTrash();

    //ZEROS WITH OK:
    void zeroPlusOk();
    void okPlusZero();
    void zeroPlusZero();

    //BORDER SITUATIONS:
    void max64();
    void max64swithced();
    void max32();
    void max32switched();

    void negativeMax64();
    void negativeMax32();

    void ninesPlusOne();
    void ninesPlusOneSwitched();
    void millionPlusOneNegative();
    void millionPlusOneNegativeSwitched();
    void millionNegativePlusOnePositive();

};
