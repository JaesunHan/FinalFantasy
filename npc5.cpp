#include "stdafx.h"
#include "npc5.h"


npc5::npc5()
{
}


npc5::~npc5()
{
}

HRESULT npc5::init(int npcX, int npcY)
{
	//npc5번 이미지 추가
	_image = IMAGEMANAGER->addFrameImage("5번npc", ".\\image\\NPC\\npc5_front.bmp", 84, 46, 3, 1, true, RGB(255, 0, 255));

	_npc.x = npcX;
	_npc.y = npcY;

	_rc = RectMake(_npc.x, _npc.y + 30, TILE_SIZEX, TILE_SIZEY / 2);

	_npcCurrentFrameX = 0;
	_npcCurrentFrameY = 0;


	return S_OK;
}

void npc5::release()
{
}

void npc5::update()
{
	worldNpcImageFrameControl();
}

void npc5::render()
{
	IMAGEMANAGER->findImage("5번npc")->frameRender(getMemDC(), _npc.x, _npc.y, _npcCurrentFrameX, 0);
	if (_isDebug)
	{
		Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);
	}
}

void npc5::worldNpcImageFrameControl()
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