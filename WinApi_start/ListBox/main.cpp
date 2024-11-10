#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include"resource.h"
#include<stdio.h>


CONST CHAR* init_bufer[] = { "This","is","my","first","List","Box" };

BOOL CALLBACK DlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK DlgProcAdd(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

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
	{
		for (int i=0; i < sizeof(init_bufer) / sizeof(init_bufer[0]); i++)
		{
			SendMessage(GetDlgItem(hWnd, IDC_LIST1), LB_ADDSTRING, 0, (LPARAM)init_bufer[i]);
		}
	}
		break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			CONST INT SIZE = 256;
			CHAR bufer[SIZE]{};
			CHAR m_bufer[SIZE]{};
			INT i = SendMessage(GetDlgItem(hWnd, IDC_LIST1), LB_GETCURSEL, 0, 0);
			SendMessage(GetDlgItem(hWnd, IDC_LIST1), LB_GETTEXT, i, (LPARAM)bufer);
			sprintf(m_bufer, "Вы выбрали пункт №%i со значением \"%s\".", i, bufer);
			MessageBox(hWnd, m_bufer, "Info", MB_OK | MB_ICONINFORMATION);
		}
		case IDC_BUTTON1://Delete
			SendMessage(GetDlgItem(hWnd, IDC_LIST1), LB_DELETESTRING, SendMessage(GetDlgItem(hWnd, IDC_LIST1),
			LB_GETCURSEL, 0, 0), 0); break;
		case IDC_BUTTON2://Add
			DialogBoxParam(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG2), hWnd, DlgProcAdd, 0);
		}break;
	}
		break;
	case WM_CLOSE: EndDialog(hWnd, 0); break;
	}

	return FALSE;

}
BOOL CALLBACK DlgProcAdd(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
		SetFocus(GetDlgItem(hWnd, IDC_EDIT1)); break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			CONST INT SIZE = 256;
			CHAR bufer[SIZE]{};
			SendMessage(GetDlgItem(hWnd, IDC_EDIT1), WM_GETTEXT, SIZE, (LPARAM)bufer);
			SendMessage(GetDlgItem(GetParent(hWnd), IDC_LIST1), LB_ADDSTRING, 0, (LPARAM)bufer);
			EndDialog(hWnd, 0);
		}break;
		case IDCANCEL: EndDialog(hWnd, 0); break;

		}break;
	}
	return FALSE;
}