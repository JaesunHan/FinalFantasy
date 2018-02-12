#include "stdafx.h"
#include "worldMapPlayer.h"


worldMapPlayer::worldMapPlayer()
{
}


worldMapPlayer::~worldMapPlayer()
{
}

HRESULT worldMapPlayer::init(int playerX, int playerY)
{
	_image = IMAGEMANAGER->addFrameImage("������÷��̾�", ".//image//playerImg//player1Move.bmp", 84, 184, 3, 4, true, RGB(255, 0, 255));
	
	_player.x = playerX;
	_player.y = playerY;

	_rc = RectMake(_player.x, _player.y+30, TILE_SIZEX, TILE_SIZEY/2);

	_currentFrameX = 0;
	_currentFrameY = 0;

	_moveSpeed = 2.0f;

	_worldPlayerDirection = WPDOWN;

	_isCollision = false;
	_checkRc = false;


	_worldMap = new worldMap;
	_worldMap->init();


	return S_OK;
}

void worldMapPlayer::release()
{
}

void worldMapPlayer::update()
{
	worldPlayerImageFrameControl();
	worldPlayerKeyControl();

}

void worldMapPlayer::render()
{
	worldPlayerImageControl();
	//IMAGEMANAGER->findImage("������÷��̾�")->frameRender(getMemDC(),_player.x, _player.y, _currentFrameX, _currentFrameY);
}

void worldMapPlayer::worldPlayerImageFrameControl()
{

	_count++;

	if (_count % 10 == 0)
	{
		_currentFrameX += 1;
		
		if (_currentFrameX == _image->getMaxFrameX())
		{
			_currentFrameX = 0;
		}
	}
}

void worldMapPlayer::worldPlayerImageControl()
{
	switch (_worldPlayerDirection)
	{
		case WPRIGHT: _currentFrameY = 3;
			IMAGEMANAGER->findImage("������÷��̾�")->frameRender(getMemDC(), _player.x, _player.y, _currentFrameX, _currentFrameY);
		break;

		case WPLEFT: _currentFrameY = 2;
			IMAGEMANAGER->findImage("������÷��̾�")->frameRender(getMemDC(), _player.x, _player.y, _currentFrameX, _currentFrameY);
		break;

		case WPUP: _currentFrameY = 1;
			IMAGEMANAGER->findImage("������÷��̾�")->frameRender(getMemDC(), _player.x, _player.y, _currentFrameX, _currentFrameY);
		break;
				
		case WPDOWN: _currentFrameY = 0;
			IMAGEMANAGER->findImage("������÷��̾�")->frameRender(getMemDC(), _player.x, _player.y, _currentFrameX, _currentFrameY);
		break;
	}

	if (_checkRc)
	{
		Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);
	}

}

