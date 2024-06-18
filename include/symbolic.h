#ifndef SYMBOLIC
#define SYMBOLIC

#include <symengine/expression.h>
#include <symengine/functions.h>
#include <symengine/simplify.h>

bool is_zero(SymEngine::Expression x);
void simplified_expr(SymEngine::Expression& x);

//Overloading operator "/"
inline SymEngine::Expression operator/(int i, const SymEngine::Expression expr) {
    return SymEngine::Expression(i)/expr;
}

inline SymEngine::Expression operator/(const SymEngine::Expression expr, int i) {
    return expr/SymEngine::Expression(i);
}

inline SymEngine::Expression operator/(unsigned int i, const SymEngine::Expression expr) {
    return SymEngine::Expression(i)/expr;
}

inline SymEngine::Expression operator/(const SymEngine::Expression expr, unsigned int i) {
    return expr/SymEngine::Expression(i);
}

inline SymEngine::Expression operator/(double d, const SymEngine::Expression expr) {
    return SymEngine::Expression(d)/expr;
}

inline SymEngine::Expression operator/(const SymEngine::Expression expr, double d) {
    return expr/SymEngine::Expression(d);
}

//Overloading operator "*"
inline SymEngine::Expression operator*(int i, const SymEngine::Expression expr) {
    return SymEngine::Expression(i)*expr;
}

inline SymEngine::Expression operator*(const SymEngine::Expression expr, int i) {
    return expr*SymEngine::Expression(i);
}

inline SymEngine::Expression operator*(unsigned int i, const SymEngine::Expression expr) {
    return SymEngine::Expression(i)*expr;
}

inline SymEngine::Expression operator*(const SymEngine::Expression expr, unsigned int i) {
    return expr*SymEngine::Expression(i);
}

inline SymEngine::Expression operator*(double d, const SymEngine::Expression expr) {
    return SymEngine::Expression(d)*expr;
}

inline SymEngine::Expression operator*(const SymEngine::Expression expr, double d) {
    return expr*SymEngine::Expression(d);
}


//Overloading operator "+"
inline SymEngine::Expression operator+(int i, const SymEngine::Expression expr) {
    return SymEngine::Expression(i)+expr;
}

inline SymEngine::Expression operator+(const SymEngine::Expression expr, int i) {
    return expr+SymEngine::Expression(i);
}

inline SymEngine::Expression operator+(unsigned int i, const SymEngine::Expression expr) {
    return SymEngine::Expression(i)+expr;
}

inline SymEngine::Expression operator+(const SymEngine::Expression expr, unsigned int i) {
    return expr+SymEngine::Expression(i);
}

inline SymEngine::Expression operator+(double d, const SymEngine::Expression expr) {
    return SymEngine::Expression(d)+expr;
}

inline SymEngine::Expression operator+(const SymEngine::Expression expr, double d) {
    return expr+SymEngine::Expression(d);
}

//Overloading operator "-"
inline SymEngine::Expression operator-(int i, const SymEngine::Expression expr) {
    return SymEngine::Expression(i)-expr;
}

inline SymEngine::Expression operator-(const SymEngine::Expression expr, int i) {
    return expr-SymEngine::Expression(i);
}

inline SymEngine::Expression operator-(unsigned int i, const SymEngine::Expression expr) {
    return SymEngine::Expression(i)-expr;
}

inline SymEngine::Expression operator-(const SymEngine::Expression expr, unsigned int i) {
    return expr-SymEngine::Expression(i);
}

inline SymEngine::Expression operator-(double d, const SymEngine::Expression expr) {
    return SymEngine::Expression(d)-expr;
}

inline SymEngine::Expression operator-(const SymEngine::Expression expr, double d) {
    return expr-SymEngine::Expression(d);
}


#endif // SYMBOLIC