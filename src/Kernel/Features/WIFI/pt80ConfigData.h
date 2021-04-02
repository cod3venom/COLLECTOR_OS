/*!
 *			Copyright (C) 2010-2015	Newland Computer (FuJian) Co.,Ltd.
 * @License	�����´�½���Թɷ����޹�˾
 *
 * @file	pt80ConfigData.h
 * @brief	PT80 ������Ϣ ������
 * @author  NEAT TEAM <neat@newlandcomputer.com>
 * @version 1.00
 * @date    2011-06-25 initial version
 */

#ifndef _PT80_CONFIGDATA_H_
#define _PT80_CONFIGDATA_H_
/**
  * @defgroup group_ConfigData PT80������Ϣ ������
  * @{
  */
#include "wx/config.h"
/** 
  * @brief PT80 SYSTEM ������Ϣ������
  */
class SDKIMPORT CPt80ConfigData {
public:
	~CPt80ConfigData();
	static CPt80ConfigData *GetHandle();

public:
#ifdef __LINUX__
#define CONFIG_FILE	"/usr/var/pt80.ini"
#else
#define CONFIG_FILE	"./pt80.ini"
#endif
	
	/**
	  * @brief ��ȡ������Ϣ
	  * �����ļ��ڴ˴�����
	  *
	  * @return �������
	  * @retval true �ɹ�
	  * @retval false ʧ��
	  */
	bool Open();

	/** 
	 * @brief ��ʼ��Ĭ��������Ϣ
     * @return �������
     * @retval true �ɹ�
     * @retval false ʧ��
	 */
	bool InitDefaultConfigData();

	/**
	  * @��������
	  * @return �������
	  * @retval true �ɹ�
	  * @retval false ʧ��
	  */
	bool Save();

