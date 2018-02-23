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

enum SELECTTITLE
{
	SELECT_0_00F,		//���� �� : 0.0f
	SELECT_0_25F,		//���� �� : 0.25f
	SELECT_0_50F,		//���� �� : 0.5f
	SELECT_0_75F,		//���� �� : 0.75f
	SELECT_1_00F		//���� �� : 1.0f
};

struct tagConfigButton
{
	image*	btnImg;			//��ư �̹���
	char	btnTxt;			//��ư �̹������� ��µ� ����
	int		btnVolume;		//�� ��ư�� ���� ������

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
	bool _isSelect[MAXCURSORSUBJECT];
	//BGM �̳� EFFECT �ʿ��� Ŀ���� ��µǾ�� �ϴ� ��Ȳ���� �� ���� true�̴�\
	���� BGM �̳� EFECT �߿� ���𰡸� �����ؼ� \
	Ŀ���� �����ʿ� 5�׸��� �����Ѿ� �ϴ� ��Ȳ�̶�� �� ���� false �̴�
	bool _isSubject;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	//void setPlayerManagerAddressLink(playerManager* pm) {	_pm = pm; }


	configMenu();
	~configMenu();
};

