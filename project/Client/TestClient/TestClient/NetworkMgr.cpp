#include "StdAfx.h"
#include "NetworkMgr.h"
#include "Utility/CommonSocket.h"
#include "resource.h"
#include "TestClientDlg.h"
#include "DataBuffer/DataBuffer.h"
#include "PacketHeader.h"
#include "DataBuffer/BufferHelper.h"
#include "CommandHandler.h"
#include "DataBuffer/BufferHelper.h"

CNetworkMgr::CNetworkMgr(void)
{
	m_hSocket		= INVALID_SOCKET;

	m_nDataLen		= 0;

	m_bConnected	= FALSE;

	m_pReadBuffer	= new CDataBuffer<BUFFSIZE>;

	m_pWriteBuffer	= new CDataBuffer<BUFFSIZE>;
}

CNetworkMgr::~CNetworkMgr(void)
{
	if(m_pReadBuffer)
	{
		delete m_pReadBuffer;
	}

	if(m_pWriteBuffer)
	{
		delete m_pWriteBuffer;
	}

}

CNetworkMgr* CNetworkMgr::GetInstancePtr()
{
	static CNetworkMgr _NetworkMgr;

	return &_NetworkMgr;
}

BOOL CNetworkMgr::InitNetSystem()
{
	if(!CommonSocket::InitNetwork())
	{
		MessageBox(NULL, "�����ʼ��ʧ��!", "������ʾ", MB_OK);
		return FALSE;
	}

	return TRUE;
}

BOOL CNetworkMgr::DisConnect()
{
	CommonSocket::CloseSocket(m_hSocket);

	m_bConnected = FALSE;

	return FALSE;
}

BOOL CNetworkMgr::ConnectToServer(std::string strIpAddr, UINT16 sPort)
{
	m_hSocket = CommonSocket::CreateSocket(AF_INET, SOCK_STREAM, 0);
	if((m_hSocket == INVALID_SOCKET)||(m_hSocket == NULL))
	{
		MessageBox(NULL, "�����׽���ʧ��!", "������ʾ", MB_OK);
		return FALSE;
	}

	CommonSocket::SetSocketUnblock(m_hSocket);

	if(!CommonSocket::ConnectSocket(m_hSocket, strIpAddr.c_str(), sPort))
	{
		MessageBox(NULL, "���ӷ�����ʧ��!", "������ʾ", MB_OK);
		return FALSE;
	}

	return TRUE;
}

BOOL CNetworkMgr::OnTime()
{
	RecvData();

	ProcessData();

	return TRUE;
}

BOOL CNetworkMgr::RecvData()
{
	int nReadLen = recv(m_hSocket, m_Buffer + m_nDataLen, BUFFSIZE - m_nDataLen, 0);
	if(nReadLen < 0)
	{
		DWORD nError = CommonSocket::GetSocketLastError();
		if(nError == WSAEWOULDBLOCK)
		{
			//���û�����ӣ��������ӳɹ�
			if(!m_bConnected)
			{
				m_bConnected = TRUE;

				((CTestClientDlg*)AfxGetMainWnd())->m_LogList.AddString("���ӳɹ�1!");
			}

			if(nError != m_nLastError)
			{
				CString strText;
				strText.Format("�������ݷ�������:%s!", CommonSocket::GetLastErrorStr(nError).c_str());
				((CTestClientDlg*)AfxGetMainWnd())->m_LogList.AddString(strText);

				m_nLastError = nError;
			}
		}
		else 
		{
			if(nError != m_nLastError)
			{
				CString strText;
				strText.Format("�������ݷ�������:%s!", CommonSocket::GetLastErrorStr(nError).c_str());
				((CTestClientDlg*)AfxGetMainWnd())->m_LogList.AddString(strText);

				m_nLastError = nError;
			}

			if(m_bConnected)
			{
				m_bConnected = FALSE;
			}
		}
	}
	else if(nReadLen == 0)
	{
		CString strText;
		strText.Format("�Է��ر�������!");
		((CTestClientDlg*)AfxGetMainWnd())->m_LogList.AddString(strText);

		if(m_bConnected)
		{
			m_bConnected = FALSE;
		}
	}
	else
	{
		if(!m_bConnected)
		{
			m_bConnected = TRUE;

			CString strText;
			strText.Format("���ӳɹ�2!�� �յ�%d�ֽ�����", nReadLen);

			((CTestClientDlg*)AfxGetMainWnd())->m_LogList.AddString(strText);
		}

		m_nDataLen += nReadLen;
	}
	

 	return TRUE;
}

BOOL CNetworkMgr::SendData( char *pData, UINT32 dwLen )
{
	if(!m_bConnected)
	{
		return FALSE;
	}

	int nWriteLen = send(m_hSocket,  (char*)pData, dwLen, 0);
	if(nWriteLen < 0)
	{
		DWORD nError = CommonSocket::GetSocketLastError();
		if(nError != m_nLastError)
		{
			CString strText;
			strText.Format("�������ݷ�������:%s!", CommonSocket::GetLastErrorStr(nError).c_str());

			((CTestClientDlg*)AfxGetMainWnd())->m_LogList.AddString(strText);

			m_nLastError = nError;
		}

		return FALSE;
	}
	else
	{
		if(nWriteLen < dwLen)
		{
			m_bConnected = FALSE;

			return FALSE;
		}
	}
	
	return TRUE;
}

BOOL CNetworkMgr::IsConnected()
{
	return m_bConnected;
}

BOOL CNetworkMgr::ProcessData()
{
	if(m_nDataLen < sizeof(TransferHeader))
	{
		return FALSE;
	}
	
	TransferHeader *pHeader = (TransferHeader *)m_Buffer;
	if(pHeader->dwSize <= m_nDataLen)
	{
		memcpy(m_pReadBuffer->GetData(), m_Buffer, pHeader->dwSize);
		
		m_pReadBuffer->SetDataLenth(pHeader->dwSize);

		m_nDataLen -= pHeader->dwSize;

		if(m_nDataLen > 0)
		{
			memmove(m_Buffer, m_Buffer+pHeader->dwSize, m_nDataLen);
		}

		CBufferHelper BufferReader(FALSE, m_pReadBuffer);
		if(!BufferReader.BeginRead())
		{
			return FALSE;
		}

		CommandHeader *pCommandHeader = BufferReader.GetCommandHeader();
		if(pCommandHeader == NULL)
		{
			return FALSE;
		}

		CClientCmdHandler::GetInstancePtr()->OnCommandHandle(pCommandHeader->wCommandID, 0, &BufferReader);
	}

	return TRUE;
}


