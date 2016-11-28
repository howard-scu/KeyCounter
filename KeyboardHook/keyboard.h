
#pragma once

// 定义共享段
#pragma data_seg ( "Shared" )
HHOOK	hKeyboard	= NULL ;	// 键盘钩子句柄
#pragma data_seg ()
#pragma comment ( linker, "/SECTION:Shared,RWS" )

BOOL _declspec(dllexport) SetHook ( BOOL isInstall );
UINT _declspec(dllexport) GetKeyCount ();

