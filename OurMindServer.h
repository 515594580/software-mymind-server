
// OurMindServer.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// COurMindServerApp:
// �йش����ʵ�֣������ OurMindServer.cpp
//

class COurMindServerApp : public CWinApp
{
public:
	COurMindServerApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern COurMindServerApp theApp;