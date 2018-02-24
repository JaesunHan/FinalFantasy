#include "stdafx.h"
#include "characterEquip.h"
#include "itemManager.h"


characterEquip::characterEquip()
{
}


characterEquip::~characterEquip()
{
}


HRESULT characterEquip::init()
{
	//백그라운드 이미지
	_bgImage = IMAGEMANAGER->findImage("캐릭터장비메뉴");

	//선택한 세이브 파일 가져오기 
	int saveFileNum = INIDATA->loadDataInterger("gameData", "gameData", "fileNum");
	_selectPlayerNum = INIDATA->loadDataInterger("gameData", "inventory", "selectChar");
	fileLoad(saveFileNum, _selectPlayerNum);  //skgFile에서 해당 캐릭터 정보 가져오기

	//--------------------------------------- 버튼 ---------------------------------------
	int buttonX, buttonY;
	buttonX = 150;
	buttonY = 10;
	_button = new fButton;
	//----------------------------------------------------------------- 상부메뉴
	for (int i = 0; i < 3; ++i)
	{
		if (i == 0) _button->buttonSet("아이콘장비장착", buttonX + (i * 210), buttonY);
		if (i == 1) _button->buttonSet("아이콘장비최적화", buttonX + (i * 210), buttonY);
		if (i == 2) _button->buttonSet("아이콘장비리셋", buttonX + (i * 210), buttonY);
	}

	//---------------------- 커서 ----------------------
	_cursorI = new cursor;
	_cursorXNum = 3;
	_cursorI->init(CURSOR_RIGHT, buttonX - 50, buttonY + 20);
	//---------------------- 커서 ----------------------

	//----------------------------------------------------------------- 장비장착
	equipsButtonSet(_iM->getWeaponInventorySize() + _iM->getArmorInventorySize());


	//--------------------------------------- 버튼 ---------------------------------------

	_equipButtonOn = false;
	_selectEquip = false;


	return S_OK;
}

void characterEquip::release()
{

}

void characterEquip::update() 
{
	//커서
	_cursorI->update();
	//버튼
	_button->update();

	//커서 컨트롤X: 메뉴버튼
	if (!_equipButtonOn)
	{
		_cursorI->keyControlX(210, _cursorXNum);

		buttonOnActive();
	}
	else
	{
		if (!_selectEquip)
		{
			_cursorI->keyControlXY(350, 70, 2, 6);
			buttonOnEquipsActive();
		}
		else
		{

		}

	}


	//옵션 메뉴가기
	if (KEYMANAGER->isOnceKeyDown(VK_BACK))
	{
		_button->buttonRemove();
		delete _button;
		SCENEMANAGER->changeScene("장비");
	}

}

void characterEquip::render() 
{
	_bgImage->render(getMemDC());
	_button->render();      //버튼
	_cursorI->render();  	//커서 

	playerSlotRender(false);						//슬롯 데이터
	playerStatusEquipsRender(_selectPlayerNum);     //상태 데이터
}


//메뉴선택시
void characterEquip::buttonOnActive()
{
	//버튼 에니메이션 활성화
	_button->setVButtonAniStart(_cursorI->getCursorXNum(), true);
	for (int i = 0; i < _cursorXNum; ++i)
	{
		if (i == _cursorI->getCursorXNum()) continue;
		_button->setVButtonAniStart(i, false);
	}


	//상단 메뉴버튼 선택시
	switch (_cursorI->getCursorXNum())
	{
		case 0:
			if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
			{
				_cursorI->init(CURSOR_RIGHT, 300, 125);
				_equipButtonOn = true;
			}
		break;
		case 1:

		break;
		case 2:

		break;
	}

}

//장비선택시
void characterEquip::buttonOnEquipsActive()
{
	//버튼 에니메이션 활성화
	_button->setVButtonAniStart(_cursorI->getCursorPos() + 3, true);
	for (int i = _cursorXNum; i < _cursorXNum + 6; ++i)
	{
		if (i == _cursorI->getCursorPos() + 3) continue;
		_button->setVButtonAniStart(i, false);
	}


	//버튼 선택시
	switch (_cursorI->getCursorXNum())
	{
		case 0:
	
			if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
			{
				_cursorI->init(CURSOR_RIGHT, 300, 125);
				_equipButtonOn = true;
			}
		break;
	}

}


//장비 버튼 셋팅
void characterEquip::equipsButtonSet(int buttonNum)
{
	//버튼위치
	int buttonX = 350;
	int buttonY = 110;
	int intervalX = 350;
	int intervalY = 70;
	
    //선택한 플레이어 번호
	char tmpSelectPlayer[128];
	sprintf(tmpSelectPlayer, "player%d", _selectPlayerNum);


	
	//아이템 버튼 & 이름
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			int tmpEquipNum = 0;  //로드파일 정보담을 변수

			switch (j)
			{
				case 0:
					switch (i)
					{
						case 0:
							tmpEquipNum = INIDATA->loadDataInterger("skgFile", tmpSelectPlayer, "myWeapon");
							_button->buttonSet("버튼아이템힐", buttonX + (j * intervalX), buttonY + (i * intervalY),
								_iM->getVItem()[itemGetNum(tmpEquipNum)]->getItemName(), 20, 2);  //전체아이템정보 벡터[로드파일정보의 아이템넘버로 탐색한 벡터넘버]->이름 
						break;
						case 1:
							tmpEquipNum = INIDATA->loadDataInterger("skgFile", tmpSelectPlayer, "myHelmet");
							_button->buttonSet("버튼아이템힐", buttonX + (j * intervalX), buttonY + (i * intervalY),
								_iM->getVItem()[itemGetNum(tmpEquipNum)]->getItemName(), 20, 2);  //전체아이템정보 벡터[로드파일정보의 아이템넘버로 탐색한 벡터넘버]->이름 
						break;
						case 2:
							//tmpEquipNum = INIDATA->loadDataInterger("skgFile", tmpSelectPlayer, "myArmor");
							_button->buttonSet("버튼아이템힐", buttonX + (j * intervalX), buttonY + (i * intervalY),
								"", 20, 2);  //전체아이템정보 벡터에서 아이템넘버로 이름받아옴 
						break;
					}
				break;
				case 1:
					switch (i)
					{
						case 0:
							tmpEquipNum = INIDATA->loadDataInterger("skgFile", tmpSelectPlayer, "mySubWeapon");
							_button->buttonSet("버튼아이템힐", buttonX + (j * intervalX), buttonY + (i * intervalY),
								_iM->getVItem()[itemGetNum(tmpEquipNum)]->getItemName(), 20, 2);  //전체아이템정보 벡터[로드파일정보의 아이템넘버로 탐색한 벡터넘버]->이름 
						break;
						case 1:
							tmpEquipNum = INIDATA->loadDataInterger("skgFile", tmpSelectPlayer, "myArmor");
							_button->buttonSet("버튼아이템힐", buttonX + (j * intervalX), buttonY + (i * intervalY),
								_iM->getVItem()[itemGetNum(tmpEquipNum)]->getItemName(), 20, 2);  //전체아이템정보 벡터[로드파일정보의 아이템넘버로 탐색한 벡터넘버]->이름 
						break;
						case 2:
							//tmpEquipNum = INIDATA->loadDataInterger("skgFile", tmpSelectPlayer, "myArmor");
							_button->buttonSet("버튼아이템힐", buttonX + (j * intervalX), buttonY + (i * intervalY),
								"", 20, 2);  //전체아이템정보 벡터에서 아이템넘버로 이름받아옴 
						break;
					}
				break;

			}

		}
	}
	



}