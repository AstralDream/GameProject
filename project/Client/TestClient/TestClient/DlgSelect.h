#pragma once


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
};
