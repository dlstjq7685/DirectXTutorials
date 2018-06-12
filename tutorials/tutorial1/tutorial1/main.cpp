#include<Windows.h>
/*
	project -> property -> linker -> input -> addinational dependency -> ++ d2d1.lib;  
	warning  property config tap, must need to

	DirectX Tutorial - 1
	create windows
*/

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	//Windows Terminate Handler
	if (uMsg == WM_DESTROY)
	{
		PostQuitMessage(0);
		return 0;
	}

	//Draw inner Windows 
	if (uMsg == WM_PAINT)
	{

	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI wWinMain(HINSTANCE hInsatance, HINSTANCE prevInstance, LPWSTR cmd, int nCmdShow) {

	WNDCLASSEX windowclass;
	
	//Initalize
	ZeroMemory(&windowclass, sizeof(WNDCLASSEX));
	windowclass.cbSize = sizeof(WNDCLASSEX);
	windowclass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	windowclass.hInstance = hInsatance;
	windowclass.lpfnWndProc = WindowProc;
	windowclass.lpszClassName = "MainWindow";
	windowclass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClassEx(&windowclass);

	//Windows Size Config
	RECT rect = { 0, 0, 800, 600 };
	AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, false, WS_EX_OVERLAPPEDWINDOW);

	//Hooking Windowhandler
	HWND windowhandle = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, "MainWindow", "Direct dude", WS_OVERLAPPEDWINDOW,
		100, 100, rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, hInsatance, 0);
	if (!windowhandle) return -1;

	//Execute Window
	ShowWindow(windowhandle, nCmdShow);

	MSG message;

	while (GetMessage(&message, NULL, 0, 0))
	{
		DispatchMessage(&message);
	}


	return 0;
}