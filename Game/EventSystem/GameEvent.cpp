#include "GameEvent.h"
#include "../gameentity.h"
#include "HelperAllEvents.h"
//Helper
template <class T>
void Put(std::vector<char>* v, int index, T value)
{
	size_t neededSize = index + sizeof(T);
	if (v->size() < neededSize)
	{
		v->resize(neededSize);
	}

	*(((T*)v->begin()) + index) = value;
};

void GameEvent::SendToAll(int entityKey)
{
	if (_sentToAll)
	{
		std::cout << "Cannot double send CreateEventPacket for event " << eventID << std::endl;
	}

	std::vector<char> data;
	switch (eventID)
	{
	case NULL_EVENT_ID:
		break;
	case CREATE_ENEMY_EVENT_ID:
		CreateEnemyEvent* ev = (CreateEnemyEvent*)this;
		//Put<int>(&data, 0, );
	}

	CreateEventPacket packet = CreateEventPacket(entityKey, eventID, triggerTick, &data);
	if (Server::GetInstance().IsStarted())
	{
		//We are server
		Server::GetInstance().Send(ALL_PARTICIPANTS_ID, &packet);
	}
	else
	{
		//We are client
		Client::GetInstance().Send(&packet);
	}

	_sentToAll = true;
}
