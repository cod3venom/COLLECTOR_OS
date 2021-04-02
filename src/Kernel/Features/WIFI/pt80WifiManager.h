/*!
 *			Copyright (C) 2010-2015	Newland Computer (FuJian) Co.,Ltd.
 * @License	福建新大陆电脑股份有限公司
 *
 * @file	pt80WifiManager.h
 * @brief	PT80 WIFI操作类
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
  * @defgroup group_WifiOpt PT80WIFI操作类
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
/** @brief 储存WIFI网络信息和密钥的基本单元
  * @note 该类常用于获取WIFI扫描结果和创建新的WIFI链接
  */
class Pt80WifiNetworkListItem{
public:
	WifiNetwork net; /**< WIFI网络连接信息 */
	wxString strUser; /**< WPA-ENT 密钥验证方式 */
	wxString strKey; /**< 密钥用于连接时使用 */
	wxString strEAP; /**< EAP方法 */
	wxString strPhase2Authentication ;/**< 阶段2身份验证方式 */
}; 

/** @brief 储存WIFI本地配置信息基本单元 
  * @note 该类只在::GetLocalNetwork 中使用
  */
class Pt80WifiNetworkConfigListItem{
public:
	WifiConfigNetwork config;

};

/** @brief 定义 Pt80WifiNetworkList 
  * @note 用于存储WIFI扫描结果
  */
WX_DEFINE_ARRAY(Pt80WifiNetworkListItem *, Pt80WifiNetworkList); 

/** @brief 定义 Pt80WifiNetworkConfigList 
  * @note 用于存储获取本地配置信息
  */
WX_DEFINE_ARRAY(Pt80WifiNetworkConfigListItem *, Pt80WifiNetworkConfigList);


/** @brief WIFIMANAGER的消息*/
enum MSG_COMMAND_WIFI{
	MSG_COMMAND_WIFI_BASE = 0x1000, /**< WIFI消息基数，未使用 */
// scan 
	MSG_COMMAND_WIFI_SCANSTART,		/**< WIFI已开始扫描 */
	MSG_COMMAND_WIFI_EXIT,			/**< 线程创建出错 */
	MSG_COMMAND_WIFI_ERROR,			/**< 错误         */
	MSG_COMMAND_WIFI_TIMEOUT,		/**< 扫描超时     */
	MSG_COMMAND_WIFI_RESULT,		/**< 扫描结果     */
	MSG_COMMAND_WIFI_USERBREAK,		/**< 用用户中断   */
	MSG_COMMAND_WIFI_NORESULT,		/**< 没有扫描结果 */
// addnetwork
	MSG_COMMAND_WIFI_ADDNETWORK,	/**< 新增WIFI网络 */
// enablenetwork
	MSG_COMMAND_WIFI_ENABLENETWORK, /**< 启用WIFI网络 */
// getstatus
	MSG_COMMAND_WIFI_GETSTATUS,		/**< 取状态消息,lwParam定义见::GETSTATUS_PARAM_RETVAL */
};
/** @brief 取状态消息 lwParam定义 */
enum GETSTATUS_PARAM_RETVAL{
	GETSTATUS_EXIT=0,		/**< 线程退出后返回 */
	GETSTATUS_ERROR,		/**< 出错，wifi服务初始化失败 */
	GETSTATUS_TIMEOUT,		/**< 在timeout时间内未连接上wifi */
	GETSTATUS_COMPLETED,	/**< WIFI已连接，在接到该消息后，线程将退出 */
	GETSTATUS_CONNECTING,	/**< WIFI正在连接 */
	GETSTATUS_DISCONNECT,	/**< WIFI未连接 */
};
/************************************************************************/
/* main class															*/
/************************************************************************/
class CPt80WifiThread_Scan;
class CPt80WifiThread_EnableNetwork;
class CPt80WifiThread_AddNetwork;
class CPt80WifiThread_GetStatus;
/** @class CPt80WifiManager WIFI操作管理类 
  * WIFI 操作管理类
  */
class SDKIMPORT CPt80WifiManager
{
public:
	CPt80WifiManager();
	~CPt80WifiManager();
	/** @brief 扫描
	  * @param[in] hwnd 关联的窗口，用来接收消息
	  * @param[in] timeout 单位毫秒
	  * @param[out] m_list 指向Pt80WifiNetworkList的链表指针
	  * @return 返回结果
	  * @retval 0 成功
	  * @retval <0 失败
	  * @note 需要处理的COMMAND: 
	  * @li ::MSG_COMMAND_WIFI_EXIT
	  * @li ::MSG_COMMAND_WIFI_ERROR 
	  * @li ::MSG_COMMAND_WIFI_TIMEOUT
	  * @li ::MSG_COMMAND_WIFI_RESULT
	  * @li ::MSG_COMMAND_WIFI_USERBREAK
	  * @li ::MSG_COMMAND_WIFI_NORESULT
	  */
	int Scan(HWND hwnd, int timeout, Pt80WifiNetworkList *m_list);

