/*!
 *			Copyright (C) 2010-2015	Newland Computer (FuJian) Co.,Ltd.
 * @License	福建新大陆电脑股份有限公司
 *
 * @file	pt80DeviceOpt.h
 * @brief	PT80 外设操作类
 * @author  NEAT TEAM <neat@newlandcomputer.com>
 * @version 1.00
 * @date    2011-11-01 initial version
 */
#ifndef __PT80_DEVICEOPT_H_
#define __PT80_DEVICEOPT_H_

#include <wx/string.h>
#include <wx/thread.h>
#include <wx/dynarray.h>
#include "pt80SystemSet.h"
#ifdef __LINUX__
#include <pt80/nlinux/include/wpa_client.h>
#else

#endif
/**
  * @defgroup group_deviceOpt PT80设备操作类
  * @{
  */

/** @class CPt80DeviceOpt PT80底层设备操作类
  * PT80 底层设备操作类(USB、电源、服务、GPIO、电池、蜂鸣器、LCD、键盘)
  */
class SDKIMPORT CPt80DeviceOpt
{
public:
/************************************************************************/
/* USB                                                                  */
/************************************************************************/
	/** @enum USB模式*/
	enum USB_MODE{
		USB_MODE_NONE,		/**< 空，不加载任何驱动*/
		USB_MODE_SERIAL_DOWNLOAD, /**< 下载模式，占用USB串口功能 */
		USB_MODE_NET,		/**< NET */
		USB_MODE_SERIAL,		/**< 串口 */
		USB_MODE_KEYBOARD,	/**< HID键盘*/
		USB_MODE_STORAGE,	/**< U盘 */
		USB_MODE_STORAGE_RO, /**< U盘只读 */
	};
	
	/**
	 * @enum USBStatus
	 * @brief USB连接状态(非NONE模式)
	 */
	enum UsbStatus{
		USB_CONNECT = 1,    /**< @brief USB连接 */
		USB_DISCONNECT = 0, /**< @brief USB未连接 */
	};

	/** @brief 设置USB模式
	  * @return 0-成功， other-错误
	  */
	static int usb_set_mode(int mode);
	
	/** @brief 获取当前USB模式
	  * @return <0 - 失败, other ::USB_MODE
	  */
	static int usb_get_mode();

	/** @brief 获取USB网卡的IP地址
	  * @retrun
	  * @retval NULL 未分配
	  * @retval 其它 USB网卡IP地址
	  */
	static char *usb_net_get_ip();

	/** @brief 设置USB网卡的IP地址
	  * @return
	  * @retval 0 成功
	  * @retval 其它 失败
	  */
	static int usb_net_set_ip(const char *network);

	/** @brief 打开USB输入设备
	  * @return >0 USB输入设备的文件描述符， 其它失败
	  */
	static int usb_hid_init();
	
	/** @brief 投射按键
	  * @param[in] fd usb_hid_init返回的文件描述符
	  * @param[in] keycode HID标准的简码值，详见HID Usage Tables手册
	  * @return 0 成功, 其它 失败
	  */
	static int usb_hid_send(int fd, int keycode, int mode);
	
	/** @brief 投射按键字符
	  * @param[in] fd usb_hid_init返回的文件描述符
	  * @param[in] buf 字符
	  * @param[in] len 字符长度
	  * @return 0 成功， 其它 失败
	  * @note 只支持字母，数字
	  */
	static int usb_hid_send_char(int fd, char *buf, int len);


	/** @brief 打开USB串口设备
	  * @return 返回值
	  * @retval fd USB串口设备fd 
	  * @retval <0 打开设备出错
	  */
	static int usb_serial_init(void);

	/** @brief  挂载USB存储设备到本地目录 
	  * @return 返回值
	  * @retval 0 成功
	  * @retval 1 设备忙
	  * @retval 其它 未知错误
	  */
	static int usb_storage_mount(wxString path);

	/** @brief  解除USB存储设备挂载 
	  * @return 返回值
	  * @retval 0 成功
	  * @retval 1 设备忙
	  */
	static int usb_storage_umount(wxString path);

	/** 
	 * @brief 获取当前USB的连接状态
	 * @return 操作结果
	 * @retval	::USB_CONNECT
	 * @retval	::USB_DISCONNECT
	 */
	static int usb_get_status();

	/**
	 * @brief 重新设置大小并格式化U盘
	 * @param[in] size  新建虚拟U盘的大小
	 *
	 * @return	操作结果
	 * @retval	::USB_SUCCESS
	 * @retval	::USB_ERR_BUSY
	 */
	static int usb_storage_format(int size);

	/** 
	 * @brief 获取USB储存设备大小
	 * @return USB储存设备大小
	 */
	static int usb_storage_getsize();

/************************************************************************/
/* 电源                                                                 */
/************************************************************************/
	/** 
	 * @brief 设置键盘锁状态
	 * @param[in] bLick 
	 * - TRUE 锁定
	 * - FALSE 未锁定
	 */
	static void kbd_set_lock(bool bLock);

