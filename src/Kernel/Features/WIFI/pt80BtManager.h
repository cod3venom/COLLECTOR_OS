/*!
 *			Copyright (C) 2010-2015	Newland Computer (FuJian) Co.,Ltd.
 * @License	�����´�½���Թɷ����޹�˾
 *
 * @file	pt80BtManager.h
 * @brief	PT80 BT ������
 * @author  NEAT TEAM <neat@newlandcomputer.com>
 * @version 1.00
 * @date    2011-11-01 initial version
 */
#ifndef _PT80BTMANAGER_H_
#define _PT80BTMANAGER_H_
#include "settings.h"
/**
  * @defgroup group_BTOpt PT80BT������
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
 * @brief	��������״̬��Իص�����
 */
typedef int (*BTPincodeFunc)(const char *name, const char *address, int mode,char *pin);

/** 
 * @typedef BTSerialStatusCbFunc
 * 
 * @brief   ��������״̬�ص�����
 * @param   status 
 * - "disconnect"   δ����
 * - "connecting"   ��������(��֤�׶�)
 * - "connected"    ������
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


/** @brief Ĭ�ϼ�����Ժ���
  * @return 0 ������ԣ� 1 �ܾ����
  * @note �ú����� CPt80BtManager::SetDiscoverEnable ����,Ĭ��סPT80�����淢��MID_INCOMING_BT_REQ�����󣬲��ȴ����
  */
int btPinFunc (const char *name, const char *address, int mode, char *pin);

/** @brief �洢BT������ݵ��б�
  * @note ���ڻ�ȡɨ��������������豸 
  */
WX_DEFINE_ARRAY(Pt80BtDataItem *, Pt80BtDataList); 
/** @class CPt80BtManager BT����������
  * BT����������
  */
class SDKIMPORT CPt80BtManager
{
public:
	int m_hwnd;
	int m_btFd; /**< BT�����������Enable�ɹ���ֵ */
	Pt80BtDataList *m_btList;  /**< ���ڴ���BTɨ���� */
	Pt80BtDataItem *m_btItem;  /**< ��������BT*/
	CPt80BTthread_Scan *m_threadScan; /** Scan thread */
	CPt80BTthread_Pair *m_threadPair; /** Pair thread */
	enum {
		MID_INCOMING_BT_REQ=1500,  /** @brief ����BT�����Ϣ */
	};
public:
	CPt80BtManager();
	/** @brief ��ȡCPt80BtManagerȫ�ֵ�Ψһʵ�� */
	static CPt80BtManager *GetHandle();

	/** @brief ���������ʼ��
	 *  @note �ڲ����ã�����ֱ��ʹ�� 
	 */
	int bt_init();

	/** @brief �Ͽ�������������
	 *  @note �ڲ����ã�����ֱ��ʹ�� 
	 */
	void bt_close();

	/** @brief �ж�BT�����Ƿ���
	  * @note �ڲ�ʵ�ʵ���CPt80SystemSet::GetSvcBtMode���ж��Ƿ���
	  */
	bool IsSvcAlive();

	/** @brief ����BT����
	  * @note �ڲ�ʵ�ʵ���CPt80SystemSet::SetSvcBtMode����������
	  */
	bool StartSvc();

	/** @brief �ر�BT����
	  * @note �ڲ�ʵ�ʵ���CPt80SystemSet::SetSvcBtMode���رշ���
	  */
	bool StopSvc();

public:
	/** @brief ���ǰȡ����״̬ 
	  * @retval BT_STATUS_OFF �ر�
	  * @retval BT_STATUS_IDLE ����
	  */	
	int GetStatus();

	/** @brief ���������µ� 
	  * @param[in] power  1�����򿪡�0�����ر� 
	  * @note �ò���������ͨ��ָ��ʹ����ģ��رգ���δ��ģ���µ� 
	  * @retval 0 �ɹ�
	  * @retval ���� ʧ��
	  */
	int SetPower(int power);

	/** @brief ɨ��
	  * @param[in] hwnd �����Ĵ��ھ��
	  * @param[out] list ָ��Pt80BtDataList��ָ�룬�����ɨ�����������б���
	  * @param[in] timeout ɨ��ʱ��(Ĭ��20��)
	  * @retval 0 �ɹ�
	  * @retval <0 ����ɨ������ʧ�� 
	  * @note ��ο�CPt80BTthread_Scan��˵��
	  */
	int Scan(HWND hwnd, Pt80BtDataList *list, int timeout=20);

	/** @brief ��ֹɨ�� */
	void StopScan();

	/** @brief ����ɨ��
	  * @retval 0 �ɹ�
	  * @retval ���� ʧ��
	  * @note ɨ�赽�����ݽ��� DEVICE_NAME: MAC����ʽ����(ͨ��bt_init()���ص��ļ�������)
	  */
	int bt_scan_start();