	/** @brief 创建新的WIFI网络
	  * @param[in] m_item 指向Pt80WifiNetworkListItem的指针，
	  * @return 返回结果
	  * @retval >=0 新增的本地网络ID，可用于开启这个网络
	  * @retval <0 失败
	  * @note 这个会阻塞一定时间，推荐使用线程版本 
	  */
	int AddNewNetwork(Pt80WifiNetworkListItem *m_item);

	/** @brief 创建新的WIFI网络
	  * @param[in] m_item 指向Pt80WifiNetworkListItem的指针，
	  * @param[in] IshiddenAP 添加的网络是否是隐藏AP(不广播SSID)
	  * @return 返回结果
	  * @retval >=0 新增的本地网络ID，可用于开启这个网络
	  * @retval <0 失败
	  * @note 这个会阻塞一定时间，推荐使用线程版本 
	  */
	int AddNewNetwork(Pt80WifiNetworkListItem *m_item, bool IshiddenAP);

	/** @brief 创建新的WIFI网络(线程版本)		该接口已废弃
	  * @param[in] hwnd 关联的窗口，用来接收消息
	  * @param[in] m_item 指向Pt80WifiNetworkListItem的指针，
	  * @return 返回结果
	  * @retval =0 线程启动成功
	  * @note 需要监听 MSG_COMMAND_WIFI_ADDNETWORK, 参数1(lParam) >=0 新增的本地网络ID，可用于开启这个网络
	  */
	int AddNewNetwork(HWND hwnd, Pt80WifiNetworkListItem *m_item);
	
	/** @brief 启用网络 
	  * @param[in] id 本地网络ID 
	  * @retrun 返回结果
	  * @retval =0 成功
	  * @retval <0 失败
	  * @note 可以不使用线程版本
	  */
	int EnableNetwork(int id );


	/** @brief 启用网络(线程)
	  * @param[in] id 本地网络ID 
	  * @retrun 返回结果
	  * @retval =0 成功
	  * @retval <0 失败
	  * @note 需要监听消息 MSG_COMMAND_WIFI_ENABLENETWORK  lwParam为0
	  */
	int EnableNetwork(HWND hwnd, int timeout, int id);

	/** @brief 删除本地网络
	  * @param[in] id 本地网络ID 
	  * @retrun 返回结果
	  * @retval =0 成功
	  * @retval <0 失败'
	  */
	int RemoveNetwork(int id);

	/** @brief 获取当前的网络状态(线程版本)
	  * @param[in] hwnd 关联的窗口，用来接收消息
	  * @param[in] timeout 总查询时间，每隔1秒发送::MSG_COMMAND_WIFI_GETSTATUS,超时将退出 ,单位s(默认5s)
	  * @return 返回结果
	  * @retval  =0 成功 
	  * @retval  <0 失败
	  * @note 
	  */
	int GetStatus(HWND hwnd, int timeout=5);
	
	/** @brief 获取当前网络状态
      * @return 返回结果
	  * @retval  WIFI_STATUS_CONNECTED 已连接
	  * @retval  WIFI_STATUS_DISCONNECT 未连接
	  * @retval  WIFI_STATUS_CONNECTING 正在连接
	  * @retval  <0 失败
	  */
	int GetStatus();

	/** @brief 用于停止GetStatus线程
	  *
	  */
	int StopGetStatus();
	
	/** @brief 取得本地网络
	  * @param[in] m_list 指向Pt80WifiNetworkConfigList的链表指针
	  * @return 返回结果
	  * @retval 0 成功
	  * @retval <0 失败
	  */
	int GetLocalNetwork(Pt80WifiNetworkConfigList *m_list);

	/** @brief 取得已连接的网络信息
	  * @param[out] item 指向Pt80WifiNetworkListItem的指针
	  * @return 返回结果
	  * @retval 0 成功
	  * @retval <0 失败
	  */
	int GetCurrentNetworkInfo(Pt80WifiNetworkListItem *item);


	/** @brief 断开当前网络连接 
	  * @retval 0 成功
	  * @retval 其它 失败
	  */
	int DisconnectCurrentNetwork();

	/**
	* @brief	获取当前无线网络连接信号强度
	* 
	* @return 操作结果
	* @retval NULL 未分配IP
	* @retval 其它 已分配的IP
	*/
	char *GetIpAddress();

	/**
	* @brief	获取当前无线网络连接信号强度
	* 
	* @return 操作结果
	* @retval NULL 无法获取，无线网络接点eth0未存在
	* @retval 其它 mac地址
	*/
	char *GetMac();

	/**
	* @brief 开启udhcpc服务
	*/
	int StartUdhcpc();

