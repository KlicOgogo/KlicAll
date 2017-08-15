#include <iostream>

using namespace std;

extern "C" int __cdecl summm1(int, int, int);
extern "C" int __stdcall summm2 (int, int, int);
extern "C" int  __fastcall mull (int, int);
extern "C" int __fastcall  summ (int, int);

int main()
{
	int a, b, x;
	cin >> a >> x >> b;
	int r=summm1 (a, x, b);
	int r1=summm2 (a, x, b);
	int rr=summ(mull(a, x), b);
	int r3=mull(a, x);
	int r2=summ(r3, b);
	cout << r << endl;
	cout << r1 << endl;
	cout << r2 << endl;
	cout << rr << endl;
	return 0;
}