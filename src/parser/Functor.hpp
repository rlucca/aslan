#pragma once

class Parameter;
class Array;

class Functor : public Symbol
{
 public:
	Functor(unsigned identifier_line, char *identifier,
			Parameter* ps = 0, Array* as = 0);
	virtual ~Functor();

	Parameter *parms();
	Array *annots();

 protected:
	Parameter *m_parms;
	Array *m_annots;
};

std::ostream& operator<<(std::ostream& os, Functor* right);