	/** 
	 * @brief 获取键盘锁状态
	 * @return 操作结果
	 * @retval TRUE 锁定
	 * @retval FALSE 未锁定
	 */
	static bool kbd_get_lock();

/************************************************************************/
/* 电源                                                                 */
/************************************************************************/
	/** @brief 抑制休眠 
	  * @return 返回值
	  * @retval true 成功
	  * @retval false 错误
	  */
	static bool pm_suppress_sleep_on();

	/** @brief 抑制休眠解除
	  * @return 返回值
	  * @retval true 成功
	  * @retval false 错误
	  */
	static bool pm_suppress_sleep_off();

	/** @brief 获取抑制休眠计数
	  *
	  * @return 操作结果
	  * @retval <0  失败
	  * @retval 其它抑制计数值
	  */
	static size_t pm_get_suppress_sleep();

	/** @brief 抑制关机
	  * @return 返回值
	  * @retval true 成功
	  * @retval false 错误
	  */
	static bool pm_suppress_powerdown_on();

	/** @brief 抑制关机解除 
	  * @retval true 成功
	  * @retval false 错误
	  */
	static bool pm_suppress_powerdown_off();

	/** @brief 获取抑制关机计数
	  *
	  * @return 操作结果
	  * @retval <0  失败
	  * @retval 其它抑制计数值
	  */
	static size_t pm_get_suppress_powerdown();

	/** @brief 设置闲置休眠时间 
	  * @return 返回值
	  * @retval true 成功
	  * @retval false 错误
	  */
	static bool pm_set_sleep_timeout (int seconds);

	/** @brief 发起重启 
	  * @return 返回值
	  * @retval true 成功
	  * @retval false 错误
	  */
	static bool pm_reboot (void);

	/** @brief 发起关机
	  * @return 返回值
	  * @retval true 成功
	  * @retval false 错误
	  */
	static bool pm_powerdown (void);

	/** @brief 发起休眠
	  * @return 返回值
	  * @retval true 成功
	  * @retval false 错误
	  */
	static bool pm_sleep (void);

	/** @brief 获取电源管理的文件描述符
	  * @return 
	  * @retval >0 电源管理操作的文件描述符
	  * @retval <0 错误
	  * @note 使用该接口来监听电源管理的状态改变，例如发起休眠，发起关机。
	  * @code 
	  fd_set fds;
	  int ret;
	  char buf[100];
	  int fd = CPt80DeviceOpt::pm_get_fd();
	  FD_ZERO(&fds);
	  FD_SET(fd, &fds);
	  ret = select(fd + 1, &fds, NULL, NULL, NULL);
	  if (ret < 0)
	    break;
	  ret = read(fd, buf, 99);
	  buf[ret] = '\0';
	  printf("Recv: %s\n", buf); // 这里可能输出sleep或者powerdown
	  * @endcode
	  */
	static int pm_get_fd(void);

/************************************************************************/
/* 服务                                                                 */
/************************************************************************/
	/** @brief 启用FTP服务
	  * @return 返回值
	  * @retval true 成功
	  * @retval false 失败
	  */
	static bool svc_ftp_start();

	/** @brief 禁用FTP服务
	  * @return 返回值
	  * @retval true 成功
	  * @retval false 失败
	  */
	static bool svc_ftp_stop();

	/** @brief 启用TELNET服务
	  * @return 返回值
	  * @retval true 成功
	  * @retval false 失败
	  */
	static bool svc_telnet_start();

	/** @brief 禁用TELNET服务
	  * @return 返回值
	  * @retval true 成功
	  * @retval false 失败
	  */
	static bool svc_telnet_stop();

	/** @brief 启用无线服务 
	  * @return 返回值
	  * @retval 0 成功
	  * @retval -2 无法识别到WIFI
	  * @retval 其它 未知错误
	  * @retval false 失败
	  */
	static int svc_wireless_start();

	/** @brief 禁用无线服务
	  * @return 返回值
	  * @retval true 成功
	  * @retval false 失败
	  */
	static bool svc_wireless_stop();

	/** @brief 启用BT服务 
	  * @return 返回值
	  * @retval true 成功
	  * @retval false 失败
	  */
	static bool svc_bt_start();

	/** @brief 禁用BT服务
	  * @return 返回值
	  * @retval true 成功
	  * @retval false 失败
	  */
	static bool svc_bt_stop();

/************************************************************************/
/* GPIO                                                                 */
/************************************************************************/
	/** @brief 振子控制
	  * @param bValue 
	  * @li true 开启振动
	  * @li false 关闭振动
	  */
	static void gpio_set_vibratorPower(bool bValue);

	/** @brief EM1300/SE955 电源控制
	  * @param bValue 
	  * @li true 开启电源
	  * @li false 关闭电源
	  */
	static void gpio_set_ScannerPower(bool bValue);

