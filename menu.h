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
	image* img;             //�÷��̾� �̹���
	float x, y;             //�÷��̾� �̹��� ��ġ
	int level;              //�÷��̾� ����
	int hp, maxHp;          //�÷��̾� ü��
	int mp, maxMp;          //�÷��̾� ����
	TCHAR name[128];		//�÷��̾� �̸�
	TCHAR job[128];			//�÷��̾� ����
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
	//======= saveLoad =======

	//======== button ========
	fButton*  _button;
	//======== button ========

	//======== player ========
	vPlayer   _vPlayer;
	viPlayer  _viPlayer;

	tagPlayer _playerSlot;  //�� ���Կ� �÷��̾� ���� ���� ����ü ����
	bool _fileLoadOk[4];    //���̺� ���� ���� �����Ǻ�
	int _selectFileCount;   //���� ������ ������ �����ֱ� ���� ī��Ʈ �� (�ٷ� ���ù�ư���� �̵����� �ʵ���) 
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




	menu();
	~menu();

};



