/*!
 *			Copyright (C) 2010-2015	Newland Computer (FuJian) Co.,Ltd.
 * @License	�����´�½���Թɷ����޹�˾
 *
 * @file	pt80WifiManager.h
 * @brief	PT80 WIFI������
 * @author  NEAT TEAM <neat@newlandcomputer.com>
 * @version 1.00
 * @date    2011-11-01 initial version
 */
#ifndef _PT80WIFIMANAGER_H_
#define _PT80WIFIMANAGER_H_

#include "settings.h"
#include "wx/string.h"
#include "wx/thread.h"
#include "wx/dynarray.h"
#include "wx/app.h"
#include "wx/config.h"
#include "neatdef.h"

/**
  * @defgroup group_WifiOpt PT80WIFI������
  * @{
  */
#ifdef __LINUX__
#include "pt80/nlinux/include/wifi.h"
#else
enum WifiFlags {
	WIFI_FLAGS_NONE = 0,    
	WIFI_FLAGS_WEP  = 1,    
	WIFI_FLAGS_WPA  = 2,    
	WIFI_FLAGS_WPA2 = 4,    
	WIFI_FLAGS_WPA2_EAP= 8,    
};

typedef struct {
	char ssid[128]; 
	char bssid[20]; 
	int frequency;  
	int quality;    
	int level;      
	int noise;      
	int flags;      
} WifiNetwork;

typedef struct {
	int networkid; /**< @brief network ID */
	char ssid[128];	/**< @brief SSID */
	int flags; /**< @brief */
}WifiConfigNetwork;

#endif
/** @brief ����WIFI������Ϣ����Կ�Ļ�����Ԫ
  * @note ���ೣ���ڻ�ȡWIFIɨ�����ʹ����µ�WIFI����
  */
class Pt80WifiNetworkListItem{
public:
	WifiNetwork net; /**< WIFI����������Ϣ */
	wxString strUser; /**< WPA-ENT ��Կ��֤��ʽ */
	wxString strKey; /**< ��Կ��������ʱʹ�� */
	wxString strEAP; /**< EAP���� */
	wxString strPhase2Authentication ;/**< �׶�2�����֤��ʽ */
}; 

/** @brief ����WIFI����������Ϣ������Ԫ 
  * @note ����ֻ��::GetLocalNetwork ��ʹ��
  */
class Pt80WifiNetworkConfigListItem{
public:
	WifiConfigNetwork config;

};

/** @brief ���� Pt80WifiNetworkList 
  * @note ���ڴ洢WIFIɨ����
  */
WX_DEFINE_ARRAY(Pt80WifiNetworkListItem *, Pt80WifiNetworkList); 

/** @brief ���� Pt80WifiNetworkConfigList 
  * @note ���ڴ洢��ȡ����������Ϣ
  */
WX_DEFINE_ARRAY(Pt80WifiNetworkConfigListItem *, Pt80WifiNetworkConfigList);


/** @brief WIFIMANAGER����Ϣ*/
enum MSG_COMMAND_WIFI{
	MSG_COMMAND_WIFI_BASE = 0x1000, /**< WIFI��Ϣ������δʹ�� */
// scan 
	MSG_COMMAND_WIFI_SCANSTART,		/**< WIFI�ѿ�ʼɨ�� */
	MSG_COMMAND_WIFI_EXIT,			/**< �̴߳������� */
	MSG_COMMAND_WIFI_ERROR,			/**< ����         */
	MSG_COMMAND_WIFI_TIMEOUT,		/**< ɨ�賬ʱ     */
	MSG_COMMAND_WIFI_RESULT,		/**< ɨ����     */
	MSG_COMMAND_WIFI_USERBREAK,		/**< ���û��ж�   */
	MSG_COMMAND_WIFI_NORESULT,		/**< û��ɨ���� */
// addnetwork
	MSG_COMMAND_WIFI_ADDNETWORK,	/**< ����WIFI���� */
// enablenetwork
	MSG_COMMAND_WIFI_ENABLENETWORK, /**< ����WIFI���� */
// getstatus
	MSG_COMMAND_WIFI_GETSTATUS,		/**< ȡ״̬��Ϣ,lwParam�����::GETSTATUS_PARAM_RETVAL */
};
/** @brief ȡ״̬��Ϣ lwParam���� */
enum GETSTATUS_PARAM_RETVAL{
	GETSTATUS_EXIT=0,		/**< �߳��˳��󷵻� */
	GETSTATUS_ERROR,		/**< ����wifi�����ʼ��ʧ�� */
	GETSTATUS_TIMEOUT,		/**< ��timeoutʱ����δ������wifi */
	GETSTATUS_COMPLETED,	/**< WIFI�����ӣ��ڽӵ�����Ϣ���߳̽��˳� */
	GETSTATUS_CONNECTING,	/**< WIFI�������� */
	GETSTATUS_DISCONNECT,	/**< WIFIδ���� */
};
/************************************************************************/
/* main class															*/
/************************************************************************/
class CPt80WifiThread_Scan;
class CPt80WifiThread_EnableNetwork;
class CPt80WifiThread_AddNetwork;
class CPt80WifiThread_GetStatus;
/** @class CPt80WifiManager WIFI���������� 
  * WIFI ����������
  */
