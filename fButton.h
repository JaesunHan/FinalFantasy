#pragma once
#include "gameNode.h"
#include <vector>


struct tagButton
{
	image* img;             //버튼 이미지
	float x, y;             //버튼 위치
	bool aniStart;          //버튼 에니시작
	animation* ani;         //버튼 에니메이션
};


class fButton : public gameNode
{
private:
	typedef vector<tagButton>			    vButton;
	typedef vector<tagButton>::iterator     viButton;

protected:
	//======== button ========
	vButton   _vButton;
	viButton  _viButton;
	int      _buttonNum;
	//======== button ========


public:
	//================================ button ===============================
	HRESULT init();
	void buttonSet(string keyName, float x, float y);
	void release();
	void update();
	void render();
	void buttonRemove();
	//================================ button ===============================

	//=========================== getter & setter ===========================
	vButton getVButton() { return _vButton; }
	void setVButtonAniStart(int num, bool aniStart) { _vButton[num].aniStart = aniStart; }
	int getButtonNum() { return _buttonNum; }
	//=========================== getter & setter ===========================

	fButton();
	~fButton();
};
