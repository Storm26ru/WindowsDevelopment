#include<Windows.h>
#include"resource.h"


CONST CHAR* init_values[] = { "This","is","my","first","Combo", "Box" };
BOOL CALLBACK DlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR CmdLine, INT CmdShow)
{

	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc, 0);


	return 0;
}


BOOL CALLBACK DlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_INITDIALOG:
	{
		HWND hCombo = GetDlgItem(hWnd, IDC_COMBO1);
		for (int i = 0; i < sizeof(init_values) / sizeof(init_values[0]); i++)
		{
			SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)init_values[i]);
		}
	}
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			MessageBox(hWnd, "Нажата кнопка ОК", "Info", MB_OK | MB_ICONINFORMATION); break;
		}
		case IDCANCEL:
			EndDialog(hWnd, 0); break;
		}
		break;
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		break;
	}

	return FALSE;


}