class SDKIMPORT CPt80WifiManager
{
public:
	CPt80WifiManager();
	~CPt80WifiManager();
	/** @brief ɨ��
	  * @param[in] hwnd �����Ĵ��ڣ�����������Ϣ
	  * @param[in] timeout ��λ����
	  * @param[out] m_list ָ��Pt80WifiNetworkList������ָ��
	  * @return ���ؽ��
	  * @retval 0 �ɹ�
	  * @retval <0 ʧ��
	  * @note ��Ҫ�����COMMAND: 
	  * @li ::MSG_COMMAND_WIFI_EXIT
	  * @li ::MSG_COMMAND_WIFI_ERROR 
	  * @li ::MSG_COMMAND_WIFI_TIMEOUT
	  * @li ::MSG_COMMAND_WIFI_RESULT
	  * @li ::MSG_COMMAND_WIFI_USERBREAK
	  * @li ::MSG_COMMAND_WIFI_NORESULT
	  */
	int Scan(HWND hwnd, int timeout, Pt80WifiNetworkList *m_list);

	/** @brief �����µ�WIFI����
	  * @param[in] m_item ָ��Pt80WifiNetworkListItem��ָ�룬
	  * @return ���ؽ��
	  * @retval >=0 �����ı�������ID�������ڿ����������
	  * @retval <0 ʧ��
	  * @note ���������һ��ʱ�䣬�Ƽ�ʹ���̰߳汾 
	  */
	int AddNewNetwork(Pt80WifiNetworkListItem *m_item);

	/** @brief �����µ�WIFI����
	  * @param[in] m_item ָ��Pt80WifiNetworkListItem��ָ�룬
	  * @param[in] IshiddenAP ��ӵ������Ƿ�������AP(���㲥SSID)
	  * @return ���ؽ��
	  * @retval >=0 �����ı�������ID�������ڿ����������
	  * @retval <0 ʧ��
	  * @note ���������һ��ʱ�䣬�Ƽ�ʹ���̰߳汾 
	  */
	int AddNewNetwork(Pt80WifiNetworkListItem *m_item, bool IshiddenAP);

	/** @brief �����µ�WIFI����(�̰߳汾)		�ýӿ��ѷ���
	  * @param[in] hwnd �����Ĵ��ڣ�����������Ϣ
	  * @param[in] m_item ָ��Pt80WifiNetworkListItem��ָ�룬
	  * @return ���ؽ��
	  * @retval =0 �߳������ɹ�
	  * @note ��Ҫ���� MSG_COMMAND_WIFI_ADDNETWORK, ����1(lParam) >=0 �����ı�������ID�������ڿ����������
	  */
	int AddNewNetwork(HWND hwnd, Pt80WifiNetworkListItem *m_item);
	
	/** @brief �������� 
	  * @param[in] id ��������ID 
	  * @retrun ���ؽ��
	  * @retval =0 �ɹ�
	  * @retval <0 ʧ��
	  * @note ���Բ�ʹ���̰߳汾
	  */
	int EnableNetwork(int id );


	/** @brief ��������(�߳�)
	  * @param[in] id ��������ID 
	  * @retrun ���ؽ��
	  * @retval =0 �ɹ�
	  * @retval <0 ʧ��
	  * @note ��Ҫ������Ϣ MSG_COMMAND_WIFI_ENABLENETWORK  lwParamΪ0
	  */
	int EnableNetwork(HWND hwnd, int timeout, int id);

	/** @brief ɾ����������
	  * @param[in] id ��������ID 
	  * @retrun ���ؽ��
	  * @retval =0 �ɹ�
	  * @retval <0 ʧ��'
	  */
	int RemoveNetwork(int id);

	/** @brief ��ȡ��ǰ������״̬(�̰߳汾)
	  * @param[in] hwnd �����Ĵ��ڣ�����������Ϣ
	  * @param[in] timeout �ܲ�ѯʱ�䣬ÿ��1�뷢��::MSG_COMMAND_WIFI_GETSTATUS,��ʱ���˳� ,��λs(Ĭ��5s)
	  * @return ���ؽ��
	  * @retval  =0 �ɹ� 
	  * @retval  <0 ʧ��
	  * @note 
	  */
	int GetStatus(HWND hwnd, int timeout=5);
	
