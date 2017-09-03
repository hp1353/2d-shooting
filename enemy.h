#pragma once

#include "gameNode.h"

class spaceShip;
class enemy : public gameNode 
{
protected:
	image* _imageName;		
	image* raybullet;
	RECT _rc;				
	RECT startrc;
	int _currentFrameX;		
	int _currentFrameY;		
	int testcount;
	float wolrdtimetick;
	int _count;			
	bool gi;
	int enemycount;
	int _fireCount;			
	int _rndFireCount;		
	int _fireCount1;
	int _fireCount2;
	int _fireCount3;
	int _fireCount4;
	int _fireCount5;
private:
	spaceShip* _ship;
public:
	enemy();
	~enemy();

	HRESULT init();
	HRESULT init(const char* imageName, POINT postion);
	void release();
	void update();
	void render();

	void move();
	void draw();
	
	bool bulletCountFire();
	bool bulletCountFire1();
	bool bulletCountFire2();
	bool bulletCountFire3();
	bool bulletCountFire4();
	inline RECT getRect() { return _rc; }

	void setShipMemoryLink(spaceShip* ss) { _ship = ss; }
};

