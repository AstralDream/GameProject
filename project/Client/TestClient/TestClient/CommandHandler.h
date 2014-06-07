#ifndef __CLIENT_CMD_HANDLER_H__
#define __CLIENT_CMD_HANDLER_H__

#include "IBufferHandler.h"
#include "CommandDef.h"
#include "PlayerObject.h"

class CClientCmdHandler : public ICommandHandler
{
private:
	CClientCmdHandler(void);

	~CClientCmdHandler(void);

public:
	static CClientCmdHandler* GetInstancePtr();

	BOOL OnCommandHandle(UINT16 wCommandID, UINT64 u64ConnID, CBufferHelper *pBufferHelper);

	BOOL OnUpdate(UINT32 dwTick);


	//*********************��Ϣ�����忪ʼ******************************
public:
	UINT32 OnCmdConnectNotify(UINT16 wCommandID, UINT64 u64ConnID, CBufferHelper *pBufferHelper);

	UINT32 OnCmdLoginGameAck(UINT16 wCommandID, UINT64 u64ConnID, CBufferHelper *pBufferHelper);

	UINT32 OnCmdEnterGameAck(UINT16 wCommandID, UINT64 u64ConnID, CBufferHelper *pBufferHelper);


	//CMD_CHAR_NEARBY_ADD,			//�����Χ�Ķ���
	//CMD_CHAR_NEARBY_UPDATE,		//������Χ�Ķ���
	//CMD_CHAR_NEARBY_REMOVE,		//ɾ����Χ�Ķ���

	UINT32 OnCmdNearByAdd(UINT16 wCommandID, UINT64 u64ConnID, CBufferHelper *pBufferHelper);
	UINT32 OnCmdNearByUpdate(UINT16 wCommandID, UINT64 u64ConnID, CBufferHelper *pBufferHelper);
	UINT32 OnCmdNearByRemove(UINT16 wCommandID, UINT64 u64ConnID, CBufferHelper *pBufferHelper);

	//*********************��Ϣ���������******************************

	CPlayerObject m_HostPlayer;

	CPlayerObjectMgr m_PlayerObjMgr;
};


#endif