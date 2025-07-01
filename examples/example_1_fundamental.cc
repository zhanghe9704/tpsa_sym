#include "sda.h"           
#include "symbolic.h"     
#include <iostream>       

using SymEngine::Expression;
using std::cout;
using std::endl;
using namespace SymbDA;   

int main(){
    // This example demonstrate how to create a DA vector using the bases
    // and how to use DA vectors in computation just as numbers. 


    // Set DA environment parameters
    int da_order = 4;   // Maximum order of DA expansion
    int da_dim = 3;     // Number of variables (dimensions)
    int da_pool = 400;  // Pool size to whole 400 DA vectors

    da_init(da_order, da_dim, da_pool); // Initialize the DA environment

    // Define symbolic variables using SymEngine
    Expression x("x");
    Expression y("y");
    Expression z("z");

    // Construct a symbolic DA vector using the symbolic variables
    // x, y, z are the symbolic variables
    // da[0], da[1], da[2] are the three bases
    DAVector da1 = 1+(1+x)*da[0] + y*da[1] + (z-0.5)*da[2];

    cout<<"Symbolic DA vector 1: "<<endl;
    cout<<da1; // Print the first DA vector

    // Construct another symbolic DA vector with different expressions
    DAVector da2 = 3.3+(0.5+x)*da[0] + y*y*da[1] + (x+z+1.1)*da[2];
    cout<<"Symbolic DA vector 2: "<<endl;
    cout<<da2; // Print the second DA vector

    // Demonstrate addition of two DA vectors
    cout<<"Summation: vec 1 + vec 2:" <<endl;
    auto da3 = da1 + da2;
    cout<<da3; // Print the result of addition

    // Demonstrate multiplication of DA vectors
    cout<<"Multiplication: vec 1 * vec 2: "<<endl;
    da3 = da1 * da3;
    cout<<da3; // Print the result of multiplication

    // Demonstrate inversion (reciprocal) of a DA vector
    cout<<"Inverse of vec 1: "<<endl;
    da3 = 1/da1;
    cout<<da3; // Print the result of inversion

    // Demonstrate square root of a DA vector
    cout<<"Square root of vec 1: "<<endl;
    da3 = sqrt(da1);
    cout<<da3; // Print the result of square root

    return 0; 
}

