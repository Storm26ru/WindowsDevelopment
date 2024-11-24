#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<stdio.h>


CONST CHAR g_sz_WINDOW_CLASS[] = "My Main Window";
INT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HICON hSizeNS,hArrow,hSizeNESW,hSizeNWSE,hSizeWE;

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT nCmdShow)
{
	INT Screen_widht = GetSystemMetrics(SM_CXSCREEN);
	INT Screen_hight = GetSystemMetrics(SM_CYSCREEN);

	hSizeNS = (HICON)LoadImage(hInstance, "ico\\SizeNS.ani", IMAGE_CURSOR, 0, 0, LR_LOADFROMFILE);
	hArrow = (HICON)LoadImage(hInstance, "ico\\Arrow.ani", IMAGE_CURSOR, 0, 0, LR_LOADFROMFILE);
	hSizeWE = (HICON)LoadImage(hInstance, "ico\\SizeWE.ani", IMAGE_CURSOR, 0, 0, LR_LOADFROMFILE);
	hSizeNWSE = (HICON)LoadImage(hInstance, "ico\\SizeNWSE.ani", IMAGE_CURSOR, 0, 0, LR_LOADFROMFILE);
	hSizeNESW = (HICON)LoadImage(hInstance, "ico\\SizeNESW.ani", IMAGE_CURSOR, 0, 0, LR_LOADFROMFILE);

	WNDCLASSEX wClass;
	ZeroMemory(&wClass, sizeof(wClass));
	wClass.style = 0;
	wClass.cbClsExtra = 0;
	wClass.cbWndExtra = 0;
	wClass.cbSize = sizeof(wClass);
	//wClass.hIcon =LoadIcon(hInstance,MAKEINTRESOURCE(IDI_ICON1));
	//wClass.hIconSm =LoadIcon(hInstance,MAKEINTRESOURCE(IDI_ICON2));
	wClass.hIcon =(HICON)LoadImage(hInstance,"ico\\web.ico",IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	wClass.hIconSm = (HICON)LoadImage(hInstance, "ico\\burn.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	wClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wClass.hCursor = (HCURSOR)LoadImage(hInstance, "ico\\Arrow.ani", IMAGE_CURSOR, 0, 0, LR_LOADFROMFILE);
	//LoadCursor(hInstance, IDC_ARROW); 

	wClass.lpszClassName = g_sz_WINDOW_CLASS;
	wClass.lpszMenuName = NULL;
	wClass.hInstance = hInstance;
	wClass.lpfnWndProc =(WNDPROC) WndProc;
	if (!RegisterClassEx(&wClass))
	{
		MessageBox(NULL, "Class registration failed", "", MB_OK | MB_ICONERROR);
		return 0;
	}
	HWND hWnd = CreateWindowEx(NULL, g_sz_WINDOW_CLASS, g_sz_WINDOW_CLASS, WS_OVERLAPPEDWINDOW, Screen_widht/8, Screen_hight/8,
		Screen_widht*.75, Screen_hight*.75, NULL, NULL, hInstance, NULL);
	if (hWnd == NULL)
	{
		MessageBox(NULL, "Window creation failed", "", MB_OK | MB_ICONERROR);
		return 0;
	}
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

INT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE: break;
	case WM_SETCURSOR:
		switch (LOWORD(lParam))
		{
		case HTTOPRIGHT:
		case HTBOTTOMLEFT:
			SetCursor(hSizeNESW); break;
		case HTTOPLEFT:
		case HTBOTTOMRIGHT:
			SetCursor(hSizeNWSE); break;
		case HTLEFT:
		case HTRIGHT:
			SetCursor(hSizeWE); break;
		case HTTOP:
		case HTBOTTOM:
			SetCursor(hSizeNS); break;
		default:
			SetCursor(hArrow); 
		}break;
	case WM_MOVE:
	case WM_SIZE:
	{
		//WINDOWINFO wInfo;
		//wInfo.cbSize = sizeof(wInfo);
		//GetWindowInfo(hWnd, &wInfo);
		RECT rect;
		GetWindowRect(hWnd, &rect);
		CONST INT SIZE = 256;
		CHAR wt_bufer[SIZE]{};
		sprintf(wt_bufer, " %s  Size - %ix%i  Position - x%i;y%i",g_sz_WINDOW_CLASS,rect.right-rect.left,
				rect.bottom-rect.top,rect.left,rect.top);
		SendMessage(hWnd, WM_SETTEXT, 0, (LPARAM)wt_bufer); break;
	}	
	case WM_COMMAND: break;
	case WM_DESTROY: PostQuitMessage(0); break;
	case WM_CLOSE: DestroyWindow(hWnd); break;
	default: return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;
}