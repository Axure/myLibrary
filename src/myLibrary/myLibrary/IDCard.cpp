// IDCard.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "myLibrary.h"
#include "IDCard.h"
#include "afxdialogex.h"

CString strType;  
int bCombo = 0;

// CIDCard �Ի���

IMPLEMENT_DYNAMIC(CIDCard, CDialogEx)

CIDCard::CIDCard(CWnd* pParent /*=NULL*/)
	: CDialogEx(CIDCard::IDD, pParent)
	, m_idc_uid(99999)
	, m_idc_name(_T(""))
	, m_idc_org(_T(""))
	, m_idc_deluid(99999)
	, m_idc_pwd(_T(""))
{

}

CIDCard::~CIDCard()
{
}

void CIDCard::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_uid, m_idc_uid);
	DDX_Text(pDX, IDC_name, m_idc_name);
	DDX_Text(pDX, IDC_ORG, m_idc_org);
	DDX_Text(pDX, IDC_deluid, m_idc_deluid);
	DDX_Text(pDX, IDC_pwd, m_idc_pwd);
	DDX_Control(pDX, IDC_COMBO1, m_idc_Combo);
	
	if(!bCombo)
	{
		m_idc_Combo.AddString(_T("��ʦ"));
		m_idc_Combo.AddString(_T("ѧ��"));      
		m_idc_Combo.SetCurSel(0);   
		bCombo = 1;
	}
}


BEGIN_MESSAGE_MAP(CIDCard, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CIDCard::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_DELETE, &CIDCard::OnBnClickedDelete)
	ON_BN_CLICKED(IDC_ADD, &CIDCard::OnBnClickedAdd)
END_MESSAGE_MAP()


// CIDCard ��Ϣ�������


void CIDCard::OnCbnSelchangeCombo1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������  
    int nSel;    
    // ��ȡ��Ͽ�ؼ����б����ѡ���������    
    nSel = m_idc_Combo.GetCurSel();    
    // ����ѡ����������ȡ�����ַ���    
    m_idc_Combo.GetLBText(nSel, strType);    
}


void CIDCard::OnBnClickedDelete()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(MessageBox(_T("ȷ��Ҫɾ����"),_T("��ʾ-ͼ�����ϵͳ"),MB_OKCANCEL)==IDCANCEL)
			return;

	if(!m_db.IsOpen() && !m_db.OpenEx(_T("DSN=mydb;DATABASE=Library;UID=admin;PWD=admin"), 
	 CDatabase::noOdbcDialog))
	{
		MessageBox(_T("���ݿ�����ʧ��"));
		return;
	}

	CRecordset m_set(&m_db);
	CString query, securequery, nowpwd;

	UpdateData(TRUE); 
	
	try
	{
		extern int nowuid;
		CDBVariant var;

		securequery.Format(_T("select lib_psw from lib_admin where lib_aid = %d"),
			nowuid);
		m_set.Open(CRecordset::forwardOnly,securequery);
		short nFields = m_set.GetODBCFieldCount();
		while(!m_set.IsEOF())
		{
			for(short index = 0; index < nFields; index++)
			{
				m_set.GetFieldValue(index, var);
				nowpwd = VariantToCString(&var);
			}
			m_set.MoveNext();
		}
		if(nowpwd != m_idc_pwd)
		{
			MessageBox(_T("���������������Ȩ������"));
			return;
		}

		query.Format(_T("delete from lib_user where lib_uid = %d"),
				m_idc_deluid);
		m_db.ExecuteSQL(query);
		MessageBox(_T("ɾ���ɹ�"));
	}
	catch(CDBException* pe)
	{
		MessageBox(_T("ɾ��ʧ��"));
		pe->Delete();
	}
	m_set.Close();
	m_db.Close();
}


void CIDCard::OnBnClickedAdd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	if(!m_db.IsOpen() && !m_db.OpenEx(_T("DSN=mydb;DATABASE=Library;UID=admin;PWD=admin"), 
	 CDatabase::noOdbcDialog))
	{
		MessageBox(_T("���ݿ�����ʧ��"));
		return;
	}

	int userclass;
	if(strType == "��ʦ"){userclass = 0;}
	else if(strType == "ѧ��"){userclass = 1;}

	CRecordset m_set(&m_db);
	CString query;

	UpdateData(TRUE); 
	try
	{
		if(m_idc_uid == 0 || m_idc_name == "" || m_idc_org == "")
		{
			MessageBox(_T("����д�����Ϣ��"));
			return;
		}
		query.Format(_T("insert into lib_user values (%d, '%s', '%s', %d)"),
				m_idc_uid, m_idc_name, m_idc_org, userclass);
		m_db.ExecuteSQL(query);
		MessageBox(_T("�Ǽǳɹ�"));
	}
	catch(CDBException* pe)
	{
		MessageBox(_T("�Ǽ�ʧ��"));
		pe->Delete();
	}
	m_set.Close();
	m_db.Close();
}

CString CIDCard::VariantToCString(CDBVariant* var)
{
	CString str; //ת���Ժ���ַ���

	if(!var)
	{
		str = "NULL Var Parameter";
		return str;
	}
	switch(var->m_dwType)
	{
	case DBVT_SHORT:
		str.Format(L"%d",(int)var->m_iVal);
		break;
	case DBVT_LONG:
		str.Format(L"%d",var->m_lVal);
		break;
	case DBVT_SINGLE:
		str.Format(L"%10.6f",(double)var->m_fltVal);
		break;
	case DBVT_DOUBLE:
		str.Format(L"%10.6f",var->m_dblVal);
		break;
	case DBVT_BOOL:
		str = (var->m_boolVal==0) ?L"FALSE": L"TRUE";
		break;
	case DBVT_STRING:
		str = var->m_pstring->GetBuffer();
		break;
	case DBVT_ASTRING: 
		str = var->m_pstringA->GetBuffer(); 
		break; 
	case DBVT_WSTRING: 
		str = var->m_pstringW->GetBuffer(); 
		break;
	case DBVT_DATE:
		str.Format(L"%d-%d-%d",(var->m_pdate)->year,(var->m_pdate)->month,(var->m_pdate)->day);
		break;
	default:
		str.Format(L"Unk type %d\n",var->m_dwType);
		TRACE(L"Unknown type %d\n",var->m_dwType);
	}
	return str;
}