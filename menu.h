#pragma once
#include "gameNode.h"
#include "fButton.h"
#include <vector>

//#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")


//****************************************//
//              wonjjang                  //
//           ver. 2018_02_16              //
//****************************************//


#define COLOR_WHITE		RGB(255, 255, 255)
#define COLOR_BLACK		RGB(0, 0, 0)
#define COLOR_RED		RGB(255, 0, 0)
#define COLOR_GREEN		RGB(0, 255, 0)
#define COLOR_BLUE		RGB(0, 0, 255)
#define COLOR_MAGENTA	RGB(255, 0, 255)

#define SAVEFILENUM 4
#define EFFECTVOLUME 0.5f

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
	float minX, maxX;       //커서 x축이동 변수
	float speed;            //커서 스피드
	float fForce;           //커서 마찰력
	int currentXNum;        //커서X 현위치
	int currentYNum;        //커서Y 현위치
	bool cursorOn;          //커서 선택위치 판별을 위한 불값
	bool cursorReset;       //커서 위치리셋 판별을 위한 불값
};

enum SAVE_TYPE
{
	SAVE_NEWGAME,
	SAVE_LOADGAME
};

struct tagPlayer
{
	image* img;             //플레이어 이미지
	float x, y;             //플레이어 이미지 위치
	int level;              //플레이어 레벨
	int hp, maxHp;          //플레이어 체력
	int mp, maxMp;          //플레이어 마력
	TCHAR name[32];		//플레이어 이름
	TCHAR job[32];			//플레이어 직업
};	

enum STAGE_SCENE
{
	STAGE_MENU,
	STAGE_OPTION,
	STAGE_OVERWORLD,
	STAGE_VILLAGE,
	STAGE_END
};

struct tagCurrentGameData
{
	TCHAR saveFileName[32];
	TCHAR stage[32];
	int fileNum;
	int gil;
	int playTime;
	int steps;
};

enum MENU_SCENE
{
	MENU_TITLE,
	MENU_NEWGAME,
	MENU_LOADGAME,
	MENU_OPTION,
	MENU_ABILITY,
	MENU_CONFIG,
	MENU_EQUIP,
	MENU_ITEM,
	MENU_SAVE,
	MENU_STATUS,
	MENU_END
};


class menu : public gameNode
{
private:
	typedef vector<tagPlayer>               vPlayer;
	typedef vector<tagPlayer>::iterator     viPlayer;

protected:
	//======== cursor ========
	tagCursor _cursor;
	int		  _cursorType;
	int       _cursorXNum;
	int       _cursorYNum;
	//======== cursor ========

	//======= saveLoad =======
	bool _saveFileSelect;
	int _saveFileNum;
	//======= saveLoad =======

	//======== button ========
	fButton*  _button;
	//======== button ========

	//======== player ========
	vPlayer   _vPlayer;
	viPlayer  _viPlayer;
	tagElements _playerElements;

	tagPlayer _playerSlot;  //각 슬롯에 플레이어 정보 담을 구조체 변수
	bool _fileLoadOk[4];    //세이브 파일 존재 유무판별
	int _selectFileCount;   //파일 선택후 슬롯을 보여주기 위한 카운트 값 (바로 선택버튼으로 이동하지 않도록) 
	//======== player ========
	
	//======= gameData =======
	elements* _gameData;
	//======= gameData =======

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
	virtual void cursorKeyControlX(float moveValueX, int downNumber);
	virtual void cursorKeyControlY(float moveValueY, int downNumber);
	virtual void cursorResetXY(float cursorX, float cursorY);
	//================================ cusor ================================

	//================================ player ===============================
	virtual void playerSlotInit(string keyName, float x, float y, int level, char* job, int hp, int maxHp, int mp, int maxMp);
	virtual void playerSlotUpdate();
	virtual void playerSlotKeyControl(float slotValueY, int slotNum);
	virtual void playerSlotRender();
	virtual void playerSlotRemove();

	virtual void fileLoad(int fileNum);
	//================================ player ===============================

	//============================== save & load ============================
	virtual tagElements saveTxtData(int fileNum, string cStage);
	virtual void saveIniPlayerData(int fileNum, int playerNum, string cName, string job, int level, int hp, int maxHp, int mp, int maxMp);
	virtual void saveIniSlotGameData(int fileNum, string stage, int gil, int playTime, int steps);
	//============================== save & load ============================

	//=============================== gameData ==============================
	virtual void saveIniGameData(int fileNum, string currentScene = "");
	virtual void gameDataRender(bool isNewGame);
	//=============================== gameData ==============================




	menu();
	~menu();

};



