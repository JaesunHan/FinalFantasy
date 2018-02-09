#pragma once
#include "gameNode.h"


class menu : public gameNode
{
protected:



public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	menu();
	~menu();


};