	/** @brief ��ȡ��ǰ����״̬
      * @return ���ؽ��
	  * @retval  WIFI_STATUS_CONNECTED ������
	  * @retval  WIFI_STATUS_DISCONNECT δ����
	  * @retval  WIFI_STATUS_CONNECTING ��������
	  * @retval  <0 ʧ��
	  */
	int GetStatus();

	/** @brief ����ֹͣGetStatus�߳�
	  *
	  */
	int StopGetStatus();
	
	/** @brief ȡ�ñ�������
	  * @param[in] m_list ָ��Pt80WifiNetworkConfigList������ָ��
	  * @return ���ؽ��
	  * @retval 0 �ɹ�
	  * @retval <0 ʧ��
	  */
	int GetLocalNetwork(Pt80WifiNetworkConfigList *m_list);

	/** @brief ȡ�������ӵ�������Ϣ
	  * @param[out] item ָ��Pt80WifiNetworkListItem��ָ��
	  * @return ���ؽ��
	  * @retval 0 �ɹ�
	  * @retval <0 ʧ��
	  */
	int GetCurrentNetworkInfo(Pt80WifiNetworkListItem *item);


	/** @brief �Ͽ���ǰ�������� 
	  * @retval 0 �ɹ�
	  * @retval ���� ʧ��
	  */
	int DisconnectCurrentNetwork();

	/**
	* @brief	��ȡ��ǰ�������������ź�ǿ��
	* 
	* @return �������
	* @retval NULL δ����IP
	* @retval ���� �ѷ����IP
	*/
	char *GetIpAddress();

	/**
	* @brief	��ȡ��ǰ�������������ź�ǿ��
	* 
	* @return �������
	* @retval NULL �޷���ȡ����������ӵ�eth0δ����
	* @retval ���� mac��ַ
	*/
	char *GetMac();

	/**
	* @brief ����udhcpc����
	*/
	int StartUdhcpc();

	/** 
	* @brief ֹͣudhdpc����
	*/
	int StopUdhcpc();




public:
#define WIFIMANAGER_ERR_THREAD_CREATE  -100
#define WIFIMANAGER_ERR_THREAD_RUN     -101

#define WIFI_STATUS_CONNECTED 1
#define WIFI_STATUS_DISCONNECT 2
#define WIFI_STATUS_CONNECTING 3 /**< �������� */

public:
	CPt80WifiThread_Scan *m_threadScan;
	CPt80WifiThread_EnableNetwork *m_threadConnect;
	CPt80WifiThread_AddNetwork *m_threadAddNetwork;
	CPt80WifiThread_GetStatus *m_theadGetStatus;
};

/** @brief ���������̰߳汾 */
class CPt80WifiThread_EnableNetwork:
	public wxThread
{
public:
	CPt80WifiThread_EnableNetwork(HWND hwnd, Pt80WifiNetworkListItem *m_item);
	CPt80WifiThread_EnableNetwork(HWND hwnd, int timeout, int id);

	virtual void *Entry();
	virtual void OnExit();
public:
	HWND m_hwnd;
	int m_timeout;
	int m_id;
	int m_retval;

};

/** @brief ����WIFI����(�̰߳汾) */
class CPt80WifiThread_AddNetwork:
	public wxThread
{
public:
	CPt80WifiThread_AddNetwork(HWND hwnd, Pt80WifiNetworkListItem *item);

	virtual void *Entry();
	virtual void OnExit();
public:
	HWND m_hwnd;
	int m_retval;
	Pt80WifiNetworkListItem *m_item;

};

/** @brief ȡWIFI״̬ */
class CPt80WifiThread_GetStatus:
	public wxThread
{
public:
	/** @brief ���캯�����߳���UI֮��ͨ��MSG��ͨ */
	CPt80WifiThread_GetStatus(HWND hwnd, int timeout);

	virtual void *Entry();
	virtual bool TestDestroy();
	virtual void OnExit();
	
	int Stop();
	int Getstatus();
private:
	HWND m_hwnd;
	bool m_bDestroy;
	int m_timeout;
	int m_Retval;
	wxMutex *m_DestroyMutex;
};

