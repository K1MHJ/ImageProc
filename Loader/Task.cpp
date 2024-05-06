#include "pch.h"
#include "Task.h"


static CBitmap m_bmp;

void CTask::Filter(CBitmap*& dst, CBitmap& src)
{
	dst = &m_bmp;
	dst->Attach(src.Detach());

	BITMAP bmp;
	dst->GetBitmap(&bmp);
	PBYTE row = (PBYTE)bmp.bmBits;

	for (int i = 0; i < bmp.bmHeight/2; ++i) {
		PBYTE col = row;
		for (int j = 0; j < bmp.bmWidth/2; ++j) {
			col[0] = 0x00;
			col[1] = 0xFF;
			col[2] = 0xFF;
			col += 4;
		}
		row += bmp.bmWidthBytes;
	}
}
void CTask::Filter2(CBitmap*& dst, CBitmap& src)
{
	dst = &m_bmp;
	dst->Attach(src.Detach());

	BITMAP bmp;
	dst->GetBitmap(&bmp);
	PBYTE row = (PBYTE)bmp.bmBits + bmp.bmHeight / 2 * bmp.bmWidthBytes;

	for (int i = bmp.bmHeight/2; i < bmp.bmHeight; ++i) {
		PBYTE col = row + bmp.bmWidth / 2 * 4;
		for (int j = bmp.bmWidth/2; j < bmp.bmWidth; ++j) {
			col[0] = 0xFF;
			col[1] = 0xFF;
			col[2] = 0xFF;
			col += 4;
		}
		row += bmp.bmWidthBytes;
	}
}

