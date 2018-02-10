#pragma once
#include "Enemy.h"

class tornadoShark : public Enemy
{
public:
	tornadoShark();
	~tornadoShark();

	virtual void update();
	virtual void render();

	virtual void bearSkill();
};

