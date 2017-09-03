#pragma once

#include "gameNode.h"
#include "minion.h"
#include "bullets.h"
#include <vector>

class spaceShip;

class enemyManager : public gameNode
{
private:
	typedef vector<enemy*> vEnemy;
	typedef vector<enemy*>::iterator viEnemy;
	//spaceShip* _sS;

private:
	vEnemy _vMinion;
	viEnemy _viMinion;

	bullet* _bullet;

	spaceShip* _ship;
	image* enemy1;
	image* enemy2;
	image* boom2;
	image* player;
	bool alphanum22;
	int alphanum2;
	float boomcheck2move;
	bool boom;
	bool gi;
	float an;
	RECT rc1;
	RECT startrc;
	RECT removerc1;
	RECT removerc2;
	RECT removerc3;
	RECT removerc4;
	RECT boomrc1;
	RECT boomrc2;
	RECT bosshp;
	float worldtime;
	int emovex;
	int emovey;
	bool make1;
	bool make2;
	bool make3;
	bool make4;
	bool make5;
	bool make6;
	bool make7;
	bool makemidboss;
	bool makeboss;
	bool bspeed;
	float speed;
	int count;
	int time;
	int removenum;
	int boomcount;
	int removex;
	int removey;
	int soundcount;
	int count5;

public:
	enemyManager();
	~enemyManager();

	HRESULT init();
	void release();
	void update();
	void render();

	//미니언 셋업 해주자
	void setMinion();
	void minionBulletFire();
	void removeMinion(int arrayNum);

	void collision();

	inline vector<enemy*> getVMinion() { return _vMinion; }
	inline vector<enemy*>::iterator getVIMinion() { return _viMinion; }

	void setShipMemoryLink(spaceShip* ss) { _ship = ss; }
};

