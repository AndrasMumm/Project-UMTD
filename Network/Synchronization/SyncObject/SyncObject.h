#pragma once

class SyncObject
{
private:
	void* ptr_;
public:
	SyncObject(void* ptr);

	void* getRawPointer() const;
};
