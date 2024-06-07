#include "sda.h"
#include "symbolic.h"
#include <iostream>

using SymEngine::Expression;
using std::cout;
using std::endl;

using namespace SymbDA;

int main(){
    int da_order = 3;
    int da_dim = 3;
    int da_pool = 400;

    da_init(da_order, da_dim, da_pool);

    Expression x("x0");
    Expression y("y0");
    Expression z("z0");
    DAVector da1 = 1+(Expression(1)+x)*da[0] + y*da[1] + (z-Expression(0.5))*da[2];

    cout<<da1;

    SymEngine::map_basic_basic subs_map;

    subs_map[x] = Expression("0.1");
    subs_map[y] = Expression("0.2");
    subs_map[z] = Expression("0.3");

    da1.eval(subs_map);

    cout<<da1;

    return 0;
}

