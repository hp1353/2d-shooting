#pragma once


#include "gameNode.h"
#include <vector>

struct tagBullet
{
	image* bulletImage;
	image* raybullet;
	RECT rc;
	int radius;
	float angle;
	float x, y;
	float fireX, fireY;
	float speed;
	bool fire;
	int count; //������ ���� ��
};

class missile : public gameNode
{
private:
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	float _range; //���� �Ÿ�

public:
	missile();
	~missile();

	HRESULT init(int bulletMax, float range);
	void release();
	void update();
	void render();

	//�̻��� �߻�
	void fire(float x, float y);
	//�̻��� ����
	void move();

	void removeMissile(int arrNum);

	vector<tagBullet> getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator getVIBullet() { return _viBullet; }
};

class bullet : public gameNode
{
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	const char* _imageName;
	float _range;
	int _bulletMax;

public:
	bullet();
	~bullet();

	HRESULT init(const char* imageName, int bulletMax, float range);
	void release();
	void update();
	void render();

	void fire(float x, float y, float angle, float speed);

	void move();

	void removeBullet(int arrNum);

	vector<tagBullet> getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator getVIBullet() { return _viBullet; }
};