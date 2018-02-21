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

#define SAVEFILENUM		3
#define EFFECTVOLUME	0.5f
#define INTCHARBUFF		16
#define CHARBUFFSHORT	32
#define CHARBUFFLONG	64

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
	float minX, maxX;       //Ŀ�� x���̵� ����
	float speed;            //Ŀ�� ���ǵ�
	float fForce;           //Ŀ�� ������
	int currentXNum;        //Ŀ��X ����ġ
	int currentYNum;        //Ŀ��Y ����ġ
	bool cursorOn;          //Ŀ�� ������ġ �Ǻ��� ���� �Ұ�
	bool cursorReset;       //Ŀ�� ��ġ���� �Ǻ��� ���� �Ұ�
};

enum SAVE_TYPE
{
	SAVE_NEWGAME,
	SAVE_LOADGAME
};

struct tagPlayer
{
	image* img;						//�÷��̾� �̹���
	float x, y;						//�÷��̾� �̹��� ��ġ
	animation* ani;                 //�̹��� ���ϸ��̼�
	bool aniStart;                  //���ϸ��̼� ���� �Ұ�
	bool slotSelect;                //���Ժ��� �Ұ�

	TCHAR name[CHARBUFFSHORT];		//�÷��̾� �̸�
	TCHAR job[CHARBUFFSHORT];		//�÷��̾� ����
	int level;						//�÷��̾� ����
	int hp, maxHp;					//�÷��̾� ü��
	int mp, maxMp;					//�÷��̾� ����
	int exp, maxExp;				//�÷��̾� ����ġ
	int strength;					//�÷��̾� ��
	int speed;						//�÷��̾� ���ǵ�
	int stamina;					//�÷��̾� ������
	int magic;						//�÷��̾� ������
	int attack;						//�÷��̾� ���ݷ�
	int attackDefence;				//�÷��̾� ���ݵ��潺
	int magicDefence;				//�÷��̾� �������潺
	int evation;					//�÷��̾� ����ȸ��
	int magicEvation;				//�÷��̾� ����ȸ��
	int partyIdx;					//�÷��̾� ��Ƽ�� �ѹ�
	TCHAR weapon[CHARBUFFSHORT];	//�÷��̾� ����
	TCHAR armor[CHARBUFFSHORT];		//�÷��̾� ���� 
	TCHAR helmet[CHARBUFFSHORT];	//�÷��̾� ����  
	TCHAR subWeapon[CHARBUFFSHORT];	//�÷��̾� ��������
};	

struct tagSaveData
{
	int fileNum;
	tagPlayer playerInfo;
	TCHAR stage[CHARBUFFSHORT];	
	int gil;
	int playTime;
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
	TCHAR saveFileName[CHARBUFFSHORT];
	TCHAR stage[CHARBUFFSHORT];
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

enum MENUITEM_KIND
{
	MENUITEM_ITEM,
	MENUITEM_ARMOR,
	MENUITEM_WEAPON,
	MENUITEM_END
};

struct tagItem
{
	int itemNum;
	int itemKind;
	int itemNameNum;
	int itemPosNum;
};

class itemManager;

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
	int  _saveFileNum;
	bool _isSavePoint;
	//======= saveLoad =======

	//======== button ========
	fButton*  _button;
	//======== button ========

	//======== player ========
	vPlayer   _vPlayer;          //�÷��̾� ��������
	viPlayer  _viPlayer;
	tagElements _playerElements;
	int _slotNum;

	vPlayer   _vPlayerStatus;    //�÷��̾� ��������
	viPlayer  _viPlayerStatus;   

	tagPlayer _playerSlot;		 //�� ���Կ� �÷��̾� ���� ���� ����ü ����
	bool _fileLoadOk[4];		 //���̺� ���� ���� �����Ǻ�
	int _selectFileCount;		 //���� ������ ������ �����ֱ� ���� ī��Ʈ �� (�ٷ� ���ù�ư���� �̵����� �ʵ���) 
	//======== player ========
	
