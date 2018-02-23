#include "stdafx.h"
#include "worldMapPlayer.h"
#include "generalMap.h"
#include "menu.h"

worldMapPlayer::worldMapPlayer()
{
}


worldMapPlayer::~worldMapPlayer()
{
}

HRESULT worldMapPlayer::init(int playerX, int playerY)
{
	_image = IMAGEMANAGER->addFrameImage("������÷��̾�", ".//image//playerImg//player1Move.bmp", 112, 184, 4, 4, true, RGB(255, 0, 255));
	
	_player.x = playerX;
	_player.y = playerY;

	_rc = RectMake(_player.x, _player.y+30, TILE_SIZEX, TILE_SIZEY/2);

	_currentFrameX = 0;
	_currentFrameY = 0;

	_moveSpeed = 2.0f;

	_worldPlayerDirection = WPDOWN;

	_isCollision = false;
	_checkRc = false;
	_isEscapeSuccess = false;
	_isEnter = false;
	_isWorldMapEnter = false;

	_battleCount = 0;
	_isEncount = false;
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

void worldMapPlayer::render(HDC hdc, POINT movePt)
{
	worldPlayerImageControl(hdc, movePt);
	//��Ʈ üũ��
	if (_isDebug)
	{
		Rectangle(hdc, _rc.left, _rc.top, _rc.right, _rc.bottom);
	}
	//IMAGEMANAGER->findImage("������÷��̾�")->frameRender(getMemDC(),_player.x, _player.y, _currentFrameX, _currentFrameY);
}

void worldMapPlayer::worldPlayerImageFrameControl()
{

	_count++;

	if (_count % 10 == 0)
	{
		_currentFrameX ++;
		
		if (_currentFrameX == _image->getMaxFrameX())
		{
			_currentFrameX = 0;
		}
	}
}

void worldMapPlayer::worldPlayerImageControl(HDC hdc, POINT movePt)
{
	switch (_worldPlayerDirection)
	{
		case WPRIGHT: _currentFrameY = 3;
			IMAGEMANAGER->findImage("������÷��̾�")->frameRender(hdc, _player.x - movePt.x, _player.y - movePt.y, _currentFrameX, _currentFrameY);
		break;

		case WPLEFT: _currentFrameY = 2;
			IMAGEMANAGER->findImage("������÷��̾�")->frameRender(hdc, _player.x - movePt.x, _player.y - movePt.y, _currentFrameX, _currentFrameY);
		break;

		case WPUP: _currentFrameY = 1;
			IMAGEMANAGER->findImage("������÷��̾�")->frameRender(hdc, _player.x - movePt.x, _player.y - movePt.y, _currentFrameX, _currentFrameY);
		break;
				
		case WPDOWN: _currentFrameY = 0;
			IMAGEMANAGER->findImage("������÷��̾�")->frameRender(hdc, _player.x - movePt.x, _player.y - movePt.y, _currentFrameX, _currentFrameY);
		break;
	}


}

void worldMapPlayer::worldPlayerKeyControl()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
					//�������� ���ؼ� 
		_battleCount += INCRESECOUNTRANGE;
		_worldPlayerDirection = WPLEFT;
		_player.x -= _moveSpeed;
		_rc = RectMake(_player.x, _player.y + 30, TILE_SIZEX, TILE_SIZEY / 2);

		//���� �Ӽ����� �޴´�.
		//worldMapŬ�������� Ÿ�������ͷ� �ε�Ǿ��ִ� ���̺�Ǿ��� Ÿ���� �Ӽ��� �޾Ƽ�
		//Ÿ���ε����� �޴� �Լ��� ���� ������ġ�� �ֺ��� Ÿ�ϼӼ��� �����Ͽ�
		//���� �� �Ӽ��� �������̴� �༮�̸� �����̴� �ӵ��� �ݴ�� �ش�.
		if (_curMap->getMapTile()[tileNum(_rc.left, _rc.top + 3)].getTerrainAttr() == ATTR_UNMOVE ||
			_curMap->getMapTile()[tileNum(_rc.left, _rc.bottom - 3)].getTerrainAttr() == ATTR_UNMOVE)
		{
			_player.x += _moveSpeed;
		}
		else if (_curMap->getMapTile()[tileNum(_rc.left, _rc.top + 3)].getTerrainAttr() == ATTR_SLOW ||
			_curMap->getMapTile()[tileNum(_rc.left, _rc.bottom - 3)].getTerrainAttr() == ATTR_SLOW)
		{
			_player.x += _moveSpeed/2;
		}
		else if (_curMap->getMapTile()[tileNum(_rc.left, _rc.top + 3)].getTerrainAttr() == ATTR_FAST ||
			_curMap->getMapTile()[tileNum(_rc.left, _rc.bottom - 3)].getTerrainAttr() == ATTR_FAST)
		{
			_player.x -= _moveSpeed*2;
		}
		if (_curMap->getMapTile()[tileNum(_rc.left, _rc.top + 3)].getObjectAttr() == ATTR_UNMOVE ||
			_curMap->getMapTile()[tileNum(_rc.left, _rc.bottom - 3)].getObjectAttr() == ATTR_UNMOVE)
		{
			_player.x += _moveSpeed;
		}
		if (_curMap->getMapTile()[tileNum(_rc.left, _rc.top + 3)].getObject() == OBJ_TOWN ||
			_curMap->getMapTile()[tileNum(_rc.left, _rc.bottom - 3)].getObject() == OBJ_TOWN)
		{
			_player.x =  _player.x - 15;
			_isEnter = true;
		}
		if (_curMap->getMapTile()[tileNum(_rc.left, _rc.top + 3)].getObject() == OBJ_WORLD_MAP ||
			_curMap->getMapTile()[tileNum(_rc.left, _rc.bottom - 3)].getObject() == OBJ_WORLD_MAP)
		{
			_player.x = _player.x - 15;
			_isWorldMapEnter = true;
		}
		


	}
	else if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		//�������� ���ؼ� 
		_battleCount += INCRESECOUNTRANGE;
		_worldPlayerDirection = WPRIGHT;
		_player.x += _moveSpeed;
		_rc = RectMake(_player.x, _player.y + 30, TILE_SIZEX, TILE_SIZEY / 2);
		if (_curMap->getMapTile()[tileNum(_rc.right, _rc.top + 3)].getTerrainAttr() == ATTR_UNMOVE ||
			_curMap->getMapTile()[tileNum(_rc.right, _rc.bottom - 3)].getTerrainAttr() == ATTR_UNMOVE)
		{
			_player.x -= _moveSpeed;
		}
		else if (_curMap->getMapTile()[tileNum(_rc.right, _rc.top + 3)].getTerrainAttr() == ATTR_SLOW ||
			_curMap->getMapTile()[tileNum(_rc.right, _rc.bottom - 3)].getTerrainAttr() == ATTR_SLOW)
		{
			_player.x -= _moveSpeed/2;
		}
		else if (_curMap->getMapTile()[tileNum(_rc.right, _rc.top + 3)].getTerrainAttr() == ATTR_FAST ||
			_curMap->getMapTile()[tileNum(_rc.right, _rc.bottom - 3)].getTerrainAttr() == ATTR_FAST)
		{
			_player.x += _moveSpeed *2;
		}
		if (_curMap->getMapTile()[tileNum(_rc.right, _rc.top + 3)].getObjectAttr() == ATTR_UNMOVE ||
			_curMap->getMapTile()[tileNum(_rc.right, _rc.bottom - 3)].getObjectAttr() == ATTR_UNMOVE)
		{
			_player.x -= _moveSpeed;
		}
		if (_curMap->getMapTile()[tileNum(_rc.right, _rc.top + 3)].getObject() == OBJ_TOWN ||
			_curMap->getMapTile()[tileNum(_rc.right, _rc.bottom - 3)].getObject() == OBJ_TOWN)
		{
			_player.x = _player.x + 15;
			_isEnter = true;
		}
		if (_curMap->getMapTile()[tileNum(_rc.right, _rc.top + 3)].getObject() == OBJ_WORLD_MAP ||
			_curMap->getMapTile()[tileNum(_rc.right, _rc.bottom - 3)].getObject() == OBJ_WORLD_MAP)
		{
			_player.x = _player.x + 15;
			_isWorldMapEnter = true;
		}

	}
	else if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		//�������� ���ؼ� 
		_battleCount += INCRESECOUNTRANGE;
		_worldPlayerDirection = WPUP;
		_player.y -= _moveSpeed;
		_rc = RectMake(_player.x, _player.y + 30, TILE_SIZEX, TILE_SIZEY / 2);
		if (_curMap->getMapTile()[tileNum(_rc.left + 3, _rc.top)].getTerrainAttr() == ATTR_UNMOVE ||
			_curMap->getMapTile()[tileNum(_rc.right - 3, _rc.top)].getTerrainAttr() == ATTR_UNMOVE)
		{
			_player.y += _moveSpeed;
		}
		else if (_curMap->getMapTile()[tileNum(_rc.left + 3, _rc.top)].getTerrainAttr() == ATTR_SLOW ||
			_curMap->getMapTile()[tileNum(_rc.right - 3, _rc.top)].getTerrainAttr() == ATTR_SLOW)
		{
			_player.y += _moveSpeed/2;
		}
		else if (_curMap->getMapTile()[tileNum(_rc.left + 3, _rc.top)].getTerrainAttr() == ATTR_FAST ||
			_curMap->getMapTile()[tileNum(_rc.right - 3, _rc.top)].getTerrainAttr() == ATTR_FAST)
		{
			_player.y -= _moveSpeed * 2;
		}
		if (_curMap->getMapTile()[tileNum(_rc.left + 3, _rc.top)].getObjectAttr() == ATTR_UNMOVE ||
			_curMap->getMapTile()[tileNum(_rc.right - 3, _rc.top)].getObjectAttr() == ATTR_UNMOVE)
		{
			_player.y += _moveSpeed;
		}
		if (_curMap->getMapTile()[tileNum(_rc.left + 3, _rc.top)].getObject() == OBJ_TOWN ||
			_curMap->getMapTile()[tileNum(_rc.right - 3, _rc.top)].getObject() == OBJ_TOWN)
		{
			_player.y = _player.y + 15;
			_isEnter = true;
		}
		if (_curMap->getMapTile()[tileNum(_rc.left + 3, _rc.top)].getObject() == OBJ_WORLD_MAP ||
			_curMap->getMapTile()[tileNum(_rc.right - 3, _rc.top)].getObject() == OBJ_WORLD_MAP)
		{
			_player.y = _player.y + 15;
			_isWorldMapEnter = true;
		}
	}
	else if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		//�������� ���ؼ� 
		_battleCount += INCRESECOUNTRANGE;
		_worldPlayerDirection = WPDOWN;
		_player.y += _moveSpeed;
		_rc = RectMake(_player.x, _player.y + 30, TILE_SIZEX, TILE_SIZEY / 2);
		if (_curMap->getMapTile()[tileNum(_rc.left+3, _rc.bottom)].getTerrainAttr() == ATTR_UNMOVE ||
			_curMap->getMapTile()[tileNum(_rc.right-3, _rc.bottom)].getTerrainAttr() == ATTR_UNMOVE)
		{
			_player.y -= _moveSpeed;
		}
		else if (_curMap->getMapTile()[tileNum(_rc.left + 3, _rc.bottom)].getTerrainAttr() == ATTR_SLOW ||
			_curMap->getMapTile()[tileNum(_rc.right - 3, _rc.bottom)].getTerrainAttr() == ATTR_SLOW)
		{
			_player.y -= _moveSpeed/2;
		}
		else if (_curMap->getMapTile()[tileNum(_rc.left + 3, _rc.bottom)].getTerrainAttr() == ATTR_FAST ||
			_curMap->getMapTile()[tileNum(_rc.right - 3, _rc.bottom)].getTerrainAttr() == ATTR_FAST)
		{
			_player.y += _moveSpeed * 2;
		}
		if (_curMap->getMapTile()[tileNum(_rc.left + 3, _rc.bottom)].getObjectAttr() == ATTR_UNMOVE ||
			_curMap->getMapTile()[tileNum(_rc.right - 3, _rc.bottom)].getObjectAttr() == ATTR_UNMOVE)
		{
			_player.y -= _moveSpeed;
		}
		if (_curMap->getMapTile()[tileNum(_rc.left + 3, _rc.bottom)].getObject() == OBJ_TOWN ||
			_curMap->getMapTile()[tileNum(_rc.right - 3, _rc.bottom)].getObject() == OBJ_TOWN)
		{
			_player.y = _player.y - 15;
			_isEnter = true;
		}
		if (_curMap->getMapTile()[tileNum(_rc.left + 3, _rc.bottom)].getObject() == OBJ_WORLD_MAP ||
			_curMap->getMapTile()[tileNum(_rc.right - 3, _rc.bottom)].getObject() == OBJ_WORLD_MAP)
		{
			_player.y = _player.y - 15;
			_isWorldMapEnter = true;
		}
	}

	//�ɾ�ٴҶ� �� ��ī���� ��������
	if (_battleCount >= MAXENCOUNT)
	{
		_isEncount = true;
		_battleCount = 0;
	}

	int test = CAMERAMANAGER->getMapTotalSize().x;
	
	if (_player.x > CAMERAMANAGER->getDcWidth() / 2 && _player.x <= CAMERAMANAGER->getMapTotalSize().x - CAMERAMANAGER->getDcWidth() / 2)
	{
		CAMERAMANAGER->setMovePt(PointMake(_player.x - CAMERAMANAGER->getDcWidth() / 2, CAMERAMANAGER->getMovePt().y));
	}


	if (_player.y > CAMERAMANAGER->getDcHeight() / 2 && _player.y <= CAMERAMANAGER->getMapTotalSize().y - CAMERAMANAGER->getDcHeight() / 2)
	{
		CAMERAMANAGER->setMovePt(PointMake(CAMERAMANAGER->getMovePt().x, _player.y - CAMERAMANAGER->getDcHeight() / 2));
	}


	switch (_worldPlayerDirection)
	{
	case WPRIGHT: //_tile->getTerrainAttr()[tileNum(_rc.left)]
		break;

	case WPLEFT: //if (_curMap->getMapTile()[tileNum(_rc.left, _rc.top + 3)].getTerrainAttr() == ATTR_UNMOVE ||
		//_curMap->getMapTile()[tileNum(_rc.left, _rc.bottom - 3)].getTerrainAttr() == ATTR_UNMOVE)
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
	tileNum = tileY * _curMap->getMapTileNum().x + tileX;

	return tileNum;
}

void worldMapPlayer::checkAttribute()
{
}

void worldMapPlayer::successEscape()
{
	_player.x = _player.x - 100;
	if (_player.x <= 0)
	{
		_player.x = 0;
	}
}

