#include <metalang99/assert.h>
#include <metalang99/aux.h>

#define FOO(x, y) M_assertPlain(x == 518 && y == 1910)

// M_id {
M_eval(v(FOO) M_id(v((518, 1910))));
M_assertEq(M_appl(M_compose(v(M_id), v(M_id)), v(181)), v(181));
// }

// M_parenthesise {
M_eval(v(FOO) M_parenthesise(v(518, 1910)));
// }

#undef FOO

// M_unparenthesiseEval {
M_assertEq(M_unparenthesiseEval(v((v(198)))), v(198));
// }

// M_unparenthesise {
M_assertEq(M_unparenthesise(v((198))), v(198));
// }

// M_parenthesiseEval + M_unparenthesiseEval {
M_assertEq(M_unparenthesiseEval(M_parenthesiseEval(v(187))), v(187));
// }

// M_parenthesise + M_unparenthesise {
M_assertEq(M_unparenthesise(M_parenthesise(v(187))), v(187));
// }

// M_const, M_const2, M_const3 {
M_assertEq(M_appl2(v(M_const), v(1810), v(~)), v(1810));
M_assertEq(M_appl3(v(M_const2), v(1810), v(~), v(~)), v(1810));
M_assertEq(M_appl(M_appl3(v(M_const3), v(1810), v(~), v(~)), v(~)), v(1810));
// }

#define ABC v(M_true)

// M_flip {
M_assert(M_appl2(M_flip(v(M_catEval)), v(C), v(AB)));
// }

// M_putBefore, M_putAfter, M_putBetween {
M_assertEq(M_putBefore(v(0), v(!)), v(!0));
M_assertEq(M_putAfter(v(!), v(0)), v(!0));
M_assertEq(M_putBetween(v(16), v(9), v(+)), v(16 + 9));
// }

#undef ABC

// M_isParenthesised, M_isUnparenthesised {
M_assert(M_isParenthesised(v((1, 2, 3))));
M_assert(M_not(M_isParenthesised(v(123))));

M_assert(M_not(M_isUnparenthesised(v((1, 2, 3)))));
M_assert(M_isUnparenthesised(v(123)));
// }

// M_consume {
M_assertEmpty(M_consume(v(1, 2, 3)));
// }

// M_semicolon {
M_semicolon();
M_semicolon();

void test_semicolon(void) {
    M_semicolon();
    M_semicolon();

    {
        M_semicolon();
        M_semicolon();

        {
            M_semicolon();
            M_semicolon();
        }
    }
}
// }

// M_braced {
struct TestBraced M_eval(M_braced(v(int a, b, c;)));
// }
