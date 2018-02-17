#include "stdafx.h"
#include "worldMapEnemySamurai.h"


worldMapEnemySamurai::worldMapEnemySamurai()
{
}


worldMapEnemySamurai::~worldMapEnemySamurai()
{
}

HRESULT worldMapEnemySamurai::init(int enemyX, int enemyY)
{
	//마더 클래스 정보 가져오고 
	worldMapEnemy::init(enemyX, enemyY);
	IMAGEMANAGER->addFrameImage("월드맵사무라이왼쪽", ".//image//enemyImg//worldEnemy_samurai_left.bmp", 192, 54, 4, 1, true, RGB(255, 0, 255));
	_image = IMAGEMANAGER->addFrameImage("월드맵사무라이", ".//image//enemyImg//worldEnemy_samurai.bmp", 190, 54, 4, 1, true, RGB(255, 0, 255));

	_enemyType = ENEMY_SKELETON;

	return S_OK;


}

void worldMapEnemySamurai::release()
{
}

void worldMapEnemySamurai::update()
{
	worldMapEnemy::update();
}

void worldMapEnemySamurai::render()
{
	worldEnemyImageControl();

	if (_isDebug)
	{
		Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);
	}
}

void worldMapEnemySamurai::move()
{
	worldMapEnemy::move();
}

void worldMapEnemySamurai::worldEnemyImageFrameControl()
{

}

void worldMapEnemySamurai::worldEnemyImageControl()
{

	//플레이어와 에너미의 위치에 따른 에너미 보는 방향 변경
	switch (_enemyDirection)
	{
	case ENEMYDIRECTION_RIGHT: _image = IMAGEMANAGER->findImage("월드맵사무라이");
		_image->frameRender(getMemDC(), _enemy.x, _enemy.y, _enemyCurrentFrameX, 0);

		break;
	case ENEMYDIRECTION_LEFT: _image = IMAGEMANAGER->findImage("월드맵사무라이왼쪽");
		_image->frameRender(getMemDC(), _enemy.x, _enemy.y, _enemyCurrentFrameX, 0);
		break;
	}
}