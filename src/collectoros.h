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

// ����һ��ܴ�����
class CCollectorosFrame : public CNeatFrameWnd
{
public:
	// �¼�������
	virtual int OnCreate(PMAINWINCREATE lpCreateStruct);

protected:
	CCollectorosView m_View;
};

// ����Ӧ�ó�����
class CCollectorosApp : public CNeatApp
{
public:
	// �����ʼ���¼���Ϣ��Ӧ����
	virtual bool OnInit(int args, const char* arg[]);

	// �����˳��¼���Ϣ��Ӧ����
	virtual int OnExit();
};

#endif // __COLLECTOROS_H__
