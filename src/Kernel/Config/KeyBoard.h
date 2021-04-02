 
#pragma once
/*
*	AUTHOR: Levan Ostrowski
*   GIT: cod3venom
*	Email: lostrovski@greensoft.biz.pl
*   Created : 2021-04-02 02:23:35
*/

#ifndef __KEYBOARD_H__
#include <iostream>
#include <neatctrl.h>
 

class KeyBoard
{
	private:
	public:
		KeyBoard();
		~KeyBoard();

		typedef enum
		{
			KEY_0 = SCANCODE_0,
			KEY_1 = SCANCODE_1,
			KEY_2 = SCANCODE_2,
			KEY_3 = SCANCODE_3,
			KEY_4 = SCANCODE_4,
			KEY_5 = SCANCODE_5,
			KEY_6 = SCANCODE_6,
			KEY_7 = SCANCODE_7,
			KEY_8 = SCANCODE_8,
			KEY_9 = SCANCODE_9,
			KEY_UP = SCANCODE_CURSORBLOCKUP,
			KEY_DOWN = SCANCODE_CURSORBLOCKDOWN,
			KEY_LEFT = SCANCODE_CURSORBLOCKLEFT,
			KEY_RIGHT = SCANCODE_CURSORBLOCKRIGHT,
			KEY_ENTER = SCANCODE_ENTER,
			KEY_DOT = SCANCODE_PERIOD,
			KEY_OK = SCANCODE_F1,
			KEY_CANCEL = SCANCODE_CANCEL,
			KEY_POWER = SCANCODE_F10,
			KEY_FUNC = SCANCODE_F2,
			KEY_BACKSPACE = SCANCODE_BACKSPACE,
			KEY_TAB = SCANCODE_TAB,
			KEY_ALPHA = SCANCODE_F8,
			KEY_SHIFT = SCANCODE_F12,
			KEY_STAR = SCANCODE_STAR,
			KEY_POUND = SCANCODE_POUND,
			KEY_HOME = SCANCODE_HOME,
		};
};

#endif // __KEYBOARD_H__