	/** @brief ֹͣɨ�� 
	  * @retval 0 �ɹ�
	  * @retval ���� ʧ��
	  */
	int bt_scan_stop();

	/** @brief ����ɨ������
	  * @retval 0 �ɹ�
	  * @retval ���� ʧ��
	  * @note BTɨ��ʱ�������UNKNOW DEVICE���ú������Զ�����
	  */
	int bt_parse_scandata(char *buf, Pt80BtDataItem &item);

	/** @brief ���
	  * @param[in] hwnd �����Ĵ��ھ��
	  * @param[out] item ָ��Pt80BtDataItem��ָ�룬��Ҫ����item->pincode
	  * @param[in] timeout ɨ��ʱ��(Ĭ��10��)
	  * @retval 0 �ɹ�
	  * @retval <0 �����������ʧ�� 
	  */
	int Pair(HWND hwnd, Pt80BtDataItem *item, int timeout=10);

	/** @brief ��ȡ����豸����Ϣ(�������ģʽ)
	 *  @param name �����豸����
	 *  @param address �����豸��ַ
	 *  @param mode �������ģʽ
	 */
	void GetPairedInfo (wxString &name, wxString &address, int &mode, wxString &pin);

	/** @brief �յ�����֮���øýӿ�����Ӧ�������(�����ģʽ)
	 *  @param result 1 ������ԣ� 0 �ܾ����
	 *  @param pin  ����Կ����ģʽʱ����ʾ�������Կ
	 */
	void SetPairedRely (int result, wxString pin);

	/** @brief ���������豸��Ϣ,�豸��Ϣ������item��
	  * @param[out] item ָ��Pt80BtDataItem��ָ��,��Ҫ������address
	  * @retval 0 �ɹ�
	  * @retval <0 ��ȡʧ��
	  */
	int GetDevInfo(Pt80BtDataItem *item);

	/** @brief ɾ���豸��Ϣ�������Ϣ��ȫ��ɾ���� 
	  * @param[in] item ָ��Pt80BtDataItem��ָ��,��Ҫ������address
	  * @retval 0 �ɹ�
	  * @retval <0 ��ȡʧ��
	  */
	int RemoveDev(Pt80BtDataItem *item);

	/** @brief ��ȡMAC��ַ
	  * @return ����ֵ
	  * @retval NULL �޷���ȡ
	  * @retval ���� MAC��ַ
	  */
	static char *GetMac();

	/** @brief ����MAC��ַ
	  * @param[in] ptr MAC��ַ
	  * @return 0 �ɹ�
	  * @note MAC�޸ĺ���Ҫ�����������Ч
	  */
	static int SetMac(char *ptr);

public:
	// NOTE��������Щ�ӿ�Ϊserver��

	/** @brief ���ñ����Ƿ�ɱ����� 
	  * @param[in] enable  true--����false--������
	  * @retval 0 �ɹ�
	  * @retval ���� ʧ��
	  * @note �����ñ����ɼ������޸�Ĭ�ϵļ�����Իص�����ΪbtPinFunc,Ĭ��ֻ������˵����س���ȥ�������
	  */
	int SetDiscoverEnable(bool enable);

	/** @brief ��ȡ�����Ƿ�ɱ����� 
	  * @return �������
	  * @retval true �ɱ�����
	  * @retval false ���ɼ�
	  */
	bool GetDiscoverEnable();

	/** @brief ��ȡ�����Ѿ���Ե��豸�б�
	  * @param[out] list BT����б�
	  * @return �豸����
	  * @retval <0 ����
	  * @retval >0 �豸����
	  * @note ����ȡ100̨�豸
	  */
	int GetPairedDevices(Pt80BtDataList *list);

	/** @brief ��ȡ��������豸����Ϣ 
	 *  @param name �����豸����
	 *  @param address �����豸��ַ
	 *  @param mode �������ģʽ
	 *  @param pin  �������PIN CODE
	 */
	void GetBePairedInfo (wxString &name, wxString &address, int &mode, wxString &pin);

	/** @brief �յ�����֮���øýӿ�����Ӧ������� 
	 *  @param result 1 ������ԣ� 0 �ܾ����
	 *  @param pin  ����Կ����ģʽʱ����ʾ�������Կ
	 */
	void SetBePairedRely (int result, wxString pin);


	/** @brief ���ñ����Ƿ�ɱ����
	  * @param[in] enable  true--����false--������
	  * @retval 0 �����ɹ�
	  * @retval ����  ʧ��
	  */
	int SetPairEnable(bool enable);

	/** @brief ��ȡ�����Ƿ�ɱ����
	  * @return �������
	  * @retval true �ɹ�
	  * @retval false ʧ��
	  */
	bool GetPairEnalbe();

