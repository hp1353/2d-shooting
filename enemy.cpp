#include "stdafx.h"
#include "enemy.h"
#include "gameStudy.h"
#include "spaceShip.h"
enemy::enemy()
{
}


enemy::~enemy()
{
}

HRESULT enemy::init()
{
	return S_OK;
}

HRESULT enemy::init(const char * imageName, POINT postion)
{
	_currentFrameX = _currentFrameY = 0;
	_count = 0;
	enemycount = 0;
	_fireCount = 0;
	_fireCount1 = 50;
	_fireCount2 = 0;
	_fireCount3 = 0;
	_fireCount4 = 0;
	_fireCount5 = 0;
	testcount = 0;
	gi = false;
	_rndFireCount = RND->getFromIntTo(1, 1000);

	_imageName = IMAGEMANAGER->findImage(imageName);
	_rc = RectMakeCenter(postion.x, postion.y, _imageName->getFrameWidth(), _imageName->getFrameHeight());
	
	
	return S_OK;
}

void enemy::release()
{
}

void enemy::update()
{
	//프레임 돌리자
	_count++;
	enemycount++;

	if (_count % 10 == 0)
	{
		_imageName->setFrameX(_imageName->getFrameX() + 1);
		_currentFrameX++;
		if (_currentFrameX > _imageName->getMaxFrameX()) _currentFrameX = 0;
	}
	
	if (TIMEMANAGER->getWorldTime() > 12 &&TIMEMANAGER->getWorldTime() <18)
	{
		_rc = RectMakeCenter(_rc.left + (_rc.right - _rc.left) / 2, _rc.top + (_rc.bottom - _rc.top) / 2 + 1,
			_imageName->getFrameWidth(), _imageName->getFrameHeight());//렉트움직이면 적도 움직인다

		
	}
	if (TIMEMANAGER->getWorldTime() > 14 && TIMEMANAGER->getWorldTime()<18)
	{
		_rc = RectMakeCenter(_rc.left + (_rc.right - _rc.left) / 2 - 1, _rc.top + (_rc.bottom - _rc.top) / 2 + 1 / 4,
			_imageName->getFrameWidth(), _imageName->getFrameHeight());//렉트움직이면 적도 움직인다
	}
	if (TIMEMANAGER->getWorldTime() > 18 && TIMEMANAGER->getWorldTime() <24)
	{
		_rc = RectMakeCenter(_rc.left + (_rc.right - _rc.left) / 2, _rc.top + (_rc.bottom - _rc.top) / 2 + 1,
			_imageName->getFrameWidth(), _imageName->getFrameHeight());//렉트움직이면 적도 움직인다


	}
	if (TIMEMANAGER->getWorldTime() > 20 && TIMEMANAGER->getWorldTime() <24)
	{
		_rc = RectMakeCenter(_rc.left + (_rc.right - _rc.left) / 2 + 1, _rc.top + (_rc.bottom - _rc.top) / 2 ,
			_imageName->getFrameWidth(), _imageName->getFrameHeight());//렉트움직이면 적도 움직인다


	}
	if (TIMEMANAGER->getWorldTime() > 24 && TIMEMANAGER->getWorldTime() <30)
	{
		_rc = RectMakeCenter(_rc.left + (_rc.right - _rc.left) / 2, _rc.top + (_rc.bottom - _rc.top) / 2 + 1,
			_imageName->getFrameWidth(), _imageName->getFrameHeight());//렉트움직이면 적도 움직인다


	}
	if (TIMEMANAGER->getWorldTime() > 26 && TIMEMANAGER->getWorldTime()<30)
	{
		_rc = RectMakeCenter(_rc.left + (_rc.right - _rc.left) / 2 - 1, _rc.top + (_rc.bottom - _rc.top) / 2 + 1 / 4,
			_imageName->getFrameWidth(), _imageName->getFrameHeight());//렉트움직이면 적도 움직인다
	}
	if (TIMEMANAGER->getWorldTime() > 30 && TIMEMANAGER->getWorldTime() <36)
	{
		_rc = RectMakeCenter(_rc.left + (_rc.right - _rc.left) / 2, _rc.top + (_rc.bottom - _rc.top) / 2 + 1,
			_imageName->getFrameWidth(), _imageName->getFrameHeight());//렉트움직이면 적도 움직인다


	}
	if (TIMEMANAGER->getWorldTime() > 32 && TIMEMANAGER->getWorldTime() <36)
	{
		_rc = RectMakeCenter(_rc.left + (_rc.right - _rc.left) / 2 + 1, _rc.top + (_rc.bottom - _rc.top) / 2,
			_imageName->getFrameWidth(), _imageName->getFrameHeight());//렉트움직이면 적도 움직인다


	}//////////////여기까지 짤몹패턴1
	if (TIMEMANAGER->getWorldTime() > 36 && TIMEMANAGER->getWorldTime() <44)
	{
		_rc = RectMakeCenter(_rc.left + (_rc.right - _rc.left) / 2 , _rc.top + (_rc.bottom - _rc.top) / 2+1,
			_imageName->getFrameWidth(), _imageName->getFrameHeight());//렉트움직이면 적도 움직인다


	}
	if (TIMEMANAGER->getWorldTime() > 45 && TIMEMANAGER->getWorldTime()<46)
	{
		_rc = RectMakeCenter(_rc.left + (_rc.right - _rc.left) / 2, _rc.top + (_rc.bottom - _rc.top) / 2 + 1,
			_imageName->getFrameWidth(), _imageName->getFrameHeight());
	}
	if (TIMEMANAGER->getWorldTime() > 46 && TIMEMANAGER->getWorldTime()<47)
	{
		_rc = RectMakeCenter(_rc.left + (_rc.right - _rc.left) / 2 + 1, _rc.top + (_rc.bottom - _rc.top) / 2+1 ,
			_imageName->getFrameWidth(), _imageName->getFrameHeight());
	}
	if (TIMEMANAGER->getWorldTime() > 48 && TIMEMANAGER->getWorldTime()<50)
	{
		_rc = RectMakeCenter(_rc.left + (_rc.right - _rc.left) / 2 - 1, _rc.top + (_rc.bottom - _rc.top) / 2 ,
			_imageName->getFrameWidth(), _imageName->getFrameHeight());
	}
	if (TIMEMANAGER->getWorldTime() > 50 && TIMEMANAGER->getWorldTime()<52)
	{
		_rc = RectMakeCenter(_rc.left + (_rc.right - _rc.left) / 2 - 1, _rc.top + (_rc.bottom - _rc.top) / 2 -1,
			_imageName->getFrameWidth(), _imageName->getFrameHeight());
	}
	if (TIMEMANAGER->getWorldTime() > 52 && TIMEMANAGER->getWorldTime()<54)
	{
		_rc = RectMakeCenter(_rc.left + (_rc.right - _rc.left) / 2 + 1, _rc.top + (_rc.bottom - _rc.top) / 2 + 1,
			_imageName->getFrameWidth(), _imageName->getFrameHeight());
	}
	if (TIMEMANAGER->getWorldTime() > 54 && TIMEMANAGER->getWorldTime()<56)
	{
		_rc = RectMakeCenter(_rc.left + (_rc.right - _rc.left) / 2 , _rc.top + (_rc.bottom - _rc.top) / 2 - 1,
			_imageName->getFrameWidth(), _imageName->getFrameHeight());
	}
	if (TIMEMANAGER->getWorldTime() > 60 && TIMEMANAGER->getWorldTime()<65)
	{
		_rc = RectMakeCenter(_rc.left + (_rc.right - _rc.left) / 2, _rc.top + (_rc.bottom - _rc.top) / 2 - 1,
			_imageName->getFrameWidth(), _imageName->getFrameHeight());
		//여기까지 중간보스 패턴
	}
	if (TIMEMANAGER->getWorldTime() > 65 && TIMEMANAGER->getWorldTime()<85)
	{
		_rc = RectMakeCenter(_rc.left + (_rc.right - _rc.left) / 2, _rc.top + (_rc.bottom - _rc.top) / 2 + 1,
			_imageName->getFrameWidth(), _imageName->getFrameHeight());

	}
	//여기까지 짤몹
	if (TIMEMANAGER->getWorldTime() > 87 && TIMEMANAGER->getWorldTime()<88)
	{
		_rc = RectMakeCenter(_rc.left + (_rc.right - _rc.left) / 2, _rc.top + (_rc.bottom - _rc.top) / 2 + 1,
			_imageName->getFrameWidth(), _imageName->getFrameHeight());

	}
	//보스
}

