#include "general_test.hpp"

#define STRING_TEST_EXPECTED								\
	EXPECT_LEX(DIV, sem, loc, ac, Aslan_lex);				\
	EXPECT_LEX(MOD, sem, loc, ac, Aslan_lex);				\
	EXPECT_LEX(MUL, sem, loc, ac, Aslan_lex);				\
	EXPECT_LEX(PLUS, sem, loc, ac, Aslan_lex);				\
	EXPECT_LEX(MINUS, sem, loc, ac, Aslan_lex);				\
	EXPECT_LEX(TEST, sem, loc, ac, Aslan_lex);				\
	EXPECT_LEX(COMMA, sem, loc, ac, Aslan_lex);				\
	EXPECT_LEX(CONTEXT, sem, loc, ac, Aslan_lex);			\
	EXPECT_LEX(SEQUENCE, sem, loc, ac, Aslan_lex);			\
	EXPECT_LEX(STRONG_NEGATION, sem, loc, ac, Aslan_lex);	\
	EXPECT_LEX(XOR_BIT, sem, loc, ac, Aslan_lex);			\
	EXPECT_LEX(DIFFERENT_CMP, sem, loc, ac, Aslan_lex);		\
	EXPECT_LEX(ACHIEVE, sem, loc, ac, Aslan_lex);			\
	EXPECT_LEX(EQUAL_CMP, sem, loc, ac, Aslan_lex);			\
	EXPECT_LEX(ASSIGNMENT, sem, loc, ac, Aslan_lex);		\
	EXPECT_LEX(AND_LOGIC, sem, loc, ac, Aslan_lex);			\
	EXPECT_LEX(AND_BIT, sem, loc, ac, Aslan_lex);			\
	EXPECT_LEX(OR_LOGIC, sem, loc, ac, Aslan_lex);			\
	EXPECT_LEX(SHIFTLEFT, sem, loc, ac, Aslan_lex);			\
	EXPECT_LEX(LESSEQUAL, sem, loc, ac, Aslan_lex);			\
	EXPECT_LEX(POINTER, sem, loc, ac, Aslan_lex);			\
	EXPECT_LEX(LESS, sem, loc, ac, Aslan_lex);				\
	EXPECT_LEX(SHIFTRIGHT, sem, loc, ac, Aslan_lex);		\
	EXPECT_LEX(GREATEQUAL, sem, loc, ac, Aslan_lex);		\
	EXPECT_LEX(GREAT, sem, loc, ac, Aslan_lex);				\
	EXPECT_LEX(NOT, sem, loc, ac, Aslan_lex)

int main()
{
	istringstream input("\n"
						"/%*+-?,:;~^ != ! == = && & || << <= <- < >> >= > not | \n"
						"(/%*+-?,:;~^ != ! == = && & || << <= <- < >> >= > nOt | )\n"
						"{/%*+-?,:;~^ != ! == = && & || << <= <- < >> >= > NoT | }\n"
						"[/%*+-?,:;~^ != ! == = && & || << <= <- < >> >= > NOT | ]\n"
						"\n");
	Aslan_Context ac(&input);
	MOC_LEX_DATA(loc, sem);

	STRING_TEST_EXPECTED;
	EXPECT_LEX(OR_BIT, sem, loc, ac, Aslan_lex);

	EXPECT_LEX(LEFTP, sem, loc, ac, Aslan_lex);
	STRING_TEST_EXPECTED;
	EXPECT_LEX(OR_BIT, sem, loc, ac, Aslan_lex);
	EXPECT_LEX(RIGHTP, sem, loc, ac, Aslan_lex);

	EXPECT_LEX(LEFTK, sem, loc, ac, Aslan_lex);
	STRING_TEST_EXPECTED;
	EXPECT_LEX(OR_BIT, sem, loc, ac, Aslan_lex);
	EXPECT_LEX(RIGHTK, sem, loc, ac, Aslan_lex);

	EXPECT_LEX(LEFTB, sem, loc, ac, Aslan_lex);
	STRING_TEST_EXPECTED;
	/*	Inside a block [] the OR_BIT is called SEParator operator.
		It is used to divide the head and tail of a list. */
	EXPECT_LEX(SEP, sem, loc, ac, Aslan_lex);
	EXPECT_LEX(RIGHTB, sem, loc, ac, Aslan_lex);

	return 0;
}
