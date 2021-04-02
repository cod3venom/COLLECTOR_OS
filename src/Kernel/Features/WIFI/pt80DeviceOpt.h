/*!
 *			Copyright (C) 2010-2015	Newland Computer (FuJian) Co.,Ltd.
 * @License	�����´�½���Թɷ����޹�˾
 *
 * @file	pt80DeviceOpt.h
 * @brief	PT80 ���������
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
  * @defgroup group_deviceOpt PT80�豸������
  * @{
  */

/** @class CPt80DeviceOpt PT80�ײ��豸������
  * PT80 �ײ��豸������(USB����Դ������GPIO����ء���������LCD������)
  */
class SDKIMPORT CPt80DeviceOpt
{
public:
/************************************************************************/
/* USB                                                                  */
/************************************************************************/
	/** @enum USBģʽ*/
	enum USB_MODE{
		USB_MODE_NONE,		/**< �գ��������κ�����*/
		USB_MODE_SERIAL_DOWNLOAD, /**< ����ģʽ��ռ��USB���ڹ��� */
		USB_MODE_NET,		/**< NET */
		USB_MODE_SERIAL,		/**< ���� */
		USB_MODE_KEYBOARD,	/**< HID����*/
		USB_MODE_STORAGE,	/**< U�� */
		USB_MODE_STORAGE_RO, /**< U��ֻ�� */
	};
	
	/**
	 * @enum USBStatus
	 * @brief USB����״̬(��NONEģʽ)
	 */
	enum UsbStatus{
		USB_CONNECT = 1,    /**< @brief USB���� */
		USB_DISCONNECT = 0, /**< @brief USBδ���� */
	};

	/** @brief ����USBģʽ
	  * @return 0-�ɹ��� other-����
	  */
	static int usb_set_mode(int mode);
	
	/** @brief ��ȡ��ǰUSBģʽ
	  * @return <0 - ʧ��, other ::USB_MODE
	  */
	static int usb_get_mode();

	/** @brief ��ȡUSB������IP��ַ
	  * @retrun
	  * @retval NULL δ����
	  * @retval ���� USB����IP��ַ
	  */
	static char *usb_net_get_ip();

	/** @brief ����USB������IP��ַ
	  * @return
	  * @retval 0 �ɹ�
	  * @retval ���� ʧ��
	  */
	static int usb_net_set_ip(const char *network);

	/** @brief ��USB�����豸
	  * @return >0 USB�����豸���ļ��������� ����ʧ��
	  */
	static int usb_hid_init();
	
	/** @brief Ͷ�䰴��
	  * @param[in] fd usb_hid_init���ص��ļ�������
	  * @param[in] keycode HID��׼�ļ���ֵ�����HID Usage Tables�ֲ�
	  * @return 0 �ɹ�, ���� ʧ��
	  */
	static int usb_hid_send(int fd, int keycode, int mode);
	
	/** @brief Ͷ�䰴���ַ�
	  * @param[in] fd usb_hid_init���ص��ļ�������
	  * @param[in] buf �ַ�
	  * @param[in] len �ַ�����
	  * @return 0 �ɹ��� ���� ʧ��
	  * @note ֻ֧����ĸ������
	  */
	static int usb_hid_send_char(int fd, char *buf, int len);


	/** @brief ��USB�����豸
	  * @return ����ֵ
	  * @retval fd USB�����豸fd 
	  * @retval <0 ���豸����
	  */
	static int usb_serial_init(void);

	/** @brief  ����USB�洢�豸������Ŀ¼ 
	  * @return ����ֵ
	  * @retval 0 �ɹ�
	  * @retval 1 �豸æ
	  * @retval ���� δ֪����
	  */
	static int usb_storage_mount(wxString path);

	/** @brief  ���USB�洢�豸���� 
	  * @return ����ֵ
	  * @retval 0 �ɹ�
	  * @retval 1 �豸æ
	  */
	static int usb_storage_umount(wxString path);

	/** 
	 * @brief ��ȡ��ǰUSB������״̬
	 * @return �������
	 * @retval	::USB_CONNECT
	 * @retval	::USB_DISCONNECT
	 */
	static int usb_get_status();

	/**
	 * @brief �������ô�С����ʽ��U��
	 * @param[in] size  �½�����U�̵Ĵ�С
	 *
	 * @return	�������
	 * @retval	::USB_SUCCESS
	 * @retval	::USB_ERR_BUSY
	 */
	static int usb_storage_format(int size);

	/** 
	 * @brief ��ȡUSB�����豸��С
	 * @return USB�����豸��С
	 */
	static int usb_storage_getsize();

/************************************************************************/
/* ��Դ                                                                 */
/************************************************************************/
	/** 
	 * @brief ���ü�����״̬
	 * @param[in] bLick 
	 * - TRUE ����
	 * - FALSE δ����
	 */
	static void kbd_set_lock(bool bLock);