	/** 
	* @brief 停止udhdpc服务
	*/
	int StopUdhcpc();




public:
#define WIFIMANAGER_ERR_THREAD_CREATE  -100
#define WIFIMANAGER_ERR_THREAD_RUN     -101

#define WIFI_STATUS_CONNECTED 1
#define WIFI_STATUS_DISCONNECT 2
#define WIFI_STATUS_CONNECTING 3 /**< 正在连接 */

public:
	CPt80WifiThread_Scan *m_threadScan;
	CPt80WifiThread_EnableNetwork *m_threadConnect;
	CPt80WifiThread_AddNetwork *m_threadAddNetwork;
	CPt80WifiThread_GetStatus *m_theadGetStatus;
};

/** @brief 允许网络线程版本 */
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

/** @brief 增加WIFI网络(线程版本) */
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

/** @brief 取WIFI状态 */
class CPt80WifiThread_GetStatus:
	public wxThread
{
public:
	/** @brief 构造函数，线程与UI之间通过MSG沟通 */
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

/** @brief 扫描线程 */
class CPt80WifiThread_Scan:
	public wxThread
{
public:
	/** @brief 构造函数，线程与UI之间通过MSG沟通 
	  * @param[in] timeout 这里超时无效，正常的通讯都会结果上报
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


/* 新的WIFI操作基类，不强制定义与UI的交互方式
 * 精简操作函数
 */
/************************************************************************/
/* 开启WIFI服务基类                                                     */
/************************************************************************/
class SDKIMPORT CPt80WifiSvc_ThreadBase: public wxThread
{
public:
	CPt80WifiSvc_ThreadBase();
	virtual void *Entry();
	virtual void OnExit();

	/** @brief 设置操作类型
	  * @param[in] bOpen
	  * - true 打开
	  * - false 关闭
	  */
	void SetType(bool bOpen=true)
	{
		 m_bType = bOpen;
	}

public:
	/** @brief 改变m_bRunning变量值 */
	void ChangeState(bool bValue);
	/** @brief 获取m_bRunning变量值 */
	bool GetState();

	/** @brief 启动线程 */
	virtual int Start(){return Run();}
	/** @brief 关闭线程 */
	virtual void Stop(){ChangeState(false);}
	/** @brief 开始进入线程 */
	virtual int OnStart(){return 0;}
	/** @brief 错误 */
	virtual int OnError(int err){return 0;}
	/** @brief 线程退出 */
	virtual int OnResult(int retval){return 0;}

public:
	bool m_bRunning;
	bool m_bEnter;
	bool m_bType;
};

/************************************************************************/
/* 取WIFI状态基类                                                       */
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
	/** @brief 设置操作超时时间 
	  * @param[in] timeout 总操作超时时间(秒)，每次查看间隔1s
	  */
	void SetTimeout(int timeout)
	{
		m_timeout = timeout;
	}

public:
	/** @brief 改变m_bRunning变量值 */
	void ChangeState(bool bValue);
	/** @brief 获取m_bRunning变量值 */
	bool GetState();

	/** @brief 启动线程 */
	virtual int Start(){return Run();}
	void Stop(){ChangeState(false);}
	/** @brief 进入线程回调 */
	virtual int OnStart(){return 0;}
	/** @brief WIFI 状态回调 */
	virtual int OnStatus(int type) {return 0;}
	/** @brief 当前连接信息 */
	virtual int OnWifiInfo(WifiNetwork &net) {return 0;}
	/** @brief 错误回调 */
	virtual int OnError(int err){return 0;}
	/** @brief 线程退出 */
	virtual int OnResult(int retval){return 0;}

public:
	bool m_bRunning;
	bool m_bEnter;
	int m_timeout;

public:
	enum {
		ERR_WIFI_INIT=-1000,/**< WIFI服务接口初始化失败 */
		ERR_WIFI_STATE, /**< 调用系统接口出错 */
		ERR_WIFI_ACCESS, /**< 无法获取WIFI管理锁 */
		ERR_WIFI_LOCALLIST, /**< 获取本地网络列表失败*/
	};

	/** @brief 取状态消息 用于OnStatus*/
	enum GETSTATUS_PARAM_RETVAL{
		GETSTATUS_EXIT=0,		/**< 线程退出后返回 */
		GETSTATUS_ERROR,		/**< 出错，wifi服务初始化失败 */
		GETSTATUS_TIMEOUT,		/**< 在timeout时间内未连接上wifi */
		GETSTATUS_COMPLETED,	/**< WIFI已连接，在接到该消息后，线程将退出 */
		GETSTATUS_CONNECTING,	/**< WIFI正在连接 */
		GETSTATUS_DISCONNECT,	/**< WIFI未连接 */
		GETSTATUS_LOCALLIST_IS_NULL, /**< 没有任何本地网络 */
	};
};

/** }end of group_WifiOpt */
#endif