	/** @brief EM1300/SE955 扫描触发控制
	  * @param bValue 
	  * @li true 触发
	  * @li false 关闭触发
	  */
	static void gpio_set_ScannerTrig(bool bValue);
	
	/** @brief SE955唤醒管脚控制
	  * @param bValue 
	  * @li true 电源拉低
	  * @li false 电源拉高
	  */
	static void gpio_set_SE955Wakeup(bool bValue);

/************************************************************************
 LED
************************************************************************/
	/** @brief 绿色LED灯操作
	  * @param bValue 
	  * @li true 亮
	  * @li false 灭
	  */
	static void led_set_green(bool bValue);

	/** @brief 红色LED灯操作
	  * @param bValue 
	  * @li true 亮
	  * @li false 灭
	  */
	static void led_set_red(bool bValue);

/************************************************************************/
/* 振子                                                                 */
/************************************************************************/
	/** @brief 持续振动一定时长
	  * @param[in] delay 持续振动时长(ms)
	  */
	static void vibrator_shake(int delay);

/************************************************************************/
/* 识读头                                                               */
/************************************************************************/
	/** 识读头设备类型 */
	enum BarcodeDevice{
		BARCODE_DEVICE_EM1300, /**< @brief EM1300 */
		BARCODE_DEVICE_SE955,  /**< @brief SE955 */
		BARCODE_DEVICE_CM42, /**< @brief CM42 */
		BARCODE_DEVICE_UNKNOW, /**< @brief UNKNOW */
	};

	/**
	  * @brief 识读头初始化
	  * @return 返回值
	  * @retval >=0 成功
	  * @retval 其它失败
      */
	static int barcode_init(void);

	/** 
	  * @brief 识读头关闭
	  * @return 返回值
	  * @retval 0 成功
	  * @retval 其它失败
	  */
	static int barcode_close();

	/**
	  * @brief 获取识读头的类型
	  * @return 识读头类型
	  * @retval ::BARCODE_DEVICE_EM1300 
	  * @retval ::BARCODE_DEVICE_SE955
	  * @retval ::BARCODE_DEVICE_CAMERA
	  * @retval <0 获取失败
	  */
	static int barcode_get_type(void);

	/**
	  * @brief 扫描硬件，返回扫描头类型
	  * @return 扫描头类型 ::BarcodeDevice
	  * @retval <0 未检测到任何扫描头
	  * @retval 其它详见::BarcodeDevice
	  * @note 以下是自动判断的逻辑
	  * @code 
	  * if (open("/dev/camera", O_RDONLY)>0){
	  *    return BARCODE_DEVICE_CAMERA;
	  * } 
	  * else {
	  *    if (send em1300 cmd and get return info )
	  *      return BARCODE_DEVICE_EM1300;
	  *    else if ( send se955 and get return info )
	  *      return BARCODE_DEVICE_SE955
	  *    else 
	  *      return BARCODE_DEVICE_UNKNOW;
	  *    
	  * }
	  * @endcode
	  */
	static int barcode_detect_scan_type();

	/**
	* @brief 设置识读头设备类型
	* @param type 扫描头类型 ::BarcodeDevice
	* @note <b>识读头设备类型会自动检测，除非你知道你在做什么，否则请停止调用该接口</b>
	*/
	static void barcode_set_type(int type);

   /**
	* @brief 读条码
	* @param[out] buf 条码存放区
	* @param[in] len 条码存放区大小
	* @param[in] timeout 超时(ms)
	* @li <0 一直等待
	* @li =0 检查并立即返回
	* @li >0 超时等待
	* @return 返回值
	* @li <0 错误
	* @li =0 超时
	* @li >0 读到的条码个数
	*/
	static int barcode_read(char *buf, int len, int timeout);

	/**
	* @brief 设置条码扫描提示方式
	* @param[in] bRing  
	* @li true 响铃
	* @li false 静音
	* @param[in] bVibrator
	* @li true 振动
	* @li false 不振动
	*/
	static void barcode_set_prompt(bool bRing, bool bVibrator);

/************************************************************************/
/* 电池                                                                 */
/************************************************************************/
	/**
	  * @brief 获取主备电池电压 
	  * @param main 指向主电池的float指针
	  * @param standby 指向备用电池的float指针
	  * @return 返回值
	  * @li true 成功
	  * @li false 失败
	  */
	static bool getBattery(float *mainVoltage, float *standbyVoltage);
	
	/**
	* @brief 获取主电池电量百分比
	* @return 操作结果
	* @li <0 错误
	* @li 其它 主电池电量
	*/
	static int getMainBattery();

	/**
	* @brief 获取备用电池电量百分比
	* @return 操作结果
	* @li <0 错误
	* @li 其它 备用电池电量
	*/
	static int getStandbyBattery();


	/*
	* @enum MainBatteryStatus 主电池充电状态 
	*/
	enum MainBatteryStatus{
		MAIN_BATTER_CHARGING, /**< @brief 正在充电 */
		MAIN_BATTER_DISCHARGING, /**< @brief 未充电 */
	};

