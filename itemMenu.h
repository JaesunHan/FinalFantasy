#pragma once
#include "menu.h"

struct tagMiniPlayer
{
	image* img;
	float x, y;
	animation* ani;
	bool aniStart;
};

class itemMenu : public menu
{
private:
	tagMiniPlayer _mTina;
	tagMiniPlayer _mLocke;
	tagMiniPlayer _mCeles;
	tagMiniPlayer _mShadow;


public:
	HRESULT init();
	void release();
	void update();
	void render();


	void buttonOnActive();
	void itemButtonSet(int buttonNum);

	itemMenu();
	~itemMenu();
};

