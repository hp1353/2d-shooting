#pragma once
#pragma comment(lib, "winmm.lib")
#include "gameNode.h"
#include "spaceShip.h"
#include "enemyManager.h"
#include "mmsystem.h"

class enemyManager;

class gameStudy : public gameNode
{
private:
	spaceShip* _ship;
	enemyManager* _enemyManager;
	image* enemys;
	image* _alphaImage;
	image* _alphatext;
	image* stage1text;
	image* boom1;
	image* boom2;
	image* enemy2;
	image* dead;
	image* midboss;
	image* boss;
	image* bosshp;
	
	RECT startrc;
	RECT erc;
	bool boom;
	bool ready;
	bool start;
	bool mciclose;
	bool mciclose2;
	int alphanum;
	int alphanum2;
	int loopx;
	bool alphanum22;
	int sbgmmove;
	float textmove;
	float stage1textmove;
	float boomcheck2move;
	float _x;
	float loop;
	
	bool sidemove;
	int emovey;
	int _index;
	int _count;
	int time;
	


	enemyManager* _em;

	RECT erc1;

	MCI_OPEN_PARMS      mciOpen; //파일을 로드

	MCI_PLAY_PARMS       mciPlay; //파일을 재생

	MCI_STATUS_PARMS   mciStatus; //파일의 상태

public:
	gameStudy();
	virtual ~gameStudy();
	float worldtime;
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	void setLink(enemyManager* em) { _em = em; }
	//void collision();

};