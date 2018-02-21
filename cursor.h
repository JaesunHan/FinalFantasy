#pragma once
#include "gameNode.h"

#define EFFECTVOLUME	0.5f

enum CURSOR_DIRECTION
{
	CURSOR_LEFT,
	CURSOR_RIGHT
};

class cursor : public gameNode
{
private:
	image* _img;             //커서 이미지
	CURSOR_DIRECTION _type;		//커서 타입

	float _x, _y;             //커서 위치
	float _startX, _startY;   //커서 초기위치
	float _minX, _maxX;       //커서 x축이동 변수
	float _speed;            //커서 스피드
	float _fForce;           //커서 마찰력
	int _currentXNum;        //커서X 현위치
	int _currentYNum;        //커서Y 현위치
	int _currentPos;		 //XY 동시 이동을 위한 커서 좌표
	bool _cursorOn;          //커서 선택위치 판별을 위한 불값
	bool _cursorReset;       //커서 위치리셋 판별을 위한 불값

public:
	cursor();
	~cursor();

	void init(CURSOR_DIRECTION type, float startX, float startY);
	void update();
	void render();
	void keyControlX(float moveValueX, int downNumber, bool leftMove = false);
	void keyControlY(float moveValueY, int downNumber);
	void keyControlXY(float moveValueX, float moveValueY, int maxNumX, int maxListNum, bool leftMove = false);
	void resetXY(float cursorX, float cursorY);

	inline int getCursorXNum(void) { return _currentXNum; }
	inline int getCursorYNum(void) { return _currentYNum; }
};

