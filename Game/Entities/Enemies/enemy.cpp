#include "enemy.h"
#include "../../gamestate.h"
#include <DirectXMath.h>

using namespace DirectX;

Enemy::Enemy()
{
}

Enemy::Enemy(float speed, float hp, float size, float armor, float shield, float regen, float progress, float x, float y, int tile, int birth, int death, vint& path)
{
	syncedData<float>* sync_speed = new syncedData<float>();
	sync_speed->flag = true;
	sync_speed->lastSyncedAt = TICK;
	sync_speed->syncFreq = 50;
	sync_speed->value = speed;
	this->addSyncedData(sync_speed);
	this->speed = &sync_speed->value;


	syncedData<float>* sync_hp = new syncedData<float>();
	sync_hp->flag = true;
	sync_hp->lastSyncedAt = TICK;
	sync_hp->syncFreq = 50;
	sync_hp->value = hp;
	this->addSyncedData(sync_hp);
	this->hp = &sync_hp->value;

	syncedData<float>* sync_size = new syncedData<float>();
	sync_size->flag = true;
	sync_size->lastSyncedAt = TICK;
	sync_size->syncFreq = 50;
	sync_size->value = size;
	this->addSyncedData(sync_size);
	this->size = &sync_size->value;

	syncedData<float>* sync_armor = new syncedData<float>();
	sync_armor->flag = true;
	sync_armor->lastSyncedAt = TICK;
	sync_armor->syncFreq = 50;
	sync_armor->value = armor;
	this->addSyncedData(sync_armor);
	this->armor = &sync_armor->value;


	syncedData<float>* sync_shield = new syncedData<float>();
	sync_shield->flag = true;
	sync_shield->lastSyncedAt = TICK;
	sync_shield->syncFreq = 50;
	sync_shield->value = shield;
	this->addSyncedData(sync_shield);
	this->shield = &sync_shield->value;


	syncedData<float>* sync_regen = new syncedData<float>();
	sync_regen->flag = true;
	sync_regen->lastSyncedAt = TICK;
	sync_regen->syncFreq = 50;
	sync_regen->value = regen;
	this->addSyncedData(sync_regen);
	this->regen = &sync_regen->value;

	syncedData<float>* sync_progress = new syncedData<float>();
	sync_progress->flag = true;
	sync_progress->lastSyncedAt = TICK;
	sync_progress->syncFreq = 50;
	sync_progress->value = progress;
	this->addSyncedData(sync_progress);
	this->progress = &sync_progress->value;

	syncedData<float>* sync_x = new syncedData<float>();
	sync_x->flag = true;
	sync_x->lastSyncedAt = TICK;
	sync_x->syncFreq = 50;
	sync_x->value = x;
	this->addSyncedData(sync_x);
	this->x = &sync_x->value;

	syncedData<float>* sync_y = new syncedData<float>();
	sync_y->flag = true;
	sync_y->lastSyncedAt = TICK;
	sync_y->syncFreq = 50;
	sync_y->value = y;
	this->addSyncedData(sync_y);
	this->y = &sync_y->value;

	syncedData<int>* sync_tile = new syncedData<int>();
	sync_tile->flag = true;
	sync_tile->lastSyncedAt = TICK;
	sync_tile->syncFreq = 50;
	sync_tile->value = tile;
	this->addSyncedData(sync_tile);
	this->tile = &sync_tile->value;


	syncedData<int>* sync_birth = new syncedData<int>();
	sync_birth->flag = true;
	sync_birth->lastSyncedAt = TICK;
	sync_birth->syncFreq = 50;
	sync_birth->value = birth;
	this->addSyncedData(sync_birth);
	this->birth = &sync_birth->value;

	syncedData<int>* sync_death = new syncedData<int>();
	sync_death->flag = true;
	sync_death->lastSyncedAt = TICK;
	sync_death->syncFreq = 50;
	sync_death->value = death;
	this->addSyncedData(sync_death);
	this->death = &sync_death->value;

	syncedData<int>* sync_current_path = new syncedData<int>();
	sync_current_path->flag = true;
	sync_current_path->lastSyncedAt = TICK;
	sync_current_path->syncFreq = 0;
	sync_current_path->value = 0;
	this->addSyncedData(sync_current_path);
	this->current_path = &sync_current_path->value;

	path_sIndex = this->syncedInts.size();
	path_length = path.size();

	for (int& i : path) {

		syncedData<int>* sync_path = new syncedData<int>();
		sync_path->flag = true;
		sync_path->lastSyncedAt = TICK;
		sync_path->syncFreq = 0;
		sync_path->value = i;
		this->addSyncedData(sync_path);
	}

	*(this->tile) = GameState::getInstance().board.getTile(x, y)->tileID;
	GameState::getInstance().board.getTile(*(this->tile))->enemys.insert({ this->entityKey,this });

}

