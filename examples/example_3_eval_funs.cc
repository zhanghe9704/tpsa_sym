#include "da.h"
#include "symbolic.h"
#include <iostream>
#include <vector>
#include <symengine/symengine_rcp.h>
#include <symengine/symbol.h>
#include <symengine/lambda_double.h>

using SymEngine::Expression;
using SymEngine::RCP;
using SymEngine::Basic;
using SymEngine::symbol;
using std::cout;
using std::endl;
using std::vector;


int main(){
    int da_order = 3;
    int da_dim = 3;
    int da_pool = 400;

    da_init(da_order, da_dim, da_pool);

    RCP<const Basic> x=symbol("x0");
    RCP<const Basic> y=symbol("y0");
    RCP<const Basic> z=symbol("z0");
    DAVector da1 = 1+(Expression(1)+x)*da[0] + y*da[1] + (z-Expression(0.5))*da[2];

    cout<<da1;

    vector<RCP<const Basic>> vars{x,y,z};
    vector<SymEngine::LambdaRealDoubleVisitor> vec;
    da1.eval_funs(vars,vec);

    for (auto& v : vec) {
        cout<< v.call({0.1, 0.2, 0.3}) <<endl;
    }
    return 0;
}

