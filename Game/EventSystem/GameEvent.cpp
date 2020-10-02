#include "GameEvent.h"
#include "../Entities/gameentity.h"
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

	*(((T*)v) + index) = value;
};

void GameEvent::SendToAll()
{
	if (!Server::GetInstance().IsStarted())
	{
		std::cout << "ERROR: Client cannot call SendToAll";
		return;
	}

	if (_sentToAll)
	{
		std::cout << "Cannot double send CreateEventPacket for event " << eventID << std::endl;
		return;
	}

	std::vector<char> data;
	switch (eventID)
	{
	case NULL_EVENT_ID:
		break;
	case CREATE_ENEMY_EVENT_ID:
		CreateEnemyEvent* ev = (CreateEnemyEvent*)this;
		Put<int>(&data, 0, ev->enemyEntityKey);
		Put<short>(&data, 4, ev->enemyID);
		Put<int>(&data, 6, ev->level);
		Put<float>(&data, 10, ev->posX);
		Put<float>(&data, 14, ev->posY);
	}

	CreateEventPacket packet = CreateEventPacket(ownerEntityKey, eventID, triggerTick, &data);

	Server::GetInstance().Send(ALL_PARTICIPANTS_ID, &packet);

	_sentToAll = true;
}
