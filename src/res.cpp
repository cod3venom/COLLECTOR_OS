// dlgres.cpp : 资源文件
// auto gen by NEAR Resource Tool, 04/02/21 03:10:10
//
#include <neatctrl.h>
#include <neatrc.h>
#include "resource.h"

//////////////////////////////////////////////////////////////////////////
//
// Dialog

static DLGID_TEMPL templ_dlg[]=
{
    {0, NULL}
};


//////////////////////////////////////////////////////////////////////////
//
// Bitmap
static STRID_TEMPL templ_bitmap[]=
{
    {0, NULL}
};

//////////////////////////////////////////////////////////////////////////
//
// Icons
static STRID_TEMPL templ_icon[]=
{
    {IDI_ICON, "icon.ico"},
    {0, NULL}
};

//////////////////////////////////////////////////////////////////////////
//
// Cursors
static STRID_TEMPL templ_cursor[]=
{
    {0, NULL}
};

//////////////////////////////////////////////////////////////////////////
//
// Toolbars
static STRID_TEMPL templ_toolbar[]=
{
    {0, NULL}
};

//////////////////////////////////////////////////////////////////////////
//
// String Tables
static STRID_TEMPL templ_strtab[]=
{
    {0, NULL}
};

//////////////////////////////////////////////////////////////////////////
//
// Menus
static MENU_TEMPL templ_menu[]=
{
    {0, NULL}
};

//////////////////////////////////////////////////////////////////////////
//
// Version
static VERSION_TEMPL templ_version[]=
{
    {""},
    {""},
    {""},
    {""},
    {""},
    {""},
    {""},
    {""},
    {""},
    {""},
    {""},
    {""},
    {""},
    {""},
    {""},
    {""},
    {""},
    {""},
    {""},
    {""},
};

#ifdef __NEATPLUGIN__
	extern wxString neatappName;
#endif
	static CNeatRes rc(	templ_dlg,		 // Dialog
						templ_bitmap,	 // Bitmap
						templ_icon,		 // Icon
						templ_strtab,	 // String Table
						templ_toolbar,	 // Toolbar
						templ_cursor,	 // Cursor
						templ_menu,		 // Menu
						templ_version	 // Version
					);
#ifdef __NEATPLUGIN__
void register_neatrc()
{
#endif // __NEATPLUGIN__
	static ResourceRegistrant rcreg(
		1, 0, 0,		// version
#ifdef __NEATPLUGIN__
		neatappName,	// app
#else
		"",
#endif
		&rc,		// resource
		"./res-collectoros"
);
#ifdef __NEATPLUGIN__
}
#endif //__NEATPLUGIN__

