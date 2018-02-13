#pragma once
#include "npcMother.h"
class npc2 :
	public npcMother
{
public:
	npc2();
	~npc2();

	HRESULT init(int npcX, int npcY);
	void release();
	void update();
	void render();
	void worldNpcImageFrameControl();
};

