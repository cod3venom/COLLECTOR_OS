#include "collectoros.h"

int CCollectorosFrame::OnCreate(PMAINWINCREATE lpCreateStruct)
{
	CNeatRect rect;
	GetClientRect( &rect );
	this->ClientToScreen(&rect);
	m_View.Create("",WS_VISIBLE|WS_CHILD,
				  rect.left,rect.top,rect.Width(),rect.Height(),
				  this);

	return CNeatWnd::OnCreate(lpCreateStruct);
}

bool CCollectorosApp::OnInit(int args, const char* arg[])
{
	CCollectorosFrame* p_Frame = new CCollectorosFrame;
	p_Frame->Create("CollectorOS", WS_THINFRAME|WS_CAPTION );
	p_Frame->ShowWindow(SW_SHOW);
	return true;
}

int CCollectorosApp::OnExit()
{
	return 0;
}

IMPLEMENT_APP(CCollectorosApp);

int NeatPluginCompileCheck(void)
{
	return 0;
}