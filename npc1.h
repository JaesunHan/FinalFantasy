#pragma once
#include "npcMother.h"
class npc1 :
	public npcMother
{
public:
	npc1();
	~npc1();

	virtual HRESULT init(int npcX, int npcY);
	void release();
	void update();
	void render();

	void worldNpcImageFrameControl();

	POINT getNpcPoint() { return _npc; }
};

