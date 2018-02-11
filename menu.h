#pragma once
#include "gameNode.h"
#include <vector>

enum CURSOR_TYPE
{
	CUSOR_LEFT,
	CUSOR_RIGHT
};

struct tagCursor
{
	image* img;             //커서 이미지
	float x, y;             //커서 위치
	float startX, startY;   //커서 초기위치
	float speed;            //커서 스피드
	float fForce;           //커서 마찰력
	int currentNum;         //커서 현위치
	bool cursorOn;          //커서 선택위치 판별을 위한 불값
};

enum SAVE_TYPE
{
	SAVE_NEWGAME,
	SAVE_LOADGAME
};

struct tagButton
{
	image* img;             //버튼 이미지
	float x, y;             //버튼 위치
	bool aniStart;          //버튼 에니시작
	animation* ani;         //버튼 에니메이션
};



class menu : public gameNode
{
private:
	typedef vector<tagButton>			    vButton;
	typedef vector<tagButton>::iterator     viButton;

protected:
	//======== cursor ========
	tagCursor _cursor;
	int		  _cursorType;
	//======== cursor ========

	//======= saveLoad =======
	int _saveType;
	//======= saveLoad =======

	//======== button ========
	tagButton _button;
	vButton   _vButton;
	viButton  _viButton;
	int       _buttonNum;
	//======== button ========


	//백그라운드 이미지
	image*    _bgImage;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	//================================ cusor ================================
	virtual void cursorInit(CURSOR_TYPE type, float startX, float startY);
	virtual void cursorUpdate();
	virtual void cursorRender();
	virtual void cursorKeyControl(float downValueY, int downNumber);
	//================================ cusor ================================

	//================================ button ===============================
	virtual void buttonInit(string keyName, float x, float y);
	virtual void buttonUpdate();
	virtual void buttonRender();
	virtual void buttonRemove();
	//================================ button ===============================

	menu();
	~menu();


};

