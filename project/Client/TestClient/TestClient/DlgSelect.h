#pragma once
#include "afxcmn.h"
#include "PacketDef\ClientPacket.h"


// CDlgSelect �Ի���

class CDlgSelect : public CDialog
{
	DECLARE_DYNAMIC(CDlgSelect)

public:
	CDlgSelect(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgSelect();

// �Ի�������
	enum { IDD = IDD_DLG_SELECT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:

	int				m_nCount;
	StCharPickInfo  m_CharInfoList[4];

	CListCtrl m_CharList;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
