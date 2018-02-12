#pragma once
#include "menu.h"


class titleScene : public menu
{
private:
	int _saveType;



public:
	HRESULT init();
	void release();
	void update();


	//=========================== getter & setter ===========================
	int getSaveType() { return _saveType; }
	void setSaveType(int saveType) { _saveType = saveType; }

	titleScene();
	~titleScene();

};

