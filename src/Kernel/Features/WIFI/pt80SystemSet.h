/*!
 *			Copyright (C) 2010-2015	Newland Computer (FuJian) Co.,Ltd.
 * @License	�����´�½���Թɷ����޹�˾
 *
 * @file	pt80SystemSet.h
 * @brief	PT80 ϵͳ������
 * @author  NEAT TEAM <neat@newlandcomputer.com>
 * @version 1.00
 * @date    2011-11-01 initial version
 */

#ifndef _PT80_SYSTEMSET_H_
#define _PT80_SYSTEMSET_H_
#include "settings.h"
#include <wx/arrstr.h>
/** @class CPt80SystemSet PT80ϵͳ������
  * ����PT80ϵͳ������������
  */
class SDKIMPORT CPt80SystemSet{
public:
	/** @brief ��ȡȫ�ֵĲ������ */
	static CPt80SystemSet *GetHandle();
	/** @brief ���ü��̱���ģʽ */
	int SetKbdBL(int mode);
	/** @brief ��ȡ���̱�������ַ���
	 *  @note �ýӿ��ѷ���
	 */
	int GetKbdBlString(wxArrayString &arryString);
	/** @brief ��ȡ���̱���ģʽ */
	int GetKbdBL();
	
	/** @brief ����LCD����ģʽ */
	int SetLcdBL(int mode);
	/** @brief ��ȡLCD��������ַ��� 
	*  @note �ýӿ��ѷ���
	*/
	int GetLcdBlString(wxArrayString &arryString);
	/** @brief ��ȡLCD����ģʽ */
	int GetLcdBL();


	/** @brief ����LCD�Աȶ� */
	int SetLcdContrast(int value);
	/** @brief ��ȡLCD�Աȶ� */
	int GetLcdContrast();

	/** @brief ����LCD���� */
	int SetLcdBrightness(int brightness);
	/** @brief ��ȡLCD���� */
	int GetLcdBrightness();
	/** @brief ��ȡLCD��������ַ��� 
	*  @note �ýӿ��ѷ���
	*/
	int GetLcdBrightnessString(wxArrayString &arryString);

	/** @brief ���ÿ�������ģʽ */
	int SetSleepMode(int mode);
	/** @brief ��ȡ��������ģʽ����ַ��� */
	int GetSleepModeString(wxArrayString &arrayString);
	/** @brief ��ȡ��������ģʽ */
	int GetSleepMode();

	/** @brief ���ÿ��йػ�ģʽ */
	int SetHaltMode(int mode);
	/** @brief ��ȡ���йػ�ģʽ����ַ��� */
	int GetHaltModeString(wxArrayString &arrayString);
	/** @brief ��ȡ���йػ�ģʽ */
	int GetHaltMode();

	/** @brief ��ȡ��ǰWIFI����Ŀ���״̬ */
	int GetSvcWifiMode();
	/** @brief ������ر�WIFI���� */
	bool SetSvcWifiMode(bool bOpen=true);

	/** @brief ��ȡ��ǰBT����Ŀ���״̬ 
	  * @return 0-�رգ�1-����
	  */
	int GetSvcBtMode();
	/** @brief ������ر�BT���� */
	bool SetSvcBtMode(bool bOpen=true);

	/** @brief ȡ���ϴ�BT�Ƿ�ɱ���� 
	 *  @return 1 �ɼ���0-���ɼ�
	 *  @note ��ֱ�Ӳ����豸��ֻ����������ʹ��
	 */
	int GetBtDiscoverEnable();
	void SetBtDiscoveryEnable(bool bValue=true);

	/** @brief ��ȡ��ǰTelnet����Ŀ���״̬ */
	int GetSvcTelnetMode();
	/** @brief ������ر�Telnet���� */
	bool SetSvcTelnetMode(bool bOpen=true);

	/** @brief ��ȡ��ǰFTP����Ŀ���״̬ */
	int GetSvcFtpMode();
	/** @brief ������ر�FTP���� */
	bool SetSvcFtpMode(bool bOpen=true);

