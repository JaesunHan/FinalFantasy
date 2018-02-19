#include "stdafx.h"
#include "npcMother.h"


npcMother::npcMother()
{
}


npcMother::~npcMother()
{
}

HRESULT npcMother::init(int npcX, int npcY)
{
	_npcCurrentFrameX = 0;
	_npcCurrentFrameY = 0;
	_count = 0;


	return S_OK;
}

void npcMother::release()
{
}

void npcMother::update()
{
	worldNpcImageFrameControl();
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