	/** 
	 * @brief ��ȡ������״̬
	 * @return �������
	 * @retval TRUE ����
	 * @retval FALSE δ����
	 */
	static bool kbd_get_lock();

/************************************************************************/
/* ��Դ                                                                 */
/************************************************************************/
	/** @brief �������� 
	  * @return ����ֵ
	  * @retval true �ɹ�
	  * @retval false ����
	  */
	static bool pm_suppress_sleep_on();

	/** @brief �������߽��
	  * @return ����ֵ
	  * @retval true �ɹ�
	  * @retval false ����
	  */
	static bool pm_suppress_sleep_off();

	/** @brief ��ȡ�������߼���
	  *
	  * @return �������
	  * @retval <0  ʧ��
	  * @retval �������Ƽ���ֵ
	  */
	static size_t pm_get_suppress_sleep();

	/** @brief ���ƹػ�
	  * @return ����ֵ
	  * @retval true �ɹ�
	  * @retval false ����
	  */
	static bool pm_suppress_powerdown_on();

	/** @brief ���ƹػ���� 
	  * @retval true �ɹ�
	  * @retval false ����
	  */
	static bool pm_suppress_powerdown_off();

	/** @brief ��ȡ���ƹػ�����
	  *
	  * @return �������
	  * @retval <0  ʧ��
	  * @retval �������Ƽ���ֵ
	  */
	static size_t pm_get_suppress_powerdown();

	/** @brief ������������ʱ�� 
	  * @return ����ֵ
	  * @retval true �ɹ�
	  * @retval false ����
	  */
	static bool pm_set_sleep_timeout (int seconds);

	/** @brief �������� 
	  * @return ����ֵ
	  * @retval true �ɹ�
	  * @retval false ����
	  */
	static bool pm_reboot (void);

	/** @brief ����ػ�
	  * @return ����ֵ
	  * @retval true �ɹ�
	  * @retval false ����
	  */
	static bool pm_powerdown (void);

	/** @brief ��������
	  * @return ����ֵ
	  * @retval true �ɹ�
	  * @retval false ����
	  */
	static bool pm_sleep (void);

	/** @brief ��ȡ��Դ������ļ�������
	  * @return 
	  * @retval >0 ��Դ����������ļ�������
	  * @retval <0 ����
	  * @note ʹ�øýӿ���������Դ�����״̬�ı䣬���緢�����ߣ�����ػ���
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
	  printf("Recv: %s\n", buf); // ����������sleep����powerdown
	  * @endcode
	  */
	static int pm_get_fd(void);

/************************************************************************/
/* ����                                                                 */
/************************************************************************/
	/** @brief ����FTP����
	  * @return ����ֵ
	  * @retval true �ɹ�
	  * @retval false ʧ��
	  */
	static bool svc_ftp_start();

	/** @brief ����FTP����
	  * @return ����ֵ
	  * @retval true �ɹ�
	  * @retval false ʧ��
	  */
	static bool svc_ftp_stop();

	/** @brief ����TELNET����
	  * @return ����ֵ
	  * @retval true �ɹ�
	  * @retval false ʧ��
	  */
	static bool svc_telnet_start();

	/** @brief ����TELNET����
	  * @return ����ֵ
	  * @retval true �ɹ�
	  * @retval false ʧ��
	  */
	static bool svc_telnet_stop();

	/** @brief �������߷��� 
	  * @return ����ֵ
	  * @retval 0 �ɹ�
	  * @retval -2 �޷�ʶ��WIFI
	  * @retval ���� δ֪����
	  * @retval false ʧ��
	  */
	static int svc_wireless_start();

	/** @brief �������߷���
	  * @return ����ֵ
	  * @retval true �ɹ�
	  * @retval false ʧ��
	  */
	static bool svc_wireless_stop();

	/** @brief ����BT���� 
	  * @return ����ֵ
	  * @retval true �ɹ�
	  * @retval false ʧ��
	  */
	static bool svc_bt_start();

	/** @brief ����BT����
	  * @return ����ֵ
	  * @retval true �ɹ�
	  * @retval false ʧ��
	  */
	static bool svc_bt_stop();

/************************************************************************/
/* GPIO                                                                 */
/************************************************************************/
	/** @brief ���ӿ���
	  * @param bValue 
	  * @li true ������
	  * @li false �ر���
	  */
	static void gpio_set_vibratorPower(bool bValue);

	/** @brief EM1300/SE955 ��Դ����
	  * @param bValue 
	  * @li true ������Դ
	  * @li false �رյ�Դ
	  */
	static void gpio_set_ScannerPower(bool bValue);

	/** @brief EM1300/SE955 ɨ�败������
	  * @param bValue 
	  * @li true ����
	  * @li false �رմ���
	  */
	static void gpio_set_ScannerTrig(bool bValue);
	
	/** @brief SE955���ѹܽſ���
	  * @param bValue 
	  * @li true ��Դ����
	  * @li false ��Դ����
	  */
	static void gpio_set_SE955Wakeup(bool bValue);

/************************************************************************
 LED
************************************************************************/
	/** @brief ��ɫLED�Ʋ���
	  * @param bValue 
	  * @li true ��
	  * @li false ��
	  */
	static void led_set_green(bool bValue);