Enemy::Enemy(int entityKey, int level, float speed, float hp, float size, float armor, float shield, float regen, float x, float y, int birthTick, int typeID) : GameEntity(entityKey)
{
	syncedData<int>* sync_level = new syncedData<int>();
	sync_level->flag = true;
	sync_level->lastSyncedAt = TICK;
	sync_level->syncFreq = 50;
	sync_level->value = level;
	this->addSyncedData(sync_level);
	this->level = &sync_level->value;

	syncedData<float>* sync_speed = new syncedData<float>();
	sync_speed->flag = true;
	sync_speed->lastSyncedAt = TICK;
	sync_speed->syncFreq = 50;
	sync_speed->value = speed;
	this->addSyncedData(sync_speed);
	this->speed = &sync_speed->value;


	syncedData<float>* sync_hp = new syncedData<float>();
	sync_hp->flag = true;
	sync_hp->lastSyncedAt = TICK;
	sync_hp->syncFreq = 50;
	sync_hp->value = hp;
	this->addSyncedData(sync_hp);
	this->hp = &sync_hp->value;

	syncedData<float>* sync_size = new syncedData<float>();
	sync_size->flag = true;
	sync_size->lastSyncedAt = TICK;
	sync_size->syncFreq = 50;
	sync_size->value = size;
	this->addSyncedData(sync_size);
	this->size = &sync_size->value;

	syncedData<float>* sync_armor = new syncedData<float>();
	sync_armor->flag = true;
	sync_armor->lastSyncedAt = TICK;
	sync_armor->syncFreq = 50;
	sync_armor->value = armor;
	this->addSyncedData(sync_armor);
	this->armor = &sync_armor->value;


	syncedData<float>* sync_shield = new syncedData<float>();
	sync_shield->flag = true;
	sync_shield->lastSyncedAt = TICK;
	sync_shield->syncFreq = 50;
	sync_shield->value = shield;
	this->addSyncedData(sync_shield);
	this->shield = &sync_shield->value;


	syncedData<float>* sync_regen = new syncedData<float>();
	sync_regen->flag = true;
	sync_regen->lastSyncedAt = TICK;
	sync_regen->syncFreq = 50;
	sync_regen->value = regen;
	this->addSyncedData(sync_regen);
	this->regen = &sync_regen->value;

	syncedData<float>* sync_progress = new syncedData<float>();
	sync_progress->flag = true;
	sync_progress->lastSyncedAt = TICK;
	sync_progress->syncFreq = 50;
	sync_progress->value = 0;
	this->addSyncedData(sync_progress);
	this->progress = &sync_progress->value;

	syncedData<float>* sync_x = new syncedData<float>();
	sync_x->flag = true;
	sync_x->lastSyncedAt = TICK;
	sync_x->syncFreq = 50;
	sync_x->value = x;
	this->addSyncedData(sync_x);
	this->x = &sync_x->value;

	syncedData<float>* sync_y = new syncedData<float>();
	sync_y->flag = true;
	sync_y->lastSyncedAt = TICK;
	sync_y->syncFreq = 50;
	sync_y->value = y;
	this->addSyncedData(sync_y);
	this->y = &sync_y->value;

	syncedData<int>* sync_tile = new syncedData<int>();
	sync_tile->flag = true;
	sync_tile->lastSyncedAt = TICK;
	sync_tile->syncFreq = 50;
	sync_tile->value = GameState::getInstance().board.getTile(x, y)->tileID;
	this->addSyncedData(sync_tile);
	this->tile = &sync_tile->value;


	syncedData<int>* sync_birth = new syncedData<int>();
	sync_birth->flag = true;
	sync_birth->lastSyncedAt = TICK;
	sync_birth->syncFreq = 50;
	sync_birth->value = birthTick;
	this->addSyncedData(sync_birth);
	this->birth = &sync_birth->value;

	syncedData<int>* sync_death = new syncedData<int>();
	sync_death->flag = true;
	sync_death->lastSyncedAt = TICK;
	sync_death->syncFreq = 50;
	sync_death->value = -1;
	this->addSyncedData(sync_death);
	this->death = &sync_death->value;

	syncedData<int>* sync_current_path = new syncedData<int>();
	sync_current_path->flag = true;
	sync_current_path->lastSyncedAt = TICK;
	sync_current_path->syncFreq = 0;
	sync_current_path->value = -1;
	this->addSyncedData(sync_current_path);
	this->current_path = &sync_current_path->value;
}

