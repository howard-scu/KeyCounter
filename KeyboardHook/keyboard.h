
#pragma once

// ���干���
#pragma data_seg ( "Shared" )
HHOOK	hKeyboard	= NULL ;	// ���̹��Ӿ��
#pragma data_seg ()
#pragma comment ( linker, "/SECTION:Shared,RWS" )

BOOL _declspec(dllexport) SetHook ( BOOL isInstall );
UINT _declspec(dllexport) GetKeyCount ();