	/** @brief ��ɫLED�Ʋ���
	  * @param bValue 
	  * @li true ��
	  * @li false ��
	  */
	static void led_set_red(bool bValue);

/************************************************************************/
/* ����                                                                 */
/************************************************************************/
	/** @brief ������һ��ʱ��
	  * @param[in] delay ������ʱ��(ms)
	  */
	static void vibrator_shake(int delay);

/************************************************************************/
/* ʶ��ͷ                                                               */
/************************************************************************/
	/** ʶ��ͷ�豸���� */
	enum BarcodeDevice{
		BARCODE_DEVICE_EM1300, /**< @brief EM1300 */
		BARCODE_DEVICE_SE955,  /**< @brief SE955 */
		BARCODE_DEVICE_CM42, /**< @brief CM42 */
		BARCODE_DEVICE_UNKNOW, /**< @brief UNKNOW */
	};

	/**
	  * @brief ʶ��ͷ��ʼ��
	  * @return ����ֵ
	  * @retval >=0 �ɹ�
	  * @retval ����ʧ��
      */
	static int barcode_init(void);

	/** 
	  * @brief ʶ��ͷ�ر�
	  * @return ����ֵ
	  * @retval 0 �ɹ�
	  * @retval ����ʧ��
	  */
	static int barcode_close();

	/**
	  * @brief ��ȡʶ��ͷ������
	  * @return ʶ��ͷ����
	  * @retval ::BARCODE_DEVICE_EM1300 
	  * @retval ::BARCODE_DEVICE_SE955
	  * @retval ::BARCODE_DEVICE_CAMERA
	  * @retval <0 ��ȡʧ��
	  */
	static int barcode_get_type(void);

	/**
	  * @brief ɨ��Ӳ��������ɨ��ͷ����
	  * @return ɨ��ͷ���� ::BarcodeDevice
	  * @retval <0 δ��⵽�κ�ɨ��ͷ
	  * @retval �������::BarcodeDevice
	  * @note �������Զ��жϵ��߼�
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
	* @brief ����ʶ��ͷ�豸����
	* @param type ɨ��ͷ���� ::BarcodeDevice
	* @note <b>ʶ��ͷ�豸���ͻ��Զ���⣬������֪��������ʲô��������ֹͣ���øýӿ�</b>
	*/
	static void barcode_set_type(int type);

   /**
	* @brief ������
	* @param[out] buf ��������
	* @param[in] len ����������С
	* @param[in] timeout ��ʱ(ms)
	* @li <0 һֱ�ȴ�
	* @li =0 ��鲢��������
	* @li >0 ��ʱ�ȴ�
	* @return ����ֵ
	* @li <0 ����
	* @li =0 ��ʱ
	* @li >0 �������������
	*/
	static int barcode_read(char *buf, int len, int timeout);

	/**
	* @brief ��������ɨ����ʾ��ʽ
	* @param[in] bRing  
	* @li true ����
	* @li false ����
	* @param[in] bVibrator
	* @li true ��
	* @li false ����
	*/
	static void barcode_set_prompt(bool bRing, bool bVibrator);

/************************************************************************/
/* ���                                                                 */
/************************************************************************/
	/**
	  * @brief ��ȡ������ص�ѹ 
	  * @param main ָ������ص�floatָ��
	  * @param standby ָ���õ�ص�floatָ��
	  * @return ����ֵ
	  * @li true �ɹ�
	  * @li false ʧ��
	  */
	static bool getBattery(float *mainVoltage, float *standbyVoltage);
	
	/**
	* @brief ��ȡ����ص����ٷֱ�
	* @return �������
	* @li <0 ����
	* @li ���� ����ص���
	*/
	static int getMainBattery();

	/**
	* @brief ��ȡ���õ�ص����ٷֱ�
	* @return �������
	* @li <0 ����
	* @li ���� ���õ�ص���
	*/
	static int getStandbyBattery();


	/*
	* @enum MainBatteryStatus ����س��״̬ 
	*/
	enum MainBatteryStatus{
		MAIN_BATTER_CHARGING, /**< @brief ���ڳ�� */
		MAIN_BATTER_DISCHARGING, /**< @brief δ��� */
	};

	/**
	* @brief ��ȡ����س��״̬
	* @return �������
	* @li <0 ����
	* @li ::MAIN_BATTER_CHARGING
	* @li ::MAIN_BATTER_DISCHARGING
	*/
	static int getMainBatteryStatus();

	/*
	* @enum StandbyBatteryStatus ���õ�س��״̬ 
	*/
	enum StandbyBatteryStatus{
		STANDBY_BATTER_CHARGING, /**< @brief ���ڳ�� */
		STANDBY_BATTER_COMPLETE_CHARGE, /**< @brief ������ */
		STANDBY_BATTER_DISCHARGING, /**< @brief δ��� */
	};

