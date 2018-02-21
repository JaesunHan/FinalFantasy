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

	npcMother::init(npcX, npcY);

	_npc.x = npcX;
	_npc.y = npcY;

	_rc = RectMake(_npc.x, _npc.y + 30, TILE_SIZEX, TILE_SIZEY / 2);

	_npcCurrentFrameX = 0;
	_npcCurrentFrameY = 0;

	_npctype = NPC_INN;
	return S_OK;
}

void npc5::release()
{
}

void npc5::update()
{
	//worldNpcImageFrameControl();
	npcMother::update();
}

void npc5::render(HDC hdc, POINT movePt)
{
	IMAGEMANAGER->findImage("5번npc")->frameRender(hdc, _npc.x - movePt.x, _npc.y - movePt.y, _npcCurrentFrameX, 0);
	if (_isDebug)
	{
		Rectangle(hdc, _rc.left - movePt.x, _rc.top - movePt.y, _rc.right - movePt.x, _rc.bottom - movePt.y);
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