#pragma once
#include "npcMother.h"
class npc4 :
	public npcMother
{
public:
	npc4();
	~npc4();

	HRESULT init(int npcX, int npcY);
	void release();
	void update();
	void render();

	void worldNpcImageFrameControl();
};