	/** 
	  * @ȡ��wxFileConfigָ�룬�����޸�����
	  * @return �������
	  * @retval not-NULL  wxFileConfig *
	  * @retval NULL ʧ��
	  */
	wxFileConfig *GetwxFileConfig();

public:
	wxFileConfig *config;

public:
	/************************************************************************/
	/* define CONFIG KEY                                                    */
	/* CONFIG KEY NAMING RULE											    */
	/* CONFIG_{SECTION}_{DESCRIBE}_{TYPE}                                   */
	/************************************************************************/

/** @brief �����ļ��Ƿ��Ѿ���ʼ���� */
#define CONFIG_CONFIG_IsInit_BOOL "/CONFIG/IsInit"								
/** @brief �������ã��Ƿ��������� */
#define CONFIG_SYSTEM_Sound_LONG "/SYSTEM/Sound"				
/** @brief ȫ����������*/
#define CONFIG_SYSTEM_GSound_LONG "/SYSTEM/GSound"				
/** @brief ����ʱ������*/
#define CONFIG_SYSTEM_BKLIGHT_LONG "/SYSTEM/Screen/Backlighting"				 
/** @brief ���̱���ʱ������*/
#define CONFIG_SYSTEM_KEYBOARD_BKLIGHT_LONG "/SYSTEM/Keyboard/Backlighting"				 
/** @brief ��Ļ�Աȶ�*/
#define CONFIG_SYSTEM_ScreenContrast_LONG "/SYSTEM/Screen/Contrast"   
/** @brief ��Ļ���ȵȼ�*/
#define CONFIG_SYSTEM_ScreenBklightness_LONG "/SYSTEM/Screen/Bklightness"   
/** @brief ���̱������ȵȼ�*/
#define CONFIG_SYSTEM_KbdBklightness_LONG "/SYSTEM/Keyboard/Bklightness"   
/** @brief ��������ʱ��*/
#define CONFIG_SYSTEM_PowerSleep_LONG "/SYSTEM/POWER/SLEEP"   
/** @brief ���ùػ�ʱ��*/
#define CONFIG_SYSTEM_PowerHalt_LONG "/SYSTEM/POWER/HALT"
/** @brief ����*/
#define CONFIG_LANG_INT "/SYSTEM/LANGUAGE/LANG"
/** @brief ������ʱ��*/
#define CONFIG_SYSTEM_BKLOCK "/SYSTEM/KBLOCK/DURATION"
/** @brief ����*/
#define CONFIG_SYSTEM_PW_KEY "/SYSTEM/PW/KEY"
/** @brief ����*/
#define CONFIG_SYSTEM_PW_SALT "/SYSTEM/PW/SALT"

/************************************************************************
 USB ģʽ
************************************************************************/
/** @brief USBģʽ */
#define CONFIG_SYSTEM_USB_MODE "/CONFIG/SYSTEM/USB/MODE"

/************************************************************************/
/* svc ��������                                                         */
/************************************************************************/
	/** @brief Telnet���� ���ùؼ��� */
#define CONFIG_SVC_TELNET_BOOL  "/CONFIG/SVC/telnet"
	/** @brief FTP���� ���ùؼ���*/
#define CONFIG_SVC_FTP_BOOL		"/CONFIG/SVC/FTP"
	/** @brief WIFI���� ���ùؼ���*/
#define CONFIG_SVC_WIFI_BOOL	"/CONFIG/SVC/WIFI"
	/** @brief BT���� ���ùؼ���*/
#define CONFIG_SVC_BT_BOOL	"/CONFIG/SVC/BT"
	/** @brief BT�Ƿ�ɼ�,����� */
#define CONFIG_BT_BE_A_SERVER  "/CONFIG/BT/SERVER"

/************************************************************************/
/* ������������                                                         */
/************************************************************************/
/** @brief �����豸���� */
#define CONFIG_BARCODE_TYPE_LONG		"/CONFIG/BARCODE/TYPE"
/** @brief ������ʾ��ʽ */
#define CONFIG_BARCODE_PROMPT_LONG		"/CONFIG/BARCODE/PROMPT"

enum {
	CODE_OUTPUTTYPE_NONE=0,  /**< ��           */
	CODE_OUTPUTTYPE_USBHID,  /**< USBHID       */
	CODE_OUTPUTTYPE_USBVCOM, /**< USB���⴮�� */
};
/***********************************************************************
  ����ɨ�����������ʽ                                                
************************************************************************/
#define CONFIG_BARCODE_OUTPUT_TYPE "/CONFIG/BARCODE/OUTPUT/TYPE"

/************************************************************************/
/* ����      	                                                        */
/************************************************************************/
/** @brief ɨ����ʾ����*/
#define CONFIG_SYSTEM_SCAN_SOUNDVOL_LONG		"/CONFIG/SYSTEM/SCAN_SOUND_VOL"
/** @brief ������ʾ����*/
#define CONFIG_SYSTEM_KBD_SOUNDVOL_LONG         "/CONFIG/SYSTEM/KBD_SOUND_VOL"

/************************************************************************/
/* ����			                                                        */
/************************************************************************/


/************************************************************************/
/* ���                                                                 */
/************************************************************************/
/** @brief �����Զ����еĲ�� */
#define CONFIG_PLUGIN_AUTORUN_NAME		"/CONFIG/PLUGIN/AUTORUN/NAME"

/************************************************************************/
/* ����ʾ                                                                 */
/************************************************************************/
/** @brief �Ƿ�������ɹ�����ʾ */
#define CONFIG_BARCODE_NORNAL_VIBRATOR_BOOL		"/CONFIG/BARCODE/NORMAL/VIBRATOR" 
/** @brief �Ƿ�������ɹ�������ʾ */
#define CONFIG_BARCODE_NORNAL_RING_BOOL			"/CONFIG/BARCODE/NORMAL/RING" 

/************************************************************************
 WIFI NET MODE
************************************************************************/
/** @brief WIFI����IP���÷�ʽ*/
#define CONFIG_WIFI_NET_MODE "/CONFIG/WIFI/NET/MODE"
/** @brief WIFI IP */
#define CONFIG_WIFI_NET_IP "/CONFIG/WIFI/NET/IP"
/** @brief WIFI NETMASK */
#define CONFIG_WIFI_NET_NETMASK "/CONFIG/WIFI/NET/NETMASK"
/** @brief WIFI GATEWAY */
#define CONFIG_WIFI_NET_GATEWAY "/CONFIG/WIFI/NET/GATEWAY"
/** @brief WIFI DNS1 */
#define CONFIG_WIFI_NET_DNS1 "/CONFIG/WIFI/NET/DNS1"
/** @brief WIFI DNS2 */
#define CONFIG_WIFI_NET_DNS2 "/CONFIG/WIFI/NET/DNS2"



};

/** }end of  group_ConfigData*/
#endif