#pragma once
#include "menu.h"
#include "cursor.h"


enum BUTTON_EQUIPS
{
	BUTTON_RIGHTHAND,
	BUTTON_LEFTHAND,
	BUTTON_HEAD,
	BUTTON_BODY,
	BUTTON_RELICS1,
	BUTTON_RELICS2
};

enum EQIUIPS_USEKIND
{
	EQUIPS_EMPTY,
	EQUIPS_WEAPON,
	EQUIPS_ARMOR,
	EQUIPS_RELICS
};


class characterEquip : public menu
{
private:
	cursor * _cursorI;

	bool _equipButtonOn;
	bool _selectEquip;
	int _selectPlayerNum;
	int _belongEquipsNum;  //������ ������� ����

	int  _previousCusor;   //���� Ŀ����ġ ����
	bool _belongSelectOK;  //������ư ���ÿ���
	bool _equipSetOk;      //������� ����
	bool _isChangeValue;   //��񺯰� �ɷ�ġ �ݿ�����
	int _preCursor;     //Ŀ������ ��ġ

	int changeMyWVNum;     //������ ��� ���ͳѹ�
	int changeMyAVNum;	   //������ ��� ���ͳѹ�
	int changeMyHVNum;	   //������ ��� ���ͳѹ�
	int changeMySVNum;	   //������ ��� ���ͳѹ�

public:
	HRESULT init();
	void release();
	void update();
	void render();

	//��ư�׼�
	void buttonOnActive();
	void buttonOnEquipsActive();
	void buttonOnItemActive();
	void equipsButtonSet(int buttonNum);
	void belongEquiopsButtonSet(int equipKInd);

	//���ⱳü
	void weaponChange(string equiptype, bool chageOn = false);


	//�޸� ��巹�� ��ũ
	void setItemManagerAddressLink(itemManager* im) { _iM = im; }


	characterEquip();
	~characterEquip();
};

