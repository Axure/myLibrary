#pragma once
#include "afxwin.h"


// CIDCard �Ի���

class CIDCard : public CDialogEx
{
	DECLARE_DYNAMIC(CIDCard)

private:
	CDatabase m_db;

public:
	CIDCard(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CIDCard();

// �Ի�������
	enum { IDD = IDD_IDCard };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int m_idc_uid;
	CString m_idc_name;
	CString m_idc_org;
	int m_idc_deluid;
	CString m_idc_pwd;
	CComboBox m_idc_Combo;
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedDelete();
	afx_msg void OnBnClickedAdd();
	CString VariantToCString(CDBVariant* var);
};
