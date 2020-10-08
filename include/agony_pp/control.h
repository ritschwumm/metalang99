/**
 * @file
 * @brief Control expressions.
 */

#ifndef AGONY_PP_CONTROL_H
#define AGONY_PP_CONTROL_H

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#include "control/if.h"
#include "control/while.h"

#endif // DOXYGEN_SHOULD_SKIP_THIS

/**
 * @brief @p x if @p cond expands to 1, otherwise @p y.
 */
#define AGONY_PP_IF(cond, x, y) AGONY_PP_PRIVATE_EVAL_AUX_IF(cond, x, y)

/**
 * @brief Executes @p op as long as @p predicate holds for @p context.
 */
#define AGONY_PP_WHILE(predicate, op, context) AGONY_PP_PRIVATE_WHILE(predicate, op, context)

#endif // AGONY_PP_CONTROL_H