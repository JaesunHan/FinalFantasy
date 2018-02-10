#pragma once
#include "gameNode.h"

enum CURSOR_TYPE
{
	CUSOR_LEFT,
	CUSOR_RIGHT
};

struct tagCursor
{
	image* img;             //Ŀ�� �̹���
	float x, y;             //Ŀ�� ��ġ
	float startX, startY;   //Ŀ�� �ʱ���ġ
	float speed;            //Ŀ�� ���ǵ�
	float fForce;           //Ŀ�� ������
	int currentNum;         //Ŀ�� ����ġ
	bool cursorOn;          //Ŀ�� ������ġ �Ǻ��� ���� �Ұ�
};

enum SAVE_TYPE
{
	SAVE_NEWGAME,
	SAVE_LOADGAME
};

class menu : public gameNode
{
protected:
	//======== cursor ========
	tagCursor _cursor;
	int		  _cursorType;
	//======== cursor ========

	//======= saveLoad =======
	int _saveType;
	//======= saveLoad =======


	//��׶��� �̹���
	image*    _bgImage;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	//=========== cusor ===========
	virtual void cursorInit(CURSOR_TYPE type, float startX, float startY);
	virtual void cursorUpdate();
	virtual void cursorRender();
	virtual void cursorKeyControl(float downValueY, int downNumber);
	//=========== cusor ===========

	menu();
	~menu();


};

