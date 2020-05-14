#pragma once
#include <memory>
#include <vector>

#include "SyncObject/SyncObject.h"

class SyncManager
{
private:
	bool isHost_;
	std::vector<std::unique_ptr<SyncObject>> syncObjects_;

public:
	SyncManager& GetInstance();

	SyncManager();
	~SyncManager();

	bool isHost() const;
	void setIsHost(bool v);

	template <typename T>
	void addSyncObject(T* obj);

	template <typename T>
	bool removeSyncObject(T* obj);
};
