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

void eval(SDA& sv, Expression& sx, Expression& sy, double x, double y, vector<double>& results){
    vector<SymEngine::RCP<const SymEngine::Basic>> vars{sx,sy};
    SymEngine::LambdaRealDoubleVisitor vec;
    sv.eval_funs(vars, vec);
    // vector<double> results;
    results.resize(sv.full_length());
    array<double, 2> inputs{0,0};
    inputs.at(0) = x;
    inputs.at(1) = y;
    vec.call(&results[0], &inputs[0]);
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

vector<double> v_exp {4.9165152645857058e+00,
0.0000000000000000e+00,
2.6498542321537581e+01,
4.9165152645857058e+00,
0.0000000000000000e+00,
7.1409596775195553e+01,
0.0000000000000000e+00,
2.6498542321537581e+01,
0.0000000000000000e+00,
1.2829210124642384e+02,
2.4582576322928529e+00,
0.0000000000000000e+00,
7.1409596775195553e+01,
0.0000000000000000e+00,
1.7286398452196264e+02,
0.0000000000000000e+00,
1.3249271160768791e+01,
0.0000000000000000e+00,
1.2829210124642384e+02,
0.0000000000000000e+00,
1.8633700347560443e+02};

vector<double> v_log {4.6536790084120744e-01 ,
0.0000000000000000e+00 ,
3.3842144920256185e+00 ,
6.2790405626020340e-01 ,
0.0000000000000000e+00 ,
-5.7264538640181080e+00,
0.0000000000000000e+00 ,
-2.1249620067974497e+00,
0.0000000000000000e+00 ,
1.2919698769684123e+01 ,
-1.9713175193400836e-01,
0.0000000000000000e+00 ,
7.1913272184077712e+00 ,
0.0000000000000000e+00 ,
-3.2792273856727924e+01,
0.0000000000000000e+00 ,
1.3342722634669408e+00 ,
0.0000000000000000e+00 ,
-2.4336993789433862e+01,
0.0000000000000000e+00 ,
8.8780870729929191e+01};

vector<double> v_sin{9.9976230933412147e-01,
0.0000000000000000e+00,
-1.1750594656606546e-01,
-2.1801945667860076e-02,
0.0000000000000000e+00,
-1.4520980722838027e+01,
0.0000000000000000e+00,
-5.3884189186181146e+00,
0.0000000000000000e+00,
5.6890241776272188e-01,
-4.9988115466706073e-01,
0.0000000000000000e+00,
3.1666090010356152e-01,
0.0000000000000000e+00,
3.5151502042766111e+01,
0.0000000000000000e+00,
5.8752973283032729e-02,
0.0000000000000000e+00,
2.6087909933960042e+01,
0.0000000000000000e+00,
-8.2629850759332735e-01};

vector<double> v_cos {-2.1801945667860076e-02,
0.0000000000000000e+00,
-5.3884189186181146e+00,
-9.9976230933412147e-01,
0.0000000000000000e+00,
3.1666090010356152e-01,
0.0000000000000000e+00,
1.1750594656606546e-01,
0.0000000000000000e+00,
2.6087909933960042e+01,
1.0900972833930038e-02,
0.0000000000000000e+00,
1.4520980722838027e+01,
0.0000000000000000e+00,
-7.6655334025393562e-01,
0.0000000000000000e+00,
2.6942094593090573e+00,
0.0000000000000000e+00,
-5.6890241776272188e-01,
0.0000000000000000e+00,
-3.7891210111979305e+01};

vector<double> v_tan {-4.5856563655598315e+01,
0.0000000000000000e+00,
1.1338982531987589e+04,
2.1038244302999406e+03,
0.0000000000000000e+00,
-2.8024649232711950e+06,
0.0000000000000000e+00,
-1.0399335485356124e+06,
0.0000000000000000e+00,
6.9274774751837516e+08,
-9.6474158908252066e+04,
0.0000000000000000e+00,
3.8559534715385360e+08,
0.0000000000000000e+00,
-1.7124190410087451e+11,
0.0000000000000000e+00,
7.1543007431555301e+07,
0.0000000000000000e+00,
-1.2708826398565749e+11,
0.0000000000000000e+00,
4.2329679125704305e+13};

vector<double> v_asin {6.3428284416340086e-01,
0.0000000000000000e+00,
6.6911493589602227e+00,
1.2414697216839945e+00,
0.0000000000000000e+00,
1.6469075934078099e+01,
0.0000000000000000e+00,
6.1113145199465828e+00,
0.0000000000000000e+00,
1.3100018800423086e+02,
5.6694384844672152e-01,
0.0000000000000000e+00,
7.2916964582939883e+01,
0.0000000000000000e+00,
1.0518658826557562e+03,
0.0000000000000000e+00,
1.3528946802779576e+01,
0.0000000000000000e+00,
7.8064892862726265e+02,
0.0000000000000000e+00,
9.8884295426925273e+03};

vector<double> v_atan {5.3496055600178871e-01,
0.0000000000000000e+00,
3.9888992597819097e+00,
7.4009671406236144e-01,
0.0000000000000000e+00,
-9.4290466347585138e+00,
0.0000000000000000e+00,
-3.4989133475920777e+00,
0.0000000000000000e+00,
1.1323711186436043e+00,
-3.2459258841791550e-01,
0.0000000000000000e+00,
6.3029729965130876e-01,
0.0000000000000000e+00,
9.7342311833335117e+01,
0.0000000000000000e+00,
1.1694478350396453e-01,
0.0000000000000000e+00,
7.2243213413241108e+01,
0.0000000000000000e+00,
-3.8276667852990363e+02};

vector<double> v_acos {9.3651348263149570e-01,
0.0000000000000000e+00,
-6.6911493589602227e+00,
-1.2414697216839945e+00,
0.0000000000000000e+00,
-1.6469075934078099e+01,
0.0000000000000000e+00,
-6.1113145199465828e+00,
0.0000000000000000e+00,
-1.3100018800423086e+02,
-5.6694384844672152e-01,
0.0000000000000000e+00,
-7.2916964582939883e+01,
0.0000000000000000e+00,
-1.0518658826557562e+03,
0.0000000000000000e+00,
-1.3528946802779576e+01,
0.0000000000000000e+00,
-7.8064892862726265e+02,
0.0000000000000000e+00,
-9.8884295426925273e+03};

vector<double> v_sinh {2.3565595853852059e+00,
0.0000000000000000e+00,
1.3797393124186938e+01,
2.5599556792005003e+00,
0.0000000000000000e+00,
3.4227691914480388e+01,
0.0000000000000000e+00,
1.2701149197350645e+01,
0.0000000000000000e+00,
6.6799770875932182e+01,
1.1782797926926030e+00,
0.0000000000000000e+00,
3.7181904860715171e+01,
0.0000000000000000e+00,
8.2856303249459728e+01,
0.0000000000000000e+00,
6.8986965620934688e+00,
0.0000000000000000e+00,
6.1492330370491651e+01,
0.0000000000000000e+00,
9.7022879950881816e+01};

vector<double> v_cosh {2.5599556792005003e+00,
0.0000000000000000e+00,
1.2701149197350645e+01,
2.3565595853852059e+00,
0.0000000000000000e+00,
3.7181904860715171e+01,
0.0000000000000000e+00,
1.3797393124186938e+01,
0.0000000000000000e+00,
6.1492330370491651e+01,
1.2799778396002501e+00,
0.0000000000000000e+00,
3.4227691914480388e+01,
0.0000000000000000e+00,
9.0007681272502936e+01,
0.0000000000000000e+00,
6.3505745986753226e+00,
0.0000000000000000e+00,
6.6799770875932182e+01,
0.0000000000000000e+00,
8.9314123524722618e+01};

vector<double> v_tanh {9.2054702529896260e-01,
0.0000000000000000e+00,
8.2243143105705130e-01,
1.5259317421323104e-01,
0.0000000000000000e+00,
-4.0804707656925352e+00,
0.0000000000000000e+00,
-1.5141736147438749e+00,
0.0000000000000000e+00,
1.2281575847812150e+01,
-1.4046919260291624e-01,
0.0000000000000000e+00,
6.8361369915647501e+00,
0.0000000000000000e+00,
-2.1423682111362041e+01,
0.0000000000000000e+00,
1.2683705942009276e+00,
0.0000000000000000e+00,
-1.5899721402944124e+01,
0.0000000000000000e+00,
2.7932271238723843e+00};

vector<double> v_pow3 {4.0394304427760002e+00,
0.0000000000000000e+00,
4.1010897131916003e+01,
7.6091242800000005e+00,
0.0000000000000000e+00,
1.3878967240480202e+02,
0.0000000000000000e+00,
5.1501817320000001e+01,
0.0000000000000000e+00,
1.5656467356527304e+02,
4.7778000000000000e+00,
0.0000000000000000e+00,
8.7146598270000013e+01,
0.0000000000000000e+00,
0.0000000000000000e+00,
0.0000000000000000e+00,
1.6169100000000000e+01,
0.0000000000000000e+00,
0.0000000000000000e+00,
0.0000000000000000e+00,
0.0000000000000000e+00};

vector<double> v_pow043 {1.2215349178657362e+00,
0.0000000000000000e+00,
1.7775925537693156e+00,
3.2981289381028916e-01,
0.0000000000000000e+00,
-1.7144900271941401e+00,
0.0000000000000000e+00,
-6.3620981768712170e-01,
0.0000000000000000e+00,
3.0364857114827242e+00,
-5.9020893341662960e-02,
0.0000000000000000e+00,
1.6901603307138011e+00,
0.0000000000000000e+00,
-6.6024064251363503e+00,
0.0000000000000000e+00,
3.1359079924927197e-01,
0.0000000000000000e+00,
-4.9000177561915139e+00,
0.0000000000000000e+00,
1.5953587087419303e+01};

vector<double> v_erf {9.7569519695814055e-01,
0.0000000000000000e+00,
4.8137783493505698e-01,
8.9314402459331130e-02,
0.0000000000000000e+00,
-4.1319722194537372e+00,
0.0000000000000000e+00,
-1.5332846798351436e+00,
0.0000000000000000e+00,
1.8983737513383726e+01,
-1.4224211735673076e-01,
0.0000000000000000e+00,
1.0566675796454568e+01,
0.0000000000000000e+00,
-4.1465045891922742e+01,
0.0000000000000000e+00,
1.9605313461703930e+00,
0.0000000000000000e+00,
-3.0773546499376767e+01,
0.0000000000000000e+00,
-2.3068466761450004e+01};

vector<double> v_der {0.0000000000000000e+00,
9.8330305291714115e+00,
0.0000000000000000e+00,
0.0000000000000000e+00,
5.2997084643075162e+01,
0.0000000000000000e+00,
9.8330305291714115e+00,
0.0000000000000000e+00,
1.4281919355039111e+02,
0.0000000000000000e+00,
0.0000000000000000e+00,
5.2997084643075162e+01,
0.0000000000000000e+00,
2.5658420249284768e+02,
0.0000000000000000e+00,
0.0000000000000000e+00,
0.0000000000000000e+00,
0.0000000000000000e+00,
0.0000000000000000e+00,
0.0000000000000000e+00,
0.0000000000000000e+00};

vector<double> v_int {
    0.0000000000000000e+00,
4.9165152645857058e+00,
0.0000000000000000e+00,
0.0000000000000000e+00,
2.6498542321537581e+01,
0.0000000000000000e+00,
1.6388384215285685e+00,
0.0000000000000000e+00,
7.1409596775195553e+01,
0.0000000000000000e+00,
0.0000000000000000e+00,
8.8328474405125252e+00,
0.0000000000000000e+00,
1.2829210124642384e+02,
0.0000000000000000e+00,
4.9165152645857052e-01,
0.0000000000000000e+00,
2.3803198925065185e+01,
0.0000000000000000e+00,
1.7286398452196264e+02,
0.0000000000000000e+00};

vector<double> v_subc {1.2291288161464264e+01,
0.0000000000000000e+00,
6.6246355803843954e+01,
0.0000000000000000e+00,
0.0000000000000000e+00,
1.4281919355039111e+02,
0.0000000000000000e+00,
0.0000000000000000e+00,
0.0000000000000000e+00,
2.5658420249284768e+02,
0.0000000000000000e+00,
0.0000000000000000e+00,
0.0000000000000000e+00,
0.0000000000000000e+00,
1.7286398452196264e+02,
0.0000000000000000e+00,
0.0000000000000000e+00,
0.0000000000000000e+00,
0.0000000000000000e+00,
0.0000000000000000e+00,
1.8633700347560443e+02};

vector<double> v_sub {1.8981620087089855e+01,
0.0000000000000000e+00,
1.7100535860620653e+02,
1.2746557474964902e+01,
0.0000000000000000e+00,
6.2681915857331160e+02,
0.0000000000000000e+00,
9.5198663144355919e+01,
0.0000000000000000e+00,
1.1023627091700214e+03,
2.4582576322928529e+00,
0.0000000000000000e+00,
2.1422879032558666e+02,
0.0000000000000000e+00,
8.6431992260981315e+02,
0.0000000000000000e+00,
1.3249271160768791e+01,
0.0000000000000000e+00,
1.2829210124642384e+02,
0.0000000000000000e+00,
1.8633700347560443e+02};

vector<double> v_subv {9.9749939097621802e+02,
0.0000000000000000e+00,
1.1512590930808019e+03,
2.1360355735584579e+02,
0.0000000000000000e+00,
-4.4758214953827373e+04,
0.0000000000000000e+00,
-1.6608796390829688e+04,
0.0000000000000000e+00,
-3.0987895299849177e+04,
-1.5407904327541128e+03,
0.0000000000000000e+00,
-1.7248397109217120e+04,
0.0000000000000000e+00,
9.7163445148612640e+05,
0.0000000000000000e+00,
-3.2002517968007724e+03,
0.0000000000000000e+00,
7.2110466370011435e+05,
0.0000000000000000e+00,
3.1279038644950697e+05};

vector<double> v_vsub0 {2.9683742321537579e+01,
0.0000000000000000e+00,
1.4820889355039111e+02,
2.7498542321537581e+01,
0.0000000000000000e+00,
3.8487630373927152e+02,
0.0000000000000000e+00,
1.4281919355039111e+02,
0.0000000000000000e+00,
6.9145593808785054e+02,
1.3249271160768791e+01,
0.0000000000000000e+00,
3.8487630373927152e+02,
0.0000000000000000e+00,
9.3168501737802217e+02,
0.0000000000000000e+00,
7.1409596775195553e+01,
0.0000000000000000e+00,
6.9145593808785054e+02,
0.0000000000000000e+00,
1.0043005476324653e+03};

vector<double> v_vsub1 {2.2789117817838105e+04,
0.0000000000000000e+00,
4.7247897335916117e+05,
8.7663315835605143e+04,
0.0000000000000000e+00,
4.8149709416966103e+06,
0.0000000000000000e+00,
1.7867305941691040e+06,
0.0000000000000000e+00,
3.2197066119944468e+07,
1.6575417872693326e+05,
0.0000000000000000e+00,
1.7921442447600685e+07,
0.0000000000000000e+00,
1.5854645261039719e+08,
0.0000000000000000e+00,
3.3251280122457058e+06,
0.0000000000000000e+00,
1.1766625423336896e+08,
0.0000000000000000e+00,
6.0926100575974762e+08};

vector<double> v_vsub2 {-1.0573135900055892e+05,
0.0000000000000000e+00,
-2.8866867756027146e+06,
-5.3559321958600974e+05,
0.0000000000000000e+00,
-3.9188057115516029e+07,
0.0000000000000000e+00,
-1.4541832426857166e+07,
0.0000000000000000e+00,
-3.5349388645438391e+08,
-1.3490391326843027e+06,
0.0000000000000000e+00,
-1.9676079547343114e+08,
0.0000000000000000e+00,
-2.3869922351913180e+09,
0.0000000000000000e+00,
-3.6506817721474491e+07,
0.0000000000000000e+00,
-1.7715214094968681e+09,
0.0000000000000000e+00,
-1.2880995781051701e+10};

vector<double> v_compc {6.2871116966104892e+04,
3.5879835234251332e+04,
-1.6797595287239095e+05};

TEST_CASE("INITIALIZE DA ENVIRONMENT") {
    int da_dim = 2;
    int da_order = 5;
    int n_vec = 400;
    int init = SymbDA::da_init(da_order, da_dim, n_vec);
    cout<<"===== Testing SDA environment initialization ====="<<endl;
    REQUIRE( init  == 0);
}

TEST_CASE("SDA FUNCTIONS") {
    auto& sda = SymbDA::da;

    Expression sx("x"), sy("y");
    double x{1.5926}, y{5.3897};
    double eps = 1e-13;
    vector<double> results;
    SDA sv;

    SECTION("SQRT"){
        cout<<"===== Testing math function: sqrt() ====="<<endl;
        sv = sqrt(sx + sda[0]*sda[0] + sy*sda[1]);
        eval(sv, sx, sy, x, y, results);
        REQUIRE(compare_vectors(v_sqrt, results, eps));
    }

    SECTION("EXP"){
        cout<<"===== Testing math function: exp() ====="<<endl;
        sv = exp(sx + sda[0]*sda[0] + sy*sda[1]);
        eval(sv, sx, sy, x, y, results);
        REQUIRE(compare_vectors(v_exp, results, eps));
    }

     SECTION("LOG"){
        cout<<"===== Testing math function: log() ====="<<endl;
        sv = log(sx + sda[0]*sda[0] + sy*sda[1]);
        eval(sv, sx, sy, x, y, results);
        REQUIRE(compare_vectors(v_log, results, eps));
     }

    SECTION("POW(SDA,INT)"){
        cout<<"===== Testing math function: pow(sda,int) ====="<<endl;
        sv = pow(sx + sda[0]*sda[0] + sy*sda[1], 3);
        eval(sv, sx, sy, x, y, results);
        REQUIRE(compare_vectors(v_pow3, results, eps));
    }

    SECTION("POW(SDA,DOUBLE)"){
        cout<<"===== Testing math function: pow(sda,double) ====="<<endl;
        sv = pow(sx + sda[0]*sda[0] + sy*sda[1], 0.43);
        eval(sv, sx, sy, x, y, results);
        REQUIRE(compare_vectors(v_pow043, results, eps));
    }

    SECTION("ERF"){
        cout<<"===== Testing math function: erf() ====="<<endl;
        sv = erf(sx + sda[0]*sda[0] + sy*sda[1]);
        eval(sv, sx, sy, x, y, results);
        REQUIRE(compare_vectors(v_erf, results, eps));
    }

    SECTION("SIN"){
        cout<<"===== Testing math function: sin() ====="<<endl;
        sv = sin(sx + sda[0]*sda[0] + sy*sda[1]);
        eval(sv, sx, sy, x, y, results);
        REQUIRE(compare_vectors(v_sin, results, eps));
    }

    SECTION("COS"){
        cout<<"===== Testing math function: cos() ====="<<endl;
        sv = cos(sx + sda[0]*sda[0] + sy*sda[1]);
        eval(sv, sx, sy, x, y, results); 
        REQUIRE(compare_vectors(v_cos, results, eps));
    }

    SECTION("TAN"){
        cout<<"===== Testing math function: tan() ====="<<endl;
        sv = tan(sx + sda[0]*sda[0] + sy*sda[1]);
        eval(sv, sx, sy, x, y, results);
        REQUIRE(compare_vectors(v_tan, results, eps));
    }

    SECTION("SINH"){
        cout<<"===== Testing math function: sinh() ====="<<endl;
        sv = sinh(sx + sda[0]*sda[0] + sy*sda[1]);
        eval(sv, sx, sy, x, y, results);
        REQUIRE(compare_vectors(v_sinh, results, eps));
    }

    SECTION("COSH"){
        cout<<"===== Testing math function: cosh() ====="<<endl;
        sv = cosh(sx + sda[0]*sda[0] + sy*sda[1]);
        eval(sv, sx, sy, x, y, results);
        REQUIRE(compare_vectors(v_cosh, results, eps));
    }

    SECTION("TANH"){
        cout<<"===== Testing math function: tanh() ====="<<endl;
        sv = tanh(sx + sda[0]*sda[0] + sy*sda[1]);
        eval(sv, sx, sy, x, y, results);
        REQUIRE(compare_vectors(v_tanh, results, eps));
    }

    SECTION("ATAN"){
        cout<<"===== Testing math function: atan() ====="<<endl;
        sv = atan(sx-1 + sda[0]*sda[0] + sy*sda[1]);
        eval(sv, sx, sy, x, y, results);
        REQUIRE(compare_vectors(v_atan, results, eps));
    }

    SECTION("DA_DER") {
        cout<<"===== Testing function: da_der() ====="<<endl;
        sv = exp(sx + sda[0]*sda[0] + sy*sda[1]);
        sv = da_der(sv, 0);
        eval(sv, sx, sy, x, y, results); 
        REQUIRE(compare_vectors(v_der, results, eps));
    }

    SECTION("DA_INT") {
        cout<<"===== Testing function: da_int() ====="<<endl;
        sv = exp(sx + sda[0]*sda[0] + sy*sda[1]);
        sv = da_int(sv, 0);
        eval(sv, sx, sy, x, y, results); 
        REQUIRE(compare_vectors(v_int, results, eps));
    }

    SECTION("SUB_CONST") {
        cout<<"===== Testing function:  da_substitute_const() ====="<<endl;
        sv = exp(sx + sda[0]*sda[0] + sy*sda[1]);
        SDA sz;
        da_substitute_const(sv, 0, 1, sz);
        sv = sz;
        eval(sv, sx, sy, x, y, results); 
        REQUIRE(compare_vectors(v_subc, results, eps));
    }

    SECTION("SUB") {
        cout<<"===== Testing function:  da_substitute() ====="<<endl;
        sv = exp(sx + sda[0]*sda[0] + sy*sda[1]);
        SDA sz, sw;
        sw = sqrt(sx + sda[0]*sda[0] + sy*sda[1]);
        da_substitute(sv, 0, sw, sz);
        sv = sz;
        eval(sv, sx, sy, x, y, results); 
        REQUIRE(compare_vectors(v_sub, results, eps));
    }

    SECTION("SUBV") {
        cout<<"===== Testing function:  da_substitute() ====="<<endl;
        sv = exp(sx + sda[0]*sda[0] + sy*sda[1]);
        SDA sz;
        std::vector<SDA> slv(2);
        slv.at(0) = sqrt(sx + sda[0]*sda[0] + sy*sda[1]);
        slv.at(1) = sin(sx + sda[0]*sda[0] + sy*sda[1]);
        std::vector<unsigned int> idx{0,1};
        da_substitute(sv, idx, slv, sz);
        sv = sz;
        eval(sv, sx, sy, x, y, results); 
        REQUIRE(compare_vectors(v_subv, results, eps));
    }

    SECTION("VSUB") {
        cout<<"===== Testing function:  da_substitute() ====="<<endl;
        std::vector<SDA> slv(2);
        slv.at(0) = sqrt(sx + sda[0]*sda[0] + sy*sda[1]);
        slv.at(1) = exp(sx + sda[0]*sda[0] + sy*sda[1]);
        std::vector<unsigned int> idx{0,1};
        std::vector<SDA> slx(3);
        std::vector<SDA> sly(3);
        slx.at(0) = sx + sda[0]*sda[0] + sy*sda[1];
        slx.at(1) = sin(sx + sda[0]*sda[0] + sy*sda[1]);
        slx.at(2) = cos(sx + sda[0]*sda[0] + sy*sda[1]);

        da_substitute(slx, idx, slv, sly);
        sv = sly.at(0);
        eval(sv, sx, sy, x, y, results); 
        REQUIRE(compare_vectors(v_vsub0, results, eps));
        sv = sly.at(1);
        eval(sv, sx, sy, x, y, results); 
        REQUIRE(compare_vectors(v_vsub1, results, eps));
        sv = sly.at(2);
        eval(sv, sx, sy, x, y, results); 
        REQUIRE(compare_vectors(v_vsub2, results, eps));
    }

    SECTION("COMP") {
        cout<<"===== Testing function:  da_composition() ====="<<endl;
        std::vector<SDA> slv(2);
        slv.at(0) = sqrt(sx + sda[0]*sda[0] + sy*sda[1]);
        slv.at(1) = exp(sx + sda[0]*sda[0] + sy*sda[1]);
        std::vector<SDA> slx(3);
        std::vector<SDA> sly(3);
        slx.at(0) = sx + sda[0]*sda[0] + sy*sda[1];
        slx.at(1) = sin(sx + sda[0]*sda[0] + sy*sda[1]);
        slx.at(2) = cos(sx + sda[0]*sda[0] + sy*sda[1]);

        da_composition(slx, slv, sly);
        sv = sly.at(0);
        eval(sv, sx, sy, x, y, results); 
        REQUIRE(compare_vectors(v_vsub0, results, eps));
        sv = sly.at(1);
        eval(sv, sx, sy, x, y, results); 
        REQUIRE(compare_vectors(v_vsub1, results, eps));
        sv = sly.at(2);
        eval(sv, sx, sy, x, y, results); 
        REQUIRE(compare_vectors(v_vsub2, results, eps));
    }

    SECTION("COMP") {
        cout<<"===== Testing function:  da_composition() ====="<<endl;
        std::vector<double> lv(2);
        lv.at(0) = x;
        lv.at(1) = y;
        std::vector<SDA> slx(3);
        std::vector<Expression> sly(3);
        slx.at(0) = sqrt(sx + sda[0]*sda[0] + sy*sda[1]);
        slx.at(1) = sin(sx + sda[0]*sda[0] + sy*sda[1]);
        slx.at(2) = cos(sx + sda[0]*sda[0] + sy*sda[1]);

        da_composition(slx, lv, sly);

        std::vector<SymEngine::RCP<const SymEngine::Basic>> vars{sx,sy};
        SymEngine::LambdaRealDoubleVisitor v;
        vector<double> results(3);
        v.init(vars, {sly.at(0).get_basic()});
        v.call(&results[0], &lv[0]);

        v.init(vars, {sly.at(1).get_basic()});
        v.call(&results[1], &lv[0]);

        v.init(vars, {sly.at(2).get_basic()});
        v.call(&results[2], &lv[0]);

        REQUIRE(compare_vectors(v_compc, results, eps));
    }

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
