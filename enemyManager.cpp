#include "stdafx.h"
#include "enemyManager.h"
#include "spaceShip.h"

enemyManager::enemyManager()
{
}


enemyManager::~enemyManager()
{
}

HRESULT enemyManager::init()
{
	_bullet = new bullet;
	_bullet->init("bullet", 10, 0);
	boom2 = new image;
	boom2->init("image/boom2.bmp", 146, 288, true, RGB(255, 242, 0));
	boomcheck2move = 320.f;
	alphanum2 = 1;
	alphanum22 = false;
	boom = false;
	make1 = false;
	make2 = false;
	make3 = false;
	make4 = false;
	make5 = false;
	make6 = false;
	make7 = false;
	removex = 0;
	removey = 0;
	gi = false;
	makemidboss = false;
	bspeed = false;
	time = 0;
	speed = 3.1f;
	an = 0.f;
	boomcount = 0;
	soundcount = 0;
	removenum = 4990;
	removerc1 = RectMakeCenter(WINSIZEX / 5 * 3+500, 240, 1000, WINSIZEY);
	removerc2 = RectMakeCenter(192, WINSIZEY +removenum, WINSIZEX / 5 * 3, 10000);
	removerc3 = RectMakeCenter(0, 240, 10, WINSIZEY);
	removerc4 = RectMakeCenter(195, 0, WINSIZEX / 5 * 3, 10);
	
	bosshp = RectMakeCenter(10, 10, 340, 10);
	count5 = 0;

	return S_OK;
}

void enemyManager::release()
{
	for(_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
	{
		SAFE_DELETE((*_viMinion));
	}
	boom2->release();
	SAFE_DELETE(boom2);
	_vMinion.clear();
}

void enemyManager::update()
{
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->update();
	}
	
	
	//if (KEYMANAGER->isOnceDown(VK_CONTROL))
	//{
	//	//ÆøÅº
	//	/*boomcount++;
	//	removerc2.top -= 10;
	//	if (boomcount > 1000)
	//	{
	//		boomcount = 0;
	//		removerc2.top = removerc2.bottom - 10000;
	//	}*/
	//	
	//}

	//ÆøÅº ÇÁ·¹ÀÓÀÌ¹ÌÁö¿¡ ¸Â°Ô ·ºÆ®Á¶Àý
	if (_ship->boomcheck)
	{
		boomrc1 = RectMakeCenter(_ship->rayx+20,_ship->rayy, 200, 200);
	}
	
	if (_ship->boomcheck &&soundcount == 0)
	{
		sndPlaySoundA("sound/beam.wav", SND_ASYNC | SND_NODEFAULT /*| SND_LOOP*/); //ÆøÅº¼Ò¸®
		soundcount = 1;
	}
	else if (!_ship->boomcheck && soundcount != 0)
	{
		soundcount = 0;
	}
	
	if (!_ship->boomcheck3 && _ship->i <= 1 && _ship->_index2<3 )
	{
		boomrc1 = RectMakeCenter(_ship->rayx + 20, _ship->rayy, 0, 0);
	}
	if (_ship->boomcheck4 && _ship->i >= 1 && _ship->_index2 > 3)
	{
		//boomrc1 = RectMakeCenter(WINSIZEX / 10 * 3 + 5, WINSIZEY - 50, 100, 100);
		//boomrc2 = RectMakeCenter(WINSIZEX / 10 * 3 + 5, WINSIZEY - 300, 80, 600);
		boomrc1 = RectMakeCenter(_ship->rayx + 20,_ship->rayy, 100, 100);
		boomrc2 = RectMakeCenter(_ship->rayx + 20,_ship->rayy-300, 80, 600);
	}
	if (_ship->i ==2 && _ship->_index2>14)
	{
		boomrc2 = RectMakeCenter(_ship->rayx + 20, _ship->rayy - 300, 0, 0);
	}
	if (!_ship->i==2 && _ship->_index2>32)
	{
		boomrc1 = RectMakeCenter(_ship->rayx + 20, _ship->rayy, 0, 0);
		
	}
	///////////////

	if (KEYMANAGER->isStayDown(VK_LEFT)&&boomrc1.left>0)
	{
		boomrc1.left -= 2;
		boomrc1.right -= 2;
		boomrc2.left -= 2;
		boomrc2.right -= 2;

	}
	if (KEYMANAGER->isStayDown(VK_RIGHT)&&boomrc1.right<WINSIZEX/5*3)
	{
		boomrc1.right += 2;
		boomrc1.left += 2;
		boomrc2.left += 2;
		boomrc2.right += 2;
	}
	if (KEYMANAGER->isStayDown(VK_DOWN)&&boomrc1.bottom<WINSIZEY)
	{
		boomrc1.top += 2;
		boomrc1.bottom += 2;
		boomrc2.top += 2;
		boomrc2.bottom += 2;
	}
	if (KEYMANAGER->isStayDown(VK_UP)&&boomrc1.top>0)
	{
		boomrc1.top -= 2;
		boomrc1.bottom -= 2;
		boomrc2.top -= 2;
		boomrc2.bottom -= 2;
	}
	if (TIMEMANAGER->getWorldTime() > 90)
	{
		speed -= 0.1f;
		if (speed < 1.f)speed = 3.1f;
		
	}
	time++;

	minionBulletFire();

	_bullet->update();

	collision();

	setMinion();

	
	
}

void enemyManager::render()
{
	
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->render();
	}
	if (_ship->die1)
	{
		removerc2.top -= 10;

	}
	else
	{
		removerc2.top = removerc2.bottom - 10000;
	}
	//Rectangle(getMemDC(), removerc1.left, removerc1.top, removerc1.right, removerc1.bottom);
	//Rectangle(getMemDC(), removerc2.left, removerc2.top, removerc2.right, removerc2.bottom);
	//Rectangle(getMemDC(), removerc3.left, removerc3.top, removerc3.right, removerc3.bottom);
	//Rectangle(getMemDC(), removerc4.left, removerc4.top, removerc4.right, removerc4.bottom);
	//Rectangle(getMemDC(), boomrc1.left, boomrc1.top, boomrc1.right, boomrc1.bottom);
	//Rectangle(getMemDC(), boomrc2.left, boomrc2.top, boomrc2.right, boomrc2.bottom);
	_bullet->render();

}

