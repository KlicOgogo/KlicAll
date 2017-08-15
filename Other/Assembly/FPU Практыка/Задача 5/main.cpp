#include <iostream>

using namespace std;

extern "C" float __cdecl summa(float, float);

int main()
{
	float x, eps;
	cin >> x >> eps;
	cout << summa(x, eps) << endl;
	return 0;
}