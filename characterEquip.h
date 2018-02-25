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
	int _belongEquipsNum;  //종류별 소유장비 갯수

	int  _previousCusor;   //이전 커서위치 저장
	bool _belongSelectOK;  //장착버튼 선택여부
	bool _equipSetOk;      //장비장착 여부
	bool _isChangeValue;   //장비변경 능력치 반영여부
	int _preCursor;     //커서이전 위치

	int changeMyWVNum;     //변경할 장비 벡터넘버
	int changeMyAVNum;	   //변경할 장비 벡터넘버
	int changeMyHVNum;	   //변경할 장비 벡터넘버
	int changeMySVNum;	   //변경할 장비 벡터넘버

public:
	HRESULT init();
	void release();
	void update();
	void render();

	//버튼액션
	void buttonOnActive();
	void buttonOnEquipsActive();
	void buttonOnItemActive();
	void equipsButtonSet(int buttonNum);
	void belongEquiopsButtonSet(int equipKInd);

	//무기교체
	void weaponChange(string equiptype, bool chageOn = false);


	//메모리 어드레스 링크
	void setItemManagerAddressLink(itemManager* im) { _iM = im; }


	characterEquip();
	~characterEquip();
};

