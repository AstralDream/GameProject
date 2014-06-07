
// TestClientDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TestClient.h"
#include "TestClientDlg.h"
#include "NetworkMgr.h"
#include "PacketDef/RolePacket.h"
#include "DataBuffer/BufferHelper.h"
#include "CommandDef.h"
#include "CommandHandler.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
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

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CTestClientDlg �Ի���




CTestClientDlg::CTestClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestClientDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LST_LOG, m_LogList);
}

BEGIN_MESSAGE_MAP(CTestClientDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_SIZE()
	ON_COMMAND(ID_Login, &CTestClientDlg::OnLogin)
	ON_WM_TIMER()
	ON_COMMAND(ID_DISCONNECT, &CTestClientDlg::OnDisconnect)
	ON_COMMAND(ID_CONNECT, &CTestClientDlg::OnConnect)
	ON_COMMAND(ID_LEAVE_GAME, &CTestClientDlg::OnLeaveGame)
END_MESSAGE_MAP()

// CTestClientDlg ��Ϣ�������
BOOL CTestClientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

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

	m_DlgGame.Create(IDD_Dlg_Game, this);

	CRect rcClient;
	GetClientRect(rcClient);
	rcClient.right -= 500;
	m_DlgGame.MoveWindow(rcClient);

	CNetworkMgr::GetInstancePtr()->InitNetSystem();

	SetTimer(1, 25, NULL);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CTestClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

//  �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTestClientDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CTestClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CTestClientDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	if(IsWindow(m_DlgGame.GetSafeHwnd()))
	{
		CRect rcClient;
		GetClientRect(rcClient);
		rcClient.right -= 500;
		m_DlgGame.MoveWindow(rcClient);
		m_DlgGame.Invalidate();
	}
}

void CTestClientDlg::OnLogin()
{
	CDlgLogin DlgLogin;

	DlgLogin.DoModal();
}

void CTestClientDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CNetworkMgr::GetInstancePtr()->OnTime();

	CDialog::OnTimer(nIDEvent);
}

void CTestClientDlg::OnDisconnect()
{ 
	// TODO: �ڴ���������������
	CNetworkMgr::GetInstancePtr()->DisConnect();
}

void CTestClientDlg::OnConnect()
{
	//CNetworkMgr::GetInstancePtr()->Start();
}

void CTestClientDlg::OnLeaveGame()
{
	StCharLeaveGameReq CharLeaveGameReq;

	CharLeaveGameReq.dwLeaveReason = 1;

	CBufferHelper WriteHelper(TRUE, CNetworkMgr::GetInstancePtr()->m_pWriteBuffer);

	WriteHelper.BeginWrite(CMD_CHAR_LEAVE_GAME_REQ, CMDH_SENCE, 12, CClientCmdHandler::GetInstancePtr()->m_HostPlayer.GetObjectID());

	WriteHelper.Write(CharLeaveGameReq);

	WriteHelper.EndWrite();

	CNetworkMgr::GetInstancePtr()->SendData(CNetworkMgr::GetInstancePtr()->m_pWriteBuffer->GetData(), CNetworkMgr::GetInstancePtr()->m_pWriteBuffer->GetDataLenth());
}
