# Metalang99

[![CI](https://github.com/Hirrolot/metalang99/workflows/C/C++%20CI/badge.svg)](https://github.com/Hirrolot/metalang99/actions)
[![docs](https://img.shields.io/badge/docs-readthedocs.io-blue)](https://metalang99.readthedocs.io/en/latest/)
[![book](https://img.shields.io/badge/book-gitbook.io-pink)](https://hirrolot.gitbook.io/metalang99/)
[![spec](https://img.shields.io/badge/spec-PDF-green)](https://github.com/Hirrolot/metalang99/blob/master/spec/spec.pdf)
[![Support me on Patreon](https://img.shields.io/endpoint.svg?url=https%3A%2F%2Fshieldsio-patreon.vercel.app%2Fapi%3Fusername%3Dhirrolot%26type%3Dpatrons&style=flat)](https://patreon.com/hirrolot)

> The dark side of the force is a pathway to many abilities, some considered to be unnatural.<br>&emsp; &emsp; <b>-- Darth Sidious</b>

[[`examples/demo.c`](examples/demo.c)]
```c
#include <metalang99.h>

// Compile-time list manipulation {
// 3, 3, 3, 3, 3
static int five_threes[] = {
    M_listEvalCommaSep(M_listReplicate(v(5), v(3))),
};

// 5, 4, 3, 2, 1
static int from_5_to_1[] = {
    M_listEvalCommaSep(M_listReverse(M_list(v(1, 2, 3, 4, 5)))),
};

// 9, 2, 5
static int lesser_than_10[] = {
    M_listEvalCommaSep(M_listFilter(M_appl(v(M_uintGreater), v(10)), M_list(v(9, 2, 11, 13, 5)))),
};
// }

// General macro recursion {
#define factorial(n) M_call(factorial, n)

#define factorial_IMPL(n)   M_uintMatch(v(n), v(factorial_))
#define factorial_Z_IMPL()  v(1)
#define factorial_S_IMPL(n) M_uintMul(M_uintInc(v(n)), factorial(v(n)))

M_assertEq(factorial(v(4)), v(24));
// }

// Overloading on a number of arguments {
typedef struct {
    double width, height;
} Rect;

#define Rect_new(...)    M_overloadPlain(Rect_new_, __VA_ARGS__)
#define Rect_new_1(x)    ((Rect){.width = x, .height = x})
#define Rect_new_2(x, y) ((Rect){.width = x, .height = y})

static Rect _7x8 = Rect_new(7, 8), _10x10 = Rect_new(10);
// }

// ... and more!

int main(void) {
    // Yeah. All is done at compile time.
}
```

(Hint: `v(something)` evaluates to `something`.)

Metalang99 is a functional language aimed at full-blown C99 preprocessor metaprogramming.

It features a wide range of concepts, including algebraic data types, control flow operators, collections, general recursion, and auto-currying -- to develop both small and complex metaprograms painlessly.

## Table of contents

 - [Motivation](#motivation)
 - [Getting started](#getting-started)
 - [Optimisation guide](#optimisation-guide)
 - [Contributing](#contributing)
 - [Source code structure](#source-code-structure)
 - [FAQ](#faq)

## Motivation

The C macro system can be viewed as a tool to extend the language with custom syntactic sugar, to make code closer to a problem domain. However, the arsenal it provides is infinitely poor: all we can do is basic copy-pasting of tokens. We cannot even operate with control flow, integers, and unbounded sequences, thereby throwing a lot of hypothetically useful metaprograms out of scope.

To solve the problem, I have implemented Metalang99 -- a functional programming language executing on any standard-confirming preprocessor. Unlike other metaprogramming libraries, Metalang99 features:

 - **General recursion.** The syntax of recursive and non-recursive calls is the same so typically you will not find yourself in a sutiation where some macro accidentally gets [blueprinted] for some mysterious reason (macro blueprinting is a very hard-to-debug disaster). In particular, to implement recursion, [Boost/Preprocessor] just copy-pastes all recursive functions up to a certain limit and forces to either keep track of recursion depth or rely on built-in deduction; Metalang99 is free from such drawbacks.

 - **Partial application.** Besides easier use of higher-order metafunctions, partial application helps to capture an environment for a macro, thus avoiding the need in packing & unpacking auxiliary parameters.

 - **Debugging and error reporting.** You can conveniently debug your macros with `M_abort` and report fatal errors with `M_fatal`. The interpreter will immediately finish its work and do the trick.

[Boost/Preprocessor]: http://boost.org/libs/preprocessor

As a practical example of what is possible with Metalang99, consider [datatype99]. It implements type-safe [sum types] in pure C99, by heavy use of metaprogramming:

```c
// Sums all nodes of a binary tree.

#include <datatype99.h>

datatype(
    BinaryTree,
    (Leaf, int),
    (Node, struct BinaryTree *, int, struct BinaryTree *)
);

int sum(const BinaryTree *tree) {
    match(*tree) {
        of(Leaf, x) {
            return *x;
        }
        of(Node, lhs, x, rhs) {
            return sum(*lhs) + *x + sum(*rhs);
        }
    }
}
```

So, in summary, Metalang99 allows to do advanced metaprogramming in C. It allows to drastically improve quality of your code -- make it safer, cleaner, and more maintainable.

[blueprinted]: https://github.com/pfultz2/Cloak/wiki/C-Preprocessor-tricks,-tips,-and-idioms#recursion
[datatype99]: https://github.com/Hirrolot/datatype99
[sum types]: https://en.wikipedia.org/wiki/Tagged_union

## Getting started

```sh
$ git clone https://github.com/Hirrolot/metalang99.git
```

After that, you must add one more include path `metalang99/include`.

To use execute Metalang99 in your code, just `#include <metalang99.h>` beforehand (or include separate header files described in the documentation).

To speed up compilation, consider using [precompiled headers] and `-ftrack-macro-expansion=0` (GCC-only).

Resources:

 - [Tutorial](https://hirrolot.gitbook.io/metalang99/)
 - [Examples](examples/)
 - [User documentation](https://metalang99.readthedocs.io/en/latest/)

Happy hacking!

[precompiled headers]: https://en.wikipedia.org/wiki/Precompiled_header

## Optimisation guide

Generally speaking, the fewer reduction steps you perform, the faster you become. A reduction step is a concept formally defined in the [specification]. Here's its informal (and imprecise) description:

 - Every `v(...)` is a reduction step.
 - Every `M_call(op, ...)` induces as many reduction steps as required to evaluate `op` and `...` plus 1.

To perform fewer reduction steps, consider using `M_callTrivial` as well as the plain versions (e.g., `M_consumePlain` instead of `M_consume`), when possible.

## Contributing

See [`CONTRIBUTING.md`](CONTRIBUTING.md).

At this moment, contributions that optimise the interpreter and the standard library are highly appreciated.

## Source code structure

Metalang99 is split into two parts: the interpreter and the standard library.

The interpreter interprets the core metalanguage described in the [specification]. It is located in [`eval.h`] and [`eval/`]. The former file contains a machine written in [continuation-passing style] which is described in the specification too. [`eval/rec/`] contains a macro recursion engine upon which everything executes.

All the other files except [`priv/`] (private auxiliary stuff) comprise the standard library. 

[continuation-passing style]: https://en.wikipedia.org/wiki/Continuation-passing_style
[specification]: https://github.com/Hirrolot/metalang99/blob/master/spec/spec.pdf
[`eval.h`]: include/metalang99/eval.h
[`eval/`]: include/metalang99/eval/
[`eval/rec/`]: include/metalang99/eval/rec/
[`priv/`]: include/metalang99/priv/

## FAQ

### Q: Why not just use third-party code generators?

A:

 - Preprocessor macros are far more seamlessly integrated with a code base: you can invoke them in the same source files where ordinary code in C is written.
 - IDE support.
 - Avoid additional burden with distribution and setup of third-party code generators.

### Q: Compilation times?

A: To run the benchmarks, execute `./scripts/bench.sh` from the root directory.

### Q: Why formal specification?

A:

 - **Formal proofs.** With a mathematical model it becomes possible to prove things about Metalang99 formally; for example, the progress theorem, which can be stated as "the interpreter always knows what to do next".

 - **It guides the implementation.** The implementation gets adjusted with the specification (i.e. reflects the formal syntax and semantics), thereby making itself easier to reason about.

 - **It guides the tests.** We immediately see many, if not all corner cases, which are ought to be tested.

 - **Distinctness.** It is much easier to answer questions like "Is it a bug of the implementation or it is a valid behaviour according to the specification?".

That is, the development flow is "specification-driven", if you prefer.

### Q: Is Metalang99 Turing-complete?

A: Nope. The C/C++ preprocessor is capable to iterate only up to a certain limit (see this [SO question](https://stackoverflow.com/questions/3136686/is-the-c99-preprocessor-turing-complete)). For Metalang99, this limit is defined in terms of reductions steps (see the [specification]).

### Q: Why do we need powerful preprocessor macros in the presence of templates?

A: Metalang99 is primarily targeted at pure C, and C lacks templates. But anyway, you can find the argumentation for C++ at the website of [Boost/Preprocessor].

### Q: What standards are supported?

A: C99/C++11 and onwards.

### Q: Why not generate an amalgamated header?

A: I don't like amalgamated headers because they induce burden with updating. In contrast to this, you can just add Metalang99 as a [Git submodule] and update it with `git submodule update --remote`.

[Git submodule]: https://git-scm.com/book/en/v2/Git-Tools-Submodules
