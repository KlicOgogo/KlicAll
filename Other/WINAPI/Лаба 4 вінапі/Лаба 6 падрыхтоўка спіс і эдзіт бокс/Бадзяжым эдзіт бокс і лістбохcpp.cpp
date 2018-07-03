#undef UNICODE

#include <windows.h>
#include "resource.h"
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>


using namespace std;

INT_PTR CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE, LPTSTR, int)
{
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
	return 0;
}

INT_PTR CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static vector <string> myw;
	static HWND hEdit;
	static string temp;
	static int n=-1;
	switch (message)
	{
	case WM_INITDIALOG:
		{
			hEdit=GetDlgItem (hDlg,IDC_EDIT1);
			ifstream fin("radki.txt");
			while (!fin.eof())
			{
				string s;
				getline(fin,s);
				myw.push_back(s);
				char buf[100];
				strcpy( buf, s.c_str() );
				SendDlgItemMessage (hDlg, IDC_LIST1, LB_ADDSTRING, 0, (LPARAM)&buf); //s
			}
			return (INT_PTR)TRUE;
		}
	case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
			case IDOK:
			case IDCANCEL:
				{
					EndDialog(hDlg, LOWORD(wParam));
					return (INT_PTR)TRUE;
				}
			case IDC_EDIT1:
				{
					if (HIWORD(wParam)==EN_CHANGE)
					{
						char buf[100];
						GetWindowText (hEdit,buf,100);
						temp=buf;
					}
					break;
				}
			case IDC_BUTTON1:
				{
					char buf[100];
					GetWindowText (hEdit,buf,100);
					temp=buf;
					myw.push_back(temp);
					//strcpy( buf, temp.c_str() );
					SendDlgItemMessage (hDlg, IDC_LIST1, LB_ADDSTRING, 0,(LPARAM)&buf); //temp
					SetWindowText (hEdit,"");
					break;
				}
			case IDC_BUTTON2:
				{
					n=SendDlgItemMessage (hDlg, IDC_LIST1, LB_GETCURSEL, 0,0);
					myw[n]=temp;
					SendDlgItemMessage (hDlg, IDC_LIST1, LB_DELETESTRING, n,0);
					char buf[100];
					strcpy( buf, temp.c_str() );
					SendDlgItemMessage (hDlg, IDC_LIST1, LB_INSERTSTRING, n,(LPARAM)&buf);
					SetWindowText (hEdit,"");
					break;
				}
			case IDC_LIST1:
				{
					if (HIWORD(wParam)==LBN_SELCHANGE)
					{
						char buf[100];
						SendDlgItemMessage (hDlg,IDC_LIST1,LB_GETTEXT,SendDlgItemMessage (hDlg,IDC_LIST1,LB_GETCURSEL,0,0),(LPARAM)&buf);
						SetWindowText (hEdit, buf);
					}
					break;
				}
			}
			break;
		}
	}
	return (INT_PTR)FALSE;
}


