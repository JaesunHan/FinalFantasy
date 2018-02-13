#pragma once
#include "battlePlayerMother.h"
class battleShadow :public battlePlayerMother
{
public:
	battleShadow();
	~battleShadow();

	HRESULT init();
	void update();
	void draw();
	void release();
};

