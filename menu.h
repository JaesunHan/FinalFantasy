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

struct tagPlayer
{
	image* img;             //플레이어 이미지
	float x, y;             //플레이어 이미지 위치
	int level;              //플레이어 레벨
	int hp, maxHp;          //플레이어 체력
	int mp, maxMp;          //플레이어 마력
	string name;            //플레이어 이름
	string job;             //플레이어 직업
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


	//====== BG 이미지 =======
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

