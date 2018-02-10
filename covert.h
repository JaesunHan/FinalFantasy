#pragma once
#include "Enemy.h"

class covert : public Enemy
{
public:
	covert();
	~covert();

	virtual void update();
	virtual void render();

	virtual void bearSkill();
};

