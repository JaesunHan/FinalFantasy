#pragma once
#include "battlePlayerMother.h"
class battleTina : public battlePlayerMother
{
private :
	int _count;					//_turnEnd �� true �� �ٲٱ� ���� ī����
public:
	battleTina();
	~battleTina();

	HRESULT init();
	void update();
	void draw();
	void release();
};

