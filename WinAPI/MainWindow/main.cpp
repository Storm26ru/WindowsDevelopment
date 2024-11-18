#include<Windows.h>

CONST CHAR g_sz_WINDOW_CLASS[] = "My Main Window";
INT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT nCmdShow)
{

	WNDCLASSEX wClass;
	ZeroMemory(&wClass, sizeof(wClass));
	wClass.style = 0;
	wClass.cbClsExtra = 0;
	wClass.cbWndExtra = 0;
	wClass.cbSize = sizeof(wClass);
	
	wClass.hIcon = LoadIcon(hInstance, IDI_APPLICATION);//https://learn.microsoft.com/ru-ru/windows/win32/menurc/about-icons
	wClass.hIconSm = LoadIcon(hInstance, IDI_APPLICATION);
	wClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wClass.hCursor = LoadCursor(hInstance, IDC_ARROW); //https://learn.microsoft.com/ru-ru/windows/win32/menurc/about-cursors

	wClass.lpszClassName = g_sz_WINDOW_CLASS;
	wClass.lpszMenuName = NULL;
	wClass.hInstance = hInstance;
	wClass.lpfnWndProc =(WNDPROC) WndProc;
	if (!RegisterClassEx(&wClass))
	{
		MessageBox(NULL, "Class registration failed", "", MB_OK | MB_ICONERROR);
		return 0;
	}
	HWND hWnd = CreateWindowEx(NULL, g_sz_WINDOW_CLASS, g_sz_WINDOW_CLASS, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
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
	case WM_COMMAND: break;
	case WM_DESTROY: PostQuitMessage(0); break;
	case WM_CLOSE: DestroyWindow(hWnd); break;
	default: return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;
}