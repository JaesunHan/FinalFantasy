#pragma once
#include "npcMother.h"
class npc3 :
	public npcMother
{
public:
	npc3();
	~npc3();

	virtual HRESULT init(int npcX, int npcY);
	void release();
	void update();
	virtual void render(HDC hdc, POINT movePt);
	
	void worldNpcImageFrameControl();

	POINT getNpcPoint() { return _npc; }
};

