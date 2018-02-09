#pragma once
#include "Enemy.h"
class VectorPup : public Enemy
{
public:
	VectorPup();
	~VectorPup();

	virtual void update();
	virtual void render();
};

