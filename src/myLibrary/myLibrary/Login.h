#pragma once


// CLogin �Ի���

class CLogin : public CDialogEx
{
	DECLARE_DYNAMIC(CLogin)

private:
	CDatabase m_db;

public:
	CLogin(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLogin();

// �Ի�������
	enum { IDD = IDD_Login };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedgotoq();
	afx_msg void OnBnClickedlogin();
	afx_msg void OnBnClickedconnect();
	afx_msg void OnBnClickeddisconnect();
	//afx_msg void OnOK();
	//afx_msg void OnCANCEL();
	int m_login_uid;
	CString m_login_pwd;
};
