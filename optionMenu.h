#pragma once
#include "menu.h"


class optionMenu : public menu
{
private:
	bool _cursorReset;
	int  _changeSlotNum;
	int  _slotSelectCount;
	int  _previousSlotNum;
	bool _isSlotReload;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void slotAniOn();
	void slotChangeKey();
	
	optionMenu();
	~optionMenu();
};

