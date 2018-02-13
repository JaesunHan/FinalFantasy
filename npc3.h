#pragma once
#include "npcMother.h"
class npc3 :
	public npcMother
{
public:
	npc3();
	~npc3();

	HRESULT init(int npcX, int npcY);
	void release();
	void update();
	void render();
	
	void worldNpcImageFrameControl();
};

