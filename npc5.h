#pragma once
#include "npcMother.h"
class npc5 :
	public npcMother
{
public:
	npc5();
	~npc5();

	virtual HRESULT init(int npcX, int npcY);
	void release();
	void update();
	virtual void render(HDC hdc, POINT movePt);

	void worldNpcImageFrameControl();

	POINT getNpcPoint() { return _npc; }
};

