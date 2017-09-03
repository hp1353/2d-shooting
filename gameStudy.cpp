#include "stdafx.h"
#include "gameStudy.h"

MCI_OPEN_PARMS m_mciOpenParms;
MCI_PLAY_PARMS m_mciPlayParms;
DWORD m_dwDeviceID;
MCI_OPEN_PARMS mciOpen;
MCI_PLAY_PARMS mciPlay;

int dwID;

gameStudy::gameStudy()
{
}


gameStudy::~gameStudy()
{
}

//초기화는 여기서 한다
HRESULT gameStudy::init()
{
	gameNode::init(true);
	//시작전
	IMAGEMANAGER->addImage("startimage", "image/startimage.bmp", WINSIZEX, WINSIZEY, false, false);
	IMAGEMANAGER->addImage("nstart", "image/nstart.bmp", 73, 34, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("start", "image/start.bmp", 73, 34, true, RGB(255, 0, 255));
	startrc = RectMakeCenter(485, 220, 73, 34);
	ready = false;
	start = false;
	worldtime = 0;
	///
	IMAGEMANAGER->addImage("background", "image/stage1.bmp", WINSIZEX/5 *3, WINSIZEY, false, false);
	IMAGEMANAGER->addImage("scoreboard", "image/scoreboard.bmp", WINSIZEX/5*2, WINSIZEY, false, false);
	IMAGEMANAGER->addImage("bullet", "image/bullet.bmp", 17, 19, true, RGB(255, 242, 0));
	
	enemys = IMAGEMANAGER->addFrameImage("enemys", "image/enemys.bmp", 108, 25, 4, 1, true, RGB(255, 255, 255));
	enemy2 = IMAGEMANAGER->addFrameImage("enemy2", "image/enemy2.bmp", 222, 41, 7, 1, true, RGB(255, 242, 0));
	midboss = IMAGEMANAGER->addFrameImage("midboss", "image/midboss.bmp", 192, 64, 4, 1, true, RGB(255, 242, 0));
	boss = IMAGEMANAGER->addFrameImage("boss", "image/boss.bmp", 113, 56, 4, 1, true, RGB(255, 242, 0));
	bosshp = IMAGEMANAGER->addImage("bosshp", "image/bosshp.bmp", 320, 4, false, false);
	
	erc = RectMakeCenter(200, 10, 25, 25);
	_alphaImage = new image;
	_alphaImage->init("image/sbgm.bmp", 32, 280, true, RGB(255, 0, 255));
	_alphatext = new image;
	_alphatext->init("image/text.bmp", 245, 36, true, RGB(255, 242, 0));
	stage1text = new image;
	stage1text->init("image/stage1text.bmp", 94, 35, true, RGB(255, 242, 0));

	IMAGEMANAGER->addImage("boom1", "image/boom1.bmp", 254, 261, true, RGB(255, 242, 0));
	IMAGEMANAGER->addImage("boom2", "image/boom2.bmp", 146, 288, true, RGB(255, 242, 0));
	

	_x = 0.0f;
	loop = 0.f;
	sidemove = false;
	emovey = 0;
	time = 0;
	alphanum = 0;
	alphanum2 = 1;
	alphanum22 = false;
	sbgmmove = 480;
	textmove = 0.f;
	stage1textmove = 0.f;
	mciclose = false;
	mciclose2 = false;
	boom = false;
	boomcheck2move = 320.f;
	_ship = new spaceShip;
	_ship->init();

	_enemyManager = new enemyManager;
	_enemyManager->init();
	_enemyManager->setMinion();

	_ship->setEmMemoryLink(_enemyManager);
	_enemyManager->setShipMemoryLink(_ship);



	return S_OK;
}

//메모리 해제는 여기서
void gameStudy::release()
{
	_ship->release();
	SAFE_DELETE(_ship);

	_enemyManager->release();
	SAFE_DELETE(_enemyManager);

	_alphaImage->release();
	SAFE_DELETE(_alphaImage);

	_alphatext->release();
	SAFE_DELETE(_alphatext);

	stage1text->release();
	SAFE_DELETE(stage1text);

	


	gameNode::release();
}

//계속 무한 반복 되어야 할 것들 여기서
void gameStudy::update()
{
	_ship->update();
	_enemyManager->update();
	if (PtInRect(&startrc, _ptMouse))//start에 마우스 갔다대면
	{
		ready = true;
		if (KEYMANAGER->isOnceDown(VK_LBUTTON))
		{
			start = true;
		}
	}
	else
	{
		ready = false;
	}
	if (TIMEMANAGER->getWorldTime() > 10)//5초지나면 걍실행함
	{
		start = true;
	}
	//사운드
	if (start)
	{
		if (TIMEMANAGER->getWorldTime() < 87&&!mciclose)
		{
			mciOpen.lpstrElementName = "sound/stage1bgm.mp3"; // 파일 경로 입력
			mciOpen.lpstrDeviceType = "mpegvideo";

			mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE,
				(DWORD)(LPVOID)&mciOpen);

			dwID = mciOpen.wDeviceID;
			mciSendCommand(dwID, MCI_PLAY, 0x00010000L, // play & repeat
				(DWORD)(LPVOID)&m_mciPlayParms);
		}
		if(TIMEMANAGER->getWorldTime()>87 &&TIMEMANAGER->getWorldTime()<88 && !mciclose)
		{
			mciSendCommandW(dwID, MCI_CLOSE, 0, NULL);
			mciclose = true;
			

		}
	}
	//
	_count++;
	enemys->setFrameY(0);
	

	if (_count % 8 == 0)
	{
		_index++;
		
		enemys->setFrameX(_index);

		if (_index > enemys->getMaxFrameX())
		{
			_index = -1;
		}

	}
	
	if (TIMEMANAGER->getWorldTime() > 90 && !mciclose2)
	{
		mciOpen.lpstrElementName = "sound/bossbgm.mp3"; // 파일 경로 입력
		mciOpen.lpstrDeviceType = "mpegvideo";

		mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE,
			(DWORD)(LPVOID)&mciOpen);

		dwID = mciOpen.wDeviceID;
		mciSendCommand(dwID, MCI_PLAY, 0x00010000L, // play & repeat
			(DWORD)(LPVOID)&m_mciPlayParms);
	}
	if (_ship->bosshpnum2 == 0 && _ship->bosshpnum >= 340 && !mciclose2)
	{
		
			mciSendCommandW(dwID, MCI_CLOSE, 0, NULL);
			mciclose2 = true;
	}
	
	
	gameNode::update();
}

