

#include "dp/dpinit/dpinit/dpinit.h"

int main()
{
    dp::dpinit d;

    d.start();
    d.blockUntilDead();

    return 0;
}
