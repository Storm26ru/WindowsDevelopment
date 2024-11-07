#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include"resource.h"
#include<cstdio>

CONST CHAR* init_value[] = { "This","is", "my","first","List","Box"};
BOOL CALLBACK DlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK DlgProcAdd(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT nCmdShow)
{

	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1),NULL, DlgProc, 0);

	return 0;
}


BOOL CALLBACK DlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HWND hList = GetDlgItem(hWnd, IDC_LIST1);
		for (int i = 0; i < sizeof(init_value) / sizeof(init_value[0]); ++i)
		{
			SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)init_value[i]);
		}
	}
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON1: // Delete
		{
			HWND hList = GetDlgItem(hWnd, IDC_LIST1);
			SendMessage(hList, LB_DELETESTRING, SendMessage(hList, LB_GETCURSEL, 0, 0), 0);
			break;
		}
		case IDC_BUTTON2: //Add
			DialogBoxParam(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG2), hWnd, DlgProcAdd, 0);
			break;
		case IDOK: 
		{
			HWND hList = GetDlgItem(hWnd, IDC_LIST1);
			CONST INT SIZE = 256;
			CHAR sz_bufer[SIZE]{};
			CHAR sz_message[SIZE]{};
			INT i = SendMessage(hList, LB_GETCURSEL, 0, 0);
			SendMessage(hList, LB_GETTEXT, i, (LPARAM)sz_bufer);
			sprintf(sz_message, "Вы выбрали пункт №%i со значением \"%s\".", i, sz_bufer);
			MessageBox(hWnd, sz_message, "Info", MB_OK | MB_ICONINFORMATION); break;
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
BOOL CALLBACK DlgProcAdd(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
		SetFocus(GetDlgItem(hWnd, IDC_EDIT1));
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			INT SIZE = SendMessage(GetDlgItem(hWnd, IDC_EDIT1), EM_LINELENGTH, 0, 0) + 1;
			CHAR* bufer = new CHAR[SIZE];
			SendMessage(GetDlgItem(hWnd, IDC_EDIT1), WM_GETTEXT, SIZE, (LPARAM) bufer);
			if (SendMessage(GetDlgItem(GetParent(hWnd), IDC_LIST1), LB_FINDSTRING, -1, (LPARAM)bufer) == LB_ERR)
			{
				SendMessage(GetDlgItem(GetParent(hWnd), IDC_LIST1), LB_ADDSTRING, 0, (LPARAM)bufer);
				delete[] bufer;
				EndDialog(hWnd, 0);
			}
			else MessageBox(hWnd, "Такой элемент уже есть", "Info", MB_OK | MB_ICONINFORMATION);
		}
		break;
		case IDCANCEL: EndDialog(hWnd, 0); break;
		}
		break;
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		break;
	}
	return FALSE;
}