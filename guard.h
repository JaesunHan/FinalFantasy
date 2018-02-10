#pragma once
#include "Enemy.h"

class guard : public Enemy
{
public:
	guard();
	~guard();

	virtual void update();
	virtual void render();

	virtual void bearSkill();
};

