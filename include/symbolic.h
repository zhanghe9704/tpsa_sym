#ifndef SYMBOLIC
#define SYMBOLIC

#include <symengine/expression.h>
#include <symengine/functions.h>
#include <symengine/simplify.h>

bool is_zero(SymEngine::Expression x);
void simplified_expr(SymEngine::Expression& x);

inline SymEngine::Expression operator/(int i, const SymEngine::Expression expr) {
    return SymEngine::Expression(i)/expr;
}

#endif // SYMBOLIC