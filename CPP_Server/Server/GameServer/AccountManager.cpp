#include "pch.h"
#include "PlayerManager.h"
#include "AccountManager.h"
AccountManager GAccountManager;

void AccountManager::AccountThenPlayer()
{
	WRITE_LOCK;
	GPlayerManager.Lock();
}

void AccountManager::Lock()
{
	WRITE_LOCK;
}
