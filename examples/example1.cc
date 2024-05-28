#include "da.h"
using SymEngine::Expression;

int main(){
    int da_order = 3;
    int da_dim = 3;
    int da_pool = 400;

    da_init(da_order, da_dim, da_pool);

    Expression x("x0");
    Expression y("y0");
    Expression z("z0");
    DAVector da1 = (Expression(1)+x)*da[0] + y*da[1] + (z-Expression(0.5))*da[2];
    auto da2 = da1 + da1;

}