	/**
	* @brief 获取主电池充电状态
	* @return 操作结果
	* @li <0 错误
	* @li ::MAIN_BATTER_CHARGING
	* @li ::MAIN_BATTER_DISCHARGING
	*/
	static int getMainBatteryStatus();

	/*
	* @enum StandbyBatteryStatus 备用电池充电状态 
	*/
	enum StandbyBatteryStatus{
		STANDBY_BATTER_CHARGING, /**< @brief 正在充电 */
		STANDBY_BATTER_COMPLETE_CHARGE, /**< @brief 充电完成 */
		STANDBY_BATTER_DISCHARGING, /**< @brief 未充电 */
	};

	/*
	* @brief 获取备用电池充电状态
	* @return 操作结果
	* @li <0 错误
	* @li ::STANDBY_BATTER_CHARGING
	* @li ::STANDBY_BATTER_COMPLETE_CHARGE
	* @li ::STANDBY_BATTER_DISCHARGING
	*/
	static int getStandbyBatteryStatus();

	/*
	* @brief 获取电池盖状态
	* @return 电盖状态
	* @li 1 关闭
	* @li 0 打开 
	* @li 其它 错误
	*/
	static int getBatteryCoverStatus();


/************************************************************************/
/* 蜂鸣器                                                               */
/************************************************************************/

	/**
	* @brief 开始响铃
	* @return 
	* @retval true 成功
	* @retval false 失败
	*/
	static bool buzz_on(void);

	/**
	* @brief 停止响铃
	* @return 
	* @retval true 成功
	* @retval false 失败
	*/
	static bool buzz_off(void);

	/** @enum 蜂鸣器响铃时长
	 */
	enum BUZZ_LEVEL {
		BUZZ_LEVEL_LOW, /**< 短 */
		BUZZ_LEVEL_MEDI, /**< 中 */
		BUZZ_LEVEL_HIGH, /**< 长 */
	};
	/**
	* @brief 响铃
	* @param[in] timing 响铃时长
	* @return 返回值
	* @retval true 成功
	* @retval false 失败
	* @note 这里只支持短中长三个预定时长的响铃 BUZZ_LEVEL
	*/
	static bool buzz_beep(int timing);

	/** @brief 设置扫描响铃频率 */
	static bool buzz_set_freq(int freq);
	
	/** @brief 设置扫描响铃占空比 */
	static bool buzz_set_duty(int duty);

	/** @brief 设置键盘响铃频率 */
	static bool buzz_kbd_set_freq(int freq);
	
	/** @brief 设置键盘响铃占空比 */
	static bool buzz_kbd_set_duty(int duty);

	/** @brief 键盘音 响铃 */
	static bool buzz_kbd_beep(int timing=0);


/************************************************************************/
/* LCD                                                                  */
/************************************************************************/
	/** @enum 背光亮度 */
	enum BL_BRIGHT{
		BL_BRIGHT_LEVEL_1,	/**< @brief 一级亮度 */
		BL_BRIGHT_LEVEL_2,  /**< @brief 二级亮度 */
		BL_BRIGHT_LEVEL_3,  /**< @brief 三级亮度 */
		BL_BRIGHT_LEVEL_4,  /**< @brief 四级亮度 */
		BL_BRIGHT_LEVEL_5,  /**< @brief 五级亮度 */
		BL_BRIGHT_LEVEL_6,  /**< @brief 六级亮度 */
		BL_BRIGHT_AUTO,     /**< @brief 自动亮度(光感控制) */
	};

	/**
	* @brief 设置LCD背光自动关闭时间
	* @param[in] timeout 背光自动关闭时间(单位:ms)
	*            - 0 背光常灭
	*            - 3600 背光常亮
	* @return 返回值
	* @retval true 成功
	* @retval false 失败
	*/
	static bool lcd_bl_set_timeout(int timeout);

	/** 
	* @brief 设置LCD背光亮度
	* @param[in] bright 背光亮度等级
	* @li ::BL_BRIGHT_LEVEL_1
	* @li ::BL_BRIGHT_LEVEL_2
	* @li ::BL_BRIGHT_LEVEL_3
	* @li ::BL_BRIGHT_LEVEL_4
	* @li ::BL_BRIGHT_LEVEL_5
	* @li ::BL_BRIGHT_LEVEL_6
	* @li ::BL_BRIGHT_AUTO
	* @return 返回值
	* @retval true 成功
	* @retval false 失败
	*/
	static bool lcd_bl_set_bright(int bright);

	/** @brief API开启背光
	* @param[in] autoClose 是否自动关闭背光
	* @li 0 不自动关闭
	* @li 1 自动关闭
	* @return 返回值
	* @retval true 成功
	* @retval false 失败
	*/
	static bool lcd_bl_turn_on(int autoClose);

	/** @brief API关闭背光
	* @return 返回值
	* @retval true 成功
	* @retval false 失败
	*/
	static bool lcd_bl_turn_off();

