#include <iostream>

extern "C" float* __cdecl raunn(float, float, float);

using namespace std;

int main()
{
	int a, b ,c;
	cin >> a >> b >> c;
	float* arr;
	int* intarr;
	int n;
	arr=raunn(a, b, c);
	intarr=(int*)arr;
	n=*intarr;
	for(int i=1; i<=n; i++)
		cout << arr[i] << endl;
	return 0;
}