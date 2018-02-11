#pragma once
#include "battlePlayerMother.h"
class battleTina : public battlePlayerMother
{
public:
	battleTina();
	~battleTina();

	HRESULT init();
	void update();
	void draw();
	void release();
};

