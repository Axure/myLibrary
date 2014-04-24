#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CLAB �Ի���

class CLAB : public CDialogEx
{
	DECLARE_DYNAMIC(CLAB)

private:
	CDatabase m_db;

public:
	CLAB(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLAB();

// �Ի�������
	enum { IDD = IDD_LAB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int m_lab_bno;
	afx_msg void OnBnClickedpersonaldata();
	CListCtrl m_ListCtrl;
	int m_lab_uid;
	afx_msg void OnBnClickedlendnew();
	afx_msg void OnBnClickedborrownew();
	CString VariantToCString(CDBVariant* var);
};
