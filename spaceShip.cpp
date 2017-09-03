#include "stdafx.h"
#include "spaceShip.h"
#include "enemyManager.h"
#include "gameStudy.h"
spaceShip::spaceShip()
{
}


spaceShip::~spaceShip()
{
}

HRESULT spaceShip::init()
{
	_count = 0;
	_index = 0;
	count = 0;
	_count1 = 0;
	_index1 = 0;
	index = 0;
	shotcount = 0;
	xnum = 0;
	ynum = 0;
	score = 0;
	sidemove = false;
	isRight = false;
	deadcheck = false;
	boomcheck2 = false;
	die1 = false;
	alphanum = 250;
	alphanum2 = 250;
	bosshpnum = 0;
	loopx = 2;
	diecount1 = false;
	diecount2 = false;
	diecount = 0;
	alphanum4 = 0;
	boomcheck3 = false;
	boomcheck4 = false;
	bosshpnum2 = 10;
	boombackgroundcount = 0;
	
	_raystand = IMAGEMANAGER->addFrameImage("raystand", "image/raystand.bmp", 120, 46, 4, 1, true, RGB(255, 0, 255));
	_raystand->setX(CENTERX - _raystand->getWidth() / 2 -80);
	_raystand->setY(CENTERY - _raystand->getHeight() / 2 + 200);
	
	_raymove = IMAGEMANAGER->addFrameImage("raymove", "image/raymove.bmp", 231, 92, 7, 2, true, RGB(255, 0, 255));
	_raymove->setX(CENTERX - _raystand->getWidth() / 2 - 80);
	_raymove->setY(CENTERY - _raystand->getHeight() / 2 + 200);

	die = IMAGEMANAGER->addFrameImage("die", "image/die.bmp", 1005, 102, 13, 1, true, RGB(255, 242, 0));
	die->setX(CENTERX - _raystand->getWidth() / 2 - 80);
	die->setY(CENTERY - _raystand->getHeight() / 2 + 200);
	
	bosshp = IMAGEMANAGER->addImage("bosshp", "image/bosshp.bmp", 340, 4, false, false);
	//bosshp2 = IMAGEMANAGER->addImage("bosshp2", "image/bosshp2.bmp", 30, 4, false, false);
	IMAGEMANAGER->addImage("0", "image/0.bmp", 13, 17, false, false);
	IMAGEMANAGER->addImage("1", "image/1.bmp", 13, 17, false, false);
	IMAGEMANAGER->addImage("2", "image/2.bmp", 13, 17, false, false);
	IMAGEMANAGER->addImage("3", "image/3.bmp", 13, 17, false, false);
	IMAGEMANAGER->addImage("4", "image/4.bmp", 13, 17, false, false);
	IMAGEMANAGER->addImage("5", "image/5.bmp", 13, 17, false, false);
	IMAGEMANAGER->addImage("6", "image/6.bmp", 13, 17, false, false);
	IMAGEMANAGER->addImage("7", "image/7.bmp", 13, 17, false, false);
	IMAGEMANAGER->addImage("8", "image/8.bmp", 13, 17, false, false);
	IMAGEMANAGER->addImage("9", "image/9.bmp", 13, 17, false, false);

	IMAGEMANAGER->addImage("bossmap", "image/bossmap.bmp", WINSIZEX / 5 * 3, WINSIZEY, false, false);
	
	IMAGEMANAGER->addImage("bossboom", "image/bossboom.bmp", 130, 554, true, RGB(255, 242, 0));

	IMAGEMANAGER->addImage("boom2", "image/boom2.bmp", 146, 288, true, RGB(255, 242, 0));


	player = IMAGEMANAGER->addImage("player", "image/player.bmp", 16, 16, false, false);
	null = IMAGEMANAGER->addImage("null", "image/null.bmp", 16, 16, false, false);
	boombackground = IMAGEMANAGER->addImage("boombackground", "image/boombackground.bmp", 400, 480, false, false);
	fuckingboom = IMAGEMANAGER->addFrameImage("fuckingboom", "image/fuckingboom.bmp", 15384, 1896, 34, 3, true, RGB(0, 0, 0));
	boompoint = IMAGEMANAGER->addImage("boompoint", "image/boompoint.bmp", 14, 14, false, false);
	end = IMAGEMANAGER->addImage("end", "image/end.bmp", WINSIZEX, WINSIZEY, false, false);
	bossboomnum = 0;
	dead = new image;
	dead->init("image/dead.bmp", 64, 64, true, RGB(255, 242, 0));
	midbossrc = RectMakeCenter(200, 10, 340, 4);
	RectMakeCenter(10, 10, 340, 10);
	alphanum3 = 250;
	boomnum = 0;
	boomcheck = false;
	null1 = false;
	null2 = false;
	null3 = false;
	ending = false;
	_index2 = 0;
	_count2 = 0;
	_missile = new missile;
	_missile->init(13, 600);
	count5 = 0;
	return S_OK;
}

