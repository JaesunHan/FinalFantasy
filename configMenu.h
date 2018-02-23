#pragma once
#include "menu.h"
#include "cursor.h"

#define MAXCONTROLBTN	5
#define MAXCURSORSUBJECT	2

//테스트용
//class playerManager;
enum SELECTSUBJECT
{
	SELECT_BGM,
	SELECT_EFFECT
};

enum SELECTTITLE
{
	SELECT_0_00F,		//볼륨 값 : 0.0f
	SELECT_0_25F,		//볼륨 값 : 0.25f
	SELECT_0_50F,		//볼륨 값 : 0.5f
	SELECT_0_75F,		//볼륨 값 : 0.75f
	SELECT_1_00F		//볼륨 값 : 1.0f
};

struct tagConfigButton
{
	image*	btnImg;			//버튼 이미지
	char	btnTxt;			//버튼 이미지위에 출력될 글자
	int		btnVolume;		//이 버튼이 갖는 볼륨값

};

class configMenu : public menu
{
private:
	vector<image*> _bgmCtrlBtn;
	vector<image*> _eftCtrlBtn;

	cursor* _cursor;

	//BGM 이랑 EFFECT 위치에 띄울 렉트들(이 위치에 커서를 출력한다)
	RECT _rcCTRLNum[MAXCURSORSUBJECT];
	//위 렉트의 가로 세로 길이
	int _rcW, _rcH;
	//방향키 입력에 따를 커서이동에 사용될 인덱스
	int _cursorIdx;

	//테스트용 껍데이 플메
	//playerManager* _pm;

	//BGM을 선택햇는지 아니면 EFFECT를 선택했는지 판별하는 불값
	bool _isSelect[MAXCURSORSUBJECT];
	//BGM 이나 EFFECT 쪽에서 커서가 출력되어야 하는 상황에는 이 값이 true이다\
	만약 BGM 이나 EFECT 중에 무언가를 선택해서 \
	커서가 오른쪽에 5항목을 가리켜야 하는 상황이라면 이 값이 false 이다
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

