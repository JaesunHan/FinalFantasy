#include "stdafx.h"
#include "worldMapTreasureBox.h"


worldMapTreasureBox::worldMapTreasureBox()
{
}


worldMapTreasureBox::~worldMapTreasureBox()
{
}

HRESULT worldMapTreasureBox::init(int enemyX, int enemyY, ENEMYMOVEPATTERN enemyPattern)
{
	//����Ŭ���� init �ѹ� ���Ƽ� �⺻ ���� �������� 
	worldMapEnemy::init(enemyX, enemyY, enemyPattern);
	//�߰��� ������ �ϴ� ������.

	_image = IMAGEMANAGER->addFrameImage("����ʹڽ�", ".//image//enemyImg//treasureBox.bmp", 120, 29, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���¹ڽ�", ".//image//enemyImg//treasureBoxOpen.bmp", 31, 29, true, RGB(255, 0, 255));
	_enemyType = ENEMY_TREASUREBOX;

	_treasureCount = 0;

	_isBox = false;

	//�̹��̴� �ƴϴ�
	_isMimic = RND->getFromIntTo(1, 1);

	_enemyMovePattern = enemyPattern;
	return S_OK;
}

void worldMapTreasureBox::release()
{
}

void worldMapTreasureBox::update()
{
	isMimic();
	worldMapEnemy::update();
	this->move();
	worldEnemyImageFrameControl();
	worldEnemyCollision();
}

void worldMapTreasureBox::render(HDC hdc, POINT movePt)
{
	worldEnemyImageControl(hdc, movePt);

	if (_isDebug)
	{
		Rectangle(hdc, _rc.left - movePt.x, _rc.top - movePt.y, _rc.right - movePt.x, _rc.bottom - movePt.y);
	}
}

void worldMapTreasureBox::move()
{
	//�̹ͶǴ� �������ڶ� ������ ����. 
	if (!_isDetect)
	{
		switch (_enemyMovePattern)
		{
		case ENEMYPATTERN_ONE:
		break;
		}
	}
}

void worldMapTreasureBox::worldEnemyImageFrameControl()
{
	/*if (_isBox)
	{
		_count++;

		if (_count % 10 == 0)
		{
			_enemyCurrentFrameX++;

			if (_enemyCurrentFrameX == _image->getMaxFrameX())
			{
				_enemyCurrentFrameX = _image->getMaxFrameX();
			}
		}
	}*/
}

void worldMapTreasureBox::worldEnemyImageControl(HDC hdc, POINT movePt)
{
	switch (_enemyDirection)
	{
	case ENEMYDIRECTION_RIGHT: _image = IMAGEMANAGER->findImage("����ʹڽ�");
		_image->frameRender(hdc, _enemy.x - movePt.x, _enemy.y - movePt.y, _enemyCurrentFrameX, 0);

		break;
	case ENEMYDIRECTION_LEFT: _image = IMAGEMANAGER->findImage("����ʹڽ�");
		_image->frameRender(hdc, _enemy.x - movePt.x, _enemy.y - movePt.y, _enemyCurrentFrameX, 0);
		break;
	}
	
	if (_isBox && _isCollision)
	{
		_image = IMAGEMANAGER->findImage("���¹ڽ�");
		_image->render(hdc, _enemy.x - movePt.x, _enemy.y - movePt.y);
	}

}


void worldMapTreasureBox::worldEnemyDetect()
{
	
}


void worldMapTreasureBox::worldEnemyCollision()
{
	
	if (getDistance(_enemy.x, _enemy.y, _wp->getWorldMapPlayerPoint().x, _wp->getWorldMapPlayerPoint().y) <= TILE_SIZEX)
	{
		_isCollision = true;
	}
}

void worldMapTreasureBox::isMimic()
{
	if (_isMimic == 1)
	{
		_isBox = true;
	}
	else if (_isMimic == 2 || _isMimic ==3)
	{
		_isBox = false;
	}
}