	/** @brief ��ȡʶ��ͷ���� */
	int GetBarcodeDeviceType();
	/** @brief ����ʶ��ͷ���� */
	int SetBarcodeDeviceType(int type);

	/** @brief ����ʶ��ͷ��ʾ��ʽ */
	int SetBarcodePrompt( bool bRing, bool bVibrator);
	/** @brief ��ȡʶ��ͷ��ʾ��ʽ */
	int GetBarcodePrompt(bool &bRing, bool &bVibrator);

	/** @enum BARCODE_PROMT
	  * ʶ��ͷ��ʾ��ʽ
	  */
	enum BARCODE_PROMT{
		BARCODE_PROMT_NOSOUND = 0,
		BARCODE_PROMT_SOUND= 1,
		BARCODE_PROMT_VIBRATOR= 2,
		BARCODE_PROMT_ALL= 3,
	};

	/** @brief ����ʶ��ͷ��ʾ��ʽ 
	  * @param[in] mode 
	  * - 0 ����
	  * - 1 ����
	  * - 2 ��
	  * - 3 �������
	  * @param[in] gSound ȫ�ֵ�����
	  * - true ȫ�־���
	  */
	int SetBarcodePrompt( int mode, bool gSound );

	/** @brief ��ȡʶ��ͷ��ʾ��ʽ 
	  *
	  */
	int GetBarcodePrompt();

	/** @brief ���ü���Repeat 
	  * @param[in] delay ��ʱ(�ڵ�һ�ΰ��������ʱ���ظ�)
	  * @param[in] period ����(��λms)
	  */
	int SetKeyboardRepeat(int delay, int period);
	/** @brief ���ü��̰�����
	  * @param[in] bSound true ����������
	  * @param[in] gSound true ȫ�־���
	  */
	int SetKeyboardSound(bool bSound, bool gSound=false);
	/** @brief ��ȡ������ */
	bool GetKeyboardSound();
	/** @brief ��ȡȫ�־��� */
	bool GetKeyboardGSound();

	/** @brief �������ó�ʼ������Ӳ�� */
	int InitDevice();
	/** @brief ���ļ���ʼ��ʱ�� */
	void SetTZFromFile();

	/** @brief ��ȡ������������ */
	int GetKbdSoundVol();
	int SetKbdSoundVol(int vol=0);
	/** @brief ��ȡɨ����ʾ�������� */
	int GetScanSoundVol();
	int SetScanSoundVol(int vol=0);

	enum WIFI_NET_MODE {
		WIFI_NET_MODE_CUSTOM,
		WIFI_NET_MODE_DHCP,
	};
	/** @brief ��ȡWIFI����IP���䷽ʽ 
	  * @return
	  * @retval ::WIFI_NET_MODE_DHCP
	  * @retval ::WIFI_NET_MODE_MANUAL
	  */
	int GetWifiNetMode();
	/** @brief ����WIFI����IP���䷽ʽ 
	  * @note ���IP��ַ��Ϣ�д��ڻ��������á�
	  */
	int SetWifiNetMode(int mode);

	/** @brief ����WIFI����IP��Ϣ */
	int SetWifiCustomNetIp(wxString ip, wxString netmask, wxString gateway, wxString dns1, wxString dns2);
	/** @brief ��ȡWIFI����IP��Ϣ */
	int GetWifiCustomNetIp(wxString &ip, wxString &netmask, wxString &gateway, wxString &dns1, wxString &dns2);

public:
	wxString GetPwKey();
	wxString GetPwSalt();
	int SetPasswd(wxString key, wxString salt);

////////////////////PT80������ӵĽӿ�/////////////////////////
/************************************************************************/
/* �Զ���з�������                                                     */
/************************************************************************/
	/** @brief ���ü��̱��⿪����ֵ���������ļ����룬��п���ģʽʱ���� */
	int SetKbdBLSchem(void);
	/** @brief ����LCD������Ʒ������������ļ����룬��п���ģʽʱ���� */
	int SetLcdBLSchem(void);

	int DetectScannerType(void);
};

#endif