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
	void render();

	void worldNpcImageFrameControl();

	POINT getNpcPoint() { return _npc; }
};

