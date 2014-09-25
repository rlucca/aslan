#include "Aslan_Context.hpp"

Aslan_Context::Aslan_Context(istream* input)
{
	init_scanner();
	input->flags((input->flags() & ~std::ios::skipws));
	this->is = input;
}

Aslan_Context::~Aslan_Context()
{
	destroy_scanner();
}
