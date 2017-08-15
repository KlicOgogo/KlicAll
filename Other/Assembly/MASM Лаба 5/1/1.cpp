#include <iostream>

using namespace std;

extern "C" int __cdecl poww (int, int);
int main()
{
	int a, n;
	cout << "a= ";
	cin >> a;
	cout << "n= ";
	cin >> n;
	cout << endl;
	int x=poww(a,n);
	cout << x << "\t" << endl;
	return 0;
}