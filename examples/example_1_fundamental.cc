#include "sda.h"
#include "symbolic.h"
#include <iostream>

using SymEngine::Expression;
using std::cout;
using std::endl;
using namespace SymbDA;

int main(){
    int da_order = 4;
    int da_dim = 3;
    int da_pool = 400;

    da_init(da_order, da_dim, da_pool);

    Expression x("x0");
    Expression y("y0");
    Expression z("z0");
    DAVector da1 = 1+(Expression(1)+x)*da[0] + y*da[1] + (z-Expression(0.5))*da[2];

    cout<<"da1 length: "<<da1.n_element()<<endl;
    

    DAVector Ocm = Expression(1)/sqrt(Expression(1)+(x*x + y*y + z*z)*(da[0]*da[0]+da[1]*da[1]+da[2]*da[2]) - 
        Expression(2)*x*da[0] - Expression(2)*y*da[1] - Expression(2)*z*da[2]);
    cout<<Ocm;

    return 0;
}

