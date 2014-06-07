
// TestClient.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "TestClient.h"
#include "TestClientDlg.h"
#include "CommandHandler.h"
#include "NetworkMgr.h"
#include "DataBuffer\BufferHelper.h"
#include "PacketDef\CommonPacket.h"
#include "PacketDef\RolePacket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTestClientApp

BEGIN_MESSAGE_MAP(CTestClientApp, CWinAppEx)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CTestClientApp ����

CTestClientApp::CTestClientApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CTestClientApp ����

CTestClientApp theApp;


// CTestClientApp ��ʼ��

BOOL CTestClientApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	AfxEnableControlContainer();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	CTestClientDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

BOOL CTestClientApp::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���

	if(pMsg->message == WM_KEYUP)
	{
		if(pMsg->wParam == VK_LEFT)
		{
			CClientCmdHandler::GetInstancePtr()->m_HostPlayer.m_ObjectPos.x-=2;
		}
		else if(pMsg->wParam == VK_RIGHT)
		{
			CClientCmdHandler::GetInstancePtr()->m_HostPlayer.m_ObjectPos.x+=2;
		}
		else if(pMsg->wParam == VK_UP)
		{
			CClientCmdHandler::GetInstancePtr()->m_HostPlayer.m_ObjectPos.z-=2;
		}
		else if(pMsg->wParam == VK_DOWN)
		{
			CClientCmdHandler::GetInstancePtr()->m_HostPlayer.m_ObjectPos.z+=2;
		}
		else
		{
			return CWinAppEx::PreTranslateMessage(pMsg);
		}

		((CTestClientDlg*)AfxGetMainWnd())->m_DlgGame.Invalidate();

		StCharMoveReq _MoveGs;
		_MoveGs.x = CClientCmdHandler::GetInstancePtr()->m_HostPlayer.m_ObjectPos.x;
		_MoveGs.y = CClientCmdHandler::GetInstancePtr()->m_HostPlayer.m_ObjectPos.y;
		_MoveGs.z = CClientCmdHandler::GetInstancePtr()->m_HostPlayer.m_ObjectPos.z;

		CBufferHelper WriteHelper(TRUE, CNetworkMgr::GetInstancePtr()->m_pWriteBuffer);

		WriteHelper.BeginWrite(CMD_ROLE_MOVE, CMDH_SENCE, 12, CClientCmdHandler::GetInstancePtr()->m_HostPlayer.GetObjectID());

		WriteHelper.Write(_MoveGs);

		WriteHelper.EndWrite();

		CNetworkMgr::GetInstancePtr()->SendData(CNetworkMgr::GetInstancePtr()->m_pWriteBuffer->GetData(), CNetworkMgr::GetInstancePtr()->m_pWriteBuffer->GetDataLenth());

		//CString strText;
		//strText.Format("��ǰ��ɫ:%d, ����x = %f, z= %f", (UINT32)CClientCmdHandler::GetInstancePtr()->m_HostPlayer.GetObjectID(),
		//	CClientCmdHandler::GetInstancePtr()->m_HostPlayer.m_ObjectPos.x,CClientCmdHandler::GetInstancePtr()->m_HostPlayer.m_ObjectPos.z);

		//((CTestClientDlg*)AfxGetMainWnd())->m_LogList.AddString(strText);

		return TRUE;
	}
	else if(pMsg->message == WM_KEYUP)
	{
		return TRUE;
	}


	return CWinAppEx::PreTranslateMessage(pMsg);
}
