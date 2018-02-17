#include "stdafx.h"
#include "worldEnemyBear.h"
//#include 

worldEnemyBear::worldEnemyBear()
{
}


worldEnemyBear::~worldEnemyBear()
{
}

HRESULT worldEnemyBear::init(int enemyX, int enemyY)
{

	//����Ŭ���� init �ѹ� ���Ƽ� �⺻ ���� �������� 
	worldMapEnemy::init(enemyX, enemyY);
	//�߰��� ������ �ϴ� ������.
	IMAGEMANAGER->addFrameImage("����ʰ����̿���", ".//image//enemyImg//worldEnemy_bear_left.bmp", 174, 34, 6, 1, true, RGB(255, 0, 255));
	_image = IMAGEMANAGER->addFrameImage("����ʰ�����", ".//image//enemyImg//worldEnemy_bear.bmp", 170, 34, 6, 1, true, RGB(255, 0, 255));

	_enemyType = ENEMY_BEAR;

	return S_OK;
}

void worldEnemyBear::release()
{
}

void worldEnemyBear::update()
{
	worldMapEnemy::update();
}

void worldEnemyBear::render()
{
	worldEnemyImageControl();

	if (_isDebug)
	{
		Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);
	}
}

void worldEnemyBear::move()
{
	worldMapEnemy::move();
}

void worldEnemyBear::worldEnemyImageFrameControl()
{
	worldMapEnemy::worldEnemyImageFrameControl();
}

void worldEnemyBear::worldEnemyImageControl()
{
	//�÷��̾�� ���ʹ��� ��ġ�� ���� ���ʹ� ���� ���� ����
	switch (_enemyDirection)
	{
	case ENEMYDIRECTION_RIGHT: _image = IMAGEMANAGER->findImage("����ʰ�����");
		_image->frameRender(getMemDC(), _enemy.x, _enemy.y, _enemyCurrentFrameX, 0);

		break;
	case ENEMYDIRECTION_LEFT: _image = IMAGEMANAGER->findImage("����ʰ����̿���");
		_image->frameRender(getMemDC(), _enemy.x, _enemy.y, _enemyCurrentFrameX, 0);
		break;
	}
}

