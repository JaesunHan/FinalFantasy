#include "stdafx.h"
#include "npcMother.h"
#include "worldMapPlayer.h"


npcMother::npcMother()
{
}


npcMother::~npcMother()
{
}

HRESULT npcMother::init(int npcX, int npcY)
{
	_npc.x = npcX;
	_npc.y = npcY;

	_npcCurrentFrameX = 0;
	_npcCurrentFrameY = 0;
	_count = 0;

	_rc = RectMake(_npc.x, _npc.y + 30, TILE_SIZEX, TILE_SIZEY / 2);

	_isCollision = false;


	return S_OK;
}

void npcMother::release()
{
}

void npcMother::update()
{
	worldNpcImageFrameControl();
	npcCollision();
}

void npcMother::render(HDC hdc, POINT movePt)
{
}

void npcMother::worldNpcImageFrameControl()
{
	_count++;

	if (_count % 10 == 0)
	{
		_npcCurrentFrameX++;

		if (_npcCurrentFrameX == _image->getMaxFrameX())
		{
			_npcCurrentFrameX = 0;
		}
	}
}

void npcMother::worldNpcImageControl()
{
}

void npcMother::worldNpcKeyControl()
{
}

void npcMother::npcCollision()
{
	if (getDistance(_npc.x, _npc.y, _wp->getWorldMapPlayerPoint().x, _wp->getWorldMapPlayerPoint().y)< TILE_SIZEX)
	{
		_isCollision = true;
	}
}

int npcMother::tileNum(float x, float y)
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
