#pragma once
#include "gameNode.h"
#include <vector>

//****************************************//
//              wonjjang                  //
//           ver. 2018_02_11              //
//****************************************//


#define COLOR_WHITE		RGB(255, 255, 255)
#define COLOR_BLACK		RGB(0, 0, 0)
#define COLOR_RED		RGB(255, 0, 0)
#define COLOR_GREEN		RGB(0, 255, 0)
#define COLOR_BLUE		RGB(0, 0, 255)
#define COLOR_MAGENTA	RGB(255, 0, 255)

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

struct tagButton
{
	image* img;             //��ư �̹���
	float x, y;             //��ư ��ġ
	bool aniStart;          //��ư ���Ͻ���
	animation* ani;         //��ư ���ϸ��̼�
};

struct tagPlayer
{
	image* img;             //�÷��̾� �̹���
	float x, y;             //�÷��̾� �̹��� ��ġ
	int level;              //�÷��̾� ����
	int hp, maxHp;          //�÷��̾� ü��
	int mp, maxMp;          //�÷��̾� ����
	string name;            //�÷��̾� �̸�
	string job;             //�÷��̾� ����
};


class menu : public gameNode
{
private:
	typedef vector<tagButton>			    vButton;
	typedef vector<tagButton>::iterator     viButton;

	typedef vector<tagPlayer>               vPlayer;
	typedef vector<tagPlayer>::iterator     viPlayer;

protected:
	//======== cursor ========
	tagCursor _cursor;
	int		  _cursorType;
	//======== cursor ========

	//======= saveLoad =======
	int _saveType;
	//======= saveLoad =======

	//======== button ========
	vButton   _vButton;
	viButton  _viButton;
	int       _buttonNum;
	//======== button ========

	//======== player ========
	vPlayer   _vPlayer;
	viPlayer  _viPlayer;
	//======== player ========


	//====== BG �̹��� =======
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

	//================================ player ===============================
	virtual void playerSlotInit(string keyName, float x, float y, int level, string job, int hp, int maxHp, int mp, int maxMp);
	virtual void playerSlotUpdate();
	virtual void playerSlotKeyControl(float slotValueY, int slotNum);
	virtual void playerSlotRender();
	virtual void playerSlotRemove();
	//================================ player ===============================

	//================================= text ================================
	virtual void textPrint(int fontWidth, int fontThick, char* fontName, char* textInput, int textX, int textY, COLORREF RGB = COLOR_WHITE, BOOL textCenter = TRUE);
	virtual char* s2c(string str);
	virtual char* i2c(int i);
	//================================= text ================================

	menu();
	~menu();


};

