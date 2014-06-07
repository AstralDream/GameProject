#pragma once


// CDlgGame �Ի���

class CDlgGame : public CDialog
{
	DECLARE_DYNAMIC(CDlgGame)

public:
	CDlgGame(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgGame();

// �Ի�������
	enum { IDD = IDD_Dlg_Game };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();

public:
	VOID  DrawPlayer(HDC hDC, int nX, int nY);

	VOID  DrawNpc(HDC hDC,int nX, int nY);

	VOID  DrawItem(HDC hDC,int nX, int nY);

	VOID Draw(HDC hDC,int nX, int nY, COLORREF clr, int nRadius);

	afx_msg void OnSize(UINT nType, int cx, int cy);
};
