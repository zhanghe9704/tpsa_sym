#include "sda.h"
#include "symbolic.h"
#include <array>
#include <iostream>
#include <vector>

using SymEngine::Expression;
using SymEngine::RCP;
using SymEngine::Basic;
using SymEngine::symbol;
using std::cout;
using std::endl;
using std::vector;
using std::array;

using namespace SymbDA;

int main(){
    // This example shows two ways to obtain callable functions from the 
    // symbolic expressions of the coefficients in a DA vector. 
    // This is convenient in testing. 
    // However, if high efficient code is desired, it is better to output
    // the symbolic expressions into a text file and then use a parser and 
    // code generator on it. 

    int da_order = 3;
    int da_dim = 3;
    int da_pool = 400;

    da_init(da_order, da_dim, da_pool); // Initialize the DA environment

    // Create symbolic variables x, y, z
    // They will show up as x0, y0, z0 in the expression.
    RCP<const Basic> x=symbol("x0");
    RCP<const Basic> y=symbol("y0");
    RCP<const Basic> z=symbol("z0");

    // Construct a symbolic DA vector using the symbolic variables
    DAVector da1 = 1+(1+x)*da[0] + y*da[1] + (z-0.5)*da[2];

    cout<<da1; // Print the symbolic DA vector

    // Use a vector of visitors, each for one coefficient of da1
    // You can consider each visitor is a function of x, y, and z
    vector<RCP<const Basic>> vars{x,y,z};
    vector<SymEngine::LambdaRealDoubleVisitor> vec;
    da1.eval_funs(vars,vec); // Generate visitors for each coefficient

    // Evaluate each coefficient at x=0.1, y=0.2, z=0.3 and print the results
    for (auto& v : vec) {
        cout<< v.call({0.1, 0.2, 0.3}) <<endl;
    }

    // Use a single visitor for all coefficients (more convenient)
    // You can consider the visotr v is a vector of functions and
    // each element of v is a function of x, y, and z
    SymEngine::LambdaRealDoubleVisitor v;
    da1.eval_funs(vars, v);
    vector<double> results;
    results.resize(da1.full_length()); // Prepare storage for all coefficients
    array<double, 3> inputs{0.1, 0.2, 0.3}; // Input values for variables
    
    cout<<"=============="<<endl;
     // Evaluate all coefficients at once for x=0.1, y=0.2, z=0.3
     // inputs - values for the variables
     // results - values for the coefficients of the DA vector
    v.call(&results[0], &inputs[0]);

    // Print all evaluated coefficients
    for (auto r : results) {
        cout<< r << endl;
    }

    return 0;
}

