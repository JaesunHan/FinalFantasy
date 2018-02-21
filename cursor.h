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
	image* _img;             //Ŀ�� �̹���
	CURSOR_DIRECTION _type;		//Ŀ�� Ÿ��

	float _x, _y;             //Ŀ�� ��ġ
	float _startX, _startY;   //Ŀ�� �ʱ���ġ
	float _minX, _maxX;       //Ŀ�� x���̵� ����
	float _speed;            //Ŀ�� ���ǵ�
	float _fForce;           //Ŀ�� ������
	int _currentXNum;        //Ŀ��X ����ġ
	int _currentYNum;        //Ŀ��Y ����ġ
	int _currentPos;		 //XY ���� �̵��� ���� Ŀ�� ��ǥ
	bool _cursorOn;          //Ŀ�� ������ġ �Ǻ��� ���� �Ұ�
	bool _cursorReset;       //Ŀ�� ��ġ���� �Ǻ��� ���� �Ұ�

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

