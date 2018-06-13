#include <Windows.h>
#include <windowsx.h>


//project -> property -> linker -> input -> addinational dependency -> ++ d2d1.lib;  
//warning  property config tap
//tutorial3 Mouse Keyboard input
//mouse: GET_X_LPARAM, GET_Y_LPARAM
//keyboard: GetKeyState(VK_F1)


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	LPCSTR msg;

	//Windows Terminate Handler
	if (uMsg == WM_DESTROY)
	{
		PostQuitMessage(0);
		return 0;
	}

	//Draw inner Windows 
	if (uMsg == WM_PAINT)
	{
		//textdraw->DrawingText();
	}


	if (uMsg == WM_MOUSEMOVE)
	{
		int xPos = GET_X_LPARAM(lParam);
		int yPos = GET_Y_LPARAM(lParam);
		char *temp = (char *)malloc(sizeof(char) * 5);


		_itoa_s(xPos, temp, 5, 10);

		msg = temp;
		OutputDebugString(msg);

		free(temp);
	}

	if (GetKeyState(VK_F1))
	{
		msg = "F1\n";
		OutputDebugString(msg);

	}


	switch (uMsg)
	{
	case WM_SYSKEYDOWN:
		msg = "WM_SYSKEYDOWN\n";
		OutputDebugString(msg);
		break;

	case WM_SYSCHAR:
		msg = "WM_SYSCHAR\n";
		OutputDebugString(msg);
		break;

	case WM_SYSKEYUP:
		msg = "WM_SYSKEYUP\n";
		OutputDebugString(msg);
		break;

	case WM_KEYDOWN:
		msg = "WM_KEYDOWN\n";
		OutputDebugString(msg);
		break;

	case WM_KEYUP:
		msg = "WM_KEYUP\n";
		OutputDebugString(msg);
		break;

	case WM_CHAR:
		msg = "WM_CHAR\n";
		OutputDebugString(msg);
		break;

		/* Handle other messages (not shown) */

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

	ShowWindow(windowhandle, nCmdShow);


	MSG message;
	while (GetMessage(&message, NULL, 0, 0))
	{
		DispatchMessage(&message);
	}

	return 0;
}