	/** @brief 设置LCD对比度
	* @param[in] contrast 对比度(1-255),推荐值65
	* @return 返回值
	* @retval true 成功
	* @retval false 失败
	*/
	static bool lcd_set_contrast(int contrast);


/************************************************************************/
/* 键盘                                                                 */
/************************************************************************/

	/** @brief 设置键盘背光自动关闭时间
	* @param[in] timeout 背光自动关闭时间(单位:ms)
	*            - 0 背光常灭
	*            - 3600 背光常亮
	* @return 返回值
	* @retval true 成功
	* @retval false 失败
	*/
	static bool kbd_bl_set_timeout(int timeout);

	/** @brief API开启背光
	* @param[in] autoClose 是否自动关闭背光
	* @li 0 不自动关闭
	* @li 1 自动关闭
	* @return 返回值
	* @retval true 成功
	* @retval false 失败
	*/
	static bool kbd_bl_turn_on(int autoClose);

	/** @brief API关闭背光
	* @return 返回值
	* @retval true 成功
	* @retval false 失败
	*/
	static bool kbd_bl_turn_off();

	/** @brief 设置按键声音
	* @param[in] bSound 
	* @li true 开启按键音
	* @li false 关闭按键音
	* @return 返回值
	* @retval true 成功
	* @retval false 失败
	*/
	static bool kbd_set_beep(bool bSound);

	/** @brief 获取键盘按键音
	* @return 键盘按键音
	* @retval 0 按键音关闭
	* @retval 1 按键音开启
	* @retval <0 获取失败
	*/
	static int kbd_get_beep (void);


/************************************************************************/
/* WIFI底层接口                                                         */
/************************************************************************/
	/** @brief 连接wpa_supplicant
	* @return 返回值
	* @retval 0 成功
	* @retval <0 失败
	*/
	static int wifi_connect_to_supplicant();

	/** @brief 返回当前的wpa_ctrl */
	static struct wpa_ctrl *wifi_get_current_ctrl();

	/** @brief 断开与wpa_supplicant的连接 */
	static void wifi_close_supplicant_connection();

	/** @brief 获取当前连接的速度 
	* @return 当前的连接速度 单位 M
	* @retval 1-100 当前的连接速度
	* @retval <0 出错
	*/
	static int  wifi_getLinkSpeed();

	/** @brief 获取MAC地址 
	* @return MAC地址
	* @retval NULL 出错
	* @retval 其它 MAC地址
	*/
	static char* wifi_getMacAddress();

	/** @brief 判断当前是否有事件数据可以读
	  * @return 返回结果
	  * @retval 1 - 有事件数据可以读，调用wifi_waitForEvent获取内容
	  * @retval 0 - 无事件数据
	  */
	static int wpa_ctrl_pending(struct wpa_ctrl *ctrl);

	/** @brief 监听wpa_supplicant事件的发生
	* @return 事件字符
	* @note 阻塞函数
	*/
	static char* wifi_waitForEvent();

	/** @brief 查看当前WIFI网络列表
	* @return 网络列表，各域之间以tab间隔
	* network id / ssid / bssid / flags
	* 0       softwaredev     any     [DISABLED]
	* 1       2012    any     [CURRENT]
	*/
	static char* wifi_listNetworks();

	/** @brief 新增网络
	* @return 返回新增网络ID
	*/
	static int wifi_addNetwork();

	/** @brief 设置网络参数
	* @param[in] name ssid,bssid,psk,wep_key0等参数
	* @param[in] value 参数值
	* @return 0 - 成功， 1 - 失败
	*/
	static int wifi_setNetworkVariable( int netId, const char* name, const char* value);

	/** @brief 获取网络参数  */
	static char* wifi_getNetworkVariable(  int netId, const char* name);

	/** @brief 移除网络
	* @param[in] netID 网络id
	* @return 0 - 成功; 其它 - 失败
	*/
	static int wifi_removeNetwork(int netId);

	/** @brief 启用网络
	* @param[in] netID 网络id
	* @param[in] disableOthers 1-启用该网络并禁止其它本地网络，0-启用该网络
	* @note enable网络后，有事件数据返回，可以监听并判断是否成功连接或者密钥是否正确(incorrect关键字为不正确的密钥)
	*/
	static int wifi_enableNetwork( int netId, int disableOthers);

	/** @brief 禁用某个网络 */
	static int wifi_disableNetwork(int netId);

	/** @brief 取WIFI状态 */
	static char *wifi_status();

	/** @brief 查看AP详细信息 
	* @param[in] ssid AP BSSID
	*/
	static char *wifi_queryApInfo(const char *bssid);

	/** @brief 测试与wpa_supplicant连通性 */
	static int wifi_ping();

	/** @brief 获取扫描结果 */
	static char * wifi_scanResults();

	/** @brief 断开当前网络
	* @return 0 - 成功; 其它 - 失败
	*/
	static int wifi_disconnect();

	/** @brief 重新连接当前网络 */
	static int wifi_reconnect();

