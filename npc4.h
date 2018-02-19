#pragma once
#include "npcMother.h"
class npc4 :
	public npcMother
{
public:
	npc4();
	~npc4();

	virtual HRESULT init(int npcX, int npcY);
	void release();
	void update();
	virtual void render(HDC hdc, POINT movePt);

	void worldNpcImageFrameControl();

	POINT getNpcPoint() { return _npc; }
};

