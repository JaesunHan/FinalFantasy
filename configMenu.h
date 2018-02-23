#pragma once
#include "menu.h"
#include "cursor.h"

#define MAXCONTROLBTN	5
#define MAXCURSORPOS	2

//테스트용
//class playerManager;

class configMenu : public menu
{
private:
	vector<image*> _bgmCtrlBtn;
	vector<image*> _eftCtrlBtn;

	cursor* _cursor;

	//BGM 이랑 EFFECT 위치에 띄울 렉트들(이 위치에 커서를 출력한다)
	RECT _rcCTRLNum[MAXCURSORPOS];
	//위 렉트의 가로 세로 길이
	int _rcW, _rcH;
	//방향키 입력에 따를 커서이동에 사용될 인덱스
	int _cursorIdx;

	//테스트용 껍데이 플메
	//playerManager* _pm;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	//void setPlayerManagerAddressLink(playerManager* pm) {	_pm = pm; }


	configMenu();
	~configMenu();
};