/** @brief ɨ���߳� */
class CPt80WifiThread_Scan:
	public wxThread
{
public:
	/** @brief ���캯�����߳���UI֮��ͨ��MSG��ͨ 
	  * @param[in] timeout ���ﳬʱ��Ч��������ͨѶ�������ϱ�
	  * @param[in] m_list Pt80WifiNetworkList
	  */
	CPt80WifiThread_Scan(HWND hwnd, int timeout, Pt80WifiNetworkList *m_list);
	~CPt80WifiThread_Scan(void);

	virtual void *Entry();
	virtual void OnExit();
	virtual bool TestDestroy();

public:
	HWND m_hwnd;
	bool bDestroy;
	int m_timeout;
	Pt80WifiNetworkList *m_wifiList;
	int m_Retval;
};


/* �µ�WIFI�������࣬��ǿ�ƶ�����UI�Ľ�����ʽ
 * �����������
 */
/************************************************************************/
/* ����WIFI�������                                                     */
/************************************************************************/
class SDKIMPORT CPt80WifiSvc_ThreadBase: public wxThread
{
public:
	CPt80WifiSvc_ThreadBase();
	virtual void *Entry();
	virtual void OnExit();

	/** @brief ���ò�������
	  * @param[in] bOpen
	  * - true ��
	  * - false �ر�
	  */
	void SetType(bool bOpen=true)
	{
		 m_bType = bOpen;
	}

public:
	/** @brief �ı�m_bRunning����ֵ */
	void ChangeState(bool bValue);
	/** @brief ��ȡm_bRunning����ֵ */
	bool GetState();

	/** @brief �����߳� */
	virtual int Start(){return Run();}
	/** @brief �ر��߳� */
	virtual void Stop(){ChangeState(false);}
	/** @brief ��ʼ�����߳� */
	virtual int OnStart(){return 0;}
	/** @brief ���� */
	virtual int OnError(int err){return 0;}
	/** @brief �߳��˳� */
	virtual int OnResult(int retval){return 0;}

public:
	bool m_bRunning;
	bool m_bEnter;
	bool m_bType;
};

/************************************************************************/
/* ȡWIFI״̬����                                                       */
/************************************************************************/
class SDKIMPORT CPt80WifiGetStatus_ThreadBase : public wxThread
{
public:
	CPt80WifiGetStatus_ThreadBase()
	{
		Create();
		m_bEnter = false;
	}
	virtual void *Entry();
	virtual void OnExit();
	/** @brief ���ò�����ʱʱ�� 
	  * @param[in] timeout �ܲ�����ʱʱ��(��)��ÿ�β鿴���1s
	  */
	void SetTimeout(int timeout)
	{
		m_timeout = timeout;
	}

public:
	/** @brief �ı�m_bRunning����ֵ */
	void ChangeState(bool bValue);
	/** @brief ��ȡm_bRunning����ֵ */
	bool GetState();

	/** @brief �����߳� */
	virtual int Start(){return Run();}
	void Stop(){ChangeState(false);}
	/** @brief �����̻߳ص� */
	virtual int OnStart(){return 0;}
	/** @brief WIFI ״̬�ص� */
	virtual int OnStatus(int type) {return 0;}
	/** @brief ��ǰ������Ϣ */
	virtual int OnWifiInfo(WifiNetwork &net) {return 0;}
	/** @brief ����ص� */
	virtual int OnError(int err){return 0;}
	/** @brief �߳��˳� */
	virtual int OnResult(int retval){return 0;}

public:
	bool m_bRunning;
	bool m_bEnter;
	int m_timeout;

public:
	enum {
		ERR_WIFI_INIT=-1000,/**< WIFI����ӿڳ�ʼ��ʧ�� */
		ERR_WIFI_STATE, /**< ����ϵͳ�ӿڳ��� */
		ERR_WIFI_ACCESS, /**< �޷���ȡWIFI������ */
		ERR_WIFI_LOCALLIST, /**< ��ȡ���������б�ʧ��*/
	};

	/** @brief ȡ״̬��Ϣ ����OnStatus*/
	enum GETSTATUS_PARAM_RETVAL{
		GETSTATUS_EXIT=0,		/**< �߳��˳��󷵻� */
		GETSTATUS_ERROR,		/**< ����wifi�����ʼ��ʧ�� */
		GETSTATUS_TIMEOUT,		/**< ��timeoutʱ����δ������wifi */
		GETSTATUS_COMPLETED,	/**< WIFI�����ӣ��ڽӵ�����Ϣ���߳̽��˳� */
		GETSTATUS_CONNECTING,	/**< WIFI�������� */
		GETSTATUS_DISCONNECT,	/**< WIFIδ���� */
		GETSTATUS_LOCALLIST_IS_NULL, /**< û���κα������� */
	};
};

/** }end of group_WifiOpt */
#endif