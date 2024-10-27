#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include"resource.h"
#include<cstdio>

CONST CHAR* init_values[] = { "This", "is","my","first","Combo","Box" };

BOOL CALLBACK DlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT nCmdShow)
{

	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc, 0);

	return 0;
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{HWND hCombo = GetDlgItem(hWnd, IDC_COMBO1); 
	for (int i = 0; i < sizeof(init_values) / sizeof(init_values[0]); i++)
	{
		SendMessage(hCombo, CB_ADDSTRING, 0,(LPARAM)init_values[i]);
	}
	}
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		{HWND hCombo = GetDlgItem(hWnd, IDC_COMBO1);
		CONST INT SIZE = 256;
		CHAR sz_buffer[SIZE]{};
		CHAR sz_message[SIZE]{};
		INT i = SendMessage(hCombo, CB_GETCURSEL, 0, 0);
		SendMessage(hCombo, CB_GETLBTEXT, i, (LPARAM)sz_buffer);
		sprintf(sz_message, "Вы выбрали пункт №%i созначением \"%s\".", i, sz_buffer);
		MessageBox(hWnd, sz_message, "Selected value", MB_OK | MB_ICONINFORMATION);
		break;
		}
		case IDCANCEL: EndDialog(hWnd, 0); break;
		}
		break;
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		break;
	}
	return FALSE;
}