	//======= gameData =======
	elements* _gameData;
	//======= gameData =======

	//====== BG �̹��� =======
	image*    _bgImage;

	//========= ITEM =========
	itemManager* _iM;
	tagItem _posItem;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	//================================ cusor ================================
	virtual void cursorInit(CURSOR_TYPE type, float startX, float startY);
	virtual void cursorUpdate();
	virtual void cursorRender();
	virtual void cursorKeyControlX(float moveValueX, int downNumber, bool leftMove = false);
	virtual void cursorKeyControlY(float moveValueY, int downNumber);
	virtual void cursorResetXY(float cursorX, float cursorY);
	//================================ cusor ================================

	//================================ player ===============================
	//--------------------------------  slot  -------------------------------
	virtual void playerSlotInit(string keyName, float x, float y, int level, char* job, 
		int hp, int maxHp, int mp, int maxMp, int exp, int maxExp, int partyIdX);
	virtual void playerSlotUpdate();
	virtual void playerSlotKeyControl(float slotValueY, int slotNum = 137);
	virtual void playerSlotRender();
	virtual void playerSlotRemove();
	virtual void playerSlotAniStart(int slotNum, bool aniStart);
	//-------------------------------  status  ------------------------------
	virtual void playerStatusInit(int strength, int speed, int stamina, int magic, int attack,
		int attackDefence, int magicDefence, int evation, int magicEvation, int partyIdx);
	virtual void playerStatusRender();
	virtual void playerStatusRemove();
	//------------------------------  fileLoad  -----------------------------
	virtual void fileLoad(int fileNum, int playerNum = -1, bool tmpFile = false);
	//------------------------------  fileCopy  -----------------------------
	virtual void fileCopyTmpFile(int fileNum);
	virtual void fileCopySaveFile(int fileNum);
	//--------------------------------  slot  -------------------------------
	virtual void slotChange(int changeSlotNum, int selectSlotNum);
	virtual int slotSelect(int selectSlotNum);
	virtual int getPlayerNum(int partyIdX);
	//================================ player ===============================

	//============================== save & load ============================
	virtual tagElements saveTxtData(int fileNum, string cStage);
	virtual void saveIniPlayerData(int fileNum, int playerNum, string cName, string job, 
		int level, int hp, int maxHp, int mp, int maxMp, int exp, int maxExp, int strength, 
		int speed, int stamina, int magic, int attack, int attackDefence, int magicDefence, 
		int evation, int magicEvation, int partyIdx, string myWeapon, string myArmor,
		string myHelmet, string mySubWeapon, bool tmpSave = false, bool saveFile = false);
	virtual void saveIniSlotGameData(int fileNum, string stage, int gil, int playTime, bool tmpSave = false);
	virtual tagSaveData loadIniPlayerData(int fileNum, int playerNum, bool tmpFile = false);
	//============================== save & load ============================

	//=============================== gameData ==============================
	virtual void saveIniGameData(int fileNum, string currentScene = "");
	virtual void gameDataRender(bool isNewGame);
	//=============================== gameData ==============================

	//================================= item ================================
	virtual void itemSave(int itemKind, int itemName, int itemNum, bool saveFile = false, int saveFileNum = 0);
	virtual void itemDataLoad(int fileNum, bool tmpFile = false);
	//================================= item =================================

	//=============================== gameTime ==============================
	virtual void gamePlayTime(float getSaveTime = 0, bool fileLoadTime = false);
	//=============================== gameTime ==============================

	//================================ getter ===============================
	int getSaveFileNum() { return _saveFileNum; }
	int setIsSavePoint(bool isSave) { _isSavePoint = isSave; }
	//================================ getter ===============================

	void setItemManagerAddressLink(itemManager* im) { _iM = im; }



	menu();
	~menu();
};



