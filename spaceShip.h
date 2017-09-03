#pragma once

#include "gameNode.h"
#include "bullets.h"
#include "gameStudy.h"
class enemyManager;

class spaceShip : public gameNode
{
	image* _raystand;
	image* _raymove;
	image* boom1;
	image* boom2;
	missile* _missile;
	image* dead;
	image* bosshp;
	//image* bosshp2;
	RECT rc;
	enemyManager* _em;
	image* bossboom;
	image* bossmagic;
	image* die;
	image* player;
	image* null;
	image* boombackground;
	image* fuckingboom;
	image* boompoint;
	image* end;
public:
	spaceShip();
	~spaceShip();

	HRESULT init();
	void release();
	void update();
	void render();
	RECT midbossrc;
	int loopx;
	int _count;
	int _index;
	int _count1;
	int _index1;
	int count;
	int index;
	int _count2;
	int _index2;
	int alphanum;
	int alphanum2;
	int shotcount;
	int xnum;
	int ynum;
	int bosshpnum;
	int bosshpnum2;
	int bossboomnum;
	int boomnum;
	int alphanum3;
	int alphanum4;
	int rayx;
	int rayy;
	bool sidemove;
	bool isRight;
	bool boomcheck;
	bool boomcheck2;
	bool boomcheck3;
	bool boomcheck4;
	bool deadcheck;
	bool die1;
	bool diecount1;
	bool diecount2;
	bool null1;
	bool null2;
	bool null3;
	int i = 0;
	int bugx;
	int bugy;
	int score; 
	int diecount;
	int boombackgroundcount;
	bool ending;
	int count5;
	void removeMissile(int arrNum);

	void collision();

	void setEmMemoryLink(enemyManager* em) { _em = em; }

	missile* getMissile() { return _missile; }

	image* getShipImage() { return _raystand; }
};

