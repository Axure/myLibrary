#pragma once


// CAdmin �Ի���

class CAdmin : public CDialogEx
{
	DECLARE_DYNAMIC(CAdmin)

public:
	CAdmin(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAdmin();

// �Ի�������
	enum { IDD = IDD_Admin_Main };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton4();
};
