#pragma once

#include <vector>

class SyncedEntity {
	unsigned long lastSyncedAt;
	bool activelySynced;
	unsigned long entityKey;
	unsigned long syncFreq;


};