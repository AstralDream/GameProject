// LoginServer.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "GameService.h"

#pragma comment(lib, "ServerEngine.lib")

int main(int argc, char* argv[])
{
	CGameService::GetInstancePtr()->StartRun();

	return 0;
}

