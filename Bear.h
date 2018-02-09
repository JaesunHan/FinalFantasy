#pragma once
#include "Enemy.h"

class Bear : public Enemy
{
public:
	Bear();
	~Bear();

	virtual void bearSkill();

	virtual void update();
	virtual void render();
};

