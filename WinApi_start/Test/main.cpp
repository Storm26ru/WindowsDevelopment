#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include"resource.h"
#include<stdio.h>

CONST CHAR* init_bufer[] = { "This","is","my","first","Combo","Box" };
BOOL CALLBACK DlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT nCmdShow)
{
	DialogBoxParam(hInstance,MAKEINTRESOURCE(IDD_DIALOG1),NULL,DlgProc,0) ;

	return 0;
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
		for (int i = 0; i < sizeof(init_bufer) / sizeof(init_bufer[0]); i++)
		{
			SendMessage(GetDlgItem(hWnd, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM) init_bufer[i]);
		}
	break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			CONST INT SIZE = 256;
			CHAR bufer[SIZE]{};
			CHAR m_bufer[SIZE]{};
			INT I = SendMessage(GetDlgItem(hWnd, IDC_COMBO1), CB_GETCURSEL, 0, 0);
			SendMessage(GetDlgItem(hWnd, IDC_COMBO1), WM_GETTEXT, SIZE, (LPARAM)bufer);
			sprintf(m_bufer, "Вы выбрали пункт №%i со значением\"%s\". ", I, bufer);
			MessageBox(hWnd, m_bufer, "Info", MB_OK | MB_ICONINFORMATION);
		}break;
		case IDCANCEL: EndDialog(hWnd, 0); break;
		}

	case WM_CLOSE: EndDialog(hWnd, 0);
		break;
	}



	return FALSE;
}