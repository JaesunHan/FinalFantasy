#pragma once
#include "menu.h"
#include "cursor.h"

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

	cursor* _cursorI;
	bool _itemButtonOn;
	bool _charButtonOn;
	bool _isSelectChar;
	int _selectItemNum;



public:
	HRESULT init();
	void release();
	void update();
	void render();


	void buttonOnActive();
	void buttonOnActiveItem();
	void buttonOnActiveCharacter();
	void itemButtonSet(int buttonNum);

	void itemDescriptionRender(int itemNum);
	void playerInfoPrint();

	void setItemManagerAddressLink(itemManager* im) { _iM = im; }

	itemMenu();
	~itemMenu();
};

