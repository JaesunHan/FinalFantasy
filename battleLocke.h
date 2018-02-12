#pragma once
#include "battlePlayerMother.h"

class battleLocke : public battlePlayerMother
{
public:
	battleLocke();
	~battleLocke();

	HRESULT init();
	void update();
	void draw();
	void release();
};

