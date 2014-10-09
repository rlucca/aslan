#include "Aslan_Context.hpp"

Aslan_Context::Aslan_Context(istream* inputs)
{
	init_scanner();
	setInputStream(inputs);
	setOutputStream(&cout);
}

Aslan_Context::~Aslan_Context()
{
	destroy_scanner();
}

istream *Aslan_Context::input()
{
	return this->is;
}

ostream *Aslan_Context::output()
{
	return this->os;
}

void Aslan_Context::setInputStream(istream *inputs)
{
	/* Always disable the flags */
	inputs->flags((inputs->flags() & ~std::ios::skipws));
	this->is = inputs;
}

void Aslan_Context::setOutputStream(ostream *outputs)
{
	this->os = outputs;
}
