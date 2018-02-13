#include "stdafx.h"
#include "npc3.h"


npc3::npc3()
{
}


npc3::~npc3()
{
}

HRESULT npc3::init(int npcX, int npcY)
{
	//npc3번 이미지 추가
	_image = IMAGEMANAGER->addFrameImage("3번npc", ".\\image\\NPC\\npc3_front.bmp", 90, 48, 3, 1, true, RGB(255, 0, 255));

	_npc.x = npcX;
	_npc.y = npcY;

	_rc = RectMake(_npc.x, _npc.y + 30, TILE_SIZEX, TILE_SIZEY / 2);

	_npcCurrentFrameX = 0;
	_npcCurrentFrameY = 0;

	_npctype = NPC_MAGIC;
	return S_OK;
}

void npc3::release()
{
}

void npc3::update()
{
	worldNpcImageFrameControl();
}

void npc3::render()
{
	IMAGEMANAGER->findImage("3번npc")->frameRender(getMemDC(), _npc.x, _npc.y, _npcCurrentFrameX, 0);
	if (_isDebug)
	{
		Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);
	}
}

void npc3::worldNpcImageFrameControl()
{
	_count++;

	if (_count % 50 == 0)
	{
		_npcCurrentFrameX++;

		if (_npcCurrentFrameX == _image->getMaxFrameX())
		{
			_npcCurrentFrameX = 0;
		}
	}
}