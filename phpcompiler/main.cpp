#include <iostream>
#include "Aslan_Context.h"

using namespace std;

int main()
{
	Aslan_Context context;

	if(!Aslan_parse(&context))
	{
		cout << "OK" << endl;
	}
}
