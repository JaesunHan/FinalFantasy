#pragma once
#include "battlePlayerMother.h"

class battleCeles : public battlePlayerMother
{
public:
	battleCeles();
	~battleCeles();

	HRESULT init();
	void update();
	void draw();
	void release();
};

