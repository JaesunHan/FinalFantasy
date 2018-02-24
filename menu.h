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
#define INTCHARBUFF		256
#define CHARBUFFSHORT	256
#define CHARBUFFLONG	512

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
	image* img;							//�÷��̾� �̹���
	float x, y;							//�÷��̾� �̹��� ��ġ
	animation* ani;						//�̹��� ���ϸ��̼�
	bool aniStart;						//���ϸ��̼� ���� �Ұ�
	bool slotSelect;					//���Ժ��� �Ұ�

	TCHAR name[CHARBUFFSHORT];			//�÷��̾� �̸�
	TCHAR job[CHARBUFFSHORT];			//�÷��̾� ����
	int level;							//�÷��̾� ����
	int hp, maxHp;						//�÷��̾� ü��
	int mp, maxMp;						//�÷��̾� ����
	int exp, maxExp;					//�÷��̾� ����ġ
	int strength;						//�÷��̾� ��
	int speed;							//�÷��̾� ���ǵ�
	int stamina;						//�÷��̾� ������
	int magic;							//�÷��̾� ������
	int attack;							//�÷��̾� ���ݷ�
	int attackDefence;					//�÷��̾� ���ݵ��潺
	int magicDefence;					//�÷��̾� �������潺
	int evation;						//�÷��̾� ����ȸ��
	int magicEvation;					//�÷��̾� ����ȸ��
	int partyIdx;						//�÷��̾� ��Ƽ�� �ѹ�
	int weapon;							//�÷��̾� ����
	int armor;							//�÷��̾� ���� 
	int helmet;				    		//�÷��̾� ����  
	int subWeapon;						//�÷��̾� ��������
	int command[8];						//�÷��̾� Ŀ�ǵ�
};	

struct tagSaveData
{
	int fileNum;
	tagPlayer playerInfo;
	TCHAR stage[CHARBUFFSHORT];	
	int gil;
	int playTime;
	POINT playerXY;
	TCHAR saveScene[CHARBUFFSHORT];
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
class playerManager;
class worldMapScene;
class townScene;

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

	POINT _playerPosition;
	string _currentSceneName;
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

	//========= ���漱�� =========
    //----------------- item
	itemManager* _iM;
	tagItem _posItem;
	//----------------- player
	playerManager* _pM;
	//----------------- Map
	worldMapScene* _wM;
	townScene*     _tM;

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
	virtual void playerSlotRender(bool textOut = true);
	virtual void playerSlotRemove();
	virtual void playerSlotAniStart(int slotNum, bool aniStart);
	//-------------------------------  status  ------------------------------
	virtual void playerStatusInit(int strength, int speed, int stamina, int magic, int attack,
		int attackDefence, int magicDefence, int evation, int magicEvation, int partyIdx,
		int weapon, int armor, int helmet, int subWeapon, int command1, int command2,
		int command3, int command4, int command5, int command6, int command7, int command8);
	virtual void playerStatusRender(int SlotNum);
	virtual void playerStatusEquipsRender(string playerNum, bool equipSet, int myWeaponVNum, int mySubWeaponNum, int myHelmetNum, int myArmorNum);
	virtual void playerStatusRemove();
	virtual string playerCommandReturn(int num);
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
		int evation, int magicEvation, int partyIdx, int myWeapon, int myArmor,int myHelmet,
		int mySubWeapon, int command1, int command2, int command3, int command4,int command5,
		int command6, int command7, int command8, bool tmpSave, bool saveFile = false);
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
	virtual int itemGetNum(int num);
	//================================= item =================================

	//=============================== gameTime ==============================
	virtual void gamePlayTime(float getSaveTime = 0, bool fileLoadTime = false);
	//=============================== gameTime ==============================

	//================================ getter ===============================
	virtual int getSaveFileNum() { return _saveFileNum; }
	virtual void setIsSavePoint(bool isSave) { _isSavePoint = isSave; }
	virtual void setCurrentScene(string sceneName) { _currentSceneName = sceneName; }
	virtual void setCurrentScene(POINT playerXY) { _playerPosition = playerXY; }
	//================================ getter ===============================

	//============================= AddressLink =============================
	virtual void setItemManagerAddressLink(itemManager* im) { _iM = im; }
	virtual void setPlayerManagerAddressLink(playerManager* pm) { _pM = pm; }
	virtual void setWorldMapAddressLink(worldMapScene* wm) { _wM = wm; }
	virtual void setWorldMapAddressLink(townScene* tm) { _tM = tm; }
	//============================= AddressLink =============================




	menu();
	~menu();
};