//그려주는 건 여기서
void gameStudy::render()
{
	
	//배경 색
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);

	if (!start) //시작누르기전
	{

		IMAGEMANAGER->findImage("startimage")->render(getMemDC());
	
		//Rectangle(getMemDC(), startrc.left, startrc.top, startrc.right, startrc.bottom);
		IMAGEMANAGER->render("nstart", getMemDC(), 450, 200);
		if (ready)
		{
			IMAGEMANAGER->render("start", getMemDC(), 450, 200);
		}
		
	}
	else //시작 누르면
	{
		
		IMAGEMANAGER->findImage("background")->loopRender(getMemDC(), &RectMake(0, 0, WINSIZEX / 5 *3, WINSIZEY), 0, _x = _x - loop);
		IMAGEMANAGER->findImage("scoreboard")->loopRender(getMemDC(), &RectMake(WINSIZEX/5*3, 0, WINSIZEX/5*2, WINSIZEY), 0, 0);
		//IMAGEMANAGER->alphaRender("boom2", getMemDC(), 100, 100, 111);
		loop += 0.002f;
		
		if (loop > 3.f)loop = 3.f;
		//===============================================
		
		_ship->render();

		_enemyManager->render();
		
		

		time++;
		if (time > 200 && time<1000)
		{
			
			_alphaImage->alphaRender(getMemDC(), WINSIZEX/5*3-30, sbgmmove, alphanum);
			_alphatext->alphaRender(getMemDC(), WINSIZEX/5*3  - textmove, 250, alphanum);
			stage1text->alphaRender(getMemDC(), stage1textmove, 100, alphanum);
			//boom2->alphaRender(getMemDC(), 20, 20, 111);
			
			if (sbgmmove <= 50)sbgmmove = 50;
			else sbgmmove -= 1;
			if (alphanum > 250)alphanum = 250;
			else alphanum += 2;
			if (textmove >= 300)textmove = 300;
			else textmove += 1.f;
			if (stage1textmove >= 100)stage1textmove = 100;
			else stage1textmove += 0.5f;
		}
		if (time > 1000)
		{
			if (!alphanum <= 0)
			{
				_alphaImage->alphaRender(getMemDC(), WINSIZEX / 5 * 3 - 30, 50, alphanum);
				_alphatext->alphaRender(getMemDC(), WINSIZEX/5*3-300 , 250, alphanum);
				stage1text->alphaRender(getMemDC(), 100, 100, alphanum);
				alphanum -= 2;
			}
		  
		}
		
		
	}
	
	//===============================================
	//백버퍼에 있는 내용을 HDC에 그린다.
	//TIMEMANAGER->render(getMemDC());
	if (_ship->ending)
	{
		IMAGEMANAGER->findImage("end")->render(getMemDC());
		mciSendCommandW(dwID, MCI_CLOSE, 0, NULL);
		mciclose = true;
		mciclose2 = true;
	}
	this->getBackBuffer()->render(getHDC());
}
