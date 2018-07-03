#include <iostream>

using namespace std;

extern "C" bool __fastcall ispal (int, char*);

int main()

{
	char radok[100];
	int leng;
	cin >> leng;
	for (int i=0; i<leng; i++)
		cin >> radok[i];
	radok[leng]='\0';
	bool is=ispal(leng, radok);
	if (is)
		cout << "yes" << endl;
	else
		cout << "no" << endl;
	return 0;
}