void enemyManager::setMinion()
{
	
		/*for (int j = 0; j < 4; j++)
		{
			enemy* ufo;
			ufo = new minion;
			ufo->init("ufo", pointMake(80 + j * 80, 80 ));

			_vMinion.push_back(ufo);
		}*/
	if (TIMEMANAGER->getWorldTime() > 12 && !make1)
	{
		enemy* enemys;

		enemys = new minion;
		enemys->init("enemys", pointMake(360, -20));

		_vMinion.push_back(enemys);


		enemys = new minion;
		enemys->init("enemys", pointMake(330, -20));

		_vMinion.push_back(enemys);

		enemys = new minion;
		enemys->init("enemys", pointMake(360, -60));

		_vMinion.push_back(enemys);

		enemys = new minion;
		enemys->init("enemys", pointMake(330, -60));

		_vMinion.push_back(enemys);
		make1 = true;
	}
	if (TIMEMANAGER->getWorldTime() > 18 && !make2)
	{
		enemy* enemys;

		enemys = new minion;
		enemys->init("enemys", pointMake(60, -20));

		_vMinion.push_back(enemys);


		enemys = new minion;
		enemys->init("enemys", pointMake(30, -20));

		_vMinion.push_back(enemys);

		enemys = new minion;
		enemys->init("enemys", pointMake(60, -60));

		_vMinion.push_back(enemys);

		enemys = new minion;
		enemys->init("enemys", pointMake(30, -60));

		_vMinion.push_back(enemys);
		make2 = true;
	}
	if (TIMEMANAGER->getWorldTime() > 24 && !make3)
	{
		enemy* enemys;

		enemys = new minion;
		enemys->init("enemys", pointMake(360, -20));

		_vMinion.push_back(enemys);


		enemys = new minion;
		enemys->init("enemys", pointMake(330, -20));

		_vMinion.push_back(enemys);

		enemys = new minion;
		enemys->init("enemys", pointMake(360, -60));

		_vMinion.push_back(enemys);

		enemys = new minion;
		enemys->init("enemys", pointMake(330, -60));

		_vMinion.push_back(enemys);
		make3 = true;
	}
	if (TIMEMANAGER->getWorldTime() > 30 && !make4)
	{
		enemy* enemys;

		enemys = new minion;
		enemys->init("enemys", pointMake(60, -20));

		_vMinion.push_back(enemys);


		enemys = new minion;
		enemys->init("enemys", pointMake(30, -20));

		_vMinion.push_back(enemys);

		enemys = new minion;
		enemys->init("enemys", pointMake(60, -60));

		_vMinion.push_back(enemys);

		enemys = new minion;
		enemys->init("enemys", pointMake(30, -60));

		_vMinion.push_back(enemys);
		make4 = true;
	}
	if (TIMEMANAGER->getWorldTime() > 36 && !make5 )
	{
		_bullet->init("bullet", 10, 600);
		enemy* enemys;
		
		enemys = new minion;
		enemys->init("enemys", pointMake(130, -20));

		_vMinion.push_back(enemys);


		enemys = new minion;
		enemys->init("enemys", pointMake(160, -30));

		_vMinion.push_back(enemys);

		enemys = new minion;
		enemys->init("enemys", pointMake(190, -40));

		_vMinion.push_back(enemys);

		enemys = new minion;
		enemys->init("enemys", pointMake(220, -50));

		_vMinion.push_back(enemys);


		enemys = new minion;
		enemys->init("enemys", pointMake(250, -50));

		_vMinion.push_back(enemys);


		enemys = new minion;
		enemys->init("enemys", pointMake(280, -40));

		_vMinion.push_back(enemys);


		enemys = new minion;
		enemys->init("enemys", pointMake(310, -30));

		_vMinion.push_back(enemys);


		enemys = new minion;
		enemys->init("enemys", pointMake(340, -20));

		_vMinion.push_back(enemys);
		
		make5 = true;
	}
	if (TIMEMANAGER->getWorldTime() > 42 &&TIMEMANAGER->getWorldTime()<45)
	{
		_bullet->init("bullet", 0, 0);
	}
	if (TIMEMANAGER->getWorldTime() > 45 && !makemidboss)
	{
		_bullet->init("bullet", 200, 600);
		enemy* midboss;
		midboss = new minion;
		midboss->init("midboss", pointMake(200, 10));

		_vMinion.push_back(midboss);
		makemidboss = true;
	}
	if (TIMEMANAGER->getWorldTime() > 65 && !make7 &TIMEMANAGER->getWorldTime()<80)
	{
		_bullet->init("bullet", 0, 0);
		enemy* enemy2;
		enemy2 = new minion;
		enemy2->init("enemy2", pointMake(WINSIZEX / 5 * 3 - 30, -20 ));
		_vMinion.push_back(enemy2);

		enemy2 = new minion;
		enemy2->init("enemy2", pointMake(WINSIZEX / 5 * 3 - 60, -40));
		_vMinion.push_back(enemy2);

		enemy2 = new minion;
		enemy2->init("enemy2", pointMake(WINSIZEX / 5 * 3 - 90, -60));
		_vMinion.push_back(enemy2);

		enemy2 = new minion;
		enemy2->init("enemy2", pointMake(WINSIZEX / 5 * 3 - 120, -80));
		_vMinion.push_back(enemy2);

		enemy2 = new minion;
		enemy2->init("enemy2", pointMake(WINSIZEX / 5 * 3 - 150, -100));
		_vMinion.push_back(enemy2);

		enemy2 = new minion;
		enemy2->init("enemy2", pointMake(WINSIZEX / 5 * 3 - 180, -120));
		_vMinion.push_back(enemy2);

		enemy2 = new minion;
		enemy2->init("enemy2", pointMake(WINSIZEX / 5 * 3 - 210, -140));
		_vMinion.push_back(enemy2);

		enemy2 = new minion;
		enemy2->init("enemy2", pointMake(WINSIZEX / 5 * 3 - 240, -160));
		_vMinion.push_back(enemy2);

		enemy2 = new minion;
		enemy2->init("enemy2", pointMake(WINSIZEX / 5 * 3 - 270, -180));
		_vMinion.push_back(enemy2);

		enemy2 = new minion;
		enemy2->init("enemy2", pointMake(WINSIZEX / 5 * 3 - 300, -200));
		_vMinion.push_back(enemy2);

		enemy2 = new minion;
		enemy2->init("enemy2", pointMake(WINSIZEX / 5 * 3 - 330, -220));
		_vMinion.push_back(enemy2);

		enemy2 = new minion;
		enemy2->init("enemy2", pointMake(WINSIZEX / 5 * 3 - 360, -240));
		_vMinion.push_back(enemy2);
		//ÇÑÁÙ

		enemy2 = new minion;
		enemy2->init("enemy2", pointMake(WINSIZEX / 5 * 3 - 330, -260));
		_vMinion.push_back(enemy2);
		enemy2 = new minion;
		enemy2->init("enemy2", pointMake(WINSIZEX / 5 * 3 - 300, -280));
		_vMinion.push_back(enemy2);

		enemy2 = new minion;
		enemy2->init("enemy2", pointMake(WINSIZEX / 5 * 3 - 270, -300));
		_vMinion.push_back(enemy2);
		enemy2 = new minion;
		enemy2->init("enemy2", pointMake(WINSIZEX / 5 * 3 - 240, -320));
		_vMinion.push_back(enemy2);
		enemy2 = new minion;
		enemy2->init("enemy2", pointMake(WINSIZEX / 5 * 3 - 210, -340));
		_vMinion.push_back(enemy2);
		enemy2 = new minion;
		enemy2->init("enemy2", pointMake(WINSIZEX / 5 * 3 - 180, -360));
		_vMinion.push_back(enemy2);
		enemy2 = new minion;
		enemy2->init("enemy2", pointMake(WINSIZEX / 5 * 3 - 150, -380));
		_vMinion.push_back(enemy2);

		enemy2 = new minion;
		enemy2->init("enemy2", pointMake(WINSIZEX / 5 * 3 - 120, -400));
		_vMinion.push_back(enemy2);
		enemy2 = new minion;
		enemy2->init("enemy2", pointMake(WINSIZEX / 5 * 3 - 90, -420));
		_vMinion.push_back(enemy2);
		enemy2 = new minion;
		enemy2->init("enemy2", pointMake(WINSIZEX / 5 * 3 - 60, -440));
		_vMinion.push_back(enemy2);
		enemy2 = new minion;
		enemy2->init("enemy2", pointMake(WINSIZEX / 5 * 3 - 30, -460));
		_vMinion.push_back(enemy2);

		for (int i = 0; i < 12; i++)
		{
			enemy2 = new minion;
			enemy2->init("enemy2", pointMake(WINSIZEX / 5 * 3 - 30*i, -460 -20*i));
			_vMinion.push_back(enemy2);

		}



		make7 = true;
	}
	if (TIMEMANAGER->getWorldTime() > 87 && !makeboss)
	{
		_bullet->init("bullet", 300, 600);
		enemy* boss;
		boss = new minion;
		boss->init("boss", pointMake(200, 10));

		_vMinion.push_back(boss);
		makeboss = true;
	}
	/*
	if (time > 4000 && !make6)
	{
		_bullet->init("bullet", 10, 0);
		enemy* enemy2;
		enemy2 = new minion;
		enemy2->init("enemy2", pointMake(WINSIZEX / 5 * 3-90, 150));
		_vMinion.push_back(enemy2);
		enemy2 = new minion;
		enemy2->init("enemy2", pointMake(WINSIZEX / 5 * 3-60, 150));
		_vMinion.push_back(enemy2);
		enemy2 = new minion;
		enemy2->init("enemy2", pointMake(WINSIZEX / 5 * 3-30, 150));
		_vMinion.push_back(enemy2);
		enemy2 = new minion;
		enemy2->init("enemy2", pointMake(WINSIZEX / 5 * 3, 150));
		_vMinion.push_back(enemy2);
		make6 = true;
	}*/
}