	/*
	* @brief ��ȡ���õ�س��״̬
	* @return �������
	* @li <0 ����
	* @li ::STANDBY_BATTER_CHARGING
	* @li ::STANDBY_BATTER_COMPLETE_CHARGE
	* @li ::STANDBY_BATTER_DISCHARGING
	*/
	static int getStandbyBatteryStatus();

	/*
	* @brief ��ȡ��ظ�״̬
	* @return ���״̬
	* @li 1 �ر�
	* @li 0 �� 
	* @li ���� ����
	*/
	static int getBatteryCoverStatus();


/************************************************************************/
/* ������                                                               */
/************************************************************************/

	/**
	* @brief ��ʼ����
	* @return 
	* @retval true �ɹ�
	* @retval false ʧ��
	*/
	static bool buzz_on(void);

	/**
	* @brief ֹͣ����
	* @return 
	* @retval true �ɹ�
	* @retval false ʧ��
	*/
	static bool buzz_off(void);

	/** @enum ����������ʱ��
	 */
	enum BUZZ_LEVEL {
		BUZZ_LEVEL_LOW, /**< �� */
		BUZZ_LEVEL_MEDI, /**< �� */
		BUZZ_LEVEL_HIGH, /**< �� */
	};
	/**
	* @brief ����
	* @param[in] timing ����ʱ��
	* @return ����ֵ
	* @retval true �ɹ�
	* @retval false ʧ��
	* @note ����ֻ֧�ֶ��г�����Ԥ��ʱ�������� BUZZ_LEVEL
	*/
	static bool buzz_beep(int timing);

	/** @brief ����ɨ������Ƶ�� */
	static bool buzz_set_freq(int freq);
	
	/** @brief ����ɨ������ռ�ձ� */
	static bool buzz_set_duty(int duty);

	/** @brief ���ü�������Ƶ�� */
	static bool buzz_kbd_set_freq(int freq);
	
	/** @brief ���ü�������ռ�ձ� */
	static bool buzz_kbd_set_duty(int duty);

	/** @brief ������ ���� */
	static bool buzz_kbd_beep(int timing=0);


/************************************************************************/
/* LCD                                                                  */
/************************************************************************/
	/** @enum �������� */
	enum BL_BRIGHT{
		BL_BRIGHT_LEVEL_1,	/**< @brief һ������ */
		BL_BRIGHT_LEVEL_2,  /**< @brief �������� */
		BL_BRIGHT_LEVEL_3,  /**< @brief �������� */
		BL_BRIGHT_LEVEL_4,  /**< @brief �ļ����� */
		BL_BRIGHT_LEVEL_5,  /**< @brief �弶���� */
		BL_BRIGHT_LEVEL_6,  /**< @brief �������� */
		BL_BRIGHT_AUTO,     /**< @brief �Զ�����(��п���) */
	};

	/**
	* @brief ����LCD�����Զ��ر�ʱ��
	* @param[in] timeout �����Զ��ر�ʱ��(��λ:ms)
	*            - 0 ���ⳣ��
	*            - 3600 ���ⳣ��
	* @return ����ֵ
	* @retval true �ɹ�
	* @retval false ʧ��
	*/
	static bool lcd_bl_set_timeout(int timeout);

	/** 
	* @brief ����LCD��������
	* @param[in] bright �������ȵȼ�
	* @li ::BL_BRIGHT_LEVEL_1
	* @li ::BL_BRIGHT_LEVEL_2
	* @li ::BL_BRIGHT_LEVEL_3
	* @li ::BL_BRIGHT_LEVEL_4
	* @li ::BL_BRIGHT_LEVEL_5
	* @li ::BL_BRIGHT_LEVEL_6
	* @li ::BL_BRIGHT_AUTO
	* @return ����ֵ
	* @retval true �ɹ�
	* @retval false ʧ��
	*/
	static bool lcd_bl_set_bright(int bright);

	/** @brief API��������
	* @param[in] autoClose �Ƿ��Զ��رձ���
	* @li 0 ���Զ��ر�
	* @li 1 �Զ��ر�
	* @return ����ֵ
	* @retval true �ɹ�
	* @retval false ʧ��
	*/
	static bool lcd_bl_turn_on(int autoClose);

	/** @brief API�رձ���
	* @return ����ֵ
	* @retval true �ɹ�
	* @retval false ʧ��
	*/
	static bool lcd_bl_turn_off();

	/** @brief ����LCD�Աȶ�
	* @param[in] contrast �Աȶ�(1-255),�Ƽ�ֵ65
	* @return ����ֵ
	* @retval true �ɹ�
	* @retval false ʧ��
	*/
	static bool lcd_set_contrast(int contrast);


/************************************************************************/
/* ����                                                                 */
/************************************************************************/

