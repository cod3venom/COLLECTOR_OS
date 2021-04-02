/*
*	AUTHOR: Levan Ostrowski
*   GIT: cod3venom
*	Email: lostrovski@greensoft.biz.pl
*   Created : 2021-04-02 02:23:35
*/

#ifndef __COLLECTOROS_H__
#define __COLLECTOROS_H__

#include <neatwin.h>
#include "collectorosView.h"

// 定义一框架窗口类
class CCollectorosFrame : public CNeatFrameWnd
{
public:
	// 事件处理函数
	virtual int OnCreate(PMAINWINCREATE lpCreateStruct);

protected:
	CCollectorosView m_View;
};

// 定义应用程序类
class CCollectorosApp : public CNeatApp
{
public:
	// 程序初始化事件消息响应函数
	virtual bool OnInit(int args, const char* arg[]);

	// 程序退出事件消息响应函数
	virtual int OnExit();
};

#endif // __COLLECTOROS_H__
