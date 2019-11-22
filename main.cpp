#include <QCoreApplication>
#include <iostream>
#include <cstdlib>
#include <cstdio>

#include "bignumber.h"
#include "bisumms.h"
#include "tst_bignumbertrying.h"

int main(int argc, char *argv[])
{
    freopen("testing,log", "w", stdout);
    bigNumberTrying * test = new bigNumberTrying;
    QCoreApplication a(argc, argv);
    QTest::qExec(test, argc, argv);
    return a.exec();
}
