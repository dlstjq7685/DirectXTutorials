#include "Core.h"
#include "TextDraw.h"

TextDraw::TextDraw() {

	pDWriteFactory_ = NULL;
	pTextFormat_ = NULL;
	pD2DFactory_ = NULL;
	pRT_ = NULL;
	pBlackBrush_ = NULL;
}

TextDraw::~TextDraw() {

	if (pDWriteFactory_)
		pDWriteFactory_->Release();

	if (pTextFormat_)
		pTextFormat_->Release();

	if (pD2DFactory_)
		pD2DFactory_->Release();

	if (pRT_)
		pRT_->Release();

	if (pBlackBrush_)
		pBlackBrush_->Release();
}

bool TextDraw::Init(HWND windowHandle)
{
	HRESULT res = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pD2DFactory_);
	if (res != S_OK) return false;

	res = DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(IDWriteFactory),
		reinterpret_cast<IUnknown**>(&pDWriteFactory_)
	);

	if (res != S_OK) return false;

	wszText_ = L"Hello World using  DirectWrite!";
	cTextLength_ = (UINT32)wcslen(wszText_);

	res = pDWriteFactory_->CreateTextFormat(
		L"Gabriola",                // Font family name.
		NULL,                       // Font collection (NULL sets it to use the system font collection).
		DWRITE_FONT_WEIGHT_REGULAR,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		72.0f,
		L"en-us",
		&pTextFormat_
	);
	if (res != S_OK) return false;

	res = pTextFormat_->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	if (res != S_OK) return false;

	res = pTextFormat_->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	if (res != S_OK) return false;

	RECT rc;
	GetClientRect(windowHandle, &rc);
	D2D1_SIZE_U size = D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top);

	if (!pRT_)
	{
		// Create a Direct2D render target.
		HRESULT res = pD2DFactory_->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(
				windowHandle,
				size
			),
			&pRT_
		);

		// Create a black brush.
		if (res == S_OK)
		{
			res = pRT_->CreateSolidColorBrush(
				D2D1::ColorF(D2D1::ColorF::Black),
				&pBlackBrush_
			);
		}
	}


	return true;
}


void TextDraw::DrawingText()
{
	pRT_->BeginDraw();
	D2D1_RECT_F layoutRect = D2D1::RectF(0, 0, 500, 400);

	pRT_->SetTransform(D2D1::IdentityMatrix());
	pRT_->Clear(D2D1::ColorF(D2D1::ColorF::White));

	pRT_->DrawText(wszText_, cTextLength_, pTextFormat_, layoutRect, pBlackBrush_);
	pRT_->EndDraw();



}