	/** @brief ���ü��̱����Զ��ر�ʱ��
	* @param[in] timeout �����Զ��ر�ʱ��(��λ:ms)
	*            - 0 ���ⳣ��
	*            - 3600 ���ⳣ��
	* @return ����ֵ
	* @retval true �ɹ�
	* @retval false ʧ��
	*/
	static bool kbd_bl_set_timeout(int timeout);

	/** @brief API��������
	* @param[in] autoClose �Ƿ��Զ��رձ���
	* @li 0 ���Զ��ر�
	* @li 1 �Զ��ر�
	* @return ����ֵ
	* @retval true �ɹ�
	* @retval false ʧ��
	*/
	static bool kbd_bl_turn_on(int autoClose);

	/** @brief API�رձ���
	* @return ����ֵ
	* @retval true �ɹ�
	* @retval false ʧ��
	*/
	static bool kbd_bl_turn_off();

	/** @brief ���ð�������
	* @param[in] bSound 
	* @li true ����������
	* @li false �رհ�����
	* @return ����ֵ
	* @retval true �ɹ�
	* @retval false ʧ��
	*/
	static bool kbd_set_beep(bool bSound);

	/** @brief ��ȡ���̰�����
	* @return ���̰�����
	* @retval 0 �������ر�
	* @retval 1 ����������
	* @retval <0 ��ȡʧ��
	*/
	static int kbd_get_beep (void);


/************************************************************************/
/* WIFI�ײ�ӿ�                                                         */
/************************************************************************/
	/** @brief ����wpa_supplicant
	* @return ����ֵ
	* @retval 0 �ɹ�
	* @retval <0 ʧ��
	*/
	static int wifi_connect_to_supplicant();

	/** @brief ���ص�ǰ��wpa_ctrl */
	static struct wpa_ctrl *wifi_get_current_ctrl();

	/** @brief �Ͽ���wpa_supplicant������ */
	static void wifi_close_supplicant_connection();

	/** @brief ��ȡ��ǰ���ӵ��ٶ� 
	* @return ��ǰ�������ٶ� ��λ M
	* @retval 1-100 ��ǰ�������ٶ�
	* @retval <0 ����
	*/
	static int  wifi_getLinkSpeed();

	/** @brief ��ȡMAC��ַ 
	* @return MAC��ַ
	* @retval NULL ����
	* @retval ���� MAC��ַ
	*/
	static char* wifi_getMacAddress();

	/** @brief �жϵ�ǰ�Ƿ����¼����ݿ��Զ�
	  * @return ���ؽ��
	  * @retval 1 - ���¼����ݿ��Զ�������wifi_waitForEvent��ȡ����
	  * @retval 0 - ���¼�����
	  */
	static int wpa_ctrl_pending(struct wpa_ctrl *ctrl);

	/** @brief ����wpa_supplicant�¼��ķ���
	* @return �¼��ַ�
	* @note ��������
	*/
	static char* wifi_waitForEvent();

	/** @brief �鿴��ǰWIFI�����б�
	* @return �����б�����֮����tab���
	* network id / ssid / bssid / flags
	* 0       softwaredev     any     [DISABLED]
	* 1       2012    any     [CURRENT]
	*/
	static char* wifi_listNetworks();

	/** @brief ��������
	* @return ������������ID
	*/
	static int wifi_addNetwork();

	/** @brief �����������
	* @param[in] name ssid,bssid,psk,wep_key0�Ȳ���
	* @param[in] value ����ֵ
	* @return 0 - �ɹ��� 1 - ʧ��
	*/
	static int wifi_setNetworkVariable( int netId, const char* name, const char* value);

	/** @brief ��ȡ�������  */
	static char* wifi_getNetworkVariable(  int netId, const char* name);

	/** @brief �Ƴ�����
	* @param[in] netID ����id
	* @return 0 - �ɹ�; ���� - ʧ��
	*/
	static int wifi_removeNetwork(int netId);

	/** @brief ��������
	* @param[in] netID ����id
	* @param[in] disableOthers 1-���ø����粢��ֹ�����������磬0-���ø�����
	* @note enable��������¼����ݷ��أ����Լ������ж��Ƿ�ɹ����ӻ�����Կ�Ƿ���ȷ(incorrect�ؼ���Ϊ����ȷ����Կ)
	*/
	static int wifi_enableNetwork( int netId, int disableOthers);

	/** @brief ����ĳ������ */
	static int wifi_disableNetwork(int netId);

	/** @brief ȡWIFI״̬ */
	static char *wifi_status();

	/** @brief �鿴AP��ϸ��Ϣ 
	* @param[in] ssid AP BSSID
	*/
	static char *wifi_queryApInfo(const char *bssid);

	/** @brief ������wpa_supplicant��ͨ�� */
	static int wifi_ping();

	/** @brief ��ȡɨ���� */
	static char * wifi_scanResults();

	/** @brief �Ͽ���ǰ����
	* @return 0 - �ɹ�; ���� - ʧ��
	*/
	static int wifi_disconnect();

	/** @brief �������ӵ�ǰ���� */
	static int wifi_reconnect();

