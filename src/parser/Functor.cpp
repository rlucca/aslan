#include "AllSymbol.hpp"
#include "Utils.hpp"

Functor::Functor(char *identifier, unsigned identifier_line,
				Symbol* parms, Symbol* annots)
	: Symbol(FUNCTOR_SYMBOL, identifier_line,
			lexema_cat(
				lexema_cat(identifier, (parms)?parms->lexema():NULL),
				(annots)?annots->lexema():NULL)
			)
{ }
