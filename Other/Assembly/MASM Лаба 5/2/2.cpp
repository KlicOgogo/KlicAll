#include <iostream>

using namespace std;

extern "C" bool __fastcall sixttn(char*, int);
extern "C" int __fastcall tentth(char*, int);

int main()

{
	int kol;
	char lik[100];
	cin >> kol;
	cout << endl;
	for (int i=0; i<kol; i++)
		cin >> lik[i];
	lik[kol]='\0';
	bool t = sixttn(lik, kol);
	if (t)
	{
		int fin=tentth(lik, kol);
		cout << fin << endl;
	}
	else
		cout << "It's not a number!!" << endl;
	return 0;
}