	/** @brief ��ȡ�豸��
	  * @param[out] name �豸��
	  * @return 0 �ɹ� 
	  */
	int GetDevName(wxString &name);

	/** @brief �����豸��
	  * @param[in] name ����
	  * @return 0 �ɹ� 
	  */
	int SetDevName(wxString name);

	/** @brief ���ü�����Իص�����
	  * @param[in] func ������Իص����� 
	  * @retval 0 �ɹ�
	  * @retval ���� ʧ��
	  * @note BTPincodeFunc ����1 ��ʾ������ԣ� ����0 ��ʾ�ܾ����
	  */
	int SetPincodeHandler(BTPincodeFunc func);


public:
	/** @brief �����������ڷ���� �������
	  * ���������豸 /dev/ttyBTS
	  * 
	  * @param[in] pincode Server�������Կ
	  * @note �ú�����Ч��btproxy --server --pincode=%s --devname=/dev/ttyBTS
	  */
	int StartSerialServer(char *pincode);
	/** @brief �ر��������� �������
	  */
	void StopSerialServer();

	/** @brief �����������ڿͻ��� �������
	  * ���������豸 /dev/ttyBTC
	  * 
	  * @param[in] pincode Server�������Կ
	  * @note �ú�����Ч��btproxy --client --address=%s --pincode=%s --devname=/dev/ttyBTC
	  */
	int StartSerialClient(char *btmac, char *pincode);
	/** @brief �ر��������� ������� 
	*/
	void StopSerialClient();

	/**
	* @brief �����������ڴ������ ״̬�ص����� 
	* ״̬
	* - "disconnect"   δ����
	* - "connecting"   ��������(��֤�׶�)
	* - "connected"    ������
	* @param[in] func �ص�����
	*/
	void SetSerialStatusCb(BTSerialStatusCbFunc func);
	
	/**
	* @brief ��ȡ��ǰ��������״̬�ص�����
	*
	* @return ����״̬
	* @retval NULL ȡ״̬����
	* @retval ���� ��������״̬
	* - "disconnect"   δ����
	* - "connecting"   ��������(��֤�׶�)
	* - "connected"    ������
	*/
	char *GetSerialStatus();

};






/************************************************************************/
/* BT ɨ���߳�                                                             */
/************************************************************************/
/** @brief BTɨ���߳�
  * @note ��Ҫ����COMMAND��Ϣ wParam:MSG_COMMAND_BT_SCAN lwParamΪ���ؽ��
  * @li ::BT_SCAN_RET_RESULT ȡ��ɨ����(�����и���Ϣ�ķ���,ֻ������ʹ��)
  * @li ::BT_SCAN_RET_FAIL   ����
  * @li ::BT_SCAN_RET_TIMEOUT ɨ�����
  * @li ::BT_SCAN_RET_NEWDEVICE ɨ�赽�µ��豸
  */

class CPt80BTthread_Scan:
	public wxThread
{
public:
	CPt80BTthread_Scan(HWND hwnd, Pt80BtDataList *list, int timeout);

	virtual void *Entry();
	virtual void OnExit();
	/**
	  * @brief ���bt ssid,������ͬ����ɾ����ԭ����SSID
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
/* BT ����߳�															*/
/************************************************************************/
/** @brief BT����߳�
  * @note ��Ҫ����COMMAND��Ϣ wParam:MSG_COMMAND_BT_PAIR lwParamΪ���ؽ��
  * @li ::BT_PAIR_RET_FAIL   ����
  * @li ::BT_PAIR_RET_TIMEOUT ɨ�賬ʱ
  * @li ::BT_PAIR_RET_SUCC ��Գɹ�
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

	const char *m_PairName;			  // ��Ե�BT����
	const char *m_PairAddress;		  // ��Ե�BT�豸MAC
	int m_PairMode;					  // ���ģʽ 0-������Կ��1-�ȶ���Կ
	wxString m_PairPinInput;		  // �������������������Կ��ֻ��ģʽ1ʹ��
	wxString m_PairPin;				  // �û������PINCODE
	wxMutex m_mutexWaitPair;
	wxCondition *m_conditionWaitPair; // �����ȴ��û�ѡ����

	bool m_bPairRet;				  // �����û�����Խ��

#define	MSG_COMMAND_BT_PAIR (MSG_USER + 100)
#define BT_PAIR_RET_FAIL -1
#define BT_PAIR_RET_SUCC  0
#define BT_PAIR_RET_TIMEOUT 1
#define BT_PAIR_RET_REQUEST 2

};


/************************************************************************/
/* ����BT�������                                                     */
/************************************************************************/
class SDKIMPORT CPt80BTSvc_ThreadBase: public wxThread
{
public:
	CPt80BTSvc_ThreadBase();
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

/** } end of group_BTOpt */
#endif