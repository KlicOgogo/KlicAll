#include <iostream>

using namespace std;

extern "C" float __cdecl integ(float, float);
//extern "C" float __cdecl graal(float, float);
int main()

{
	float fin;
	fin=integ(0, 3.1415926*2);
	cout << fin << endl;
//	fin=graal(0, 3.1415926*2);
//	cout << fin << endl;
	return 0;
}