	/** @brief ������֤ 
	 * @note ��ͨ��wifi_waitForEvent����
	 */
	static int wifi_reassociate();

	/** @brief ����ɨ��
	* @param[in] forceActive 1 - ACTIVE; 0 - PASSIVE
	* @note ��ͨ��wifi_waitForEvent������"CTRL-EVENT-SCAN-RESULTS "��־���¼��Ľ���
	*/
	static int wifi_scan(int forceActive);

	/** @brief �������� */
	static int wifi_saveConfig();

	/** @brief ���¼����������� */
	static int wifi_reloadConfig();

/************************************************************************/
/* WIFI �ӿ�(�Եײ�ӿڽ��з�װ)�Ƽ�ʹ��                                */
/************************************************************************/
	enum WifiFlags {
		WIFI_FLAGS_NONE = 0,    
		WIFI_FLAGS_WEP  = 1,    
		WIFI_FLAGS_WPA  = 2,    
		WIFI_FLAGS_WPA2 = 4,    
		WIFI_FLAGS_WPA2_EAP= 8,    
	};

	enum WiFiStatus{
		WIFI_STATUS_CONNECTED_ = 1, /**< ������ */
		WIFI_STATUS_DISCONNECT_, /**< δ���� */
		WIFI_STATUS_CONNECTING_, /**< �������� */
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

	/** @brief ����WIFI������Ϣ����Կ�Ļ�����Ԫ
	* @note ���ೣ���ڻ�ȡWIFIɨ�����ʹ����µ�WIFI����
	*/
	class CPt80WifiNetworkListItem{
	public:
		WifiNetwork net; /**< WIFI����������Ϣ */
		wxString strUser; /**< WPA-ENT ��Կ��֤��ʽ */
		wxString strKey; /**< ��Կ��������ʱʹ�� */
		wxString strEAP; /**< EAP���� */
		wxString strPhase2Authentication ;/**< �׶�2�����֤��ʽ */
	}; 

	/** @brief ���� Pt80WifiNetworkList 
	* @note ���ڴ洢WIFIɨ����
	*/
	WX_DEFINE_ARRAY(CPt80WifiNetworkListItem *, CPt80WifiNetworkList); 

	/** @brief ��ȡWIFIɨ����(Ĭ��5S��ʱ)
	  * @param[out] list WIFIɨ��������
	  * @return ���ؽ�� 0-�ɹ�,����ʧ��
	  * @note ��������,ʱ��(1S-3S),�����Ҫ����WX_CLEAR_ARRAY(list)���ͷ�ɨ�����ݿռ�
	  */
	static int wifi_mgr_Scan(CPt80WifiNetworkList &list);

	/** @brief ��ȡ��ǰWIFI��״̬ 
	  * @return �������
	  * @retval WIFI_STATUS_CONNECTED_ ������
	  * @retval WIFI_STATUS_DISCONNECT_ δ����
	  * @retval WIFI_STATUS_CONNECTING_ ��������
	  */
	static int wifi_mgr_GetStatus();

	/** @brief ��������,��������Ϣ
	  * @param[out] netID �����ӵ�����ID���������û����Ƴ���������
	  * @param[out] net ����������Ϣ
	  * @param[in] IshiddenAP ��ӵ������Ƿ�������AP(���㲥SSID)
	  * @return ���ؽ�� 0-�ɹ�,����ʧ��
	  */
	static int wifi_mgr_AddNetwork(int &netID, CPt80WifiNetworkListItem &item, bool IshiddenAP);


	/** @brief ��������,��������Ϣ
	  * @param[out] netID �����ӵ�����ID���������û����Ƴ���������
	  * @param[out] net ����������Ϣ
	  * @return ���ؽ�� 0-�ɹ�,����ʧ��
	  */
	static int wifi_mgr_AddNetwork(int &netID, CPt80WifiNetworkListItem &item);

	
	/** @brief �Ƴ����� */
	static int wifi_mgr_RemoveNetwork(int netID);

	/** @brief ����ĳ���� 
	  * @param[in] netID 
	  * @param[in] bDisableOthers �Ƿ������������
	  * @return ����ֵ
	  * @retval 0 �ɹ�(�Ѿ�����)
	  * @retval 1 ��֤����(��Կ����)
	  * @retval 2 ��ʱ (Ĭ��15S��֤ʱ��)
	  * @retval <0 δ֪����
	  * @note ��֤���󣬻��߳�ʱ���Զ��Ƴ�������ID
	  */
	static int wifi_mgr_EnableNetwork(int netID, bool bDisableOthers);

	/** @brief ��������
	  * @note �ú������оٵ�ǰ�����������б����Ƴ��յ������б��ٽ��б�������
	  */
	static int wifi_mgr_SaveConfig();

	/** @brief ��ѯ��������
	  * @param list ������������
	  * @return ���ؽ��
	  * @retval 0 �ɹ�
	  * @retval <0 ʧ��
	  */
	static int wifi_mgr_LocalNetwork(CPt80WifiNetworkList &list);

