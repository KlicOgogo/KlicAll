#include <iostream>

using namespace std;

extern "C" char* __stdcall concatt (char*, int, char*, int);
int main()
{
	int kol1, kol2;
	char str1[100], str2[100];
	cin >> kol1;
	for (int i=0; i<kol1; i++)
		cin >> str1[i];
	str1[kol1]='\0';
	cin >> kol2;
	for (int i=0; i<kol2; i++)
		cin >> str2[i];
	str2[kol2]='\0';
	char* str3= concatt(str1, kol1, str2, kol2);
	for (int i=0; i<kol1+kol2; i++)
		cout << str3[i];
	cout << endl;
	return 0;
}