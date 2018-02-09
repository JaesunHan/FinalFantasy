#pragma once
#include "Enemy.h"


class VectorPup : public Enemy
{
public:
	VectorPup();
	~VectorPup();

	//virtual HRESULT init();
	virtual void update();
	virtual void render();

	virtual void vectorPupAttack();

	virtual void vectorPupSkill();
};

