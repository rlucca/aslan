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

		Aslan_Context(istream* input = &cin);
		virtual ~Aslan_Context();

		istream *input();
		ostream *output();
		void setInputStream(istream *input);
		void setOutputStream(ostream *output);

protected: // defined in aslan.l
		void init_scanner();
		void destroy_scanner();

		istream* is;	//< input stream
		ostream* os;	//< output stream
};

int Aslan_parse(Aslan_Context*);
