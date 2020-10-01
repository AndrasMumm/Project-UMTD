#pragma once

#include <vector>
#include <string>

template <typename T>  class syncedData{

public:
	T value;
	int lastSyncedAt;
	int syncFreq;
	bool flag;

};



class SyncedEntity {
	
public:
	SyncedEntity(int entityKey);
	int* addSyncedData(syncedData<int>&);
	float* addSyncedData(syncedData<float>&);
	std::string* addSyncedData(syncedData<std::string>&); 

	void flagInt(int id);
	void flagFloat(int id);
	void flagString(int id);

	void clearAllFlags();
	const int entityKey;
	bool activelySynced = false;
	int syncFreq = 0;
	
private:

	
	std::vector<syncedData<int>> syncedInts;
	std::vector<syncedData<float>> syncedFloat;
	std::vector<syncedData<std::string>> syncedString;


};