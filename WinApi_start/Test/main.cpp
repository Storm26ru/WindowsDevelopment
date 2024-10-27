#include<Windows.h>
#include"resource.h"

BOOL CALLBACK DlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT nCmdShow)
{
	//MessageBox(NULL, "HELLOW WINAPI\nЭто текстовое собщение", "Info", MB_ABORTRETRYIGNORE | MB_ICONINFORMATION | MB_DEFBUTTON1);
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG2), NULL,DlgProc,0 );
	return 0;
}
BOOL CALLBACK DlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON11));
		SendMessage(hWnd, WM_SETICON, 0, (LPARAM)hIcon);
	} break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK: MessageBox(hWnd, "Была нажата кнопка ОК", "Info", MB_OK | MB_ICONINFORMATION); break;
		case IDCANCEL: EndDialog(hWnd, 0); break;
		}
	case WM_CLOSE: EndDialog(hWnd, 0); break;
	}
	return FALSE;

}