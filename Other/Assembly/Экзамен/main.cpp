#undef UNICODE
#include<vector>
#include <iostream>  
#include <iomanip>
#include <windows.h>
#include <algorithm>
#include "resource.h"

using namespace std;

BOOL CALLBACK DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

extern "C" float __cdecl ary(float);
extern "C" float __cdecl tryga(float);
extern "C" float __cdecl laga(float);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), 0, DlgProc);
	return 0;
}
BOOL CALLBACK DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lparam)
{
	static char ch1[100];
	static double x1;
	static float fin;
	static char buf[100];
	switch (message)
	{
	case WM_INITDIALOG:

		return FALSE;
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON1:
			GetDlgItemText(hwnd, IDC_EDIT1, ch1, 100);
			x1=atof(ch1);
			fin=ary((float)x1);
			sprintf(buf, "%.6f", fin);
			SetDlgItemText(hwnd, IDC_EDIT1, buf);
			break;
		case IDC_BUTTON2:
			GetDlgItemText(hwnd, IDC_EDIT1, ch1, 100);
			x1=atof(ch1);
			fin=tryga((float)x1);
			sprintf(buf, "%.6f", fin);
			SetDlgItemText(hwnd, IDC_EDIT1, buf);
			break;
		case IDC_BUTTON3:
			GetDlgItemText(hwnd, IDC_EDIT1, ch1, 100);
			x1=atof(ch1);
			fin=laga((float)x1);
			sprintf(buf, "%.6f", fin);
			SetDlgItemText(hwnd, IDC_EDIT1, buf);
			break;
		case IDOK:
			EndDialog(hwnd, LOWORD(wParam));
			return TRUE;
		}
	}
	return FALSE;

}

