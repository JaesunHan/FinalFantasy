#pragma once
#include "menu.h"
#include "cursor.h"

#define MAXCONTROLBTN	5
#define MAXCURSORSUBJECT	2

//�׽�Ʈ��
//class playerManager;
enum SELECTSUBJECT
{
	SELECT_BGM,
	SELECT_EFFECT
};

class configMenu : public menu
{
private:
	vector<image*> _bgmCtrlBtn;
	vector<image*> _eftCtrlBtn;

	cursor* _cursor;

	//BGM �̶� EFFECT ��ġ�� ��� ��Ʈ��(�� ��ġ�� Ŀ���� ����Ѵ�)
	RECT _rcCTRLNum[MAXCURSORSUBJECT];
	//�� ��Ʈ�� ���� ���� ����
	int _rcW, _rcH;
	//����Ű �Է¿� ���� Ŀ���̵��� ���� �ε���
	int _cursorIdx;

	//�׽�Ʈ�� ������ �ø�
	//playerManager* _pm;

	//BGM�� �����޴��� �ƴϸ� EFFECT�� �����ߴ��� �Ǻ��ϴ� �Ұ�
	bool isSelect[MAXCURSORSUBJECT];

public:
	HRESULT init();
	void release();
	void update();
	void render();

	//void setPlayerManagerAddressLink(playerManager* pm) {	_pm = pm; }


	configMenu();
	~configMenu();
};

