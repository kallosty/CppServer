#include "pch.h"
#include "UserManager.h"
#include "AccountManager.h"

void UserManager::ProcessSave()
{
	//DeadLock 상태를 해결하는 방법
	//순서를 신경써서 잡아주는 것이 좋음
	//DeadLock Manager를 통해 잡아줘도 좋음 -> 알고리즘 : Graph를 사용
	//그래프에서 사이클이 돌면 확인 (서로 연결되어있는 것 확인)

	Account* account = AccountManager::Instance()->GetAccount(100);
	lock_guard<mutex> guard(_mutex);
}