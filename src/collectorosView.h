/*
*	AUTHOR: Levan Ostrowski
*   GIT: cod3venom
*	Email: lostrovski@greensoft.biz.pl
*   Created : 2021-04-02 02:23:35
*/

#ifndef __COLLECTOROSVIEW_H__
#define __COLLECTOROSVIEW_H__

#include <neatwin.h>
#include <neatctrl.h>
#include "Kernel/Boot/BootLoader.h"

class CCollectorosView : public CNeatView
{

public:
	virtual int OnCreate(PMAINWINCREATE lpCreateStruct);
	virtual int OnPaint();
	virtual int OnKeyDown(UINT nKeyCode, UINT nRepCnt, UINT nFlags);
};

#endif // __COLLECTOROSVIEW_H__
