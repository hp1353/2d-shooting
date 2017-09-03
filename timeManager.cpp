#include "stdafx.h"
#include "timeManager.h"


timeManager::timeManager() : _timer(NULL)
{
}


timeManager::~timeManager()
{
}

HRESULT timeManager::init()
{
	//타이머 생성
	
		_timer = new timer;

		_timer->init();
	
   
	return S_OK;
}

void timeManager::release()
{
	if (_timer != NULL)
	{
		SAFE_DELETE(_timer);
	}
}

void timeManager::update(float lock)
{
	
		if (_timer != NULL)
			_timer->tick(lock);
	
}

void timeManager::render(HDC hdc)
{
	char str[256];
	string strFrame;

	//글자 배경모드 (TRANSPARENT : 투명 , QPAQUEL : 불투명)
	SetBkMode(hdc, TRANSPARENT);

	//글자 색상
	SetTextColor(hdc, RGB(255, 255, 255));

#ifdef _DEBUG
	{
		if (_timer != NULL)
		{
			
				//프레임 찍어주자
				wsprintf(str, "frmaePerSec : %d", _timer->getFrameRate());
				TextOut(hdc, 0, 0, str, strlen(str));

				//월드타임 찍어주자
				sprintf_s(str, "worldtime : %f", _timer->getWorldTime());
				TextOut(hdc, 0, 20, str, strlen(str));

				//갱신 Tick 찍어주자
				sprintf_s(str, "elapsedTime : %f", _timer->getElapsedTime());
				TextOut(hdc, 0, 40, str, strlen(str));
			
		}
	}
#else
	{
		if (_timer != NULL)
		{
			//프레임 찍어주자
			wsprintf(str, "frmaePerSec : %d", _timer->getFrameRate());
			TextOut(hdc, 0, 0, str, strlen(str));
		}
	}
#endif
}