int Enemy::getPath(int index)
{
	if (index > path_length) return -1;
	return this->syncedInts[path_sIndex + index]->value;
}

Tile* Enemy::getCurrentTile()
{
	return GameState::getInstance().board.getTile(syncedInts[path_sIndex + *current_path]->value);
}
Tile* Enemy::getNextTile()
{
	return GameState::getInstance().board.getTile(syncedInts[path_sIndex + *current_path + 1]->value);
}

void Enemy::Update(int dt) {

	eventManager.Update(dt);
	GameState& game = GameState::getInstance();
	Board& board = game.board;

	Tile* current = board.getTile(*tile);

	// movement
	if (*current_path != -1 && *speed != 0) {
		XMVECTOR pos = XMVectorSet(*x, *y, 0, 0);
		XMVECTOR target = XMVectorSet(getNextTile()->x + .5f, getNextTile()->y + .5f, 0, 0);
		XMVECTOR delta = XMVectorSubtract(target, pos);
		XMVECTOR dir = XMVector3Normalize(delta);

		vector<XMVECTOR> forces;

		for (auto i : current->enemys)
		{
			Enemy* e = i.second;
			XMVECTOR pos2 = XMVectorSet(*(e->x), *(e->x), 0, 0);
			XMVECTOR delta = XMVectorSubtract(pos, pos2);
			float norm2 = XMVectorGetX(XMVector2Length(delta));
			XMVECTOR dir = XMVector3Normalize(delta);
			if (norm2 == 0) {
				norm2 = 0.01f;
				dir = XMVectorSet(1, 0, 0, 0);
			}
			XMVECTOR force = dir * (1 / (norm2 * norm2));

			forces.push_back(force);
		}

		XMVECTOR force_dir = dir;
		for (XMVECTOR& f : forces) {
			force_dir = XMVectorAdd(force_dir, XMVectorScale(f, 1.0f));
		}

		XMVECTOR move_dir = XMVector3Normalize(force_dir);

		*x += XMVectorGetX(move_dir) * (*speed) * dt;
		*y += XMVectorGetY(move_dir) * (*speed) * dt;

	}

	updateTile();
}

void Enemy::updateTile()
{
	GameState& game = GameState::getInstance();
	Board& board = game.board;
	Tile* current = board.getTile(*tile);

	if ((int)(*x) != current->x || (int)(*y) != current->y)
	{
		Tile* willBeNext = GameState::getInstance().board.getTile(*x, *y);

		current->enemys.erase(this->entityKey);
		willBeNext->enemys.insert({ this->entityKey, this });

		if (getNextTile()->tileID == willBeNext->tileID) {
			(*current_path)++;
			if (*current_path >= path_length - 1) {
				*current_path = 0;
			}
		}

		*tile = willBeNext->tileID;

	}

}