	/** @brief ��ѯָ��BSSID����ϸ��Ϣ
	  * @param[out] item PT80 WIFI������Ϣ
	  * @return ����ֵ
	  * @retval 0 �ѻ�ȡ��ϸ��Ϣ
	  * @retval 1 ���κη��ؽ��
	  * @retval <0 ����
	  * @note ��Ҫ������item�е�bssid����
	  */
	static int wifi_mgr_QueryInfo(CPt80WifiNetworkListItem &item);

	/** @brief ��ѯ��ǰ�����������ϸ��Ϣ
	  * @param[out] item PT80 WIFI������Ϣ
	  * @return ����ֵ
	  * @retval 0 �ѻ�ȡ��ϸ��Ϣ
	  * @retval 1 ���κη��ؽ��
	  * @retval <0 ����
	  */
	static int wifi_mgr_Current(CPt80WifiNetworkListItem &item);

	/** @brief �Ͽ���ǰ�������� 
	  * @return ����ֵ
	  * @retval 0 �ɹ�
	  * @retval ��������
	  */
	static int wifi_mgr_Disconnect();

	/** @brief ��ȡ��ǰ�������� IP��ַ
	  * @return ����ֵ
	  * @retval NULL δ����IP
	  * @retval ���� �ѷ����IP
	  */
	static char *wifi_mgr_get_ip();

	/** @brief ��ȡ��ǰ��������mac��ַ
	  * @return �������
	  * @retval NULL �޷���ȡ����������ӵ�eth0δ����
	  * @retval ���� mac��ַ
	  */
	static char *wifi_mgr_get_mac();

	/** @brief ����udhcpc���� */
	static int wifi_mgr_start_udhcpc();

	/** @brief �ر�udhcpc���� */
	static int wifi_mgr_stop_udhcpc();

	/** @brief ������������IP��ַ�����롢���ء�DNS
	  * @return �������
	  * @retval 0 �ɹ�
	  * @retval ���� ʧ��
	  */
	static int wifi_mgr_set_ip(wxString ip, wxString netmask, wxString gateway, wxString dns1, wxString dns2);

	/** @brief ��ȡ��ǰ�ź�ֵ 
	  * @return �ź�ǿ��(��λdBm)
	  */
	static int wifi_mgr_GetRssi();

	/** @brief ת��dbmֵΪ�ź�ǿ�Ȱٷֱ�
	  * @return �ź�ǿ�Ȱٷֱ�
	  */
	static int wifi_mgr_GetRssi_Percentage();

	/** @brief ת��dbmֵΪ�ź�ǿ�Ȱٷֱ�
	  * @parm[in] dBm �ź�ǿ��
	  * @return �ź�ǿ�Ȱٷֱ�
	  */
	static int wifi_mgr_GetRssi_Percentage(int dBm);


/************************************************************************/
/* �������															*/
/************************************************************************/
	/** @brief ��ȡϵͳʱ�� */
	static void getsystemtime(int* hh, int* mm, int* ss);
    /** @brief ��ȡ��ǰ��ʱ�� */
	static float GetCurrentFloatTime();
	/** @brief ��ȡָ���������ܴ�С����ʣ��ռ��С
	  * @param[out] path ����·��(/usr/���� /usr/local/
	  * @param[out] total �����ܴ�С
	  * @param[out] freespace ����ʣ���С
	  */
	static bool GetDiskSize( wxString path, long &total, long &freeSpace );

////////////////////////////PT80 ������ӵĽӿ�///////////////////////////
/************************************************************************/
/* ʶ��ͷ                                                               */
/************************************************************************/
	/** @brief ʶ��ͷ�����ӿ�
	  * @param[in] op ��ʼ/����ʶ��
	  * @note ���ڵ���barcode_init��ʹ�øýӿ�
	  */
	static void TriggerScaner(bool op);

/************************************************************************/
/* ��Դ����                                                             */
/************************************************************************/
	typedef int (*SleepCallbackFunc)(void);
	/** @brief �������߻ص�����
	  * @param[in] callback �µ����߻ص�����
	  * @note ���ط�0ֵ������ֹ������������
	  * @return ���ý��
	  */
	static bool pm_set_sleep_callback(SleepCallbackFunc callback);
	/** @brief ������߻ص�����
	  * @return ��ǰ�����߻ص�����
	  */
	static SleepCallbackFunc pm_get_sleep_callback( void );

/************************************************************************/
/* ����                                                                 */
/************************************************************************/
	/**
	* @brief ������
	* @param[out] buf ��������
	* @param[in] len ����������С
	* @param[out] pCodeTypeID ��������ID
	* @param[in] timeout ��ʱ(ms)
	* @li <0 һֱ�ȴ�
	* @li =0 ��鲢��������
	* @li >0 ��ʱ�ȴ�
	* @return ����ֵ
	* @li <0 ����
	* @li =0 ��ʱ
	* @li >0 �������������
	*/
	static int barcode_read( char *buf, int len, int* pCodeTypeID, int timeout );

