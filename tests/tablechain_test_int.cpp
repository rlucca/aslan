#include "TableChain.hpp"

#define OTHER_TEST
#include "symbol_test_int.cpp"

#include <cassert>

static void testNoSectionToRemove(
		TableChain<Symbol> &tc)
{
	tc.pop();
	// Now we dont have a global section to remove
	tc.pop();

	assert(tc.n_sections() == 0);
	assert(tc.n_tokens() == 0);
}

static void testNoSectionAddingElement(
		TableChain<Symbol> &tc)
{
	SSS *a = new SSS(1, strdup("baka"));
	tc.add(a);

	assert(tc.n_sections() == 0);
	assert(tc.n_tokens() == 0 && "it isn't allowed to insert without sections");
	delete a;
}

static void testNoSectionPush(
		TableChain<Symbol> &tc)
{
	tc.push();

	assert(tc.n_sections() == 1);
	assert(tc.n_tokens() == 0);
}

static void testGlobalSectionCreateElements(
		TableChain<Symbol> &tc)
{
	SSS *a = new SSS(1, strdup("baka"));
	SSS *b = new SSS(1, strdup("+"));
	SSS *c = new SSS(1, strdup("2"));
	tc.add(a);
	tc.add(b);
	tc.add(c);

	assert(tc.n_sections() == 1);
	assert(tc.n_tokens() == 3);
}

static void testGlobalSectionFindAndPushAndFind(
		TableChain<Symbol> &tc)
{
	SSS *a = new SSS(8, strdup("foo"));
	SSS *b = new SSS(10, strdup("bar"));
	a->add(b);
	delete b;

	assert(tc.find(1, "baka") != tc.end());
	assert(tc.find(1, "+") != tc.end());
	assert(tc.find(1, "2") != tc.end());
	tc.push();
	assert(tc.find(1, "baka") == tc.end());
	assert(tc.find(1, "+") == tc.end());
	assert(tc.find(1, "end") == tc.end());

	assert(tc.find(1, "baka", true) != tc.end());
	assert(tc.find(1, "+", true) != tc.end());
	assert(tc.find(1, "end", true) == tc.end());
	assert(tc.find(1, "2", true) != tc.end());

	tc.add(a);
	assert(tc.find(7, "foobar") == tc.end());
	assert(tc.find(8, "foobar") != tc.end());
	assert(tc.find(9, "foobar") != tc.end());
	assert(tc.find(10, "foobar") != tc.end());
	assert(tc.find(11, "foobar") == tc.end());
}

int main()
{
	TableChain<Symbol> tc;
	testNoSectionToRemove(tc);
	testNoSectionAddingElement(tc);
	testNoSectionPush(tc);
	testGlobalSectionCreateElements(tc);
	testGlobalSectionFindAndPushAndFind(tc);
	return 0;
}
