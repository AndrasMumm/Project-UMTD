#pragma once
#include <Network/packet.h>

class SyncObject
{
private:
	void* ptr_;
public:
	SyncObject(void* ptr);

	void* getRawPointer() const;

	virtual void update(Packet& packet) = 0;
	virtual Packet& getUpdateData() = 0;
};
