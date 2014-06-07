
// TestClientDlg.h : ͷ�ļ�
//

#pragma once
#include "DlgLogin.h"
#include "DlgGame.h"
#include "afxwin.h"

// CTestClientDlg �Ի���
class CTestClientDlg : public CDialog
{
// ����
public:
	CTestClientDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TESTCLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	CDlgLogin  m_DlgLogin;

	CDlgGame   m_DlgGame;

public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLogin();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CListBox m_LogList;
	afx_msg void OnDisconnect();
	afx_msg void OnConnect();
	afx_msg void OnLeaveGame();
};
