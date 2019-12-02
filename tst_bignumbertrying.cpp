#include "tst_bignumbertrying.h"

//targeting:
void bigNumberTrying::max64()
{
    bigNumber A = bigNumber("18446744073709551615");
    bigNumber B = bigNumber("1");
    bigNumber result = bigNumber("18446744073709551616");
    biSumms test = biSumms();
    bigNumber result2 = test.getSumm(A, B);

    QCOMPARE(test.getSumm(A, B), result);
}

void bigNumberTrying::max64swithced()
{
    bigNumber A = bigNumber("1");
    bigNumber B = bigNumber("18446744073709551615");
    bigNumber result = bigNumber("18446744073709551616");
    biSumms test = biSumms();
    bigNumber result2 = test.getSumm(A, B);

    QCOMPARE(test.getSumm(A, B), result);
}

void bigNumberTrying::max32()
{
    bigNumber A = bigNumber("4294967295");
    bigNumber B = bigNumber("1");
    bigNumber result = bigNumber("4294967296");
    biSumms test = biSumms();

    QCOMPARE(test.getSumm(A, B), result);
}

void bigNumberTrying::max32switched()
{
    bigNumber A = bigNumber("1");
    bigNumber B = bigNumber("4294967295");
    bigNumber result = bigNumber("4294967296");
    biSumms test = biSumms();

    QCOMPARE(test.getSumm(A, B), result);
}

void bigNumberTrying::negativeMax64()
{
    bigNumber A = bigNumber("-1");
    bigNumber B = bigNumber("18446744073709551616");
    bigNumber result = bigNumber("18446744073709551615");
    biSumms test = biSumms();
    bigNumber result2 = test.getSumm(A, B);

    QCOMPARE(test.getSumm(A, B), result);
}

void bigNumberTrying::negativeMax32()
{
    bigNumber A = bigNumber("-1");
    bigNumber B = bigNumber("4294967296");
    bigNumber result = bigNumber("4294967295");
    biSumms test = biSumms();
    bigNumber result2 = test.getSumm(A, B);

    QCOMPARE(test.getSumm(A, B), result);
}


//POSITIVE:
void bigNumberTrying::positiveSameNumbers()
{
    bigNumber A = bigNumber("111111111");
    bigNumber B = bigNumber("111111111");
    bigNumber result = bigNumber("222222222");
    biSumms test = biSumms();

    QCOMPARE(test.getSumm(A, B), result);
}

void bigNumberTrying::ulongPlusOne()
{
    bigNumber A = bigNumber("4294967295");
    bigNumber B = bigNumber("1");
    bigNumber result = bigNumber("4294967296");
    biSumms test = biSumms();

    QCOMPARE(test.getSumm(A, B), result);
}

void bigNumberTrying::positiveSameNumbersBig()
{
    bigNumber A = bigNumber("111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111");
    bigNumber B = bigNumber("111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111");
    bigNumber result = bigNumber("222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222");
    biSumms test = biSumms();

    QCOMPARE(test.getSumm(A, B), result);
}

void bigNumberTrying::positiveDifferentNumbers()
{
    bigNumber A = bigNumber("111121111");
    bigNumber B = bigNumber("113111711");
    bigNumber result = bigNumber("224232822");
    biSumms test = biSumms();

    QCOMPARE(test.getSumm(A, B), result);
}

void bigNumberTrying::positiveDifferentNumbersSwitched()
{
    bigNumber A = bigNumber("113111711");
    bigNumber B = bigNumber("111121111");
    bigNumber result = bigNumber("224232822");
    biSumms test = biSumms();

    QCOMPARE(test.getSumm(A, B), result);
}

//POSITIVE + NEGATIVE:
void bigNumberTrying::positiveNegative()
{
    bigNumber A = bigNumber("88888888");
    bigNumber B = bigNumber("-11111111");
    bigNumber result = bigNumber("77777777");
    biSumms test = biSumms();

    QCOMPARE(test.getSumm(A, B), result);
}

void bigNumberTrying::negativePositive()
{
    bigNumber A = bigNumber("-88888888");
    bigNumber B = bigNumber("11111111");
    bigNumber result = bigNumber("-77777777");
    biSumms test = biSumms();

    QCOMPARE(test.getSumm(A, B), result);
}

void bigNumberTrying::positiveNegativeSwitched()
{
    bigNumber A = bigNumber("-11111111");
    bigNumber B = bigNumber("88888888");
    bigNumber result = bigNumber("77777777");
    biSumms test = biSumms();

    QCOMPARE(test.getSumm(A, B), result);
}

void bigNumberTrying::negativePositiveSwitched()
{
    bigNumber A = bigNumber("-11111111");
    bigNumber B = bigNumber("88888888");
    bigNumber result = bigNumber("77777777");
    biSumms test = biSumms();

    QCOMPARE(test.getSumm(A, B), result);
}

void bigNumberTrying::positiveNegativeSame()
{
    bigNumber A = bigNumber("88888888");
    bigNumber B = bigNumber("-88888888");
    bigNumber result = bigNumber("0");
    biSumms test = biSumms();

    QCOMPARE(test.getSumm(A, B), result);
}

