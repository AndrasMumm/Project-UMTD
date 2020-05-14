#include "SyncFloat.h"

SyncFloat::SyncFloat(float* ptr) : SyncObject(ptr)
{
	dataPtr_ = ptr;
}

void update(Packet& packet)
{
};
Packet& getUpdateData()
{
};
