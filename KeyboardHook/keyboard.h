
#pragma once

// ���干���
#pragma data_seg ( "Shared" )
HHOOK	hKeyboard	= NULL ;	// ���̹��Ӿ��
ULONG	keyCount    = 0;
#pragma data_seg ()
#pragma comment ( linker, "/SECTION:Shared,RWS" )

BOOL WINAPI SetHook ( BOOL isInstall ) ;
