#pragma once

class SyncObject
{
private:
	void* ptr_;
public:
	SyncObject(void* ptr);

	void* getRawPointer() const;

	virtual void update(char* data, int size) = 0;
	virtual char* getUpdateData(int* size) = 0;
};
