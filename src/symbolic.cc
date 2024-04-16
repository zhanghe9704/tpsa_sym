#include symbolic.H

using SymEngine::Expression;
using SymEngine::simplify;
using SymEngine::expand;

bool is_zero(Expression x) {
    Expression y = simplify(expand(x));
    return y == Expression(0);
}

void simplified_expr(Expression& x) {
    x = simplify(expand(x));
}