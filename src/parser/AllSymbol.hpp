#pragma once

enum {
	BELIEF_TYPE_SYMBOL = 'B',			// Belief
	CONSTANT_EXPRESSION_SYMBOL = 'I',	// Immutable
	FUNCTOR_SYMBOL = 'F',				// Functor
	EXPRESSION_SYMBOL = 'E',			// Expression
	PLAN_TYPE_SYMBOL = 'P',				// Plan
	PARAMETER_SYMBOL = 'C',				// Characteristic
	ARRAY_SET_SYMBOL = 'A',				// Array data set
	ACTION_TYPE_SYMBOL = 'D',			// Doing action
	EVENT_TYPE_SYMBOL = 'V',			// eVent type (Belief/Goal/Test)
};

#include "Symbol.hpp"
#include "Expression.hpp"
#include "ConstantExpression.hpp"
#include "Belief.hpp"
#include "Functor.hpp"
#include "Plan.hpp"
#include "StackedSymbol.hpp"
#include "Parameter.hpp"
#include "Array.hpp"
#include "Action.hpp"
