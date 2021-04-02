/*!
 *			Copyright (C) 2010-2015	Newland Computer (FuJian) Co.,Ltd.
 * @License	福建新大陆电脑股份有限公司
 *
 * @file	pt80BtManager.h
 * @brief	PT80 BT 操作类
 * @author  NEAT TEAM <neat@newlandcomputer.com>
 * @version 1.00
 * @date    2011-11-01 initial version
 */
#ifndef _PT80BTMANAGER_H_
#define _PT80BTMANAGER_H_
#include "settings.h"
/**
  * @defgroup group_BTOpt PT80BT操作类
  * @{
  */
#include "neat/neatwin.h"
#include "wx/string.h"
#include "wx/thread.h"
#include "wx/dynarray.h"
#include "wx/listimpl.cpp"
#include "wx/app.h"
#include "wx/config.h"

#ifdef __LINUX__
#include "pt80/nlinux/include/bt.h"
#else
typedef struct {
	char name[128];         
	char address[24];       
	char rfcomm[32];        
	unsigned int cls;       
	int paired;             
	int connected;          
	int trusted;            
} BTDevice;

/**
 * @typedef	BTPincodeFunc
 *
 * @brief	蓝牙监听状态配对回调函数
 */
typedef int (*BTPincodeFunc)(const char *name, const char *address, int mode,char *pin);

/** 
 * @typedef BTSerialStatusCbFunc
 * 
 * @brief   蓝牙串口状态回调函数
 * @param   status 
 * - "disconnect"   未连接
 * - "connecting"   正在连接(认证阶段)
 * - "connected"    已连接
 */
typedef int (*BTSerialStatusCbFunc)(const char *status);
#endif

class Pt80BtDataItem {
public:
	BTDevice device;
	wxString pincode;
};


class CPt80BTthread_Scan;
class CPt80BTthread_Pair;


/** @brief 默认监听配对函数
  * @return 0 接受配对， 1 拒绝配对
  * @note 该函数被 CPt80BtManager::SetDiscoverEnable 调用,默认住PT80的桌面发送MID_INCOMING_BT_REQ的请求，并等待结果
  */
int btPinFunc (const char *name, const char *address, int mode, char *pin);

/** @brief 存储BT相关数据的列表
  * @note 用于获取扫描结果，或者配对设备 
  */
WX_DEFINE_ARRAY(Pt80BtDataItem *, Pt80BtDataList); 
/** @class CPt80BtManager BT操作管理类
  * BT操作管理类
  */
class SDKIMPORT CPt80BtManager
{
public:
	int m_hwnd;
	int m_btFd; /**< BT操作句柄，在Enable成功后赋值 */
	Pt80BtDataList *m_btList;  /**< 用于储存BT扫描结果 */
	Pt80BtDataItem *m_btItem;  /**< 用于连接BT*/
	CPt80BTthread_Scan *m_threadScan; /** Scan thread */
	CPt80BTthread_Pair *m_threadPair; /** Pair thread */
	enum {
		MID_INCOMING_BT_REQ=1500,  /** @brief 请求BT配对消息 */
	};
public:
	CPt80BtManager();
	/** @brief 获取CPt80BtManager全局的唯一实例 */
	static CPt80BtManager *GetHandle();

	/** @brief 蓝牙服务初始化
	 *  @note 内部调用，请务直接使用 
	 */
	int bt_init();

	/** @brief 断开蓝牙服务连接
	 *  @note 内部调用，请务直接使用 
	 */
	void bt_close();

	/** @brief 判断BT服务是否开启
	  * @note 内部实际调用CPt80SystemSet::GetSvcBtMode来判断是否开启
	  */
	bool IsSvcAlive();

	/** @brief 开启BT服务
	  * @note 内部实际调用CPt80SystemSet::SetSvcBtMode来开启服务
	  */
	bool StartSvc();

	/** @brief 关闭BT服务
	  * @note 内部实际调用CPt80SystemSet::SetSvcBtMode来关闭服务
	  */
	bool StopSvc();

public:
	/** @brief 获得前取蓝牙状态 
	  * @retval BT_STATUS_OFF 关闭
	  * @retval BT_STATUS_IDLE 空闲
	  */	
	int GetStatus();

	/** @brief 给蓝牙上下电 
	  * @param[in] power  1——打开、0——关闭 
	  * @note 该操作仅仅是通过指令使蓝牙模块关闭，并未给模块下电 
	  * @retval 0 成功
	  * @retval 其它 失败
	  */
	int SetPower(int power);

	/** @brief 扫描
	  * @param[in] hwnd 关联的窗口句柄
	  * @param[out] list 指向Pt80BtDataList的指针，如果有扫描结果会加入该列表中
	  * @param[in] timeout 扫描时间(默认20秒)
	  * @retval 0 成功
	  * @retval <0 创建扫描任务失败 
	  * @note 请参考CPt80BTthread_Scan的说明
	  */
	int Scan(HWND hwnd, Pt80BtDataList *list, int timeout=20);

	/** @brief 中止扫描 */
	void StopScan();

