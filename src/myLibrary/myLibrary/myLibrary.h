
// myLibrary.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include "afxcmn.h"
#include "afxdb.h"
#include <Sql.h> 
#include <Sqlext.h> 
#include <Sqltypes.h>


// CmyLibraryApp:
// �йش����ʵ�֣������ myLibrary.cpp
//

class CmyLibraryApp : public CWinApp
{
public:
	CmyLibraryApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
	afx_msg void OnIdokGotoq();
};

extern CmyLibraryApp theApp;
