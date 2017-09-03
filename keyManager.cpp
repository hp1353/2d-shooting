#include "stdafx.h"
#include "keyManager.h"


keyManager::keyManager()
{
}


keyManager::~keyManager()
{
}

HRESULT keyManager::init()
{
	for (int i = 0; i < KEYMAX; i++)
	{
		this->_keyDown.set(i, false);
		this->_keyUp.set(i, false);
	}

	return S_OK;
}

void keyManager::release()
{

}

//is 붙이면 bool 과 관련되어 있다고 생각되어질 수 있다. ( 가독성 향상 )
bool keyManager::isOnceDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		if (this->_keyDown[key] == false)
		{
			this->_keyDown.set(key, true);
			return true;
		}
	}
	else
	{
		this->_keyDown.set(key, false);
	}

	return false;
}

bool keyManager::isOnceUp(int key)
{
	if (GetAsyncKeyState(key) & 0x8000) _keyUp.set(key, true);
	else
	{
		if (_keyUp[key])
		{
			_keyUp.set(key, false);
			return true;
		}
	}

	return false;
}

bool keyManager::isStayDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000) return true;
	else return false;
}

bool keyManager::isToggle(int key)
{
	if (GetKeyState(key) & 0x0001) return true;
	else return false;
}