void bigNumberTrying::negativePositiveSame()
{
    bigNumber A = bigNumber("-11111111");
    bigNumber B = bigNumber("11111111");
    bigNumber result = bigNumber("0");
    biSumms test = biSumms();

    QCOMPARE(test.getSumm(A, B), result);
}

//TWO NEGATIVE:
void bigNumberTrying::negativeNegative()
{
    bigNumber A = bigNumber("-112635211");
    bigNumber B = bigNumber("-222222222");
    bigNumber result = bigNumber("-334857433");
    biSumms test = biSumms();

    QCOMPARE(test.getSumm(A, B), result);
}

void bigNumberTrying::negativeNegativeSwitched()
{
    bigNumber A = bigNumber("-222222222");
    bigNumber B = bigNumber("-112635211");
    bigNumber result = bigNumber("-334857433");
    biSumms test = biSumms();

    QCOMPARE(test.getSumm(A, B), result);
}

void bigNumberTrying::negativeSameNumbersBig()
{
         bigNumber A = bigNumber("-222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222");
         bigNumber B = bigNumber("-222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222");
    bigNumber result = bigNumber("-444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444");
    biSumms test = biSumms();
    bigNumber result2 = test.getSumm(A, B);

    QCOMPARE(test.getSumm(A, B), result);
}

void bigNumberTrying::negativeDifferentNumbersBig()
{
         bigNumber A = bigNumber("-222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222");
         bigNumber B = bigNumber("-777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777");
    bigNumber result = bigNumber("-999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999");
    biSumms test = biSumms();
    bigNumber result2 = test.getSumm(A, B);

    QCOMPARE(test.getSumm(A, B), result);
}

void bigNumberTrying::negativeNegativeSame()
{
    bigNumber A = bigNumber("-222222222");
    bigNumber B = bigNumber("-222222222");
    bigNumber result = bigNumber("-444444444");
    biSumms test = biSumms();

    QCOMPARE(test.getSumm(A, B), result);
}


//TRASH WITH NORMAL:

void bigNumberTrying::trashPlusNormal()
{
    bigNumber A = bigNumber("-2fdguif");
    bigNumber B = bigNumber("222222222");
    bigNumber result = bigNumber("222222222");
    biSumms test = biSumms();

    QCOMPARE(test.getSumm(A, B), result);
}

void bigNumberTrying::normalPlusTrash()
{
    bigNumber A = bigNumber("222222222");
    bigNumber B = bigNumber("-2fdguif");
    bigNumber result = bigNumber("222222222");
    biSumms test = biSumms();

    QCOMPARE(test.getSumm(A, B), result);
}

void bigNumberTrying::trashPlusTrash()
{
    bigNumber A = bigNumber("sdfkjgfhds2");
    bigNumber B = bigNumber("-2fdguif");
    bigNumber result = bigNumber("0");
    biSumms test = biSumms();

    QCOMPARE(test.getSumm(A, B), result);
}

//ZEROS WITH OK:
void bigNumberTrying::zeroPlusOk()
{
    bigNumber A = bigNumber("0");
    bigNumber B = bigNumber("236452");
    bigNumber result = bigNumber("236452");
    biSumms test = biSumms();

    QCOMPARE(test.getSumm(A, B), result);
}

void bigNumberTrying::okPlusZero()
{
    bigNumber A = bigNumber("236452");
    bigNumber B = bigNumber("0");
    bigNumber result = bigNumber("236452");
    biSumms test = biSumms();

    QCOMPARE(test.getSumm(A, B), result);
}

void bigNumberTrying::zeroPlusZero()
{
    bigNumber A = bigNumber("0");
    bigNumber B = bigNumber("0");
    bigNumber result = bigNumber("0");
    biSumms test = biSumms();

    QCOMPARE(test.getSumm(A, B), result);
}

//EXTREMAL SITUATIONS:
void bigNumberTrying::ninesPlusOne()
{
    bigNumber A = bigNumber("999999");
    bigNumber B = bigNumber("1");
    bigNumber result = bigNumber("1000000");
    biSumms test = biSumms();

    QCOMPARE(test.getSumm(A, B), result);
}

void bigNumberTrying::ninesPlusOneSwitched()
{
    bigNumber A = bigNumber("1");
    bigNumber B = bigNumber("999999");
    bigNumber result = bigNumber("1000000");
    biSumms test = biSumms();

    QCOMPARE(test.getSumm(A, B), result);
}

void bigNumberTrying::millionPlusOneNegative()
{
    bigNumber A = bigNumber("1000000");
    bigNumber B = bigNumber("-1");
    bigNumber result = bigNumber("999999");
    biSumms test = biSumms();

    QCOMPARE(test.getSumm(A, B), result);
}

void bigNumberTrying::millionPlusOneNegativeSwitched()
{
    bigNumber A = bigNumber("-1");
    bigNumber B = bigNumber("1000000");
    bigNumber result = bigNumber("999999");
    biSumms test = biSumms();

    QCOMPARE(test.getSumm(A, B), result);
}

void bigNumberTrying::millionNegativePlusOnePositive()
{
    bigNumber A = bigNumber("-1000000");
    bigNumber B = bigNumber("1");
    bigNumber result = bigNumber("-999999");
    biSumms test = biSumms();

    QCOMPARE(test.getSumm(A, B), result);
}
