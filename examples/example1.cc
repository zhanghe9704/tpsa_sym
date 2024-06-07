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

    cout<<"da1 length: "<<da1.n_element()<<endl;
    
    for(int i=0; i<da1.n_element(); ++i) {
        std::vector<unsigned int> c{0,0,0};
        Expression elem;
        da1.element(i, c, elem);
        cout<<i;
        for (auto idx : c) {
            cout<< idx << ' ';
        }
        cout<< expand(elem) <<endl;
    }
    auto da2 = da1 * da1;



}

