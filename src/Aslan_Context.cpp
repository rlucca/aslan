#include "Aslan_Context.hpp"

Aslan_Context::Aslan_Context(istream* inputs)
{
	init_scanner();
	setInputStream(inputs);
}

Aslan_Context::~Aslan_Context()
{
	destroy_scanner();
}

istream *Aslan_Context::input()
{
	return this->is;
}

void Aslan_Context::setInputStream(istream *inputs)
{
	/* Always disable the flags */
	inputs->flags((inputs->flags() & ~std::ios::skipws));
	this->is = inputs;
}
