#pragma once
#include "Enemy.h"

class DarkWind : public Enemy
{
public:
	DarkWind();
	~DarkWind();

	//virtual HRESULT init();
	virtual void update();
	virtual void render();

	virtual void darkWindSkill();
};

