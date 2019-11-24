#include <QCoreApplication>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <QString>

#include "bignumber.h"
#include "bisumms.h"
#include "tst_bignumbertrying.h"



int main(int argc, char *argv[])
{
//    freopen("testing,log", "w", stdout);
//    bigNumberTrying * test = new bigNumberTrying;
    QCoreApplication a(argc, argv);

    int x = 0;
    bigNumber asd = bigNumber();
    bigNumber qwe = bigNumber();
    asd = bigNumber("23874620249029420520");
    qwe = asd;

    bigNumber ytr = bigNumber("23874620249029420520");

    if (asd == ytr) {
        x = 100;
    }
    std::cout << ytr << std::endl;
    //QTest::qExec(test, argc, argv);

    return a.exec();
}
