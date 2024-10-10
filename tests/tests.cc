//#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "sda.h"

#include <algorithm>
#include <array>
#include <cmath>
// #include <complex>
// #include <fstream>
// #include <sstream>
// #include <string>
#include <vector>
#include <iomanip>

typedef SymbDA::DAVector SDA;
// using std::complex;
// using std::string;
typedef SymbDA::DAVector SDA;
using SymEngine::Expression;
using std::cout;
using std::endl;
using std::vector;
using std::array;
// using namespace std::complex_literals;


bool compare_vectors(vector<double>& a, vector<double>& b, double eps) {
    int l1 = a.size();
    int l2 = b.size();
    if (l1 != l2) return false;
    for(int i=0; i<l1; ++i) {
        double d = fabs(a.at(i)-b.at(i));
        if (d>eps) d /= fabs(b.at(i));
        if (d>eps) {
            cout<<std::scientific << std::setprecision(16);
            cout<<i<<' '<<a.at(i)<<' '<<b.at(i)<<' '<<d<<endl;
            return false;
        }
    }
    return true;
}

vector<double> v_sqrt {1.2619825672330027e+00  ,
0.0000000000000000e+00  ,
2.1354098463568110e+00  ,
3.9620198644763360e-01  ,
0.0000000000000000e+00  ,
-1.8066712371137301e+00 ,
0.0000000000000000e+00  ,
-6.7041625215270972e-01 ,
0.0000000000000000e+00  ,
3.0570814914830691e+00  ,
-6.2194208597204828e-02 ,
0.0000000000000000e+00  ,
1.7016242971685265e+00  ,
0.0000000000000000e+00  ,
-6.4661371792376841e+00 ,
0.0000000000000000e+00  ,
3.1571781308208735e-01  ,
0.0000000000000000e+00  ,
-4.7988846720505292e+00 ,
0.0000000000000000e+00  ,
1.5317956604581280e+01 };



TEST_CASE("INITIALIZE DA ENVIRONMENT") {
    int da_dim = 2;
    int da_order = 5;
    int n_vec = 400;
    int init = SymbDA::da_init(da_order, da_dim, n_vec);
    REQUIRE( init  == 0);
}

TEST_CASE("SDA FUNCTIONS") {
    auto& sda = SymbDA::da;

    Expression sx("x"), sy("y");
    double x{1.5926}, y{5.3897};
    double eps = 1e-15;

    SDA sv = sqrt(sx + sda[0]*sda[0] + sy*sda[1]);
    vector<SymEngine::RCP<const SymEngine::Basic>> vars{sx,sy};
    SymEngine::LambdaRealDoubleVisitor vec;
    sv.eval_funs(vars, vec);
    vector<double> results;
    results.resize(sv.full_length());
    array<double, 2> inputs{0,0};
    inputs.at(0) = x;
    inputs.at(1) = y;
    
    cout<<"===== Testing math function: sqrt() ====="<<endl;
    vec.call(&results[0], &inputs[0]);

    SECTION("SQRT") {
        REQUIRE(compare_vectors(v_sqrt, results, eps));
    }

	// DAVector z;
    // da_substitute(y, 0, 1, z);

    // SECTION("SUBSTITUTE A NUMBER") {
    //     REQUIRE(compare_da_with_file("substitute_number.txt", z, eps));
    // }

    // da_substitute(y, 0, x, z);

    // SECTION("SUBSTITUTE A DA VECTOR") {
    //     REQUIRE(compare_da_with_file("substitute_da_vector.txt", z, eps));
    // }

	// std::vector<DAVector> lv(2);
    // lv.at(0) = sin(x);
    // lv.at(1) = cos(x);
    // std::vector<unsigned int> idx{0,1};
    // da_substitute(y, idx, lv, z);
    // SECTION("SUBSTITUTE MULTIPLE DA VECTORS") {
    //     REQUIRE(compare_da_with_file("substitute_multiple_da_vectors.txt", z, eps));
    // }

	// std::vector<DAVector> lx(3);
    // std::vector<DAVector> ly(3);
    // lx.at(0) = x;
    // lx.at(1) = y;
    // lx.at(2) = sinh(x);

    // da_substitute(lx, idx, lv, ly);

    // SECTION("BUNCH SUBSTITUTION") {
    //     REQUIRE(compare_da_with_file("bunch_substitution_0.txt", ly.at(0), eps));
    //     REQUIRE(compare_da_with_file("bunch_substitution_1.txt", ly.at(1), eps));
    //     REQUIRE(compare_da_with_file("bunch_substitution_2.txt", ly.at(2), eps));
    // }

	// std::vector<DAVector> lu(3);
    // lu.at(0) = sin(x);
    // lu.at(1) = cos(x);
    // lu.at(2) = tan(x);
    // da_composition(lx, lu, ly);

    // SECTION("DA COMPOSITION") {
    //     REQUIRE(compare_da_with_file("da_composition_0.txt", ly.at(0), eps));
    //     REQUIRE(compare_da_with_file("da_composition_1.txt", ly.at(1), eps));
    //     REQUIRE(compare_da_with_file("da_composition_2.txt", ly.at(2), eps));
    // }

}

