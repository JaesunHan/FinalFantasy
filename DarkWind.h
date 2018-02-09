#pragma once
#include "Enemy.h"

class DarkWind : public Enemy
{
public:
	DarkWind();
	~DarkWind();

	virtual void darkWindSkill();

	virtual void update();
	virtual void render();
};

