#include <iostream>
#include <cmath>

using namespace std;

extern "C" float __cdecl pokazat(float, float);
int main()

{
	float x;
	cin >> x;
	cout << pow (0.5, x) << '\t'  << pokazat (0.5, x) << endl;
	return 0;
}