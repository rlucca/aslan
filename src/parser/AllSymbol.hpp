#pragma once

enum {
	BELIEF_TYPE_SYMBOL = 'B',			// Belief
	CONSTANT_EXPRESSION_SYMBOL = 'I',	// Immutable
	FUNCTOR_SYMBOL = 'F',				// Functor
	EXPRESSION_SYMBOL = 'E',			// Expression
	PLAN_TYPE_SYMBOL = 'P',				// Plan
	PARAMETER_SYMBOL = 'C',				// Characteristic
};

#include "Symbol.hpp"
#include "Expression.hpp"
#include "ConstantExpression.hpp"
#include "Belief.hpp"
#include "Functor.hpp"
#include "Plan.hpp"
#include "StackedSymbol.hpp"
#include "Parameter.hpp"
