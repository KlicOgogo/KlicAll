#undef UNICODE
#include <windows.h>
#include <iostream>
#include <fstream>
#include "resource.h"
#include <vector>
#include <string>
#include <stdio.h>

using namespace std;

INT_PTR CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

static HINSTANCE h;
static int pos=0;
static HWND hEdit;
		
		
HWND rbuttons[5];

class Question
{
public:
	vector<string> ans;
	string ques;
	int right;
	int current;
	Question(vector<string> v,string s,int num): ans(v),ques(s),right(num),current(0){};
	bool compare()
	{
		return(right==current);
	}
};

static vector<Question> v;


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE, LPTSTR, int)
{
	h=hInstance;
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
	return 0;
}
INT_PTR CALLBACK DlgSubProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

INT_PTR CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{ 

	

	
	static ifstream in("Text.txt");
	
   
	switch (message)
	{
		
		
	case WM_INITDIALOG:
		{
			while(!in.eof())
		{
			string tmp;
		vector<string> e;
		getline(in,tmp);
		string s;
		getline(in,s);
		int k=s[0]-'0';
		for(int i=0;i<k;i++)
		{
			string tm;
			getline(in,tm);
			e.push_back(tm);
		}
		getline(in,s);
		int cur=s[0]-'0';
		
		v.push_back(Question(e,tmp,cur));
	
		}
		int f;
		/*HWND*/ hEdit=GetDlgItem(hDlg,IDC_EDIT1);
		SetWindowText(hEdit, v[pos].ques.c_str());
		for(int i=0;i<5;i++)
			rbuttons[i]=GetDlgItem(hDlg,IDC_RADIO1+i);
		for(int i=0;i<v[0].ans.size();i++)
			SetWindowText(rbuttons[i],v[0].ans[i].c_str());
		for(int i=v[0].ans.size();i<5;i++)
		{
			HWND hRadio=GetDlgItem(hDlg,IDC_RADIO1+i);
			ShowWindow(hRadio,SW_HIDE);
			//SetWindowText(rbuttons[i]," ");
		}

		return (INT_PTR)TRUE;
		}
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDC_RADIO1:
			v[pos].current=1;
			break;
		case IDC_RADIO2:
			v[pos].current=2;
			break;
		case IDC_RADIO3:
			v[pos].current=3;
			break;
		case IDC_RADIO4:
			v[pos].current=4;
			break;
		case IDC_RADIO5:
			v[pos].current=5;
			break;
		}
		if(LOWORD(wParam)==IDC_NEXT)
		{     if((pos+1)>=v.size());
		else
			pos++;
		SetWindowText(hEdit, v[pos].ques.c_str());
		for(int i=0;i<v[pos].ans.size();i++)
		{
			HWND hRadio=GetDlgItem(hDlg,IDC_RADIO1+i);
			ShowWindow(hRadio,SW_SHOW);
			SetWindowText(rbuttons[i],v[pos].ans[i].c_str());
		}
		for(int i=v[pos].ans.size();i<5;i++)
		{
			HWND hRadio=GetDlgItem(hDlg,IDC_RADIO1+i);
			ShowWindow(hRadio,SW_HIDE);
			//SetWindowText(rbuttons[i]," ");
		}
		CheckRadioButton(hDlg,IDC_RADIO1,IDC_RADIO5,IDC_RADIO1+v[pos].current-1);
		}
		if(LOWORD(wParam)==IDC_PREV)
		{
			if((pos-1)<0);
			else
			pos--;
			SetWindowText(hEdit, v[pos].ques.c_str());
			for(int i=0;i<v[pos].ans.size();i++)
			{

				HWND hRadio=GetDlgItem(hDlg,IDC_RADIO1+i);
			ShowWindow(hRadio,SW_SHOW);
			SetWindowText(rbuttons[i],v[pos].ans[i].c_str());
			}
		for(int i=v[pos].ans.size();i<5;i++)
		{
			HWND hRadio=GetDlgItem(hDlg,IDC_RADIO1+i);
			ShowWindow(hRadio,SW_HIDE);
		}
			//SetWindowText(rbuttons[i]," ");
		CheckRadioButton(hDlg,IDC_RADIO1,IDC_RADIO5,IDC_RADIO1+v[pos].current-1);
		}
		
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			char str[200];
			int result=0;
			for(int i=0;i<v.size();i++)
				if(v[i].compare()==true) result++;
			sprintf(str,"Правільных адказаў: %d.Усяго пытанняў: %d",result,v.size()-1);
			for(int i=0;i<10001;i++)
			MessageBeep(i);
			MessageBox(hDlg,str,"Вынік",NULL);
			EndDialog(hDlg, LOWORD(wParam));   
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
