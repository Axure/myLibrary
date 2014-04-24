// Login.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "myLibrary.h"
#include "afxdialogex.h"
#include "Query.h"
#include "Admin.h"
#include "Login.h"

int nowuid;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// CLogin �Ի���

IMPLEMENT_DYNAMIC(CLogin, CDialogEx)

CLogin::CLogin(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLogin::IDD, pParent)
	, m_login_uid(1)
	, m_login_pwd(_T("123456"))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CLogin::~CLogin()
{
}

void CLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_AID, m_login_uid);
	DDX_Text(pDX, IDC_EDIT_PWD, m_login_pwd);
}


BEGIN_MESSAGE_MAP(CLogin, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_gotoQ, &CLogin::OnBnClickedgotoq)
	ON_BN_CLICKED(IDC_login, &CLogin::OnBnClickedlogin)
	ON_BN_CLICKED(IDC_connect, &CLogin::OnBnClickedconnect)
	ON_BN_CLICKED(IDC_disconnect, &CLogin::OnBnClickeddisconnect)
END_MESSAGE_MAP()

// CLogin ��Ϣ�������

BOOL CLogin::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CLogin::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CLogin::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CLogin::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//void CLogin::OnOK(){}
//void CLogin::OnCANCEL(){}


void CLogin::OnBnClickedgotoq()
{
		CQuery queryDlg;
		queryDlg.DoModal();
}


void CLogin::OnBnClickedlogin()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CRecordset m_set(&m_db);
	CDBVariant var;
	CString query;
	int count = 0;

	UpdateData(TRUE); 

	nowuid = m_login_uid;
	if(!(!m_db.IsOpen() && !m_db.OpenEx(_T("DSN=mydb;DATABASE=Library;UID=admin;PWD=admin"), 
		CDatabase::noOdbcDialog)))
	{
		if(m_login_uid != 0 && m_login_pwd != "")
		{ 
			query.Format(_T("select * from lib_admin where lib_aid = %d and lib_psw = '%s'"),
				m_login_uid, m_login_pwd);
			m_set.Open(CRecordset::forwardOnly,query,CRecordset::readOnly);	
			while(!m_set.IsEOF())
			{
				m_set.MoveNext();
				count++;
			}
			if(count>0)
			{
				CAdmin adminDlg;
				adminDlg.DoModal();
			}
			else
			{
				MessageBox(_T("�û������������"));
			}
		}
		else
		{
			MessageBox(_T("�û������������"));
		}
	}


}


void CLogin::OnBnClickedconnect()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(!m_db.IsOpen() && !m_db.OpenEx(_T("DSN=mydb;UID=admin;PWD=admin"), 
			CDatabase::noOdbcDialog))
	{
		MessageBox(_T("���Ӵ���"));
		return;
	}
	else
	{
		MessageBox(_T("���ӳɹ���"));
		return;
	}
}

void CLogin::OnBnClickeddisconnect()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(!m_db.IsOpen())
	{
		MessageBox(_T("δ�������ݿ⣡"));
		return;
	}
	m_db.Close();
	if(!m_db.IsOpen())
	{
		MessageBox(_T("�Ͽ��ɹ���"));
		return;
	}
	else
	{
		MessageBox(_T("�Ͽ�ʧ�ܣ�"));
		return;
	}
}
