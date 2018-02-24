#pragma once
#include "menu.h"
#include "cursor.h"


class characterEquip : public menu
{
private:
	cursor * _cursorI;

	bool _equipButtonOn;
	bool _selectEquip;
	int _selectPlayerNum;


public:
	HRESULT init();
	void release();
	void update();
	void render();


	void buttonOnActive();
	void buttonOnEquipsActive();
	void equipsButtonSet(int buttonNum);
	void setItemManagerAddressLink(itemManager* im) { _iM = im; }


	characterEquip();
	~characterEquip();
};

