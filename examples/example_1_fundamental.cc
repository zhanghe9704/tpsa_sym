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

    Expression x("x");
    Expression y("y");
    Expression z("z");
    DAVector da1 = 1+(1+x)*da[0] + y*da[1] + (z-0.5)*da[2];

    cout<<"Symbolic DA vector 1: "<<endl;
    cout<<da1;

    DAVector da2 = 3.3+(0.5+x)*da[0] + y*y*da[1] + (x+z+1.1)*da[2];
    cout<<"Symbolic DA vector 2: "<<endl;
    cout<<da2;

    cout<<"Summation: vec 1 + vec 2:" <<endl;
    auto da3 = da1 + da2;
    cout<<da3;

    cout<<"Multiplication: vec 1 * vec 2: "<<endl;
    da3 = da1 * da3;
    cout<<da3;

    cout<<"Inverse of vec 1: "<<endl;
    da3 = 1/da1;
    cout<<da3;

    cout<<"Square root of vec 1: "<<endl;
    da3 = sqrt(da1);
    cout<<da3;

    return 0;
}

