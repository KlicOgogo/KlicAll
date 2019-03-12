#include <iostream>

using namespace std;

extern "C" int __fastcall NoInSecond(int, int);
extern "C" int __fastcall Biggest(int);

int main()
{
	int a, b;
	cin >> a >> b;
	int t=NoInSecond (a, b);
	int tt=Biggest(b);
	cout << t << '\t' << tt << endl;
	return 0;
}