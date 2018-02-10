#pragma once
#include "Enemy.h"

class Bear : public Enemy
{
private:

public:
	Bear();
	~Bear();

	//virtual HRESULT init();
	virtual void update();
	virtual void render();

	virtual void bearSkill();
};