	/** @brief 开启扫描
	  * @retval 0 成功
	  * @retval 其它 失败
	  * @note 扫描到的数据将以 DEVICE_NAME: MAC的形式返回(通过bt_init()返回的文件描述符)
	  */
	int bt_scan_start();

	/** @brief 停止扫描 
	  * @retval 0 成功
	  * @retval 其它 失败
	  */
	int bt_scan_stop();

	/** @brief 处理扫描数据
	  * @retval 0 成功
	  * @retval 其它 失败
	  * @note BT扫描时，会出现UNKNOW DEVICE，该函数会自动过滤
	  */
	int bt_parse_scandata(char *buf, Pt80BtDataItem &item);

	/** @brief 配对
	  * @param[in] hwnd 关联的窗口句柄
	  * @param[out] item 指向Pt80BtDataItem的指针，需要设置item->pincode
	  * @param[in] timeout 扫描时间(默认10秒)
	  * @retval 0 成功
	  * @retval <0 创建配对任务失败 
	  */
	int Pair(HWND hwnd, Pt80BtDataItem *item, int timeout=10);

	/** @brief 获取配对设备的信息(主动配对模式)
	 *  @param name 蓝牙设备名称
	 *  @param address 蓝牙设备地址
	 *  @param mode 蓝牙配对模式
	 */
	void GetPairedInfo (wxString &name, wxString &address, int &mode, wxString &pin);

	/** @brief 收到请求之后用该接口来回应配对请求(主配对模式)
	 *  @param result 1 接收配对， 0 拒绝配对
	 *  @param pin  在密钥输入模式时，表示输入的密钥
	 */
	void SetPairedRely (int result, wxString pin);

	/** @brief 获得已配对设备信息,设备信息更新在item中
	  * @param[out] item 指向Pt80BtDataItem的指针,需要已设置address
	  * @retval 0 成功
	  * @retval <0 获取失败
	  */
	int GetDevInfo(Pt80BtDataItem *item);

	/** @brief 删除设备信息（配对信息等全部删除） 
	  * @param[in] item 指向Pt80BtDataItem的指针,需要已设置address
	  * @retval 0 成功
	  * @retval <0 获取失败
	  */
	int RemoveDev(Pt80BtDataItem *item);

	/** @brief 获取MAC地址
	  * @return 返回值
	  * @retval NULL 无法获取
	  * @retval 其它 MAC地址
	  */
	static char *GetMac();

	/** @brief 设置MAC地址
	  * @param[in] ptr MAC地址
	  * @return 0 成功
	  * @note MAC修改后，需要重启服务才有效
	  */
	static int SetMac(char *ptr);

public:
	// NOTE：以下这些接口为server端

	/** @brief 设置本机是否可被发现 
	  * @param[in] enable  true--允许、false--不允许
	  * @retval 0 成功
	  * @retval 其它 失败
	  * @note 在设置本机可见，会修改默认的监听配对回调函数为btPinFunc,默认只给桌面菜单主控程序去处理配对
	  */
	int SetDiscoverEnable(bool enable);

	/** @brief 获取本南是否可被发现 
	  * @return 操作结果
	  * @retval true 可被发现
	  * @retval false 不可见
	  */
	bool GetDiscoverEnable();

	/** @brief 获取本机已经配对的设备列表
	  * @param[out] list BT配对列表
	  * @return 设备数量
	  * @retval <0 出错
	  * @retval >0 设备数量
	  * @note 最多获取100台设备
	  */
	int GetPairedDevices(Pt80BtDataList *list);

	/** @brief 获取请求配对设备的信息 
	 *  @param name 蓝牙设备名称
	 *  @param address 蓝牙设备地址
	 *  @param mode 蓝牙配对模式
	 *  @param pin  蓝牙配对PIN CODE
	 */
	void GetBePairedInfo (wxString &name, wxString &address, int &mode, wxString &pin);

	/** @brief 收到请求之后用该接口来回应配对请求 
	 *  @param result 1 接收配对， 0 拒绝配对
	 *  @param pin  在密钥输入模式时，表示输入的密钥
	 */
	void SetBePairedRely (int result, wxString pin);


	/** @brief 设置本机是否可被配对
	  * @param[in] enable  true--允许、false--不允许
	  * @retval 0 操作成功
	  * @retval 其它  失败
	  */
	int SetPairEnable(bool enable);

	/** @brief 获取本机是否可被配对
	  * @return 操作结果
	  * @retval true 成功
	  * @retval false 失败
	  */
	bool GetPairEnalbe();

	/** @brief 获取设备名
	  * @param[out] name 设备名
	  * @return 0 成功 
	  */
	int GetDevName(wxString &name);

	/** @brief 设置设备名
	  * @param[in] name 名称
	  * @return 0 成功 
	  */
	int SetDevName(wxString name);