// TEST_CASE("CD FUNCTIONS") {
//     double eps = 1e-14;
//     DAVector x1, x2, x3, x4;
//     x1 = da[0] + 2*da[1] + 3*da[2];
//     x2 = sin(x1);
//     x1 = cos(x1);

//     x3 = 0.5*da[0] + 4*da[1] + 2.7*da[2];
//     x4 = sin(x3);
//     x3 = cos(x3);

//     auto y1 = x1 + x2*1i;
//     auto y2 = x3 + x4*1i;

//     SECTION("CD FUNDAMENTAL CALCULATIONS") {
//         auto r = y1+y2;
//         REQUIRE(compare_cd_with_file("cd_calculation_0.txt", r, eps));
//         r = y1-y2;
//         REQUIRE(compare_cd_with_file("cd_calculation_1.txt", r, eps));
//         r = y1*y2;
//         REQUIRE(compare_cd_with_file("cd_calculation_2.txt", r, eps));
//         r = y1/y2;
//         REQUIRE(compare_cd_with_file("cd_calculation_3.txt", r, eps));
//     }

//     std::vector<DAVector> mmap;
//     mmap.push_back(x1);
//     mmap.push_back(x2);
//     std::vector<complex<DAVector>> cnmap;
//     cnmap.push_back(y1);
//     cnmap.push_back(y2);
//     cnmap.push_back(y1*y2);
//     std::vector<complex<DAVector>> comap(2);
//     cd_composition(mmap, cnmap, comap);

//     SECTION("DA COMPOSITION CD") {
//         REQUIRE(compare_cd_with_file("da_composition_cd_0.txt", comap.at(0), eps));
//         REQUIRE(compare_cd_with_file("da_composition_cd_1.txt", comap.at(1), eps));
//     }

// 	std::vector<complex<DAVector>> cmmap;
//     cmmap.push_back(x1+1i*exp(x1));
//     cmmap.push_back(x2+1i*exp(x2));

//     cd_composition(cmmap, cnmap, comap);

//     SECTION("CD COMPOSITION CD") {
//         REQUIRE(compare_cd_with_file("cd_composition_cd_0.txt", comap.at(0), eps));
//         REQUIRE(compare_cd_with_file("cd_composition_cd_1.txt", comap.at(1), eps));
//     }

// 	mmap.push_back(x1+0.33*x2);
//     cd_composition(cmmap, mmap, comap);

//     SECTION("CD COMPOSITION DA") {
//         REQUIRE(compare_cd_with_file("cd_composition_da_0.txt", comap.at(0), eps));
//         REQUIRE(compare_cd_with_file("cd_composition_da_1.txt", comap.at(1), eps));
//     }
// }
