#include "SyncManager.h"
#include <cstdint>
#include <string>
#include <vector>

#include "Game/helpingHeader.h"

bool SyncManager::isHost() const
{
	return isHost_;
}

void SyncManager::setIsHost(bool v)
{
	isHost_ = v;
}

/*
void SyncManager::addSyncObject(char* obj)
{
}
*/

template<typename T>
bool SyncManager::removeSyncObject(T* objToDelete)
{
	void* objToDeleteRawPointer = static_cast<void*>(objToDelete);
	auto it = syncObjects_.begin();
	while (it != syncObjects_.end())
	{
		if ((*it)->getRawPointer() == objToDeleteRawPointer)
		{
			syncObjects_.erase(it);
			return true;
		}
	}

	return false;
}
