
// KeyCounter.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CKeyCounterApp:
// �йش����ʵ�֣������ KeyCounter.cpp
//

class CKeyCounterApp : public CWinApp
{
public:
	CKeyCounterApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CKeyCounterApp theApp;