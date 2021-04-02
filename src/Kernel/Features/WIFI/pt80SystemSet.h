/*!
 *			Copyright (C) 2010-2015	Newland Computer (FuJian) Co.,Ltd.
 * @License	福建新大陆电脑股份有限公司
 *
 * @file	pt80SystemSet.h
 * @brief	PT80 系统配置类
 * @author  NEAT TEAM <neat@newlandcomputer.com>
 * @version 1.00
 * @date    2011-11-01 initial version
 */

#ifndef _PT80_SYSTEMSET_H_
#define _PT80_SYSTEMSET_H_
#include "settings.h"
#include <wx/arrstr.h>
/** @class CPt80SystemSet PT80系统设置类
  * 配置PT80系统，并保存配置
  */
class SDKIMPORT CPt80SystemSet{
public:
	/** @brief 获取全局的操作句柄 */
	static CPt80SystemSet *GetHandle();
	/** @brief 设置键盘背光模式 */
	int SetKbdBL(int mode);
	/** @brief 获取键盘背光相关字符串
	 *  @note 该接口已废弃
	 */
	int GetKbdBlString(wxArrayString &arryString);
	/** @brief 获取键盘背光模式 */
	int GetKbdBL();
	
	/** @brief 设置LCD背光模式 */
	int SetLcdBL(int mode);
	/** @brief 获取LCD背光相关字符串 
	*  @note 该接口已废弃
	*/
	int GetLcdBlString(wxArrayString &arryString);
	/** @brief 获取LCD背光模式 */
	int GetLcdBL();


	/** @brief 设置LCD对比度 */
	int SetLcdContrast(int value);
	/** @brief 获取LCD对比度 */
	int GetLcdContrast();

	/** @brief 设置LCD亮度 */
	int SetLcdBrightness(int brightness);
	/** @brief 获取LCD亮度 */
	int GetLcdBrightness();
	/** @brief 获取LCD亮度相关字符串 
	*  @note 该接口已废弃
	*/
	int GetLcdBrightnessString(wxArrayString &arryString);

	/** @brief 设置空闲休眠模式 */
	int SetSleepMode(int mode);
	/** @brief 获取空闲休眠模式相关字符串 */
	int GetSleepModeString(wxArrayString &arrayString);
	/** @brief 获取空闲休眠模式 */
	int GetSleepMode();

	/** @brief 设置空闲关机模式 */
	int SetHaltMode(int mode);
	/** @brief 获取空闲关机模式相关字符串 */
	int GetHaltModeString(wxArrayString &arrayString);
	/** @brief 获取空闲关机模式 */
	int GetHaltMode();

	/** @brief 获取当前WIFI服务的开启状态 */
	int GetSvcWifiMode();
	/** @brief 开启或关闭WIFI服务 */
	bool SetSvcWifiMode(bool bOpen=true);

	/** @brief 获取当前BT服务的开启状态 
	  * @return 0-关闭；1-开启
	  */
	int GetSvcBtMode();
	/** @brief 开启或关闭BT服务 */
	bool SetSvcBtMode(bool bOpen=true);

	/** @brief 取得上次BT是否可被配对 
	 *  @return 1 可见；0-不可见
	 *  @note 不直接操作设备，只做储存配置使用
	 */
	int GetBtDiscoverEnable();
	void SetBtDiscoveryEnable(bool bValue=true);

	/** @brief 获取当前Telnet服务的开启状态 */
	int GetSvcTelnetMode();
	/** @brief 开启或关闭Telnet服务 */
	bool SetSvcTelnetMode(bool bOpen=true);

	/** @brief 获取当前FTP服务的开启状态 */
	int GetSvcFtpMode();
	/** @brief 开启或关闭FTP服务 */
	bool SetSvcFtpMode(bool bOpen=true);

	/** @brief 获取识读头类型 */
	int GetBarcodeDeviceType();
	/** @brief 设置识读头类型 */
	int SetBarcodeDeviceType(int type);

	/** @brief 设置识读头提示方式 */
	int SetBarcodePrompt( bool bRing, bool bVibrator);
	/** @brief 获取识读头提示方式 */
	int GetBarcodePrompt(bool &bRing, bool &bVibrator);

	/** @enum BARCODE_PROMT
	  * 识读头提示方式
	  */
	enum BARCODE_PROMT{
		BARCODE_PROMT_NOSOUND = 0,
		BARCODE_PROMT_SOUND= 1,
		BARCODE_PROMT_VIBRATOR= 2,
		BARCODE_PROMT_ALL= 3,
	};

	/** @brief 设置识读头提示方式 
	  * @param[in] mode 
	  * - 0 无声
	  * - 1 响铃
	  * - 2 振动
	  * - 3 响铃和振动
	  * @param[in] gSound 全局的声音
	  * - true 全局静音
	  */
	int SetBarcodePrompt( int mode, bool gSound );

	/** @brief 获取识读头提示方式 
	  *
	  */
	int GetBarcodePrompt();

	/** @brief 设置键盘Repeat 
	  * @param[in] delay 延时(在第一次按键后多少时间重复)
	  * @param[in] period 周期(单位ms)
	  */
	int SetKeyboardRepeat(int delay, int period);
	/** @brief 设置键盘按键音
	  * @param[in] bSound true 开启按键音
	  * @param[in] gSound true 全局静音
	  */
	int SetKeyboardSound(bool bSound, bool gSound=false);
	/** @brief 获取按键音 */
	bool GetKeyboardSound();
	/** @brief 获取全局静音 */
	bool GetKeyboardGSound();

	/** @brief 根据配置初始化所有硬件 */
	int InitDevice();
	/** @brief 从文件初始化时区 */
	void SetTZFromFile();

	/** @brief 获取键盘音量设置 */
	int GetKbdSoundVol();
	int SetKbdSoundVol(int vol=0);
	/** @brief 获取扫描提示音量设置 */
	int GetScanSoundVol();
	int SetScanSoundVol(int vol=0);

	enum WIFI_NET_MODE {
		WIFI_NET_MODE_CUSTOM,
		WIFI_NET_MODE_DHCP,
	};
	/** @brief 获取WIFI网络IP分配方式 
	  * @return
	  * @retval ::WIFI_NET_MODE_DHCP
	  * @retval ::WIFI_NET_MODE_MANUAL
	  */
	int GetWifiNetMode();
	/** @brief 设置WIFI网络IP分配方式 
	  * @note 如果IP地址信息有存在会立即设置。
	  */
	int SetWifiNetMode(int mode);

	/** @brief 设置WIFI网络IP信息 */
	int SetWifiCustomNetIp(wxString ip, wxString netmask, wxString gateway, wxString dns1, wxString dns2);
	/** @brief 获取WIFI网络IP信息 */
	int GetWifiCustomNetIp(wxString &ip, wxString &netmask, wxString &gateway, wxString &dns1, wxString &dns2);

public:
	wxString GetPwKey();
	wxString GetPwSalt();
	int SetPasswd(wxString key, wxString salt);

////////////////////PT80二期添加的接口/////////////////////////
/************************************************************************/
/* 自动光感方案配置                                                     */
/************************************************************************/
	/** @brief 设置键盘背光开启阀值，从配置文件读入，光感控制模式时启用 */
	int SetKbdBLSchem(void);
	/** @brief 设置LCD背光控制方案，从配置文件读入，光感控制模式时启用 */
	int SetLcdBLSchem(void);

	int DetectScannerType(void);
};

#endif