	/** @brief 重新认证 
	 * @note 需通过wifi_waitForEvent监听
	 */
	static int wifi_reassociate();

	/** @brief 触发扫描
	* @param[in] forceActive 1 - ACTIVE; 0 - PASSIVE
	* @note 需通过wifi_waitForEvent监听，"CTRL-EVENT-SCAN-RESULTS "标志着事件的结束
	*/
	static int wifi_scan(int forceActive);

	/** @brief 保存配置 */
	static int wifi_saveConfig();

	/** @brief 重新加载驱动配置 */
	static int wifi_reloadConfig();

/************************************************************************/
/* WIFI 接口(对底层接口进行封装)推荐使用                                */
/************************************************************************/
	enum WifiFlags {
		WIFI_FLAGS_NONE = 0,    
		WIFI_FLAGS_WEP  = 1,    
		WIFI_FLAGS_WPA  = 2,    
		WIFI_FLAGS_WPA2 = 4,    
		WIFI_FLAGS_WPA2_EAP= 8,    
	};

	enum WiFiStatus{
		WIFI_STATUS_CONNECTED_ = 1, /**< 已连接 */
		WIFI_STATUS_DISCONNECT_, /**< 未连接 */
		WIFI_STATUS_CONNECTING_, /**< 正在连接 */
	};

	typedef struct {
		char ssid[128]; 
		char bssid[25]; 
		int frequency;  
		int quality;    
		int level;      
		int noise;      
		int flags;      
		int netId;
	} WifiNetwork;

	/** @brief 储存WIFI网络信息和密钥的基本单元
	* @note 该类常用于获取WIFI扫描结果和创建新的WIFI链接
	*/
	class CPt80WifiNetworkListItem{
	public:
		WifiNetwork net; /**< WIFI网络连接信息 */
		wxString strUser; /**< WPA-ENT 密钥验证方式 */
		wxString strKey; /**< 密钥用于连接时使用 */
		wxString strEAP; /**< EAP方法 */
		wxString strPhase2Authentication ;/**< 阶段2身份验证方式 */
	}; 

	/** @brief 定义 Pt80WifiNetworkList 
	* @note 用于存储WIFI扫描结果
	*/
	WX_DEFINE_ARRAY(CPt80WifiNetworkListItem *, CPt80WifiNetworkList); 

	/** @brief 获取WIFI扫描结果(默认5S超时)
	  * @param[out] list WIFI扫描结果数组
	  * @return 返回结果 0-成功,其它失败
	  * @note 阻塞函数,时间(1S-3S),最后需要调用WX_CLEAR_ARRAY(list)来释放扫描数据空间
	  */
	static int wifi_mgr_Scan(CPt80WifiNetworkList &list);

	/** @brief 获取当前WIFI的状态 
	  * @return 操作结果
	  * @retval WIFI_STATUS_CONNECTED_ 已连接
	  * @retval WIFI_STATUS_DISCONNECT_ 未连接
	  * @retval WIFI_STATUS_CONNECTING_ 正在连接
	  */
	static int wifi_mgr_GetStatus();

	/** @brief 新增网络,并配置信息
	  * @param[out] netID 新增加的网络ID，用于启用或者移除网络配置
	  * @param[out] net 网络配置信息
	  * @param[in] IshiddenAP 添加的网络是否是隐藏AP(不广播SSID)
	  * @return 返回结果 0-成功,其它失败
	  */
	static int wifi_mgr_AddNetwork(int &netID, CPt80WifiNetworkListItem &item, bool IshiddenAP);


	/** @brief 新增网络,并配置信息
	  * @param[out] netID 新增加的网络ID，用于启用或者移除网络配置
	  * @param[out] net 网络配置信息
	  * @return 返回结果 0-成功,其它失败
	  */
	static int wifi_mgr_AddNetwork(int &netID, CPt80WifiNetworkListItem &item);

	
	/** @brief 移除网络 */
	static int wifi_mgr_RemoveNetwork(int netID);

	/** @brief 启用某网络 
	  * @param[in] netID 
	  * @param[in] bDisableOthers 是否禁用其它网络
	  * @return 返回值
	  * @retval 0 成功(已经连接)
	  * @retval 1 认证错误(密钥错误)
	  * @retval 2 超时 (默认15S认证时间)
	  * @retval <0 未知错误
	  * @note 认证错误，或者超时会自动移除该网络ID
	  */
	static int wifi_mgr_EnableNetwork(int netID, bool bDisableOthers);

	/** @brief 保存配置
	  * @note 该函数会列举当前的所有网络列表，并移除空的网络列表，再进行保存配置
	  */
	static int wifi_mgr_SaveConfig();

	/** @brief 查询本地网络
	  * @param list 本地网络数组
	  * @return 返回结果
	  * @retval 0 成功
	  * @retval <0 失败
	  */
	static int wifi_mgr_LocalNetwork(CPt80WifiNetworkList &list);

