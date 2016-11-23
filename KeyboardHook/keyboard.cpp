#include <windows.h>
#include "keyboard.h"
#include "stdio.h"

HINSTANCE	hDllInst	= NULL ;	// DLL模块实例句柄

int WINAPI DllMain ( HINSTANCE hInstance, DWORD fdwReason, PVOID pvReserved )
{ 
	if ( fdwReason == DLL_PROCESS_ATTACH )
		hDllInst = hInstance ;		// 保存DLL实例句柄
	return true ;
}

// 键盘钩子消息处理过程
LRESULT CALLBACK KeyboardProc ( int nCode, WPARAM wParam, LPARAM lParam )
{
	//nCode：处理消息标识。nCode<0表示Hook无法处理
	//wParam：虚拟键值
	//lParam：消息参数，包括重复次数/扫描码等
	// 最高位为0(lParam>0)，表示VM_KEYDOWN消息
	if( ( nCode == HC_ACTION ) && ( lParam > 0 ) )
	{
		WCHAR KeyName[10] = {0} ;
		GetKeyNameText ( (LONG)lParam, KeyName, 50 ) ;
		//MessageBox ( NULL, KeyName, L"全局键盘钩子", MB_OK ) ;
		keyCount++;
	}

	// 继续传递消息
	return CallNextHookEx ( hKeyboard, nCode, wParam, lParam ) ;
}

// 钩子控制函数，能够启动/卸载钩子
BOOL WINAPI SetHook ( BOOL isInstall ) 
{
	// 需要安装，且键盘钩子不存在
	if ( isInstall && !hKeyboard )
	{
		// 设置全局钩子(Hook类型，回调函数，句柄，线程)
		hKeyboard = SetWindowsHookEx ( WH_KEYBOARD, (HOOKPROC)KeyboardProc, hDllInst, 0 ) ;
		if ( hKeyboard == NULL )
		{
			DWORD dwErrorCode = GetLastError () ;
			return FALSE ;
		}
	}

	// 需要卸载，且键盘钩子存在
	if ( !isInstall && hKeyboard )
	{
		// 卸载钩子
		BOOL ret = UnhookWindowsHookEx ( hKeyboard ) ;
		hKeyboard	= NULL ;
		return ret ;
	}

	return TRUE ;
}