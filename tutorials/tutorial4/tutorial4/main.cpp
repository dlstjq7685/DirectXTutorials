#include <Windows.h>
#include <d2d1.h>
#include <tchar.h>
#include <wingdi.h>
#include <windowsx.h>
#include <stdlib.h>
#include <iostream>
#include <wincodec.h>

#include "atlbase.h"  
#include "atlstr.h"  
#include "comutil.h"  
using namespace std;

#pragma comment( lib, "d2d1.lib" )
#pragma comment( lib, "dwrite.lib" )
#pragma comment( lib, "Kernel32.lib" )
#pragma comment( lib, "Windowscodecs.lib" )

/*
project -> property -> linker -> input -> addinational dependency -> ++ d2d1.lib;
warning  property config tap, must need to

DirectX Tutorial - 4
Load image tutorial
*/
ID2D1Factory* factory;
ID2D1HwndRenderTarget* rendertarget;
ID2D1Bitmap* bmp;



LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	//Windows Terminate Handler
	if (uMsg == WM_DESTROY)
	{
		if (bmp) bmp->Release();

		PostQuitMessage(0);
		return 0;
	}

	//Draw inner Windows 
	if (uMsg == WM_PAINT)
	{
		rendertarget->BeginDraw();
		rendertarget->DrawBitmap(
			bmp,
			D2D1::RectF(0.0f, 0.0f, bmp->GetSize().width, bmp->GetSize().height),
			1.0f,
			D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR
			, D2D1::RectF(0.0f, 0.0f, bmp->GetSize().width, bmp->GetSize().height)
		);


		rendertarget->EndDraw();

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


	HRESULT res = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory);
	if (res != S_OK) return false;

	RECT rects;
	GetClientRect(windowhandle, &rects);

	res = factory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(windowhandle, D2D1::SizeU(rects.right, rects.bottom)),
		&rendertarget);
	if (res != S_OK)return false;

	bmp = NULL;
	HRESULT hr;

	IWICImagingFactory *wicFactory = NULL;
	hr = CoCreateInstance(
		CLSID_WICImagingFactory,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IWICImagingFactory,
		(LPVOID*)&wicFactory
	);

	IWICBitmapDecoder *wicDecoder = NULL;
	hr = wicFactory->CreateDecoderFromFilename(
		L"test.png",
		NULL,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&wicDecoder
	);

	IWICBitmapFrameDecode* wicFrame = NULL;
	hr = wicDecoder->GetFrame(0, &wicFrame);

	IWICFormatConverter *wicConverter = NULL;
	hr = wicFactory->CreateFormatConverter(&wicConverter);

	hr = wicConverter->Initialize(
		wicFrame,
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		NULL,
		0.0,
		WICBitmapPaletteTypeCustom
	);

	hr = rendertarget->CreateBitmapFromWicBitmap(
		wicConverter,
		NULL,
		&bmp
	);


	if (wicFactory) wicFactory->Release();
	if (wicDecoder) wicDecoder->Release();
	if (wicConverter) wicConverter->Release();
	if (wicFrame) wicFrame->Release();




	while (GetMessage(&message, NULL, 0, 0))
	{
		DispatchMessage(&message);
	}

	return 0;
}