/*!
 *			Copyright (C) 2010-2015	Newland Computer (FuJian) Co.,Ltd.
 * @License	福建新大陆电脑股份有限公司
 *
 * @file	pt80ConfigData.h
 * @brief	PT80 配置信息 操作类
 * @author  NEAT TEAM <neat@newlandcomputer.com>
 * @version 1.00
 * @date    2011-06-25 initial version
 */

#ifndef _PT80_CONFIGDATA_H_
#define _PT80_CONFIGDATA_H_
/**
  * @defgroup group_ConfigData PT80配置信息 操作类
  * @{
  */
#include "wx/config.h"
/** 
  * @brief PT80 SYSTEM 配置信息储存类
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
	  * @brief 读取配置信息
	  * 配置文件在此处创建
	  *
	  * @return 操作结果
	  * @retval true 成功
	  * @retval false 失败
	  */
	bool Open();

	/** 
	 * @brief 初始化默认配置信息
     * @return 操作结果
     * @retval true 成功
     * @retval false 失败
	 */
	bool InitDefaultConfigData();

	/**
	  * @保存配置
	  * @return 操作结果
	  * @retval true 成功
	  * @retval false 失败
	  */
	bool Save();

	/** 
	  * @取得wxFileConfig指针，用于修改配置
	  * @return 操作结果
	  * @retval not-NULL  wxFileConfig *
	  * @retval NULL 失败
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

/** @brief 配置文件是否已经初始化过 */
#define CONFIG_CONFIG_IsInit_BOOL "/CONFIG/IsInit"								
/** @brief 声音设置，是否允许按键音 */
#define CONFIG_SYSTEM_Sound_LONG "/SYSTEM/Sound"				
/** @brief 全局声音设置*/
#define CONFIG_SYSTEM_GSound_LONG "/SYSTEM/GSound"				
/** @brief 背光时间设置*/
#define CONFIG_SYSTEM_BKLIGHT_LONG "/SYSTEM/Screen/Backlighting"				 
/** @brief 键盘背光时间设置*/
#define CONFIG_SYSTEM_KEYBOARD_BKLIGHT_LONG "/SYSTEM/Keyboard/Backlighting"				 
/** @brief 屏幕对比度*/
#define CONFIG_SYSTEM_ScreenContrast_LONG "/SYSTEM/Screen/Contrast"   
/** @brief 屏幕亮度等级*/
#define CONFIG_SYSTEM_ScreenBklightness_LONG "/SYSTEM/Screen/Bklightness"   
/** @brief 键盘背光亮度等级*/
#define CONFIG_SYSTEM_KbdBklightness_LONG "/SYSTEM/Keyboard/Bklightness"   
/** @brief 闲置休眠时间*/
#define CONFIG_SYSTEM_PowerSleep_LONG "/SYSTEM/POWER/SLEEP"   
/** @brief 闲置关机时间*/
#define CONFIG_SYSTEM_PowerHalt_LONG "/SYSTEM/POWER/HALT"
/** @brief 语言*/
#define CONFIG_LANG_INT "/SYSTEM/LANGUAGE/LANG"
/** @brief 键盘锁时间*/
#define CONFIG_SYSTEM_BKLOCK "/SYSTEM/KBLOCK/DURATION"
/** @brief 密码*/
#define CONFIG_SYSTEM_PW_KEY "/SYSTEM/PW/KEY"
/** @brief 掩码*/
#define CONFIG_SYSTEM_PW_SALT "/SYSTEM/PW/SALT"

/************************************************************************
 USB 模式
************************************************************************/
/** @brief USB模式 */
#define CONFIG_SYSTEM_USB_MODE "/CONFIG/SYSTEM/USB/MODE"

/************************************************************************/
/* svc 服务配置                                                         */
/************************************************************************/
	/** @brief Telnet服务 配置关键字 */
#define CONFIG_SVC_TELNET_BOOL  "/CONFIG/SVC/telnet"
	/** @brief FTP服务 配置关键字*/
#define CONFIG_SVC_FTP_BOOL		"/CONFIG/SVC/FTP"
	/** @brief WIFI服务 配置关键字*/
#define CONFIG_SVC_WIFI_BOOL	"/CONFIG/SVC/WIFI"
	/** @brief BT服务 配置关键字*/
#define CONFIG_SVC_BT_BOOL	"/CONFIG/SVC/BT"
	/** @brief BT是否可见,被配对 */
#define CONFIG_BT_BE_A_SERVER  "/CONFIG/BT/SERVER"

/************************************************************************/
/* 条码设置类型                                                         */
/************************************************************************/
/** @brief 条码设备类型 */
#define CONFIG_BARCODE_TYPE_LONG		"/CONFIG/BARCODE/TYPE"
/** @brief 条码提示方式 */
#define CONFIG_BARCODE_PROMPT_LONG		"/CONFIG/BARCODE/PROMPT"

enum {
	CODE_OUTPUTTYPE_NONE=0,  /**< 无           */
	CODE_OUTPUTTYPE_USBHID,  /**< USBHID       */
	CODE_OUTPUTTYPE_USBVCOM, /**< USB虚拟串口 */
};
/***********************************************************************
  条码扫描数据输出方式                                                
************************************************************************/
#define CONFIG_BARCODE_OUTPUT_TYPE "/CONFIG/BARCODE/OUTPUT/TYPE"

/************************************************************************/
/* 音量      	                                                        */
/************************************************************************/
/** @brief 扫描提示音量*/
#define CONFIG_SYSTEM_SCAN_SOUNDVOL_LONG		"/CONFIG/SYSTEM/SCAN_SOUND_VOL"
/** @brief 键盘提示音量*/
#define CONFIG_SYSTEM_KBD_SOUNDVOL_LONG         "/CONFIG/SYSTEM/KBD_SOUND_VOL"

/************************************************************************/
/* 蓝牙			                                                        */
/************************************************************************/


/************************************************************************/
/* 插件                                                                 */
/************************************************************************/
/** @brief 开机自动运行的插件 */
#define CONFIG_PLUGIN_AUTORUN_NAME		"/CONFIG/PLUGIN/AUTORUN/NAME"

/************************************************************************/
/* 振动提示                                                                 */
/************************************************************************/
/** @brief 是否开启解码成功振动提示 */
#define CONFIG_BARCODE_NORNAL_VIBRATOR_BOOL		"/CONFIG/BARCODE/NORMAL/VIBRATOR" 
/** @brief 是否开启解码成功响铃提示 */
#define CONFIG_BARCODE_NORNAL_RING_BOOL			"/CONFIG/BARCODE/NORMAL/RING" 

/************************************************************************
 WIFI NET MODE
************************************************************************/
/** @brief WIFI网络IP设置方式*/
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