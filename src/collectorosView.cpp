#include "collectorosView.h"

 
int CCollectorosView::OnCreate(PMAINWINCREATE lpCreateStruct)
{
	return CNeatView::OnCreate(lpCreateStruct);
}

int CCollectorosView::OnPaint()
{
	CNeatPaintDC dc(this);
	CNeatRect rect;
	GetClientRect( &rect );
	BootLoader bootLoader(this);
	bootLoader.Load();
	return 1;
}

int CCollectorosView::OnKeyDown(UINT nKeyCode, UINT nRepCnt, UINT nFlags)
{
	return CNeatView::OnKeyDown(nKeyCode,nRepCnt,nFlags);
}