	/** @brief 设置监听配对回调函数
	  * @param[in] func 监听配对回调函数 
	  * @retval 0 成功
	  * @retval 其它 失败
	  * @note BTPincodeFunc 返回1 表示接受配对， 返回0 表示拒绝配对
	  */
	int SetPincodeHandler(BTPincodeFunc func);


public:
	/** @brief 启动蓝牙串口服务端 代理程序
	  * 蓝牙串口设备 /dev/ttyBTS
	  * 
	  * @param[in] pincode Server的配对密钥
	  * @note 该函数等效于btproxy --server --pincode=%s --devname=/dev/ttyBTS
	  */
	int StartSerialServer(char *pincode);
	/** @brief 关闭蓝牙串口 代理程序
	  */
	void StopSerialServer();

	/** @brief 启动蓝牙串口客户端 代理程序
	  * 蓝牙串口设备 /dev/ttyBTC
	  * 
	  * @param[in] pincode Server的配对密钥
	  * @note 该函数等效于btproxy --client --address=%s --pincode=%s --devname=/dev/ttyBTC
	  */
	int StartSerialClient(char *btmac, char *pincode);
	/** @brief 关闭蓝牙串口 代理程序 
	*/
	void StopSerialClient();

	/**
	* @brief 设置蓝牙串口代理程序 状态回调函数 
	* 状态
	* - "disconnect"   未连接
	* - "connecting"   正在连接(认证阶段)
	* - "connected"    已连接
	* @param[in] func 回调函数
	*/
	void SetSerialStatusCb(BTSerialStatusCbFunc func);
	
	/**
	* @brief 获取当前蓝牙串口状态回调函数
	*
	* @return 蓝牙状态
	* @retval NULL 取状态错误
	* @retval 其它 蓝牙串口状态
	* - "disconnect"   未连接
	* - "connecting"   正在连接(认证阶段)
	* - "connected"    已连接
	*/
	char *GetSerialStatus();

};






/************************************************************************/
/* BT 扫描线程                                                             */
/************************************************************************/
/** @brief BT扫描线程
  * @note 需要监听COMMAND消息 wParam:MSG_COMMAND_BT_SCAN lwParam为返回结果
  * @li ::BT_SCAN_RET_RESULT 取得扫描结果(不会有该消息的发送,只做兼容使用)
  * @li ::BT_SCAN_RET_FAIL   出错
  * @li ::BT_SCAN_RET_TIMEOUT 扫描结束
  * @li ::BT_SCAN_RET_NEWDEVICE 扫描到新的设备
  */

class CPt80BTthread_Scan:
	public wxThread
{
public:
	CPt80BTthread_Scan(HWND hwnd, Pt80BtDataList *list, int timeout);

	virtual void *Entry();
	virtual void OnExit();
	/**
	  * @brief 检查bt ssid,如有相同的则删除掉原来的SSID
	  */
	void CheckBtSSID(const char *name, const char *ssid);

	void ChangeRunStatus(bool bValue);
	bool GetRunStatus();
	
public:
	HWND m_hwnd;
	int m_timeout;
	int m_retval;
	bool m_bRun;
	Pt80BtDataList *m_list;
	wxMutex m_mutex;
#define	MSG_COMMAND_BT_SCAN (MSG_USER+101)
#define BT_SCAN_RET_FAIL -1
#define BT_SCAN_RET_RESULT 0
#define BT_SCAN_RET_TIMEOUT 1
#define BT_SCAN_RET_NEWDEVICE 2
#define BT_SCAN_RET_USERBREAK 3
};

/************************************************************************/
/* BT 配对线程															*/
/************************************************************************/
/** @brief BT配对线程
  * @note 需要监听COMMAND消息 wParam:MSG_COMMAND_BT_PAIR lwParam为返回结果
  * @li ::BT_PAIR_RET_FAIL   出错
  * @li ::BT_PAIR_RET_TIMEOUT 扫描超时
  * @li ::BT_PAIR_RET_SUCC 配对成功
  */

class SDKIMPORT CPt80BTthread_Pair: public wxThread
{
public:
	CPt80BTthread_Pair(HWND hwnd, Pt80BtDataItem *item, int timeout);

	virtual void *Entry();
	virtual void OnExit();
public:
	HWND m_hwnd;
	int m_timeout;
	int m_retval;
	Pt80BtDataItem *m_item;

	const char *m_PairName;			  // 配对的BT名称
	const char *m_PairAddress;		  // 配对的BT设备MAC
	int m_PairMode;					  // 配对模式 0-输入密钥；1-比对密钥
	wxString m_PairPinInput;		  // 用来储存随机产生的密钥，只在模式1使用
	wxString m_PairPin;				  // 用户输入的PINCODE
	wxMutex m_mutexWaitPair;
	wxCondition *m_conditionWaitPair; // 条件等待用户选择结果

	bool m_bPairRet;				  // 来自用户层配对结果

#define	MSG_COMMAND_BT_PAIR (MSG_USER + 100)
#define BT_PAIR_RET_FAIL -1
#define BT_PAIR_RET_SUCC  0
#define BT_PAIR_RET_TIMEOUT 1
#define BT_PAIR_RET_REQUEST 2

};


/************************************************************************/
/* 开启BT服务基类                                                     */
/************************************************************************/
class SDKIMPORT CPt80BTSvc_ThreadBase: public wxThread
{
public:
	CPt80BTSvc_ThreadBase();
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

/** } end of group_BTOpt */
#endif