void spaceShip::release()
{
	_missile->release();
	SAFE_DELETE(_missile);

	dead->release();
	SAFE_DELETE(dead);
	
	/*boom2->release();
	SAFE_DELETE(boom2);*/
}

void spaceShip::update()
{
	rayx = _raystand->getX();
	rayy = _raystand->getY();
	if (KEYMANAGER->isStayDown(VK_LEFT) && _raystand->getX() > 0)
	{
		isRight = false;
		sidemove = true;
		_raystand->setX(_raystand->getX() - 2.0f);
		die->setX(_raystand->getX() - 2.0f);
	}
	if (KEYMANAGER->isStayDown(VK_RIGHT) && _raystand->getX() < WINSIZEX/5*3-30)
	{
		isRight = true;
		sidemove = true;
		_raystand->setX(_raystand->getX() + 2.0f);
		die->setX(_raystand->getX() + 2.0f);
	}
	if (KEYMANAGER->isStayDown(VK_UP)&& _raystand->getY()>0 )
	{
		_raystand->setY(_raystand->getY() - 2.0f);
		die->setY(_raystand->getY() - 2.0f);
	}
	if (KEYMANAGER->isStayDown(VK_DOWN)&& _raystand->getY()<WINSIZEY -40)
	{
		_raystand->setY(_raystand->getY() + 2.0f);
		die->setY(_raystand->getY() + 2.0f);
	}

	if (KEYMANAGER->isStayDown(VK_SPACE))
	{
		shotcount++;
		if(shotcount%10 ==0)
		_missile->fire(_raystand->getX() + _raystand->getWidth() / 2 -45, _raystand->getY() - 20);
	}

	if (KEYMANAGER->isOnceDown(VK_CONTROL)&& !boomcheck)
	{
		if(!null3)boomcheck = true;
		if (null1&&null2)null3 = true;
		if (null1)null2 = true;
		null1 = true;
	
	}
		_count++;
		
		_raystand->setFrameY(0);
		if (die1)
		{
			_raystand->setX(CENTERX - _raystand->getWidth() / 2 - 80);
			_raystand->setY(CENTERY - _raystand->getHeight() / 2 + 200);
			_count1++;
			
			die->setFrameY(0);

			if (_count1 % 10 == 0)

			{
			
				_index1++;
				die->setFrameX(_index1);
				if (_index1 > die->getMaxFrameX())
				{
					die1 = false;
					
					_index1 = 0;
				}

			}
		}

		if (isRight)
		{
			
			_raystand->setFrameY(0);
			_raymove->setFrameY(1);
		
			if (_count % 10 == 0)
			{
				_index++;
				_raystand->setFrameX(_index);
				_raymove->setFrameX(_index);
				
				if (_index > _raystand->getMaxFrameX())
				{
					_index = 0;
				}

				if (_index > _raymove->getMaxFrameX())
				{
					_index = 0;
				}
				


			}
		} //�������̹��� ������
		else
		{
			
			_raystand->setFrameY(0);
			_raymove->setFrameY(0);
			
			if (_count % 10 == 0)
			{
				_index++;
				_raystand->setFrameX(_index);
				_raymove->setFrameX(_index);
				
				if (_index > _raystand->getMaxFrameX())
				{
					_index = 0;
				}

				if (_index > _raymove->getMaxFrameX())
				{
					_index = 0;
				}
				


			}
		}         //�������̹��� ����
		
		if (boomcheck2)
		{
			//IMAGEMANAGER->alphaRender("boom2", getMemDC(),10,10, 250);
		}
		
		if (deadcheck)
		{
			alphanum--;
			if (alphanum <= 0)deadcheck = false;
		}
		
			if (die1)
			{
				//ù��° �׾����� ����ϳ�����
				diecount1 = true;
				diecount++;
				null1 = false; //��ź �ʱ�ȭ
				null2 = false;
				null3 = false;
			}
			if (die1 && diecount1 && diecount>130)
			{
				//�ι�° �׾����� �ι�°��� ����
				diecount2 = true;
				null1 = false;
				null2 = false;
				null3 = false;
				
			}
			if (die1 && diecount1 && diecount2 && diecount>260)
			{
				//exit(0);
				ending = true;
				count5++;
				if (count5 > 100)exit(0);
				//����پ��� �׾�����
			}
		


			//��ź������ ������
			if (boomcheck4)
			{
				_count2++;


				if (_count2 % 3 == 0)
				{
					_index2++;
					
					fuckingboom->setFrameX(_index2);

					if (_index2 > fuckingboom->getMaxFrameX())
					{

						_index2 = 0;
						i += 1;
						if (i > 2)
						{
							i = 0;
							//�����Ӵٵ���
							boomcheck4 = false;
							boomcheck3 = false;
							boomcheck = false;
							alphanum4 = 0;
						}
						fuckingboom->setFrameY(i);
					}

				}
			}


			//������� ��ź
			
	_missile->update();

	collision();
}

