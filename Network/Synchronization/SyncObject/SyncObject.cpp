#include "syncObject.h"
#include <cstdint>

SyncObject::SyncObject(void* ptr)
{
	ptr_ = ptr;
}

void* SyncObject::getRawPointer() const
{
	return ptr_;
}