void enemy::render()
{
	draw();
	
}


void enemy::move()
{
	
}

void enemy::draw()
{
	_imageName->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY);
}

bool enemy::bulletCountFire()
{
	_fireCount1++;
	_fireCount++;
	if (TIMEMANAGER->getWorldTime() < 46)
	{
		if (_fireCount % _rndFireCount == 0)
		{
			_fireCount = 0;
			_rndFireCount = RND->getFromIntTo(1, 1000);
			return true;
		}
		return false;
	}
	if (TIMEMANAGER->getWorldTime() > 46 && TIMEMANAGER->getWorldTime()<64)
	{
		if (_fireCount1 > 500) //기모으는소리
		{
			gi = true;
			_fireCount1 =50;
			
			sndPlaySoundA("sound/se_power0.wav", SND_ASYNC | SND_NODEFAULT /*| SND_LOOP*/);
			IMAGEMANAGER->alphaRender("midbossgi", getMemDC(), 111,200,15);
		}
		if (_fireCount > 500 )
		{
			_fireCount = 50;
			
			sndPlaySoundA("sound/se_tan00.wav", SND_ASYNC | SND_NODEFAULT /*| SND_LOOP*/);
			return true;
		}

		return false;
	}
	if (TIMEMANAGER->getWorldTime() > 90 ) //보스 기본 탄막패턴
	{
		if (_fireCount > 500)
		{
			_fireCount = 0;
			
			sndPlaySoundA("sound/se_tan00.wav", SND_ASYNC | SND_NODEFAULT /*| SND_LOOP*/);
			return true;
		}
		return false;
	}
}
bool enemy::bulletCountFire1() //보스 딸피패턴1 (무작위쏘기)
{
	_fireCount2++;
	if (TIMEMANAGER->getWorldTime() > 90  )
	{
		if (_fireCount2 > 20)
		{
			_fireCount2 = 0;
			//sndPlaySoundA("sound/se_tan00.wav", SND_ASYNC | SND_NODEFAULT /*| SND_LOOP*/);
			return true;
		}

		return false;
	}
}

bool enemy::bulletCountFire2() //보스 딸피패턴1 (무작위쏘기)
{
	_fireCount3++;
	if (TIMEMANAGER->getWorldTime() > 90 )
	{
		if (_fireCount3 > 200)
		{
			_fireCount3 = 0;
			//sndPlaySoundA("sound/se_tan00.wav", SND_ASYNC | SND_NODEFAULT /*| SND_LOOP*/);
			return true;
		}

		return false;
	}
}

bool enemy::bulletCountFire3() 
{
	_fireCount4++;
	if (TIMEMANAGER->getWorldTime() > 90)
	{
		if (_fireCount4 > 200)
		{
			_fireCount4 = 0;
			
			return true;
		}

		return false;
	}
}

bool enemy::bulletCountFire4() 
{
	_fireCount5++;
	if (TIMEMANAGER->getWorldTime() > 90)
	{
		if (_fireCount5 > 200)
		{
			_fireCount5 = 0;
			
			return true;
		}

		return false;
	}
}