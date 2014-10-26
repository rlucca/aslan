#include "AllSymbol.hpp"
#include "Utils.hpp"

Belief::Belief(Symbol *head, Symbol *opt_context)
	: Symbol(BELIEF_TYPE_SYMBOL, head->firstLine(),
			lexema_cat(head->lexema(),
						(opt_context) ? opt_context->lexema() : NULL))
	{ }