	/** @brief ���������������
	  * @param[in] id ����ID
	  * @return id��Ӧ������
	  */
	static const char* barcode_get_type_name( int id );

	/** @brief ������������ǰ׺
	  * @return �������
	  * @li =0 �ɹ�
	  * @li <0 ʧ��
	  */
	static int barcode_enable_codeID(void);

	/** @brief �ر���������ǰ׺
	  * @return �������
	  * @li =0 �ɹ�
	  * @li <0 ʧ��
	  */
	static int barcode_disable_codeID(void);


	/************************************************************************/
	/* ��Դ����                                                             */
	/************************************************************************/
	static bool pm_set_powerdown_timeout(int seconds);

	/************************************************************************/
	/* ����ʶ��                                                             */
	/************************************************************************/
	static int barcode_read_raw( char *buf, int len, int timeout );

	static int barcode_factory_reset(void);
};

/** @class CPt80NConfig Uboot�������������� 
  * Uboot ��������������
  */
class SDKIMPORT CPt80NConfig
{
public:
	/** @brief �򿪲������� */
	bool Open();
	/** @brief ���ڴ��е�����д��������� */
	bool Close();
	/** @brief ���ò���
	  * @param[in] name ������
	  * @param[in] value ����ֵ
	  */
	bool SetEnv(wxString name, wxString value);
	/** @brief ��ȡ����
	  * @param[in] name ������
	  * @return 
	  * @li ���δ�����򷵻��㳤�ȵ�wxString
	  */
	wxString GetEnv(wxString name);

public:
	/** @brief ��ȡSN
	  * @note ���ȵ��� CPt80NConfig::Open()
	  */
	wxString GetSN();
	/** @brief ��ȡSN
	  * @return true ���óɹ�, false ����ʧ��
	  * @note д��FLASH�����  CPt80NConfig::Close()
	  */
	bool SetSN(wxString str);

	/** @brief ��ȡӲ��SN
	  * @note ���ȵ��� CPt80NConfig:Open();
	  */
	wxString GetHardSN();

	/** @brief ����Ӳ��SN
	  * @note д��FLASH�����  CPt80NConfig::Close()
	  */
	bool SetHardSN(wxString str);

	/** @brief ��ȡ��������
	  * @note ���ȵ��� CPt80NConfig:Open();
	  */
	wxString GetFactoryDate();

	/** @brief ���ó�������
	  * @note д��FLASH�����  CPt80NConfig::Close()
	  */
	bool SetFactoryDate(wxString str);

	/** @brief ��ȡ��Ʒ����
	  * @note ���ȵ��� CPt80NConfig:Open();
	  */
	wxString GetProductName();
	
	/** @brief ���ò�Ʒ����
	  * @note ���ȵ��� CPt80NConfig:Open();
	  */
	bool SetProductName(wxString str);

public:
#define STR_UBOOT_VER "UBOOT_VER"	/*< @brief UBOOT�汾 */
#define STR_KERNEL_VER "KERNEL_VER" /*< @brief �ں˰汾 */
#define STR_ROOTFS_VER "ROOTFS_VER" /*< @brief ROOTFS�汾 */
#define STR_APPFS_VER "APPFS_VER"   /*< @brief APPFS�汾 */
#define STR_FIRMWARE_VER "FIRMWARE_VER" /*< @brief �̼��汾 */
};


/** @class CPt80Barcode_ReadThreadBase ��������� 
  * ������������ʵ�����½ӿ�OnData��OnError��OnReturn��OnStart
  * @note �����̣߳���ʹ������Ҫ�ֶ�delete�߳�
  */
class SDKIMPORT CPt80Barcode_ReadThreadBase:public wxThread
{
public:
	CPt80Barcode_ReadThreadBase();
	virtual void *Entry();
	virtual void OnExit();

	/** @brief �����̣߳������� */
	virtual int Start();
	/** @brief ֹͣɨ�� 
	 *  @note �ڲ����� Delete(NULL); Wait(); ��ͣ��һ��ʱ��
	 */
	virtual int Stop();

	virtual int SE955_Read();
	virtual int EM1300_Read();
	virtual int CM42_Read();
	virtual int EMU_Read();

public:
	/** @brief ���ݷ��ػص�(�����ڻ���m_ReadBuffer��
	  * @param[in] len ���������볤��
	  * @return ����ֵ
	  * @retval 0 ������ȡ����
	  * @retval ���� �����˳��������߳�
	  */
	virtual int OnData(int len){return 0;}
	/** @brief ����ص�����
	  */
	virtual int OnError(int errno){return 0;}
	/** @brief �߳��˳��ص�
	  * @param[in] retval <0 �̲߳�δ������ѭ������ =0 �߳������˳�
	  */
	virtual int OnReturn(int retval){return 0;}
	/** @brief ��ʼ������ص� */
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
#define CMD_BARCODE_NEW (MSG_USER +4) //����

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