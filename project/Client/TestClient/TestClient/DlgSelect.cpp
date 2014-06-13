// DlgSelect.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TestClient.h"
#include "DlgSelect.h"
#include "CommandHandler.h"


// CDlgSelect �Ի���

IMPLEMENT_DYNAMIC(CDlgSelect, CDialog)

CDlgSelect::CDlgSelect(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSelect::IDD, pParent)
{

}

CDlgSelect::~CDlgSelect()
{
}

void CDlgSelect::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_CharList);
}


BEGIN_MESSAGE_MAP(CDlgSelect, CDialog)
	ON_BN_CLICKED(IDOK, &CDlgSelect::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_NEW_CHAR, &CDlgSelect::OnBnClickedBtnNewChar)
END_MESSAGE_MAP()


// CDlgSelect ��Ϣ�������

BOOL CDlgSelect::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_CharList.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);

	m_CharList.InsertColumn(0, "��ɫ��", LVCFMT_LEFT, 100);
	m_CharList.InsertColumn(1, "�ȼ�", LVCFMT_LEFT, 100);
	m_CharList.InsertColumn(2, "�Ա�", LVCFMT_LEFT, 100);
	m_CharList.InsertColumn(3, "ְҵ", LVCFMT_LEFT, 100);
	m_CharList.InsertColumn(4, "����", LVCFMT_LEFT, 100);

	RefreshListCtrl();

	return TRUE; 
}

void CDlgSelect::OnBnClickedOk()
{
	int nIndex = m_CharList.GetSelectionMark();
	if(nIndex < 0)
	{
		return ;
	}

	int SelData = m_CharList.GetItemData(nIndex);

	CClientCmdHandler::GetInstancePtr()->SendPickCharReq(m_CharInfoList[SelData].u64CharID);

	OnOK();
}

void CDlgSelect::OnBnClickedBtnNewChar()
{
	CClientCmdHandler::GetInstancePtr()->SendNewCharReq(m_dwAccountID,"Testtet" ,123);

	OnOK();
}

BOOL CDlgSelect::AddCharPickInfo( StCharPickInfo &PickInfo )
{
	if(m_nCount >= 4)
	{
		return FALSE;
	}

	m_CharInfoList[m_nCount] = PickInfo;

	m_nCount++;

	return TRUE;
}

BOOL CDlgSelect::RefreshListCtrl()
{
	m_CharList.DeleteAllItems();

	CHAR szValue[64]={0};
	for(int i = 0; i < m_nCount; i++)
	{
		sprintf(szValue, "%d", m_CharInfoList[i].dwLevel);
		m_CharList.InsertItem(i, m_CharInfoList[i].szCharName);
		m_CharList.SetItemText(i, 1, szValue);
		m_CharList.SetItemText(i, 2, "��");
		m_CharList.SetItemText(i, 3,"��ʦ");
		m_CharList.SetItemData(i, i);
	}

	return TRUE;
}
