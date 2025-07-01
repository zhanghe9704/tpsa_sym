#include "sda.h"          
#include "symbolic.h"      
#include <iostream>       

using SymEngine::Expression; 
using std::cout;
using std::endl;

using namespace SymbDA;     

int main(){
    // This example shows how to plug in values to the variables in the
    // symbolic expressions of the coefficients in a DA vector. 
    // This is convenient in testing. 
    // However, if high efficient code is desired, it is better to output
    // the symbolic expressions into a text file and then use a parser and 
    // code generator on it. 

    // Set DA environment parameters
    int da_order = 3;   // Maximum order of DA expansion
    int da_dim = 3;     // Number of variables (dimensions)
    int da_pool = 400;  // Pool size to hold 400 DA vectors

    da_init(da_order, da_dim, da_pool); // Initialize the DA environment

    // Define symbolic variables x, y, z. 
    // They will show up as x0, y0, z0 in the expression.
    Expression x("x0");
    Expression y("y0");
    Expression z("z0");

    // Construct a symbolic DA vector
    // x, y, z are the symbolic variables
    // da[0], da[1], da[2] are the three bases
    DAVector da1 = 1+(1+x)*da[0] + y*da[1] + (z-0.5)*da[2];

    cout<<da1; // Print the symbolic DA vector

    // Create a substitution map for variable evaluation
    SymEngine::map_basic_basic subs_map;

    // Assign numerical values to symbolic variables
    // x = 0.1, y=0.2, z=0.3
    subs_map[x] = Expression("0.1");
    subs_map[y] = Expression("0.2");
    subs_map[z] = Expression("0.3");

    // Evaluate the DA vector with the substitutions
    da1.eval(subs_map);

    cout<<da1; // Print the evaluated DA vector

    return 0; 
}

