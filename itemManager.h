#pragma once
#include "gameNode.h"
#include <vector>
#include "expendablesItem.h"
#include "weaponItem.h"

class itemManager : public gameNode
{
private:
	vector<itemMother*>				_vItem;


public:
	itemManager();
	~itemManager();

	HRESULT init();
};
