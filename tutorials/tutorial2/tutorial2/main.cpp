#include"Core.h"

/*
project -> property -> linker -> input -> addinational dependency -> ++ d2d1.lib;
warning  property config tap, must need to

DirectX Tutorial - 2
text render
*/

TextDraw* textdraw;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	if (uMsg == WM_DESTROY)
	{
		PostQuitMessage(0);
		return 0;
	}

	if (uMsg == WM_PAINT)
	{
		textdraw->DrawingText();
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI wWinMain(HINSTANCE hInsatance, HINSTANCE prevInstance, LPWSTR cmd, int nCmdShow) {

	WNDCLASSEX windowclass;
	ZeroMemory(&windowclass, sizeof(WNDCLASSEX));
	windowclass.cbSize = sizeof(WNDCLASSEX);
	windowclass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	windowclass.hInstance = hInsatance;
	windowclass.lpfnWndProc = WindowProc;
	windowclass.lpszClassName = "MainWindow";
	windowclass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClassEx(&windowclass);

	RECT rect = { 0, 0, 800, 600 };
	AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, false, WS_EX_OVERLAPPEDWINDOW);

	HWND windowhandle = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, "MainWindow", "Direct dude", WS_OVERLAPPEDWINDOW,
		100, 100, rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, hInsatance, 0);
	if (!windowhandle) return -1;

	textdraw = new TextDraw();

	if (!textdraw->Init(windowhandle))
	{
		delete textdraw;
		return -1;

	}

	ShowWindow(windowhandle, nCmdShow);

	MSG message;
	while (GetMessage(&message, NULL, 0, 0))
	{
		DispatchMessage(&message);
	}

	delete textdraw;

	return 0;
}