void worldMapPlayer::worldPlayerKeyControl()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_worldPlayerDirection = WPLEFT;
		_player.x -= _moveSpeed;
		_rc = RectMake(_player.x, _player.y + 30, TILE_SIZEX, TILE_SIZEY / 2);

		//���� �Ӽ����� �޴´�.
		//worldMapŬ�������� Ÿ�������ͷ� �ε�Ǿ��ִ� ���̺�Ǿ��� Ÿ���� �Ӽ��� �޾Ƽ�
		//Ÿ���ε����� �޴� �Լ��� ���� ������ġ�� �ֺ��� Ÿ�ϼӼ��� �����Ͽ�
		//���� �� �Ӽ��� �������̴� �༮�̸� �����̴� �ӵ��� �ݴ�� �ش�.
		if (_worldMap->getWorldMapTiles()[tileNum(_rc.left, _rc.top + 3)].getTerrainAttr() == ATTR_UNMOVE ||
			_worldMap->getWorldMapTiles()[tileNum(_rc.left, _rc.bottom - 3)].getTerrainAttr() == ATTR_UNMOVE)
		{
			_player.x += _moveSpeed;
		}
		//������Ʈ��Ʈ����Ʈ�� �߰��ؾ��Ѵ�
		//������Ʈ �Ӽ� OBJ_MOUNTAIN, OBJ_CAVE, OBJ_TOWN, OBJ_CASTLE, OBJ_NPC, OBJ_ENEMY,
	}
	else if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_worldPlayerDirection = WPRIGHT;
		_player.x += _moveSpeed;
		_rc = RectMake(_player.x, _player.y + 30, TILE_SIZEX, TILE_SIZEY / 2);
		if (_worldMap->getWorldMapTiles()[tileNum(_rc.right, _rc.top + 3)].getTerrainAttr() == ATTR_UNMOVE ||
			_worldMap->getWorldMapTiles()[tileNum(_rc.right, _rc.bottom - 3)].getTerrainAttr() == ATTR_UNMOVE)
		{
			_player.x -= _moveSpeed;
		}
	}
	else if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_worldPlayerDirection = WPUP;
		_player.y -= _moveSpeed;
		_rc = RectMake(_player.x, _player.y + 30, TILE_SIZEX, TILE_SIZEY / 2);
		if (_worldMap->getWorldMapTiles()[tileNum(_rc.left + 3, _rc.top)].getTerrainAttr() == ATTR_UNMOVE ||
			_worldMap->getWorldMapTiles()[tileNum(_rc.right - 3, _rc.top)].getTerrainAttr() == ATTR_UNMOVE)
		{
			_player.y += _moveSpeed;
		}
	}
	else if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_worldPlayerDirection = WPDOWN;
		_player.y += _moveSpeed;
		_rc = RectMake(_player.x, _player.y + 30, TILE_SIZEX, TILE_SIZEY / 2);
		if (_worldMap->getWorldMapTiles()[tileNum(_rc.left+3, _rc.bottom)].getTerrainAttr() == ATTR_UNMOVE ||
			_worldMap->getWorldMapTiles()[tileNum(_rc.right-3, _rc.bottom)].getTerrainAttr() == ATTR_UNMOVE)
		{
			_player.y -= _moveSpeed;
		}
	}
	
	//��Ʈ üũ��
	if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{
		_checkRc = true;
	}


	switch (_worldPlayerDirection)
	{
	case WPRIGHT: //_tile->getTerrainAttr()[tileNum(_rc.left)]
		break;

	case WPLEFT: //if (_worldMap->getWorldMapTiles()[tileNum(_rc.left, _rc.top + 3)].getTerrainAttr() == ATTR_UNMOVE ||
		//_worldMap->getWorldMapTiles()[tileNum(_rc.left, _rc.bottom - 3)].getTerrainAttr() == ATTR_UNMOVE)
	//{
	//	_player.x += _moveSpeed;
	//}
		break;

	case WPUP:
		break;

	case WPDOWN: 
		break;
	}
}


int worldMapPlayer::tileNum(float x, float y)
{
	//Ÿ�� ���⿡ ����� Ÿ�� �ε���
	int tileX, tileY;	//�÷��̾� ������⿡ '����'�� Ÿ�� �ε��� ����� ���� 

	int tileNum;

	tileNum = 0;

	//���� Ÿ�� ��ġ�� �˱� ���� �����ǿ��� Ÿ�ϻ������ �����ش�.
	tileX = x / TILE_SIZEX;
	tileY = y / TILE_SIZEY;

	//����� Ÿ���� ->  ���� 5x5 ������ Ÿ���϶�
	//Ÿ��y ���ϱ� xŸ�ϰ����� �ϸ� 0���� ���° Y��° Ÿ�ϱ������� ����̵ǰ� 
	//�� ���� Ÿ��X�� ���ϸ� ���° XŸ�������� ���´�.
	//����ʿ� ����� �� ũ���� x���� �޾ƿ��� 
	tileNum = tileY * _worldMap->getWorldMapPOINT().x + tileX;

	return tileNum;
}