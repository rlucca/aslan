#pragma once

#include <iostream>

using namespace std;

/** It's the proxy between the program and the flex/yacc.
	It keep the scanner and a reference to where get
	new data (cin or a istringstream). */
class Aslan_Context
{
public:
		void *scanner;	//< the scanner state
		istream* is;	//< input stream

		Aslan_Context(istream* input = &cin);
		virtual ~Aslan_Context();

protected: // defined in aslan.l
		void init_scanner();
		void destroy_scanner();
};

int Aslan_parse(Aslan_Context*);
