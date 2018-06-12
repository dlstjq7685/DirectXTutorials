#pragma once

class TextDraw
{
	IDWriteFactory* pDWriteFactory_;
	IDWriteTextFormat* pTextFormat_;

	const wchar_t* wszText_;
	UINT32 cTextLength_;

	ID2D1Factory* pD2DFactory_;
	ID2D1HwndRenderTarget* pRT_;
	ID2D1SolidColorBrush* pBlackBrush_;


public:
	TextDraw();
	~TextDraw();

	bool Init(HWND windowHandle);

	void DrawingText();
};