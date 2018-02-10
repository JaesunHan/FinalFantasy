#pragma once
#include "Enemy.h"

class siren : public Enemy
{
public:
	siren();
	~siren();

	virtual void update();
	virtual void render();

	virtual void bearSkill();
};

