#pragma once
#include "npcMother.h"
class npc5 :
	public npcMother
{
public:
	npc5();
	~npc5();

	HRESULT init(int npcX, int npcY);
	void release();
	void update();
	void render();

	void worldNpcImageFrameControl();
};

