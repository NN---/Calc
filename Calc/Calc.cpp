// Calc.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Calculator.h"
#include "resource.h"

HINSTANCE g_hInstance;

LRESULT CALLBACK CalcDlg(HWND hDlg,UINT uMsg,WPARAM wParam,LPARAM lParam);
LRESULT CALLBACK AboutDlg(HWND hDlg,UINT uMsg,WPARAM wParam,LPARAM lParam);

int main()
{
	g_hInstance=GetModuleHandle(NULL);
	DialogBox(g_hInstance,MAKEINTRESOURCE(IDD_CALC),HWND_DESKTOP,(DLGPROC)CalcDlg);
	ExitProcess(0);
}

LRESULT CALLBACK CalcDlg(HWND hDlg,UINT uMsg,WPARAM wParam,LPARAM /*lParam*/)
{
	switch(uMsg)
	{
		case WM_INITDIALOG:
			{
				HICON hIcon=LoadIcon(g_hInstance,MAKEINTRESOURCE(IDI_CALC));
				SendMessage(hDlg,WM_SETICON,ICON_BIG,(LPARAM)hIcon);
				SendMessage(hDlg,WM_SETICON,ICON_SMALL,(LPARAM)hIcon);
				SendDlgItemMessage(hDlg,IDC_EXPRESSION,EM_SETLIMITTEXT,MAX_CALC_STRING,0);
				HMENU hMenu=GetSystemMenu(hDlg,FALSE);
				TCHAR szAbout[50];
				LoadString(g_hInstance,IDS_ABOUT,szAbout,50);
				AppendMenu(hMenu,MF_SEPARATOR,0,0);
				AppendMenu(hMenu,MF_STRING,IDM_ABOUT,szAbout);
			}
			break;
		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
				case IDC_EXPRESSION:
					switch(HIWORD(wParam))
					{
						case EN_CHANGE:
							{
								TCHAR szText[MAX_CALC_STRING];
								GetDlgItemText(hDlg,IDC_EXPRESSION,szText,MAX_CALC_STRING);
								Calculator calc(szText);
								SetDlgItemText(hDlg,IDC_RESULT,calc.GetResultS());
							}
						break;
					}
				break;
				case IDC_EXIT:
					EndDialog(hDlg,0);
					break;
			}
			break;
		case WM_SYSCOMMAND:
			if(wParam == IDM_ABOUT)
				DialogBox(g_hInstance,MAKEINTRESOURCE(IDD_ABOUT),hDlg,(DLGPROC)AboutDlg);
			break;
		case WM_CLOSE:
			EndDialog(hDlg,0);
			break;
	}
	return 0;
}

LRESULT CALLBACK AboutDlg(HWND hDlg,UINT uMsg,WPARAM wParam,LPARAM /*lParam*/)
{
	switch(uMsg)
	{
		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
				case IDC_EMAIL:
					ShellExecute(hDlg,"open","mailto:NN<nn-mail@bk.ru>",NULL,NULL,SW_SHOW);
					break;
				case IDC_SITE:
					ShellExecute(hDlg,"open","http://our-site.nm.ru",NULL,NULL,SW_SHOW);
					break;
				case IDOK:
					EndDialog(hDlg,0);
					break;
			}
			break;
		case WM_CLOSE:
			EndDialog(hDlg,0);
			break;
	}
	return 0;
}