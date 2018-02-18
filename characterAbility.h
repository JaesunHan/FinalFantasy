#pragma once
#include "menu.h"


class characterAbility : public menu
{
protected:



public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();


	characterAbility();
	~characterAbility();
};

