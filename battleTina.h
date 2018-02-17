#pragma once
#include "battlePlayerMother.h"
class battleTina : public battlePlayerMother
{
private :
	int _count;					//_turnEnd 를 true 로 바꾸기 위한 카운터
public:
	battleTina();
	~battleTina();

	HRESULT init();
	void update();
	void draw();
	void release();
};

