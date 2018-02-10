#pragma once
#include "Enemy.h"

class samurai : public Enemy
{
public:
	samurai();
	~samurai();

	virtual void update();
	virtual void render();

	virtual void bearSkill();
};

