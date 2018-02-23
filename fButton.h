#pragma once
#include "gameNode.h"
#include <vector>


struct tagButton
{
	image* img;             //버튼 이미지
	float x, y;             //버튼 위치
	float centerX, centerY; //버튼 중심점
	bool aniStart;          //버튼 에니시작
	animation* ani;         //버튼 에니메이션
	char* text;             //버튼 제목
	float textSize;         //버튼 제목 크기
	bool textOn;            //버튼 제목 출력여부
	int textSort;           //버튼 제목 위치정렬 type1
	TCHAR subText[4];       //버튼 서브 텍스트
	bool isAddText;         //버튼 서브 텍스트 출력여부
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
	int       _buttonNum;
	

	tagButton _button;
	//======== button ========


public:
	//================================ button ===============================
	HRESULT init();
	void buttonSet(string keyName, float x, float y);
	void buttonSet(string keyName, float x, float y, char* buttonText, float textSize = 10,
		int textSortType = 0, bool isAddText = false, int subTextNum = 0) ;
	void release();
	void update();
	void render();
	void buttonRemove();
	void buttonRemoveOne(int buttonNum);
	//================================ button ===============================

	//=========================== getter & setter ===========================
	vButton getVButton() { return _vButton; }
	void setVButtonAniStart(int num, bool aniStart) { _vButton[num].aniStart = aniStart; }
	int getButtonNum() { return _buttonNum; }
	char* getButtonText(int num) { return _vButton[num].text; }
	//=========================== getter & setter ===========================

	fButton();
	~fButton();
};
