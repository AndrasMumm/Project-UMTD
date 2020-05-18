#pragma once
#include "SyncObject.h"

class SyncFloat : SyncObject
{
private:
	float* dataPtr_;
public:
	SyncFloat(float*);

	void update(Packet& packet) override;
	Packet& getUpdateData() override;
};