void enemyManager::minionBulletFire()
{
	
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
	{
		if ((*_viMinion)->bulletCountFire())
		{
			if (TIMEMANAGER->getWorldTime() < 45)
			{
				RECT rc = (*_viMinion)->getRect();
				_bullet->fire(rc.left + (rc.right - rc.left) / 2,
					rc.bottom + (rc.top - rc.bottom) / 2 + 30,
					MY_UTIL::getAngle(rc.left + (rc.right - rc.left) / 2, rc.bottom + (rc.top - rc.bottom) / 2 + 30, _ship->getShipImage()->getCenterX(), _ship->getShipImage()->getCenterY()), 2.0f);

			}
			if (TIMEMANAGER->getWorldTime() > 45  && TIMEMANAGER->getWorldTime()<65)
			{
				RECT rc = (*_viMinion)->getRect();
				_bullet->fire(rc.left + (rc.right - rc.left) / 2,
					rc.bottom + (rc.top - rc.bottom) / 2 + 20,
					1.84f, 1.3f);
				RECT rc1 = (*_viMinion)->getRect();
				_bullet->fire(rc.left + (rc.right - rc.left) / 2,
					rc.bottom + (rc.top - rc.bottom) / 2 + 20,
					1.84f, 1.1f);
				RECT rc2 = (*_viMinion)->getRect();
				_bullet->fire(rc.left + (rc.right - rc.left) / 2,
					rc.bottom + (rc.top - rc.bottom) / 2 + 20,
					1.84f, 0.9f);
				RECT rc3 = (*_viMinion)->getRect();
				_bullet->fire(rc.left + (rc.right - rc.left) / 2,
					rc.bottom + (rc.top - rc.bottom) / 2 + 20,
					1.84f, 0.7f);
				RECT rc4 = (*_viMinion)->getRect();
				_bullet->fire(rc.left + (rc.right - rc.left) / 2,
					rc.bottom + (rc.top - rc.bottom) / 2 + 20,
					1.84f, 0.5f);
				RECT rc5 = (*_viMinion)->getRect();
				_bullet->fire(rc.left + (rc.right - rc.left) / 2,
					rc.bottom + (rc.top - rc.bottom) / 2 + 20,
					2.84f, 1.3f);
				RECT rc6 = (*_viMinion)->getRect();
				_bullet->fire(rc.left + (rc.right - rc.left) / 2,
					rc.bottom + (rc.top - rc.bottom) / 2 + 20,
					2.84f, 1.1f);
				RECT rc7 = (*_viMinion)->getRect();
				_bullet->fire(rc.left + (rc.right - rc.left) / 2,
					rc.bottom + (rc.top - rc.bottom) / 2 + 20,
					2.84f, 0.9f);
				RECT rc8 = (*_viMinion)->getRect();
				_bullet->fire(rc.left + (rc.right - rc.left) / 2,
					rc.bottom + (rc.top - rc.bottom) / 2 + 20,
					2.84f, 0.7f);
				RECT rc9 = (*_viMinion)->getRect();
				_bullet->fire(rc.left + (rc.right - rc.left) / 2,
					rc.bottom + (rc.top - rc.bottom) / 2 + 20,
					2.84f, 0.5f);
				RECT rc10 = (*_viMinion)->getRect();
				_bullet->fire(rc.left + (rc.right - rc.left) / 2,
					rc.bottom + (rc.top - rc.bottom) / 2 + 20,
					3.4f, 1.3f);
				RECT rc11 = (*_viMinion)->getRect();
				_bullet->fire(rc.left + (rc.right - rc.left) / 2,
					rc.bottom + (rc.top - rc.bottom) / 2 + 20,
					3.4f, 1.1f);
				RECT rc12 = (*_viMinion)->getRect();
				_bullet->fire(rc.left + (rc.right - rc.left) / 2,
					rc.bottom + (rc.top - rc.bottom) / 2 + 20,
					3.4f, 0.9f);
				RECT rc13 = (*_viMinion)->getRect();
				_bullet->fire(rc.left + (rc.right - rc.left) / 2,
					rc.bottom + (rc.top - rc.bottom) / 2 + 20,
					3.4f, 0.7f);
				RECT rc14 = (*_viMinion)->getRect();
				_bullet->fire(rc.left + (rc.right - rc.left) / 2,
					rc.bottom + (rc.top - rc.bottom) / 2 + 20,
					3.4f, 0.5f);
				RECT rc15 = (*_viMinion)->getRect();
				_bullet->fire(rc.left + (rc.right - rc.left) / 2,
					rc.bottom + (rc.top - rc.bottom) / 2 + 20,
					4.4f, 1.3f);
				RECT rc16 = (*_viMinion)->getRect();
				_bullet->fire(rc.left + (rc.right - rc.left) / 2,
					rc.bottom + (rc.top - rc.bottom) / 2 + 20,
					4.4f, 1.1f);
				RECT rc17 = (*_viMinion)->getRect();
				_bullet->fire(rc.left + (rc.right - rc.left) / 2,
					rc.bottom + (rc.top - rc.bottom) / 2 + 20,
					4.4f, 0.9f);
				RECT rc18 = (*_viMinion)->getRect();
				_bullet->fire(rc.left + (rc.right - rc.left) / 2,
					rc.bottom + (rc.top - rc.bottom) / 2 + 20,
					4.4f, 0.7f);
				RECT rc19 = (*_viMinion)->getRect();
				_bullet->fire(rc.left + (rc.right - rc.left) / 2,
					rc.bottom + (rc.top - rc.bottom) / 2 + 20,
					4.4f, 0.5f);

				RECT rc20 = (*_viMinion)->getRect();
				_bullet->fire(rc.left + (rc.right - rc.left) / 2,
					rc.bottom + (rc.top - rc.bottom) / 2 + 20,
					4.95f, 1.3f);
				RECT rc21 = (*_viMinion)->getRect();
				_bullet->fire(rc.left + (rc.right - rc.left) / 2,
					rc.bottom + (rc.top - rc.bottom) / 2 + 20,
					4.95f, 1.1f);
				RECT rc22 = (*_viMinion)->getRect();
				_bullet->fire(rc.left + (rc.right - rc.left) / 2,
					rc.bottom + (rc.top - rc.bottom) / 2 + 20,
					4.95f, 0.9f);
				RECT rc23 = (*_viMinion)->getRect();
				_bullet->fire(rc.left + (rc.right - rc.left) / 2,
					rc.bottom + (rc.top - rc.bottom) / 2 + 20,
					4.95f, 0.7f);
				RECT rc24 = (*_viMinion)->getRect();
				_bullet->fire(rc.left + (rc.right - rc.left) / 2,
					rc.bottom + (rc.top - rc.bottom) / 2 + 20,
					4.95f, 0.5f);
				RECT rc25 = (*_viMinion)->getRect();
				_bullet->fire(rc.left + (rc.right - rc.left) / 2,
					rc.bottom + (rc.top - rc.bottom) / 2 + 20,
					5.95f, 1.3f);
				RECT rc26 = (*_viMinion)->getRect();
				_bullet->fire(rc.left + (rc.right - rc.left) / 2,
					rc.bottom + (rc.top - rc.bottom) / 2 + 20,
					5.95f, 1.1f);
				RECT rc27 = (*_viMinion)->getRect();
				_bullet->fire(rc.left + (rc.right - rc.left) / 2,
					rc.bottom + (rc.top - rc.bottom) / 2 + 20,
					5.95f, 0.9f);
				RECT rc28 = (*_viMinion)->getRect();
				_bullet->fire(rc.left + (rc.right - rc.left) / 2,
					rc.bottom + (rc.top - rc.bottom) / 2 + 20,
					5.95f, 0.7f);
				RECT rc29 = (*_viMinion)->getRect();
				_bullet->fire(rc.left + (rc.right - rc.left) / 2,
					rc.bottom + (rc.top - rc.bottom) / 2 + 20,
					5.95f, 0.5f);

				RECT rc30 = (*_viMinion)->getRect();
				_bullet->fire(rc.left + (rc.right - rc.left) / 2,
					rc.bottom + (rc.top - rc.bottom) / 2 + 20,
					7.5f, 1.3f);
				RECT rc31 = (*_viMinion)->getRect();
				_bullet->fire(rc.left + (rc.right - rc.left) / 2,
					rc.bottom + (rc.top - rc.bottom) / 2 + 20,
					7.5f, 1.1f);
				RECT rc32 = (*_viMinion)->getRect();
				_bullet->fire(rc.left + (rc.right - rc.left) / 2,
					rc.bottom + (rc.top - rc.bottom) / 2 + 20,
					7.5f, 0.9f);
				RECT rc33 = (*_viMinion)->getRect();
				_bullet->fire(rc.left + (rc.right - rc.left) / 2,
					rc.bottom + (rc.top - rc.bottom) / 2 + 20,
					7.5f, 0.7f);
				RECT rc34 = (*_viMinion)->getRect();
				_bullet->fire(rc.left + (rc.right - rc.left) / 2,
					rc.bottom + (rc.top - rc.bottom) / 2 + 20,
					7.5f, 0.5f);
				RECT rc35 = (*_viMinion)->getRect();
				_bullet->fire(rc.left + (rc.right - rc.left) / 2,
					rc.bottom + (rc.top - rc.bottom) / 2 + 20,
					6.5f, 1.3f);
				RECT rc36 = (*_viMinion)->getRect();
				_bullet->fire(rc.left + (rc.right - rc.left) / 2,
					rc.bottom + (rc.top - rc.bottom) / 2 + 20,
					6.5f, 1.1f);
				RECT rc37 = (*_viMinion)->getRect();
				_bullet->fire(rc.left + (rc.right - rc.left) / 2,
					rc.bottom + (rc.top - rc.bottom) / 2 + 20,
					6.5f, 0.9f);
				RECT rc38 = (*_viMinion)->getRect();
				_bullet->fire(rc.left + (rc.right - rc.left) / 2,
					rc.bottom + (rc.top - rc.bottom) / 2 + 20,
					6.5f, 0.7f);
				RECT rc39 = (*_viMinion)->getRect();
				_bullet->fire(rc.left + (rc.right - rc.left) / 2,
					rc.bottom + (rc.top - rc.bottom) / 2 + 20,
					6.5f, 0.5f);

				/*RECT rc1 = (*_viMinion)->getRect();
				_bullet->fire(rc.left + (rc.right - rc.left) / 2,
					rc.bottom + (rc.top - rc.bottom) / 2 + 20,
					an += 0.21f, 1.f);*/
				for (float i = 0.2; i < 6.28f; i += 0.2f)
				{
					RECT rc40 = (*_viMinion)->getRect();
					_bullet->fire(rc.left + (rc.right - rc.left) / 2,
						rc.bottom + (rc.top - rc.bottom) / 2 + 20,
						i, 2*i);
				}
			}
			if (TIMEMANAGER->getWorldTime() > 90 && _ship->bosshpnum <280 ) //º¸½ºÅº¸·ÆÐÅÏ
			{
				for (int i = 1; i < 20; i++)
				{
					RECT rc = (*_viMinion)->getRect();
					_bullet->fire(rc.left + (rc.right - rc.left) / 2,
						rc.bottom + (rc.top - rc.bottom) / 2 + 20,
						2.5f+i*0.2f, speed);
				}
				RECT rc = (*_viMinion)->getRect();
				_bullet->fire(rc.left + (rc.right - rc.left) / 2,
					rc.bottom + (rc.top - rc.bottom) / 2 + 20,
					4.1f  , 1.5f);
				RECT rc2 = (*_viMinion)->getRect();
				_bullet->fire(rc.left + (rc.right - rc.left) / 2,
					rc.bottom + (rc.top - rc.bottom) / 2 + 20,
					4.2f, 2.4f);
				RECT rc3 = (*_viMinion)->getRect();
				_bullet->fire(rc.left + (rc.right - rc.left) / 2,
					rc.bottom + (rc.top - rc.bottom) / 2 + 20,
					4.3f, 0.7f);
				RECT rc4 = (*_viMinion)->getRect();
				_bullet->fire(rc.left + (rc.right - rc.left) / 2,
					rc.bottom + (rc.top - rc.bottom) / 2 + 20,
					4.4f, 3.1f);
				RECT rc5 = (*_viMinion)->getRect();
				_bullet->fire(rc.left + (rc.right - rc.left) / 2,
					rc.bottom + (rc.top - rc.bottom) / 2 + 20,
					4.5f, 0.9f);
				RECT rc6 = (*_viMinion)->getRect();
				_bullet->fire(rc.left + (rc.right - rc.left) / 2,
					rc.bottom + (rc.top - rc.bottom) / 2 + 20,
					4.6f, 1.9f);
				RECT rc7 = (*_viMinion)->getRect();
				_bullet->fire(rc.left + (rc.right - rc.left) / 2,
					rc.bottom + (rc.top - rc.bottom) / 2 + 20,
					4.7f, 1.1f);
				RECT rc8 = (*_viMinion)->getRect();
				_bullet->fire(rc.left + (rc.right - rc.left) / 2,
					rc.bottom + (rc.top - rc.bottom) / 2 + 20,
					4.8f, 2.8f);
				RECT rc9 = (*_viMinion)->getRect();
				_bullet->fire(rc.left + (rc.right - rc.left) / 2,
					rc.bottom + (rc.top - rc.bottom) / 2 + 20,
					4.9f, 3.3f);
				RECT rc10 = (*_viMinion)->getRect();
				_bullet->fire(rc.left + (rc.right - rc.left) / 2,
					rc.bottom + (rc.top - rc.bottom) / 2 + 20,
					5.0f, 2.1f);
				RECT rc11 = (*_viMinion)->getRect();
				_bullet->fire(rc.left + (rc.right - rc.left) / 2,
					rc.bottom + (rc.top - rc.bottom) / 2 + 20,
					5.1f, 1.2f);
			}
			
			/*if (_ship->bosshpnum >= 280 && _ship->bosshpnum <340)
			{
				RECT rc = (*_viMinion)->getRect();
				_bullet->fire(rc.left + (rc.right - rc.left) / 2,
					rc.bottom + (rc.top - rc.bottom) / 2 + 30,
					MY_UTIL::getAngle(rc.left + (rc.right - rc.left) / 2, rc.bottom + (rc.top - rc.bottom) / 2 + 30, _ship->getShipImage()->getCenterX(), _ship->getShipImage()->getCenterY()), 1.5f);
				RECT rc2 = (*_viMinion)->getRect();
				_bullet->fire(rc.left + (rc.right - rc.left) / 2,
					rc.bottom + (rc.top - rc.bottom) / 2 + 30,
					MY_UTIL::getAngle(rc.left + (rc.right - rc.left) / 2, rc.bottom + (rc.top - rc.bottom) / 2 + 30, _ship->getShipImage()->getCenterX(), _ship->getShipImage()->getCenterY()), 1.6f);

				RECT rc3 = (*_viMinion)->getRect();
				_bullet->fire(rc.left + (rc.right - rc.left) / 2,
					rc.bottom + (rc.top - rc.bottom) / 2 + 30,
					MY_UTIL::getAngle(rc.left + (rc.right - rc.left) / 2, rc.bottom + (rc.top - rc.bottom) / 2 + 30, _ship->getShipImage()->getCenterX(), _ship->getShipImage()->getCenterY()), 1.7f);

				RECT rc4 = (*_viMinion)->getRect();
				_bullet->fire(rc.left + (rc.right - rc.left) / 2,
					rc.bottom + (rc.top - rc.bottom) / 2 + 30,
					MY_UTIL::getAngle(rc.left + (rc.right - rc.left) / 2, rc.bottom + (rc.top - rc.bottom) / 2 + 30, _ship->getShipImage()->getCenterX(), _ship->getShipImage()->getCenterY()), 1.8f);
				RECT rc5 = (*_viMinion)->getRect();
				_bullet->fire(rc.left + (rc.right - rc.left) / 2,
					rc.bottom + (rc.top - rc.bottom) / 2 + 30,
					MY_UTIL::getAngle(rc.left + (rc.right - rc.left) / 2 +0.2f, rc.bottom + (rc.top - rc.bottom) / 2 + 30, _ship->getShipImage()->getCenterX()+20, _ship->getShipImage()->getCenterY()), 2.0f);

				RECT rc6 = (*_viMinion)->getRect();
				_bullet->fire(rc.left + (rc.right - rc.left) / 2,
					rc.bottom + (rc.top - rc.bottom) / 2 + 30,
					MY_UTIL::getAngle(rc.left + (rc.right - rc.left) / 2 +0.4f, rc.bottom + (rc.top - rc.bottom) / 2 + 30, _ship->getShipImage()->getCenterX()+40, _ship->getShipImage()->getCenterY()), 2.0f);

				RECT rc7 = (*_viMinion)->getRect();
				_bullet->fire(rc.left + (rc.right - rc.left) / 2,
					rc.bottom + (rc.top - rc.bottom) / 2 + 30,
					MY_UTIL::getAngle(rc.left + (rc.right - rc.left) / 2 + 0.6f, rc.bottom + (rc.top - rc.bottom) / 2 + 30, _ship->getShipImage()->getCenterX()+60, _ship->getShipImage()->getCenterY()), 2.0f);

				RECT rc8 = (*_viMinion)->getRect();
				_bullet->fire(rc.left + (rc.right - rc.left) / 2,
					rc.bottom + (rc.top - rc.bottom) / 2 + 30,
					MY_UTIL::getAngle(rc.left + (rc.right - rc.left) / 2+ 0.8f, rc.bottom + (rc.top - rc.bottom) / 2 + 30, _ship->getShipImage()->getCenterX()+80, _ship->getShipImage()->getCenterY()), 2.0f);

				RECT rc9 = (*_viMinion)->getRect();
				_bullet->fire(rc.left + (rc.right - rc.left) / 2,
					rc.bottom + (rc.top - rc.bottom) / 2 + 30,
					MY_UTIL::getAngle(rc.left + (rc.right - rc.left) / 2+1.f, rc.bottom + (rc.top - rc.bottom) / 2 + 30, _ship->getShipImage()->getCenterX()+100, _ship->getShipImage()->getCenterY()), 2.0f);

				RECT rc10 = (*_viMinion)->getRect();
				_bullet->fire(rc.left + (rc.right - rc.left) / 2,
					rc.bottom + (rc.top - rc.bottom) / 2 + 30,
					MY_UTIL::getAngle(rc.left + (rc.right - rc.left) / 2-0.2f, rc.bottom + (rc.top - rc.bottom) / 2 + 30, _ship->getShipImage()->getCenterX()-20, _ship->getShipImage()->getCenterY()), 2.0f);

				RECT rc11 = (*_viMinion)->getRect();
				_bullet->fire(rc.left + (rc.right - rc.left) / 2,
					rc.bottom + (rc.top - rc.bottom) / 2 + 30,
					MY_UTIL::getAngle(rc.left + (rc.right - rc.left) / 2-0.4f, rc.bottom + (rc.top - rc.bottom) / 2 + 30, _ship->getShipImage()->getCenterX()-40, _ship->getShipImage()->getCenterY()), 2.0f);

				RECT rc12 = (*_viMinion)->getRect();
				_bullet->fire(rc.left + (rc.right - rc.left) / 2,
					rc.bottom + (rc.top - rc.bottom) / 2 + 30,
					MY_UTIL::getAngle(rc.left + (rc.right - rc.left) / 2-0.6f, rc.bottom + (rc.top - rc.bottom) / 2 + 30, _ship->getShipImage()->getCenterX()-60, _ship->getShipImage()->getCenterY()), 2.0f);

				RECT rc13 = (*_viMinion)->getRect();
				_bullet->fire(rc.left + (rc.right - rc.left) / 2,
					rc.bottom + (rc.top - rc.bottom) / 2 + 30,
					MY_UTIL::getAngle(rc.left + (rc.right - rc.left) / 2-0.8f, rc.bottom + (rc.top - rc.bottom) / 2 + 30, _ship->getShipImage()->getCenterX()-80, _ship->getShipImage()->getCenterY()), 2.0f);
 
				RECT rc14 = (*_viMinion)->getRect();
				_bullet->fire(rc.left + (rc.right - rc.left) / 2,
					rc.bottom + (rc.top - rc.bottom) / 2 + 30,
					MY_UTIL::getAngle(rc.left + (rc.right - rc.left) / 2-1.f, rc.bottom + (rc.top - rc.bottom) / 2 + 30, _ship->getShipImage()->getCenterX()-100, _ship->getShipImage()->getCenterY()), 2.0f);
				RECT rc15 = (*_viMinion)->getRect();
				_bullet->fire(rc.left + (rc.right - rc.left) / 2,
					rc.bottom + (rc.top - rc.bottom) / 2 + 30,
					MY_UTIL::getAngle(rc.left + (rc.right - rc.left) / 2 , rc.bottom + (rc.top - rc.bottom) / 2 + 30, _ship->getShipImage()->getCenterX() , _ship->getShipImage()->getCenterY()), 2.0f);

			}*/
			
		}
		if ((*_viMinion)->bulletCountFire1() && _ship->bosshpnum >= 280 && _ship->bosshpnum <340 )
		{
			if (!(_ship->ending))
			sndPlaySoundA("sound/se_tan00.wav", SND_ASYNC | SND_NODEFAULT /*| SND_LOOP*/);
			RECT rc = (*_viMinion)->getRect();
			_bullet->fire(rc.left + (rc.right - rc.left) / 2,
				rc.bottom + (rc.top - rc.bottom) / 2 + 20,
				an += 0.21f, 1.f);
			RECT rc2 = (*_viMinion)->getRect();
			_bullet->fire(rc.left + (rc.right - rc.left) / 2,
				rc.bottom + (rc.top - rc.bottom) / 2 + 20,
				an += 0.31f, 1.f);
			RECT rc3 = (*_viMinion)->getRect();
			_bullet->fire(rc.left + (rc.right - rc.left) / 2,
				rc.bottom + (rc.top - rc.bottom) / 2 + 20,
				an += 0.41f, 1.f);
			RECT rc4 = (*_viMinion)->getRect();
			_bullet->fire(rc.left + (rc.right - rc.left) / 2,
				rc.bottom + (rc.top - rc.bottom) / 2 + 20,
				an += 0.51f, 1.f);
			RECT rc5 = (*_viMinion)->getRect();
			_bullet->fire(rc.left + (rc.right - rc.left) / 2,
				rc.bottom + (rc.top - rc.bottom) / 2 + 20,
				an += 0.61f, 1.f);
		}
		if ((*_viMinion)->bulletCountFire2() && _ship->bosshpnum >= 280 && _ship->bosshpnum < 340 )
		{
			if (!(_ship->ending))
			sndPlaySoundA("sound/se_tan00.wav", SND_ASYNC | SND_NODEFAULT /*| SND_LOOP*/);
			RECT rc = (*_viMinion)->getRect();
			_bullet->fire(rc.left + (rc.right - rc.left) / 2,
				rc.bottom + (rc.top - rc.bottom) / 2 + 30,
				MY_UTIL::getAngle(rc.left + (rc.right - rc.left) / 2, rc.bottom + (rc.top - rc.bottom) / 2 + 30, _ship->getShipImage()->getCenterX(), _ship->getShipImage()->getCenterY()), 1.5f);
			RECT rc2 = (*_viMinion)->getRect();
			_bullet->fire(rc.left + (rc.right - rc.left) / 2,
				rc.bottom + (rc.top - rc.bottom) / 2 + 30,
				MY_UTIL::getAngle(rc.left + (rc.right - rc.left) / 2, rc.bottom + (rc.top - rc.bottom) / 2 + 30, _ship->getShipImage()->getCenterX(), _ship->getShipImage()->getCenterY()), 1.6f);

			RECT rc3 = (*_viMinion)->getRect();
			_bullet->fire(rc.left + (rc.right - rc.left) / 2,
				rc.bottom + (rc.top - rc.bottom) / 2 + 30,
				MY_UTIL::getAngle(rc.left + (rc.right - rc.left) / 2, rc.bottom + (rc.top - rc.bottom) / 2 + 30, _ship->getShipImage()->getCenterX(), _ship->getShipImage()->getCenterY()), 1.7f);

			RECT rc4 = (*_viMinion)->getRect();
			_bullet->fire(rc.left + (rc.right - rc.left) / 2,
				rc.bottom + (rc.top - rc.bottom) / 2 + 30,
				MY_UTIL::getAngle(rc.left + (rc.right - rc.left) / 2, rc.bottom + (rc.top - rc.bottom) / 2 + 30, _ship->getShipImage()->getCenterX(), _ship->getShipImage()->getCenterY()), 1.8f);
			RECT rc5 = (*_viMinion)->getRect();
			_bullet->fire(rc.left + (rc.right - rc.left) / 2,
				rc.bottom + (rc.top - rc.bottom) / 2 + 30,
				MY_UTIL::getAngle(rc.left + (rc.right - rc.left) / 2 + 0.2f, rc.bottom + (rc.top - rc.bottom) / 2 + 30, _ship->getShipImage()->getCenterX() + 20, _ship->getShipImage()->getCenterY()), 2.0f);

			RECT rc6 = (*_viMinion)->getRect();
			_bullet->fire(rc.left + (rc.right - rc.left) / 2,
				rc.bottom + (rc.top - rc.bottom) / 2 + 30,
				MY_UTIL::getAngle(rc.left + (rc.right - rc.left) / 2 + 0.4f, rc.bottom + (rc.top - rc.bottom) / 2 + 30, _ship->getShipImage()->getCenterX() + 40, _ship->getShipImage()->getCenterY()), 2.0f);

			RECT rc7 = (*_viMinion)->getRect();
			_bullet->fire(rc.left + (rc.right - rc.left) / 2,
				rc.bottom + (rc.top - rc.bottom) / 2 + 30,
				MY_UTIL::getAngle(rc.left + (rc.right - rc.left) / 2 + 0.6f, rc.bottom + (rc.top - rc.bottom) / 2 + 30, _ship->getShipImage()->getCenterX() + 60, _ship->getShipImage()->getCenterY()), 2.0f);

			RECT rc8 = (*_viMinion)->getRect();
			_bullet->fire(rc.left + (rc.right - rc.left) / 2,
				rc.bottom + (rc.top - rc.bottom) / 2 + 30,
				MY_UTIL::getAngle(rc.left + (rc.right - rc.left) / 2 + 0.8f, rc.bottom + (rc.top - rc.bottom) / 2 + 30, _ship->getShipImage()->getCenterX() + 80, _ship->getShipImage()->getCenterY()), 2.0f);

			RECT rc9 = (*_viMinion)->getRect();
			_bullet->fire(rc.left + (rc.right - rc.left) / 2,
				rc.bottom + (rc.top - rc.bottom) / 2 + 30,
				MY_UTIL::getAngle(rc.left + (rc.right - rc.left) / 2 + 1.f, rc.bottom + (rc.top - rc.bottom) / 2 + 30, _ship->getShipImage()->getCenterX() + 100, _ship->getShipImage()->getCenterY()), 2.0f);

			RECT rc10 = (*_viMinion)->getRect();
			_bullet->fire(rc.left + (rc.right - rc.left) / 2,
				rc.bottom + (rc.top - rc.bottom) / 2 + 30,
				MY_UTIL::getAngle(rc.left + (rc.right - rc.left) / 2 - 0.2f, rc.bottom + (rc.top - rc.bottom) / 2 + 30, _ship->getShipImage()->getCenterX() - 20, _ship->getShipImage()->getCenterY()), 2.0f);

			RECT rc11 = (*_viMinion)->getRect();
			_bullet->fire(rc.left + (rc.right - rc.left) / 2,
				rc.bottom + (rc.top - rc.bottom) / 2 + 30,
				MY_UTIL::getAngle(rc.left + (rc.right - rc.left) / 2 - 0.4f, rc.bottom + (rc.top - rc.bottom) / 2 + 30, _ship->getShipImage()->getCenterX() - 40, _ship->getShipImage()->getCenterY()), 2.0f);

			RECT rc12 = (*_viMinion)->getRect();
			_bullet->fire(rc.left + (rc.right - rc.left) / 2,
				rc.bottom + (rc.top - rc.bottom) / 2 + 30,
				MY_UTIL::getAngle(rc.left + (rc.right - rc.left) / 2 - 0.6f, rc.bottom + (rc.top - rc.bottom) / 2 + 30, _ship->getShipImage()->getCenterX() - 60, _ship->getShipImage()->getCenterY()), 2.0f);

			RECT rc13 = (*_viMinion)->getRect();
			_bullet->fire(rc.left + (rc.right - rc.left) / 2,
				rc.bottom + (rc.top - rc.bottom) / 2 + 30,
				MY_UTIL::getAngle(rc.left + (rc.right - rc.left) / 2 - 0.8f, rc.bottom + (rc.top - rc.bottom) / 2 + 30, _ship->getShipImage()->getCenterX() - 80, _ship->getShipImage()->getCenterY()), 2.0f);

			RECT rc14 = (*_viMinion)->getRect();
			_bullet->fire(rc.left + (rc.right - rc.left) / 2,
				rc.bottom + (rc.top - rc.bottom) / 2 + 30,
				MY_UTIL::getAngle(rc.left + (rc.right - rc.left) / 2 - 1.f, rc.bottom + (rc.top - rc.bottom) / 2 + 30, _ship->getShipImage()->getCenterX() - 100, _ship->getShipImage()->getCenterY()), 2.0f);
			RECT rc15 = (*_viMinion)->getRect();
			_bullet->fire(rc.left + (rc.right - rc.left) / 2,
				rc.bottom + (rc.top - rc.bottom) / 2 + 30,
				MY_UTIL::getAngle(rc.left + (rc.right - rc.left) / 2, rc.bottom + (rc.top - rc.bottom) / 2 + 30, _ship->getShipImage()->getCenterX(), _ship->getShipImage()->getCenterY()), 2.0f);

			RECT rc16 = (*_viMinion)->getRect();
			_bullet->fire(rc.left + (rc.right - rc.left) / 2,
				rc.bottom + (rc.top - rc.bottom) / 2 + 30,
				MY_UTIL::getAngle(rc.left + (rc.right - rc.left) / 2, rc.bottom + (rc.top - rc.bottom) / 2 + 30, _ship->getShipImage()->getCenterX(), _ship->getShipImage()->getCenterY()), 2.3f);

			RECT rc17 = (*_viMinion)->getRect();
			_bullet->fire(rc.left + (rc.right - rc.left) / 2,
				rc.bottom + (rc.top - rc.bottom) / 2 + 30,
				MY_UTIL::getAngle(rc.left + (rc.right - rc.left) / 2, rc.bottom + (rc.top - rc.bottom) / 2 + 30, _ship->getShipImage()->getCenterX(), _ship->getShipImage()->getCenterY()), 2.6f);

		}
	}
}