	/** @brief 查询指定BSSID的详细信息
	  * @param[out] item PT80 WIFI数据信息
	  * @return 返回值
	  * @retval 0 已获取详细信息
	  * @retval 1 无任何返回结果
	  * @retval <0 错误
	  * @note 需要先设置item中的bssid参数
	  */
	static int wifi_mgr_QueryInfo(CPt80WifiNetworkListItem &item);

	/** @brief 查询当前连接网络的详细信息
	  * @param[out] item PT80 WIFI数据信息
	  * @return 返回值
	  * @retval 0 已获取详细信息
	  * @retval 1 无任何返回结果
	  * @retval <0 错误
	  */
	static int wifi_mgr_Current(CPt80WifiNetworkListItem &item);

	/** @brief 断开当前无线网络 
	  * @return 返回值
	  * @retval 0 成功
	  * @retval 其它错误
	  */
	static int wifi_mgr_Disconnect();

	/** @brief 获取当前无线网络 IP地址
	  * @return 返回值
	  * @retval NULL 未分配IP
	  * @retval 其它 已分配的IP
	  */
	static char *wifi_mgr_get_ip();

	/** @brief 获取当前无线网络mac地址
	  * @return 操作结果
	  * @retval NULL 无法获取，无线网络接点eth0未存在
	  * @retval 其它 mac地址
	  */
	static char *wifi_mgr_get_mac();

	/** @brief 开启udhcpc服务 */
	static int wifi_mgr_start_udhcpc();

	/** @brief 关闭udhcpc服务 */
	static int wifi_mgr_stop_udhcpc();

	/** @brief 设置无线网络IP地址、掩码、网关、DNS
	  * @return 操作结果
	  * @retval 0 成功
	  * @retval 其它 失败
	  */
	static int wifi_mgr_set_ip(wxString ip, wxString netmask, wxString gateway, wxString dns1, wxString dns2);

	/** @brief 获取当前信号值 
	  * @return 信号强度(单位dBm)
	  */
	static int wifi_mgr_GetRssi();

	/** @brief 转换dbm值为信号强度百分比
	  * @return 信号强度百分比
	  */
	static int wifi_mgr_GetRssi_Percentage();

	/** @brief 转换dbm值为信号强度百分比
	  * @parm[in] dBm 信号强度
	  * @return 信号强度百分比
	  */
	static int wifi_mgr_GetRssi_Percentage(int dBm);


/************************************************************************/
/* 杂项处理类															*/
/************************************************************************/
	/** @brief 获取系统时间 */
	static void getsystemtime(int* hh, int* mm, int* ss);
    /** @brief 获取当前的时间 */
	static float GetCurrentFloatTime();
	/** @brief 获取指定分区的总大小，和剩余空间大小
	  * @param[out] path 分区路径(/usr/或者 /usr/local/
	  * @param[out] total 分区总大小
	  * @param[out] freespace 分区剩余大小
	  */
	static bool GetDiskSize( wxString path, long &total, long &freeSpace );

////////////////////////////PT80 二期添加的接口///////////////////////////
/************************************************************************/
/* 识读头                                                               */
/************************************************************************/
	/** @brief 识读头触发接口
	  * @param[in] op 开始/结束识读
	  * @note 请在调用barcode_init后使用该接口
	  */
	static void TriggerScaner(bool op);

/************************************************************************/
/* 电源管理                                                             */
/************************************************************************/
	typedef int (*SleepCallbackFunc)(void);
	/** @brief 设置休眠回调函数
	  * @param[in] callback 新的休眠回调函数
	  * @note 返回非0值即可阻止机器进入休眠
	  * @return 设置结果
	  */
	static bool pm_set_sleep_callback(SleepCallbackFunc callback);
	/** @brief 获得休眠回调函数
	  * @return 当前的休眠回调函数
	  */
	static SleepCallbackFunc pm_get_sleep_callback( void );

/************************************************************************/
/* 读码                                                                 */
/************************************************************************/
	/**
	* @brief 读条码
	* @param[out] buf 条码存放区
	* @param[in] len 条码存放区大小
	* @param[out] pCodeTypeID 条码类型ID
	* @param[in] timeout 超时(ms)
	* @li <0 一直等待
	* @li =0 检查并立即返回
	* @li >0 超时等待
	* @return 返回值
	* @li <0 错误
	* @li =0 超时
	* @li >0 读到的条码个数
	*/
	static int barcode_read( char *buf, int len, int* pCodeTypeID, int timeout );

	/** @brief 获得条码类型名称
	  * @param[in] id 条码ID
	  * @return id对应的名称
	  */
	static const char* barcode_get_type_name( int id );

	/** @brief 开启条码类型前缀
	  * @return 操作结果
	  * @li =0 成功
	  * @li <0 失败
	  */
	static int barcode_enable_codeID(void);

	/** @brief 关闭条码类型前缀
	  * @return 操作结果
	  * @li =0 成功
	  * @li <0 失败
	  */
	static int barcode_disable_codeID(void);


