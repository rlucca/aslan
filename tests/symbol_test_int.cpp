#include "Symbol.hpp"
#include "Utils.hpp"
#include <cstring>
#include <cassert>

class SSS : public Symbol
{
	public:
		SSS(unsigned line, char *fool)
			: Symbol(1, line, fool)
		{
			// EMPTY
		}

		virtual void add(Symbol *t)
		{
			m_lexema = lexema_append(m_lexema, t->lexema());
			((SSS *) t)->m_lexema = 0; // This cast is soo ugly
			m_many++;
			// I am not sure if it is always true
			m_endLine =
				(t->lastLine() > m_endLine) ? t->lastLine() : m_endLine;
		}
};

#ifndef OTHER_TEST
// I feel like I am testing the C++ library...
// At leat I have one example with the add function
int main()
{
	SSS a(2, strdup("sss"));
	SSS b(4, strdup("baka"));

	assert(a.firstLine() == a.lastLine() && "both lines must be equals");
	assert(a.firstLine() == 2 && "both lines must be equals to 2");
	assert(a.manyComponents() == 1 && "must be 1");
	assert(a.type() == 1 && "must be 1");
	assert(a.getId() == 1 && "must be 1");
	assert(!strcmp(a.lexema(), "sss") && "must be exactly \"sss\"");

	assert(b.firstLine() == b.lastLine() && "both lines must be equals");
	assert(b.firstLine() == 4 && "both lines must be equals to 4");
	assert(b.manyComponents() == 1 && "must be 1");
	assert(b.type() == 1 && "must be 1");
	assert(b.getId() == 2 && "must be 2");
	assert(!strcmp(b.lexema(), "baka") && "must be exactly \"baka\"");

	a.add(&b);

	assert(a.firstLine() != a.lastLine() && "both lines must differ");
	assert(a.firstLine() == 2 && a.lastLine() == 4);
	assert(a.manyComponents() == 2 && "after add must be 1 + 1");
	assert(a.type() == 1 && "must be 1");
	assert(a.getId() == 1 && "must be 1");
	assert(!strcmp(a.lexema(), "sssbaka") && "must be exactly \"sssbaka\"");
	return 0;
}
#endif
