#include <Windows.h>

//project -> property -> linker -> input -> addinational dependency -> ++ d2d1.lib;  
//warning  property config tap
//tutorial5 Rebuild Program loop, dont use WindowProc



LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_DESTROY) { PostQuitMessage(0); return 0; }
	DefWindowProc(hwnd, uMsg, wParam, lParam);

	if (uMsg == WM_PAINT)
	{
	}
}

int WINAPI wWinMain(HINSTANCE hInsatance, HINSTANCE prevInstance, LPWSTR cmd, int nCmdShow) {

	//window initialize-start
	WNDCLASSEX windowclass;
	ZeroMemory(&windowclass, sizeof(WNDCLASSEX));
	windowclass.cbSize = sizeof(WNDCLASSEX);
	windowclass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	windowclass.hInstance = hInsatance;
	windowclass.lpfnWndProc = WindowProc;
	windowclass.lpszClassName = "MainWindow";
	windowclass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClassEx(&windowclass);
	//windowsize-set
	RECT rect = { 0, 0, 800, 600 };
	AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, false, WS_EX_OVERLAPPEDWINDOW);

	HWND windowhandle = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, "MainWindow", "Direct dude", WS_OVERLAPPEDWINDOW,
		100, 100, rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, hInsatance, 0);
	if (!windowhandle) return -1;


	ShowWindow(windowhandle, nCmdShow);

	//window initialize-end


	MSG message;
	message.message = WM_NULL;


	//main loop
	while (message.message != WM_QUIT)
	{

		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{
			DispatchMessage(&message);
		}

		else
		{
			//Update here
			//running some loop

		}
	}
}