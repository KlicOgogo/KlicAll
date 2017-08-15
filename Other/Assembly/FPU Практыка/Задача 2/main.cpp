#include <iostream>
#include <cmath>

using namespace std;

extern "C" double __cdecl lndva();
//extern "C" double __cdecl llndva();

int main()

{
	cout.precision(30);
	cout << lndva() << endl;
	//cout << llndva() << endl;
	cout << logf(2) << endl;
	return 0;
}
