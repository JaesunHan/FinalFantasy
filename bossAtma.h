#pragma once
#include "Enemy.h"

class bossAtma : public Enemy
{
public:
	bossAtma();
	~bossAtma();

	virtual void update();
	virtual void render();

	virtual void bearSkill();
};