void spaceShip::render()
{

	if (bosshpnum > 280 && !(bosshpnum >= 340))
	{
		IMAGEMANAGER->findImage("bossmap")->loopRender(getMemDC(), &RectMake(0, 0, WINSIZEX / 5 * 3, WINSIZEY), 0, loopx -= 2);
		//���� ��ź��
		//IMAGEMANAGER->findImage("bossboom")->alphaRender(getMemDC(), 360, WINSIZEY-bossboomnum, alphanum2);
		if (!(alphanum2 <= 1))
		{
			IMAGEMANAGER->alphaRender("bossboom", getMemDC(), 254, 380 + bossboomnum, alphanum2);
		}
		bossboomnum--;
		alphanum2--;
		if (bossboomnum >= 100)bossboomnum = 100;
	}

	if (!sidemove && !die1)//�¿�Ű �ȴ����� ���ĵ� �̹������
		IMAGEMANAGER->frameRender("raystand", getMemDC(), _raystand->getX(), _raystand->getY());
	if (sidemove && !die1)
	{
		IMAGEMANAGER->frameRender("raymove", getMemDC(), _raystand->getX(), _raystand->getY());
		sidemove = false;
	}
	if (die1)
	{
		IMAGEMANAGER->frameRender("die", getMemDC(), _raystand->getX() - 25, _raystand->getY() - 25);
		//die1 = false;

	}


	/*if (deadcheck)
	{

		dead->alphaRender(getMemDC(), rc.left, rc.top, alphanum);
		alphanum--;
		deadcheck = false;

	}*/

	
	//���� ����////////////////////////////

	////////////////////////////
	if (boomcheck3)
	{
		IMAGEMANAGER->alphaRender("boombackground", getMemDC(), 0, 0, alphanum4);
		alphanum4++;
		if (alphanum4 > 254)
		{
			alphanum4 = 255;

			boomcheck4 = true;
		}


	}


	if (boomcheck4)
	{
		IMAGEMANAGER->frameRender("fuckingboom", getMemDC(), _raystand->getX() - 220, _raystand->getY() - 400);
		//��ź�̹���
	}
	if (TIMEMANAGER->getWorldTime() > 87)
	{
		IMAGEMANAGER->findImage("bosshp")->render(getMemDC(), 40, 10, 0, 0, 340 - bosshpnum, 4);
	}
	if (boomcheck) //��ź����
	{
		boomcheck3 = true;
		if (!(alphanum3 <= 1)) //�����̹��� ���������������� ������
		{
			IMAGEMANAGER->alphaRender("boom2", getMemDC(), 0, 350 - boomnum, alphanum3);
			boomnum++;
			alphanum3--;
		}
		else //����������������
		{
			boomnum = 0;
			alphanum3 = 250;
			boomcheck = false;
		}
	}

	IMAGEMANAGER->findImage("scoreboard")->loopRender(getMemDC(), &RectMake(WINSIZEX / 5 * 3, 0, WINSIZEX / 5 * 2, WINSIZEY), 0, 0);
	if (!diecount1 && !diecount2) //��� �ΰ���������
	{
		IMAGEMANAGER->render("player", getMemDC(), 476, 97);
		IMAGEMANAGER->render("player", getMemDC(), 494, 97);
	}
	else if (diecount1 && !diecount2) //����ϳ�������
	{
		IMAGEMANAGER->render("player", getMemDC(), 476, 97);
	}
	else if (diecount1 && diecount2)
	{
		
		
	}
	if (TIMEMANAGER->getWorldTime() > 45)
	{

		Rectangle(getMemDC(), midbossrc.left, midbossrc.top, midbossrc.right, midbossrc.bottom);
	}
	if (score == 0)
	{
		IMAGEMANAGER->findImage("0")->render(getMemDC(), 475, 65); //100000000 (����)
		IMAGEMANAGER->findImage("0")->render(getMemDC(), 490, 65); //10000000
		IMAGEMANAGER->findImage("0")->render(getMemDC(), 505, 65); //1000000
		IMAGEMANAGER->findImage("0")->render(getMemDC(), 520, 65); //100000
		IMAGEMANAGER->findImage("0")->render(getMemDC(), 535, 65); //10000
		IMAGEMANAGER->findImage("0")->render(getMemDC(), 550, 65); //1000
		IMAGEMANAGER->findImage("0")->render(getMemDC(), 565, 65); //100
		IMAGEMANAGER->findImage("0")->render(getMemDC(), 580, 65); //10
		IMAGEMANAGER->findImage("0")->render(getMemDC(), 595, 65); //1
	}
	else
	{
		IMAGEMANAGER->findImage("0")->render(getMemDC(), 475, 65); //100000000 (����)
		IMAGEMANAGER->findImage("0")->render(getMemDC(), 490, 65); //10000000
		IMAGEMANAGER->findImage("0")->render(getMemDC(), 505, 65); //1000000
		IMAGEMANAGER->findImage("0")->render(getMemDC(), 520, 65); //100000
		IMAGEMANAGER->findImage("0")->render(getMemDC(), 535, 65); //10000
		IMAGEMANAGER->findImage("0")->render(getMemDC(), 550, 65); //1000
		IMAGEMANAGER->findImage("0")->render(getMemDC(), 565, 65); //100
		IMAGEMANAGER->findImage("0")->render(getMemDC(), 580, 65); //10
		IMAGEMANAGER->findImage("0")->render(getMemDC(), 595, 65); //1
		//1���ڸ�
		if (score % 10 == 0)IMAGEMANAGER->findImage("0")->render(getMemDC(), 595, 65);
		else if (score % 10 == 1)IMAGEMANAGER->findImage("1")->render(getMemDC(), 595, 65);
		else if (score % 10 == 2)IMAGEMANAGER->findImage("2")->render(getMemDC(), 595, 65);
		else if (score % 10 == 3)IMAGEMANAGER->findImage("3")->render(getMemDC(), 595, 65);
		else if (score % 10 == 4)IMAGEMANAGER->findImage("4")->render(getMemDC(), 595, 65);
		else if (score % 10 == 5)IMAGEMANAGER->findImage("5")->render(getMemDC(), 595, 65);
		else if (score % 10 == 6)IMAGEMANAGER->findImage("6")->render(getMemDC(), 595, 65);
		else if (score % 10 == 7)IMAGEMANAGER->findImage("7")->render(getMemDC(), 595, 65);
		else if (score % 10 == 8)IMAGEMANAGER->findImage("8")->render(getMemDC(), 595, 65);
		else if (score % 10 == 9)IMAGEMANAGER->findImage("9")->render(getMemDC(), 595, 65);
		//10���ڸ�
		if (score/10 % 10 == 0)IMAGEMANAGER->findImage("0")->render(getMemDC(), 580, 65);
		else if (score/10 % 10 == 1)IMAGEMANAGER->findImage("1")->render(getMemDC(), 580, 65);
		else if (score/10 % 10 == 2)IMAGEMANAGER->findImage("2")->render(getMemDC(), 580, 65);
		else if (score/10 % 10 == 3)IMAGEMANAGER->findImage("3")->render(getMemDC(), 580, 65);
		else if (score/10 % 10 == 4)IMAGEMANAGER->findImage("4")->render(getMemDC(), 580, 65);
		else if (score/10 % 10 == 5)IMAGEMANAGER->findImage("5")->render(getMemDC(), 580, 65);
		else if (score/10 % 10 == 6)IMAGEMANAGER->findImage("6")->render(getMemDC(), 580, 65);
		else if (score/10 % 10 == 7)IMAGEMANAGER->findImage("7")->render(getMemDC(), 580, 65);
		else if (score/10 % 10 == 8)IMAGEMANAGER->findImage("8")->render(getMemDC(), 580, 65);
		else if (score/10 % 10 == 9)IMAGEMANAGER->findImage("9")->render(getMemDC(), 580, 65);
		//100���ڸ�

		if (score / 100 % 10 == 0)IMAGEMANAGER->findImage("0")->render(getMemDC(), 565, 65);
		else if (score / 100 % 10 == 1)IMAGEMANAGER->findImage("1")->render(getMemDC(), 565, 65);
		else if (score / 100 % 10 == 2)IMAGEMANAGER->findImage("2")->render(getMemDC(), 565, 65);
		else if (score / 100 % 10 == 3)IMAGEMANAGER->findImage("3")->render(getMemDC(), 565, 65);
		else if (score / 100 % 10 == 4)IMAGEMANAGER->findImage("4")->render(getMemDC(), 565, 65);
		else if (score / 100 % 10 == 5)IMAGEMANAGER->findImage("5")->render(getMemDC(), 565, 65);
		else if (score / 100 % 10 == 6)IMAGEMANAGER->findImage("6")->render(getMemDC(), 565, 65);
		else if (score / 100 % 10 == 7)IMAGEMANAGER->findImage("7")->render(getMemDC(), 565, 65);
		else if (score / 100 % 10 == 8)IMAGEMANAGER->findImage("8")->render(getMemDC(), 565, 65);
		else if (score / 100 % 10 == 9)IMAGEMANAGER->findImage("9")->render(getMemDC(), 565, 65);

		//1000���ڸ�


		if (score / 1000 % 10 == 0)IMAGEMANAGER->findImage("0")->render(getMemDC(), 550, 65);
		else if (score / 1000 % 10 == 1)IMAGEMANAGER->findImage("1")->render(getMemDC(), 550, 65);
		else if (score / 1000 % 10 == 2)IMAGEMANAGER->findImage("2")->render(getMemDC(), 550, 65);
		else if (score / 1000 % 10 == 3)IMAGEMANAGER->findImage("3")->render(getMemDC(), 550, 65);
		else if (score / 1000 % 10 == 4)IMAGEMANAGER->findImage("4")->render(getMemDC(), 550, 65);
		else if (score / 1000 % 10 == 5)IMAGEMANAGER->findImage("5")->render(getMemDC(), 550, 65);
		else if (score / 1000 % 10 == 6)IMAGEMANAGER->findImage("6")->render(getMemDC(), 550, 65);
		else if (score / 1000 % 10 == 7)IMAGEMANAGER->findImage("7")->render(getMemDC(), 550, 65);
		else if (score / 1000 % 10 == 8)IMAGEMANAGER->findImage("8")->render(getMemDC(), 550, 65);
		else if (score / 1000 % 10 == 9)IMAGEMANAGER->findImage("9")->render(getMemDC(), 550, 65);

		//10000�� �ڸ�
		if (score / 10000 % 10 == 0)IMAGEMANAGER->findImage("0")->render(getMemDC(), 535, 65);
		else if (score / 10000 % 10 == 1)IMAGEMANAGER->findImage("1")->render(getMemDC(), 535, 65);
		else if (score / 10000 % 10 == 2)IMAGEMANAGER->findImage("2")->render(getMemDC(), 535, 65);
		else if (score / 10000 % 10 == 3)IMAGEMANAGER->findImage("3")->render(getMemDC(), 535, 65);
		else if (score / 10000 % 10 == 4)IMAGEMANAGER->findImage("4")->render(getMemDC(), 535, 65);
		else if (score / 10000 % 10 == 5)IMAGEMANAGER->findImage("5")->render(getMemDC(), 535, 65);
		else if (score / 10000 % 10 == 6)IMAGEMANAGER->findImage("6")->render(getMemDC(), 535, 65);
		else if (score / 10000 % 10 == 7)IMAGEMANAGER->findImage("7")->render(getMemDC(), 535, 65);
		else if (score / 10000 % 10 == 8)IMAGEMANAGER->findImage("8")->render(getMemDC(), 535, 65);
		else if (score / 10000 % 10 == 9)IMAGEMANAGER->findImage("9")->render(getMemDC(), 535, 65);

		//10���ڸ�
		if (score / 100000 % 10 == 0)IMAGEMANAGER->findImage("0")->render(getMemDC(), 520, 65);
		else if (score / 100000 % 10 == 1)IMAGEMANAGER->findImage("1")->render(getMemDC(), 520, 65);
		else if (score / 100000 % 10 == 2)IMAGEMANAGER->findImage("2")->render(getMemDC(), 520, 65);
		else if (score / 100000 % 10 == 3)IMAGEMANAGER->findImage("3")->render(getMemDC(), 520, 65);
		else if (score / 100000 % 10 == 4)IMAGEMANAGER->findImage("4")->render(getMemDC(), 520, 65);
		else if (score / 100000 % 10 == 5)IMAGEMANAGER->findImage("5")->render(getMemDC(), 520, 65);
		else if (score / 100000 % 10 == 6)IMAGEMANAGER->findImage("6")->render(getMemDC(), 520, 65);
		else if (score / 100000 % 10 == 7)IMAGEMANAGER->findImage("7")->render(getMemDC(), 520, 65);
		else if (score / 100000 % 10 == 8)IMAGEMANAGER->findImage("8")->render(getMemDC(), 520, 65);
		else if (score / 100000 % 10 == 9)IMAGEMANAGER->findImage("9")->render(getMemDC(), 520, 65);

		//100���ڸ�
		if (score / 1000000 % 10 == 0)IMAGEMANAGER->findImage("0")->render(getMemDC(), 505, 65);
		else if (score / 1000000 % 10 == 1)IMAGEMANAGER->findImage("1")->render(getMemDC(), 505, 65);
		else if (score / 1000000 % 10 == 2)IMAGEMANAGER->findImage("2")->render(getMemDC(), 505, 65);
		else if (score / 1000000 % 10 == 3)IMAGEMANAGER->findImage("3")->render(getMemDC(), 505, 65);
		else if (score / 1000000 % 10 == 4)IMAGEMANAGER->findImage("4")->render(getMemDC(), 505, 65);
		else if (score / 1000000 % 10 == 5)IMAGEMANAGER->findImage("5")->render(getMemDC(), 505, 65);
		else if (score / 1000000 % 10 == 6)IMAGEMANAGER->findImage("6")->render(getMemDC(), 505, 65);
		else if (score / 1000000 % 10 == 7)IMAGEMANAGER->findImage("7")->render(getMemDC(), 505, 65);
		else if (score / 1000000 % 10 == 8)IMAGEMANAGER->findImage("8")->render(getMemDC(), 505, 65);
		else if (score / 1000000 % 10 == 9)IMAGEMANAGER->findImage("9")->render(getMemDC(), 505, 65);

		//1000���ڸ�
		if (score / 10000000 % 10 == 0)IMAGEMANAGER->findImage("0")->render(getMemDC(), 490, 65);
		else if (score / 10000000 % 10 == 1)IMAGEMANAGER->findImage("1")->render(getMemDC(), 490, 65);
		else if (score / 10000000 % 10 == 2)IMAGEMANAGER->findImage("2")->render(getMemDC(), 490, 65);
		else if (score / 10000000 % 10 == 3)IMAGEMANAGER->findImage("3")->render(getMemDC(), 490, 65);
		else if (score / 10000000 % 10 == 4)IMAGEMANAGER->findImage("4")->render(getMemDC(), 490, 65);
		else if (score / 10000000 % 10 == 5)IMAGEMANAGER->findImage("5")->render(getMemDC(), 490, 65);
		else if (score / 10000000 % 10 == 6)IMAGEMANAGER->findImage("6")->render(getMemDC(), 490, 65);
		else if (score / 10000000 % 10 == 7)IMAGEMANAGER->findImage("7")->render(getMemDC(), 490, 65);
		else if (score / 10000000 % 10 == 8)IMAGEMANAGER->findImage("8")->render(getMemDC(), 490, 65);
		else if (score / 10000000 % 10 == 9)IMAGEMANAGER->findImage("9")->render(getMemDC(), 490, 65);

		//1���ڸ�
		if (score / 100000000 % 10 == 0)IMAGEMANAGER->findImage("0")->render(getMemDC(), 475, 65);
		else if (score / 100000000 % 10 == 1)IMAGEMANAGER->findImage("1")->render(getMemDC(), 475, 65);
		else if (score / 100000000 % 10 == 2)IMAGEMANAGER->findImage("2")->render(getMemDC(), 475, 65);
		else if (score / 100000000 % 10 == 3)IMAGEMANAGER->findImage("3")->render(getMemDC(), 475, 65);
		else if (score / 100000000 % 10 == 4)IMAGEMANAGER->findImage("4")->render(getMemDC(), 475, 65);
		else if (score / 100000000 % 10 == 5)IMAGEMANAGER->findImage("5")->render(getMemDC(), 475, 65);
		else if (score / 100000000 % 10 == 6)IMAGEMANAGER->findImage("6")->render(getMemDC(), 475, 65);
		else if (score / 100000000 % 10 == 7)IMAGEMANAGER->findImage("7")->render(getMemDC(), 475, 65);
		else if (score / 100000000 % 10 == 8)IMAGEMANAGER->findImage("8")->render(getMemDC(), 475, 65);
		else if (score / 100000000 % 10 == 9)IMAGEMANAGER->findImage("9")->render(getMemDC(), 475, 65);
	} //����  //����

	IMAGEMANAGER->findImage("boompoint")->render(getMemDC(), 477, 113);
	IMAGEMANAGER->findImage("boompoint")->render(getMemDC(), 495, 113);
	IMAGEMANAGER->findImage("boompoint")->render(getMemDC(), 513, 113);
	if (null1)
	{
		IMAGEMANAGER->findImage("null")->render(getMemDC(), 513, 113);
	}
	if (null2)
	{
		IMAGEMANAGER->findImage("null")->render(getMemDC(), 495, 113);
	}
	if (null3)
	{
		IMAGEMANAGER->findImage("null")->render(getMemDC(), 477, 113);
	}
	//for (int i = 0; i < _missile->getVBullet().size(); i++) //�̻��ϰ���
	//{
	//	for (int j = 0; j < _em->getVMinion().size(); j++) //������
	//	{
	//		//�浹�˻�
	//		//RECT rc;
	//		if (IntersectRect(&rc, &_missile->getVBullet()[i].rc, &_em->getVMinion()[j]->getRect()))
	//		{

	//			deadcheck = true;
	//			//alphanum = 250;

	//			//dead->alphaRender(getMemDC(), rc.left, rc.top, 111);
	//			dead->render(getMemDC(), rc.left, rc.top);
	//			//alphanum--;
	//			//break;
	//		}

	//	}
	//}
	//if (deadcheck)
	//{
	//	dead->render(getMemDC(), rc.left, rc.top);
	//}

	//���⿡ ����hp2�׷�����
	/*if(TIMEMANAGER->getWorldTime()>87)
	IMAGEMANAGER->findImage("bosshp2")->render(getMemDC(), 15, 10,0,0,bosshpnum2,4);*/
	_missile->render();
	if (ending)
	{
		IMAGEMANAGER->findImage("end")->render(getMemDC());
	}
}	

