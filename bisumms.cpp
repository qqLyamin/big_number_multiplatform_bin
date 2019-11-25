#include "bisumms.h"

biSumms::biSumms()
{

}

bigNumber biSumms::getSumm(const bigNumber & A, const bigNumber & B)
{
    bigNumber C = bigNumber();
    C = A;
    C = C + B;
    return C;
}