	/************************************************************************/
	/* 电源管理                                                             */
	/************************************************************************/
	static bool pm_set_powerdown_timeout(int seconds);

	/************************************************************************/
	/* 条码识读                                                             */
	/************************************************************************/
	static int barcode_read_raw( char *buf, int len, int timeout );

	static int barcode_factory_reset(void);
};

/** @class CPt80NConfig Uboot参数分区访问类 
  * Uboot 参数分区访问类
  */
class SDKIMPORT CPt80NConfig
{
public:
	/** @brief 打开参数分区 */
	bool Open();
	/** @brief 把内存中的数据写入参数分区 */
	bool Close();
	/** @brief 设置参数
	  * @param[in] name 参数名
	  * @param[in] value 参数值
	  */
	bool SetEnv(wxString name, wxString value);
	/** @brief 获取参数
	  * @param[in] name 参数名
	  * @return 
	  * @li 如果未设置则返回零长度的wxString
	  */
	wxString GetEnv(wxString name);

public:
	/** @brief 获取SN
	  * @note 请先调用 CPt80NConfig::Open()
	  */
	wxString GetSN();
	/** @brief 获取SN
	  * @return true 设置成功, false 设置失败
	  * @note 写入FLASH需调用  CPt80NConfig::Close()
	  */
	bool SetSN(wxString str);

	/** @brief 获取硬件SN
	  * @note 请先调用 CPt80NConfig:Open();
	  */
	wxString GetHardSN();

	/** @brief 设置硬件SN
	  * @note 写入FLASH需调用  CPt80NConfig::Close()
	  */
	bool SetHardSN(wxString str);

	/** @brief 获取出厂日期
	  * @note 请先调用 CPt80NConfig:Open();
	  */
	wxString GetFactoryDate();

	/** @brief 设置出厂日期
	  * @note 写入FLASH需调用  CPt80NConfig::Close()
	  */
	bool SetFactoryDate(wxString str);

	/** @brief 获取产品名称
	  * @note 请先调用 CPt80NConfig:Open();
	  */
	wxString GetProductName();
	
	/** @brief 设置产品名称
	  * @note 请先调用 CPt80NConfig:Open();
	  */
	bool SetProductName(wxString str);

public:
#define STR_UBOOT_VER "UBOOT_VER"	/*< @brief UBOOT版本 */
#define STR_KERNEL_VER "KERNEL_VER" /*< @brief 内核版本 */
#define STR_ROOTFS_VER "ROOTFS_VER" /*< @brief ROOTFS版本 */
#define STR_APPFS_VER "APPFS_VER"   /*< @brief APPFS版本 */
#define STR_FIRMWARE_VER "FIRMWARE_VER" /*< @brief 固件版本 */
};


/** @class CPt80Barcode_ReadThreadBase 读条码基类 
  * 请在派生类中实现以下接口OnData、OnError、OnReturn、OnStart
  * @note 联合线程，在使用完需要手动delete线程
  */
class SDKIMPORT CPt80Barcode_ReadThreadBase:public wxThread
{
public:
	CPt80Barcode_ReadThreadBase();
	virtual void *Entry();
	virtual void OnExit();

	/** @brief 开启线程，并运行 */
	virtual int Start();
	/** @brief 停止扫描 
	 *  @note 内部调用 Delete(NULL); Wait(); 会停顿一段时间
	 */
	virtual int Stop();

	virtual int SE955_Read();
	virtual int EM1300_Read();
	virtual int CM42_Read();
	virtual int EMU_Read();

public:
	/** @brief 数据返回回调(数据在基类m_ReadBuffer中
	  * @param[in] len 读到的条码长度
	  * @return 返回值
	  * @retval 0 继续读取条码
	  * @retval 其它 立即退出读条码线程
	  */
	virtual int OnData(int len){return 0;}
	/** @brief 错误回调函数
	  */
	virtual int OnError(int errno){return 0;}
	/** @brief 线程退出回调
	  * @param[in] retval <0 线程并未进入主循环函数 =0 线程正常退出
	  */
	virtual int OnReturn(int retval){return 0;}
	/** @brief 开始读条码回调 */
	virtual int OnStart(){return 0;}

public:
	int m_type;
	bool m_bEnter;
	wxCharBuffer m_ReadBuffer;
	int m_barcodeTypeID;

public:

#define CMD_BARCODE_START (MSG_USER +1)
#define CMD_BARCODE_EXIT (MSG_USER +2)
#define CMD_BARCODE_EMU (MSG_USER +3)
#define CMD_BARCODE_NEW (MSG_USER +4) //条码

	enum {
		ERR_BARCODE_DEVICE = -1,
		ERR_BARCODE_TIMEOUT = -2,
		ERR_BARCODE_SELECT = -3,
		ERR_BARCODE_OPENFAIL = -4,
		ERR_BARCODE_CM42_OPEN = -5,
	};
};


/** @} end of group_deviceOpt */

#endif