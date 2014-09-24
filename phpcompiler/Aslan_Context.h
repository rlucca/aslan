#pragma once

#include <iostream>

using namespace std;

class Aslan_Context
{
	public:
		void *scanner;	// the scanner state
		istream* is;	// input stream

		Aslan_Context(istream* is = &cin)
		{
			init_scanner();
			is->flags((is->flags() & ~std::ios::skipws));
			this->is = is;
		}

		virtual ~Aslan_Context()
		{
			destroy_scanner();
		}

protected: // defined in aslan.l
		void init_scanner();
		void destroy_scanner();
};

int Aslan_parse(Aslan_Context*);
