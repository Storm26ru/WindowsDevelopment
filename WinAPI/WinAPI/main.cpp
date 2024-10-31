﻿#include<Windows.h>
#include"resource.h"
//#include<CommCtrl.h>
#include<windowsx.h>
//#define MESSAGE_BOX

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	
#ifdef MESSAGE_BOX
	MessageBox
	(
		NULL,
		"Hello WinAPI!\n Это окно сообщения", "Info",
		MB_YESNOCANCEL | MB_ICONWARNING | MB_DEFBUTTON2 | MB_HELP
	);
#endif // MESSAGE_BOX

	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc, 0);

	return 0;
}
BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
		HWND hEdit = GetDlgItem(hwnd, IDC_EDIT1);
		SendMessage(hwnd, WM_SETICON, 0, (LPARAM)hIcon);
		SetWindowText(hEdit, "Inter text");

		
	}
	break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_EDIT1:
			if (HIWORD(wParam) == EN_SETFOCUS) SetWindowText((HWND)lParam, "");
				//&&strcmp())//https://learn.microsoft.com/ru-ru/cpp/c-runtime-library/reference/strcmp-wcscmp-mbscmp?view=msvc-170
			if (HIWORD(wParam) == EN_KILLFOCUS&&SendMessage((HWND)lParam,EM_LINELENGTH,0,0)==0) SetWindowText((HWND)lParam, "Inter text");

			break;
		case IDC_BUTTON1:
		{
			HWND hEdit1 = GetDlgItem(hwnd, IDC_EDIT1);
			HWND hEdit2 = GetDlgItem(hwnd, IDC_EDIT2);
		    INT SIZE =  SendMessage(hEdit1, EM_LINELENGTH, 0, 0);
			CHAR* bufer = new CHAR[SIZE + 1];
			//*((LPWORD)bufer) = SIZE;
			SendMessage(hEdit1, EM_GETLINE,0,(LPARAM)bufer);
			bufer[SIZE] = 0;
			SetWindowText(hEdit2, bufer);
			delete [] bufer;
		} break;
		
		case IDOK:MessageBox(hwnd, "Была нажата кнопка ОК", "Info", MB_OK | MB_ICONINFORMATION); break;
		case IDCANCEL: EndDialog(hwnd, 0); break;
		}
		break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);
		break;
	}
		return FALSE;
}
