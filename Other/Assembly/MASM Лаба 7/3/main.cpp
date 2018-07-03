#include <iostream>

using namespace std;

extern "C" int __fastcall showord(int, char*);

int main()
{
	char str[100];
	int len;
	cin.get(str, 100);
	cin >> len;
	int t=showord(len, str);
	cout << t << endl;
	return 0;
}