#include <iostream>

using namespace std;

extern "C" char* __fastcall bezprob (int, char*);

int main()

{
	int len;
	char rad[100];
	cin.get(rad, 100);
	cin >> len;
	char* fin=bezprob (len, rad);
	for (int i=0; i<strlen(fin); i++)
		cout << fin[i];
	cout << endl;
	return 0;
}