void enemyManager::removeMinion(int arrayNum)
{
	SAFE_DELETE(_vMinion[arrayNum]);
	_vMinion.erase(_vMinion.begin() + arrayNum);
}

void enemyManager::collision()
{
	
		for (int j = 0; j < getVMinion().size(); j++) //ÆøÅºÃæµ¹
		{
			//ÆøÅº Ãæµ¹°Ë»ç
			RECT rc;
			if (IntersectRect(&rc, &boomrc1, &getVMinion()[j]->getRect()) && TIMEMANAGER->getWorldTime()<45)
			{
				sndPlaySoundA("sound/monsterdead.wav", SND_ASYNC | SND_NODEFAULT /*| SND_LOOP*/); //Á×´Â¼Ò¸®
				_ship->score += 32111;
				removeMinion(j);
				break;
			}
			if (IntersectRect(&rc, &boomrc2, &getVMinion()[j]->getRect()) && TIMEMANAGER->getWorldTime()<45)
			{
				sndPlaySoundA("sound/monsterdead.wav", SND_ASYNC | SND_NODEFAULT /*| SND_LOOP*/); //Á×´Â¼Ò¸®
				_ship->score += 32111;
				removeMinion(j);
				break;
			}
			//Áß°£º¸½º ÆøÅºÃæµ¹
			if (IntersectRect(&rc, &boomrc1, &getVMinion()[j]->getRect()) && TIMEMANAGER->getWorldTime()>45 &&
				TIMEMANAGER->getWorldTime()<65)
			{
				
				
				break;
			}
			if (IntersectRect(&rc, &boomrc2, &getVMinion()[j]->getRect()) && TIMEMANAGER->getWorldTime() > 45 &&
				TIMEMANAGER->getWorldTime() < 65)
			{
				_ship->midbossrc.right -= 2;
				if (_ship->midbossrc.right <= _ship->midbossrc.left)
				{
					_ship->score += 5432111;
					sndPlaySoundA("sound/midbossdead.wav", SND_ASYNC | SND_NODEFAULT /*| SND_LOOP*/); //Á×´Â¼Ò¸®
				    removeMinion(j);
				}
				break;
			}

			//Â©¸÷ ÆøÅºÃæµ¹
			if (IntersectRect(&rc, &boomrc1, &getVMinion()[j]->getRect()) && TIMEMANAGER->getWorldTime()>65 &&
				TIMEMANAGER->getWorldTime()<87)
			{
				sndPlaySoundA("sound/monsterdead.wav", SND_ASYNC | SND_NODEFAULT /*| SND_LOOP*/); //Á×´Â¼Ò¸®
				_ship->score += 32111;
				removeMinion(j);
				break;
			}
			if (IntersectRect(&rc, &boomrc2, &getVMinion()[j]->getRect()) && TIMEMANAGER->getWorldTime()>65 &&
				TIMEMANAGER->getWorldTime()<87)
			{
				sndPlaySoundA("sound/monsterdead.wav", SND_ASYNC | SND_NODEFAULT /*| SND_LOOP*/); //Á×´Â¼Ò¸®
				_ship->score += 32111;
				removeMinion(j);
				break;
			}
			//º¸½º ÆøÅºÃæµ¹
			if (IntersectRect(&rc, &boomrc1, &getVMinion()[j]->getRect()) && TIMEMANAGER->getWorldTime()>87)
			{
				
				break;
			}
			if (IntersectRect(&rc, &boomrc2, &getVMinion()[j]->getRect()) && TIMEMANAGER->getWorldTime()>87)
			{
				_ship->bosshpnum += 1;
				if (_ship->bosshpnum >= 340)
				{
					
					_ship->score += 5432111;
					sndPlaySoundA("sound/bossdead.wav", SND_ASYNC | SND_NODEFAULT /*| SND_LOOP*/); //Á×´Â¼Ò¸®
					
					removeMinion(j);
						
				
					break;
				}
				break;
			}


		}
	
		for (int i = 0; i < _bullet->getVBullet().size(); i++)
		{
			if (!(_ship->die1))
			{
				if (IntersectRect(&RectMake(0, 0, 0, 0), &_ship->getShipImage()->boundingBox(), &_bullet->getVBullet()[i].rc))
				{
					_bullet->removeBullet(i);
					if (!(_ship->ending))
					sndPlaySoundA("sound/dead.wav", SND_ASYNC | SND_NODEFAULT /*| SND_LOOP*/); //Á×´Â¼Ò¸®
					_ship->die1 = true;
					break;
				}
			}
			if (IntersectRect(&RectMake(0, 0, 0, 0), &removerc1, &_bullet->getVBullet()[i].rc))
			{
				_bullet->removeBullet(i);

				break;
			}
			if (IntersectRect(&RectMake(0, 0, 0, 0), &removerc2, &_bullet->getVBullet()[i].rc))
			{
				_bullet->removeBullet(i);

				break;
			}
			if (IntersectRect(&RectMake(0, 0, 0, 0), &removerc3, &_bullet->getVBullet()[i].rc))
			{
				_bullet->removeBullet(i);

				break;
			}
			if (IntersectRect(&RectMake(0, 0, 0, 0), &removerc4, &_bullet->getVBullet()[i].rc))
			{
				_bullet->removeBullet(i);

				break;
			}
			if (IntersectRect(&RectMake(0, 0, 0, 0), &boomrc1, &_bullet->getVBullet()[i].rc)) //ÆøÅº±â¸ðÀ¸´Â°Å
			{
				_bullet->removeBullet(i);

				break;
			}
			if (IntersectRect(&RectMake(0, 0, 0, 0), &boomrc2, &_bullet->getVBullet()[i].rc)) //ÆøÅº·¹ÀÌÀú
			{
				_bullet->removeBullet(i);

				break;
			}
		}

		
	
	
}
