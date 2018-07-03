#include <iostream>

extern "C" int* __fastcall center (int, int*);
extern "C" int* __fastcall second (int, int*);
extern "C" int* __fastcall mider (int, int*);
extern "C" int* __fastcall reper (int, int*);
extern "C" int* __fastcall lowsum (int, int*);

using namespace std;

int main()
{
	int arr[100], kol;
	cin >> kol;
	for (int i=0; i<kol; i++)
		cin >> arr[i];
	int* b=center(kol, arr);
	int* a=second(kol, arr);
	int* c=mider(kol, arr);
	int* d=reper(kol, arr);
	int* e=lowsum(kol, arr);
	cout << b << '\t' << *b << endl;
	cout << a << '\t' << *a << endl;
	cout << c << '\t' << *c << endl;
	cout << d << '\t' << *d << endl;
	cout << e << '\t' << *e << endl;
	return 0;
}