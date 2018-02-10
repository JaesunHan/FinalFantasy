#pragma once
#include "Enemy.h"

class gobbler : public Enemy
{
public:
	gobbler();
	~gobbler();

	virtual void update();
	virtual void render();

	virtual void bearSkill();
};