void spaceShip::removeMissile(int arrNum)
{
	if (_missile)
	{
		_missile->removeMissile(arrNum);
	}
}

void spaceShip::collision()
{
	//�� �Ѿ˰� ���� �浹 ������...
	
	if (TIMEMANAGER->getWorldTime() > 44 && TIMEMANAGER->getWorldTime() < 45)
	{
		for (int j = 0; j < _em->getVMinion().size(); j++)
			_em->removeMinion(j);
	}
	if (TIMEMANAGER->getWorldTime() > 63 && TIMEMANAGER->getWorldTime() < 65)
	{
		for (int j = 0; j < _em->getVMinion().size(); j++)
			_em->removeMinion(j);
		midbossrc.right = 0;
		midbossrc.left = 0;
	}
	if (TIMEMANAGER->getWorldTime() > 85 && TIMEMANAGER->getWorldTime() <86)
	{
		for (int j = 0; j < _em->getVMinion().size(); j++)
			_em->removeMinion(j);
		
	}
	
	for (int j = 0; j < _em->getVMinion().size(); j++)
	{
		if (!die1)
		{
			if (IntersectRect(&rc, &_raystand->boundingBox(), &_em->getVMinion()[j]->getRect()))
			{
				//���̶� ���� �浹
				if(!ending)
				sndPlaySoundA("sound/dead.wav", SND_ASYNC | SND_NODEFAULT /*| SND_LOOP*/); //�״¼Ҹ�
				die1 = true;
			}
		}
	}
	if (TIMEMANAGER->getWorldTime() < 45)
	{
		for (int i = 0; i < _missile->getVBullet().size(); i++) //�̻��ϰ���
		{
			for (int j = 0; j < _em->getVMinion().size(); j++) //������
			{
				//�浹�˻�
				//RECT rc;
				if (IntersectRect(&rc, &_missile->getVBullet()[i].rc, &_em->getVMinion()[j]->getRect()))
				{
					if (!ending)
					sndPlaySoundA("sound/monsterdead.wav", SND_ASYNC | SND_NODEFAULT /*| SND_LOOP*/); //�״¼Ҹ�
					//deadcheck = true;
					alphanum = 250;
					score += 135311;
					_missile->removeMissile(i);
					_missile->init(1, 600);
					_em->removeMinion(j);
					break;
				}
			
			}
		}
	}
	else if (TIMEMANAGER->getWorldTime() > 45 && TIMEMANAGER->getWorldTime() < 65) //87
	{
		for (int i = 0; i < _missile->getVBullet().size(); i++) //�̻��ϰ���
		{
			for (int j = 0; j < _em->getVMinion().size(); j++) //������
			{
				//�浹�˻�
				//RECT rc;
				if (IntersectRect(&rc, &_missile->getVBullet()[i].rc, &_em->getVMinion()[j]->getRect()))
				{

					
					
					_missile->removeMissile(i);
					_missile->init(1, 600);
					//_em->removeMinion(j);
					midbossrc.right -= 5;
					
					if (midbossrc.right <= midbossrc.left)
					{
						
						sndPlaySoundA("sound/midbossdead.wav", SND_ASYNC | SND_NODEFAULT /*| SND_LOOP*/); //�״¼Ҹ�
						_em->removeMinion(j);
						score += 6979811;
					}
					break;
				}
			}
		}
	}
	else if (TIMEMANAGER->getWorldTime() > 65 && TIMEMANAGER->getWorldTime() < 87) //87
	{
		for (int i = 0; i < _missile->getVBullet().size(); i++) //�̻��ϰ���
		{
			for (int j = 0; j < _em->getVMinion().size(); j++) //������
			{
				//�浹�˻�
				//RECT rc;
				if (IntersectRect(&rc, &_missile->getVBullet()[i].rc, &_em->getVMinion()[j]->getRect()))
				{
					if (!ending)
					sndPlaySoundA("sound/monsterdead.wav", SND_ASYNC | SND_NODEFAULT /*| SND_LOOP*/); //�״¼Ҹ�

					score += 135311;
					_missile->removeMissile(i);
					_missile->init(1, 600);
					_em->removeMinion(j);
					

					
					break;
				}
			}
		}
	}
	else if (TIMEMANAGER->getWorldTime() > 87)
	{
		for (int i = 0; i < _missile->getVBullet().size(); i++) //�̻��ϰ���
		{
			for (int j = 0; j < _em->getVMinion().size(); j++) //������
			{
				//�浹�˻�
				//RECT rc;
				if (IntersectRect(&rc, &_missile->getVBullet()[i].rc, &_em->getVMinion()[j]->getRect()))
				{

					if (bosshpnum > 280) bosshpnum += 1;
					else bosshpnum += 3;
					
					_missile->removeMissile(i);
					_missile->init(1, 600);
					
					
					if (bosshpnum>=340)
					{
						
						sndPlaySoundA("sound/bossdead.wav", SND_ASYNC | SND_NODEFAULT /*| SND_LOOP*/); //�״¼Ҹ�
						
						_em->removeMinion(j);
							
							
						
						score += 69098031;
						
						break;
					}
					break;
				}
			}
		}
	}
}
