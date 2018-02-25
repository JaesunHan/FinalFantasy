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
	_belongEquipsNum = 0;
	_previousCusor = 0;
	_belongSelectOK = false;
	_equipSetOk = false;
	_isChangeValue = false;
	_preCursor = 0;

	changeMyWVNum = -1;
	changeMyAVNum = -1;
	changeMyHVNum = -1;
	changeMySVNum = -1;

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

	//커서 컨트롤
	if (!_equipButtonOn)  //메뉴버튼
	{
		_cursorI->keyControlX(210, _cursorXNum);

		buttonOnActive();

	}
	else
	{
		if (!_selectEquip)  //장착버튼
		{
			_cursorI->keyControlXY(350, 70, 2, 6);
			buttonOnEquipsActive();
		}
		else  //장착장비 선택버튼
		{
			_cursorI->keyControlY(70, _belongEquipsNum + 1);
			buttonOnItemActive();
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

	playerSlotRender(false);						    //슬롯 데이터
	char playerNum[256];
	sprintf(playerNum, "player%d", _selectPlayerNum);
	playerStatusEquipsRender(playerNum, _equipSetOk, changeMyWVNum, changeMyAVNum, changeMyHVNum, changeMySVNum, _isChangeValue);   //상태 데이터
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
	for (int i = _cursorXNum; i < _button->getVButton().size(); ++i)
	{
		if (i == _cursorI->getCursorPos() + 3) continue;
		_button->setVButtonAniStart(i, false);
	}


	//다른 버튼을 선택하면
	if (_previousCusor != _cursorI->getCursorPos() && _belongSelectOK)
	{
		//버튼삭제
		if (_button->getVButton().size() > 9)
		{
			for (int i = 9; i < _button->getVButton().size();)
			{
				_button->buttonRemoveOne(i);
			}
		}

		_belongSelectOK = false;
	}


	//버튼 선택시
	if (!_belongSelectOK)
	{
		//버튼생성
		switch (_cursorI->getCursorPos())
		{
			case BUTTON_RIGHTHAND: case BUTTON_LEFTHAND:
				belongEquiopsButtonSet(EQUIPS_WEAPON);
				if (_belongEquipsNum != 0) _belongSelectOK = true;
			break;
			case BUTTON_HEAD:
				belongEquiopsButtonSet(BUTTON_HEAD);
				if (_belongEquipsNum != 0) _belongSelectOK = true;
			break;
			case BUTTON_BODY:
				belongEquiopsButtonSet(BUTTON_BODY);
				if (_belongEquipsNum != 0) _belongSelectOK = true;
			break;
			case BUTTON_RELICS1: case BUTTON_RELICS2:
				belongEquiopsButtonSet(BUTTON_RELICS1);
				if (_belongEquipsNum != 0) _belongSelectOK = true;
			break;
		}

		_previousCusor = _cursorI->getCursorPos();
	}


	//장비선택 버튼으로(다음으로...)
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN) && _belongSelectOK)
	{
		_cursorI->init(CURSOR_RIGHT, 950, 120);
		_selectEquip = true;
	}


	//뒤로 돌아가기
	if (KEYMANAGER->isOnceKeyDown(VK_BACK))
	{
		_cursorI->init(CURSOR_RIGHT, 100, 30);
		_equipButtonOn = false;


		//버튼 에니메이션 STOP
		for (int i = _cursorXNum; i < _button->getVButton().size(); ++i)
		{
			_button->setVButtonAniStart(i, false);
		}
	}
}

void characterEquip::buttonOnItemActive()
{
	_equipSetOk = false; 


	//버튼 에니메이션 활성화
	_button->setVButtonAniStart(9 + _cursorI->getCursorYNum(), true);
	for (int i = 9; i < _button->getVButton().size(); ++i)
	{
		if (i == _cursorI->getCursorYNum() + 9) continue;
		_button->setVButtonAniStart(i, false);
	}

	//장비착용후 능력치 초기화 
	if (_cursorI->getCursorYNum() == _preCursor) _isChangeValue = true;  
	else _isChangeValue = false;



	//해당 장비 장착
	switch (_cursorI->getCursorYNum())
	{
		case 0:
			switch (_previousCusor)
			{
				case BUTTON_RIGHTHAND:
				weaponChange("myWeapon");
				break;
				case BUTTON_LEFTHAND:
				weaponChange("mySubWeapon");
				break;
				case BUTTON_HEAD:
				weaponChange("myHelmet");
				break;
				case BUTTON_BODY:
				weaponChange("myArmor");
				break;
			}

			_preCursor = _cursorI->getCursorYNum();
		break;
		case 1:
			switch (_previousCusor)
			{
				case BUTTON_RIGHTHAND:
				weaponChange("myWeapon");
				break;
				case BUTTON_LEFTHAND:
				weaponChange("mySubWeapon");
				break;
				case BUTTON_HEAD:
				weaponChange("myHelmet");
				break;
				case BUTTON_BODY:
				weaponChange("myArmor");
				break;
			}

			_preCursor = _cursorI->getCursorYNum();
		break;
		case 2:
			switch (_previousCusor)
			{
				case BUTTON_RIGHTHAND:
				weaponChange("myWeapon");
				break;
				case BUTTON_LEFTHAND:
				weaponChange("mySubWeapon");
				break;
				case BUTTON_HEAD:
				weaponChange("myHelmet");
				break;
				case BUTTON_BODY:
				weaponChange("myArmor");
				break;
			}

			_preCursor = _cursorI->getCursorYNum();
		break;
		case 3:
			switch (_previousCusor)
			{
				case BUTTON_RIGHTHAND:
				weaponChange("myWeapon");
				break;
				case BUTTON_LEFTHAND:
				weaponChange("mySubWeapon");
				break;
				case BUTTON_HEAD:
				weaponChange("myHelmet");
				break;
				case BUTTON_BODY:
				weaponChange("myArmor");
				break;
			}

			_preCursor = _cursorI->getCursorYNum();
		break;
	}


	//장비를 선택하면
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{		
		//초기화
		changeMyWVNum = -1;
		changeMyAVNum = -1;
		changeMyHVNum = -1;
		changeMySVNum = -1;

		//파일정보 리로딩
		this->init();

		_equipSetOk = true;  	//장비장착 능력치 tmp파일 저장 초기화
	}


	//뒤로 돌아가기
	if (KEYMANAGER->isOnceKeyDown(VK_BACK))
	{
		_cursorI->init(CURSOR_RIGHT, 300, 125);
		_selectEquip = false;
		_isChangeValue = false;
	}
}

//무기교체
void characterEquip::weaponChange(string equiptype, bool chageOn)
{
	//선택 플레이어
	char tmpPlayerNum[32];
	sprintf(tmpPlayerNum, "player%d", _selectPlayerNum);

	//선택 장비
	char tmpSelectEquip[32];
	ZeroMemory(&tmpSelectEquip, sizeof(tmpSelectEquip));

	//교체전 장비 아이템넘버
	int mountingEquip = 0;

	//교체할 장비 아이템넘버
	//int changeEquipNum = 0;
	char changeEqNum[CHARBUFFSHORT];
	ZeroMemory(&changeEqNum, sizeof(changeEqNum));

	//아이템 갯수 차감변수
	int minusWeaponEquip = 0;

	//장비타입 반환
	int equipType = 0;
	if		(!strcmp(equiptype.c_str(), "myWeapon"))	equipType = BUTTON_RIGHTHAND;
	else if (!strcmp(equiptype.c_str(), "mySubWeapon"))	equipType = BUTTON_LEFTHAND;
	else if (!strcmp(equiptype.c_str(), "myHelmet"))	equipType = BUTTON_HEAD;
	else if (!strcmp(equiptype.c_str(), "myArmor"))		equipType = BUTTON_BODY;

	mountingEquip = INIDATA->loadDataInterger("skgFile", tmpPlayerNum, equiptype.c_str());						//장착되어있는 장비 ItemNum


	int changeEquipVNum = 0;  //교체할장비의 벡터넘버

	switch (equipType)
	{
	case BUTTON_RIGHTHAND: case BUTTON_LEFTHAND:
		//교체할 장비의 아이템넘버
		for (int i = 0; i < _iM->getWeaponInventorySize(); ++i)
		{
			if (!strcmp(_button->getButtonText(_cursorI->getCursorYNum() + 9), _iM->getVItem()[_iM->getWeaponVNum(i)]->getItemName()))
			{
				if (equipType == BUTTON_RIGHTHAND)
				{
					changeMyWVNum = _iM->getVItem()[_iM->getWeaponVNum(i)]->getItemNumber();  //교체할 장비 ItemNum
					sprintf(changeEqNum, "%d", changeMyWVNum);
				}
				else
				{
					changeMySVNum = _iM->getVItem()[_iM->getWeaponVNum(i)]->getItemNumber();  //교체할 장비 ItemNum
					sprintf(changeEqNum, "%d", changeMySVNum);
				}
			
			}
		}

		//출력은 여기까지만 연산하고 리턴
		if (!chageOn) return;

		//교체할장비의 벡터넘버
		if (equipType == BUTTON_RIGHTHAND)
		{
			for (int i = 0; i < _iM->getWeaponInventorySize(); ++i)
			{
				if (_iM->getVItem()[_iM->getWeaponVNum(i)]->getItemNumber() == changeMyWVNum)
				{
					break;
				}
				changeEquipVNum++;
			}
		}
		else
		{
			for (int i = 0; i < _iM->getWeaponInventorySize(); ++i)
			{
				if (_iM->getVItem()[_iM->getWeaponVNum(i)]->getItemNumber() == changeMySVNum)
				{
					break;
				}
				changeEquipVNum++;
			}
		}


		//예외처리: 무기가 아니면...
		if (_iM->getVItem()[_iM->getWeaponVNum(changeEquipVNum)]->getItmeKind() != ITEM_WEAPON &&
			_iM->getVItem()[_iM->getWeaponVNum(changeEquipVNum)]->getItmeKind() != ITEM_SUB_WEAPON) break;


		minusWeaponEquip = _iM->getWeaponCount(changeEquipVNum) - 1;	 //선택된 장비 -> 갯수차감 
	

		if (minusWeaponEquip <= 0)
		{
			_iM->changeWeaponNumber(_iM->getVItem()[_iM->getWeaponVNum(changeEquipVNum)]->getItemName(), -1);
		}
		else
		{
			if (equipType == BUTTON_RIGHTHAND)
			{
				itemSave(MENUITEM_WEAPON, (changeMyWVNum - 1), minusWeaponEquip);  //선택된 장비 -> 갯수차감 저장
			}
			else
			{
				itemSave(MENUITEM_WEAPON, (changeMySVNum - 1), minusWeaponEquip);  //선택된 장비 -> 갯수차감 저장
			}

		}

		itemSave(MENUITEM_WEAPON, (mountingEquip - 1), 1);				 //장착되어있는 장비 -> 소유장비로 저장
		INIDATA->addData(tmpPlayerNum, equiptype.c_str(), changeEqNum);  //교체할 장비 착용
		INIDATA->iniSave("skgFile");
		break;
	case BUTTON_HEAD: case BUTTON_BODY:

		//교체할 장비의 아이템넘버
		for (int i = 0; i < _iM->getArmorInventorySize(); ++i)
		{
			if (!strcmp(_button->getButtonText(_cursorI->getCursorYNum() + 9), _iM->getVItem()[_iM->getArmorVNum(i)]->getItemName()))
			{

				if (equipType == BUTTON_HEAD)
				{
					changeMyHVNum = _iM->getVItem()[_iM->getArmorVNum(i)]->getItemNumber();  //교체할 장비 ItemNum
					sprintf(changeEqNum, "%d", changeMyHVNum);
				}
				else
				{
					changeMySVNum = _iM->getVItem()[_iM->getArmorVNum(i)]->getItemNumber();  //교체할 장비 ItemNum
					sprintf(changeEqNum, "%d", changeMySVNum);
				}
		
			}
		}

		//출력은 여기까지만 연산하고 리턴
		if (!chageOn) return;
	
		//교체할장비의 벡터넘버
		if (equipType == BUTTON_HEAD)
		{
			for (int i = 0; i < _iM->getArmorInventorySize(); ++i)
			{
				if (_iM->getVItem()[_iM->getArmorVNum(i)]->getItemNumber() == changeMyHVNum)
				{
					break;
				}
				changeEquipVNum++;
			}
		}
		else
		{
			for (int i = 0; i < _iM->getArmorInventorySize(); ++i)
			{
				if (_iM->getVItem()[_iM->getArmorVNum(i)]->getItemNumber() == changeMySVNum)
				{
					break;
				}
				changeEquipVNum++;
			}
		}

		//예외처리: 갑옷이 아니면...
		if (_iM->getVItem()[_iM->getArmorVNum(changeEquipVNum)]->getItmeKind() != ITEM_HELMET &&
			_iM->getVItem()[_iM->getArmorVNum(changeEquipVNum)]->getItmeKind() != ITEM_ARMOR) break;


		minusWeaponEquip = _iM->getArmorCount(changeEquipVNum) - 1;	 //선택된 장비 -> 갯수차감 

		if (minusWeaponEquip <= 0)
		{
			_iM->changeArmorNumber(_iM->getVItem()[_iM->getArmorVNum(changeEquipVNum)]->getItemName(), -1);
			//_iM->changeArmorNumber(changeEquipVNum, -1);  //예외처리(아이템 벡터삭제) -> 육포가 들어감!!!
		}
		else
		{
			if (equipType == BUTTON_HEAD)
			{
				itemSave(MENUITEM_ARMOR, (changeMyHVNum - 1), minusWeaponEquip);  //선택된 장비 -> 갯수차감 저장
			}
			else
			{
				itemSave(MENUITEM_ARMOR, (changeMySVNum - 1), minusWeaponEquip);  //선택된 장비 -> 갯수차감 저장
			}
		}

		itemSave(MENUITEM_ARMOR, (mountingEquip - 1), 1);				 //장착되어있는 장비 -> 소유장비로 저장
		INIDATA->addData(tmpPlayerNum, equiptype.c_str(), changeEqNum);  //교체할 장비 착용
		INIDATA->iniSave("skgFile");

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


//소유장비 버튼 셋팅
void characterEquip::belongEquiopsButtonSet(int useKInd)
{
	//버튼위치
	int buttonX = 1000;
	int buttonY = 100;
	int intervalY = 70;

	//선택한 플레이어 번호
	char tmpSelectPlayer[128];
	sprintf(tmpSelectPlayer, "player%d", _selectPlayerNum);

	_belongEquipsNum = 0;

	//========================== 버튼생성 ==========================
	//---------------------------------------- 버튼갯수
	switch (useKInd)
	{
		case EQUIPS_WEAPON:
			_belongEquipsNum = _iM->getWeaponInventorySize();
		break;
		case BUTTON_HEAD:	
			for (int i = 0; i < _iM->getArmorInventorySize(); ++i)
			{
				if (_iM->getVItem()[_iM->getArmorVNum(i)]->getItmeKind() == ITEM_HELMET)
				{
					_belongEquipsNum++;
				}
			}
		break;
		case BUTTON_BODY:
			for (int i = 0; i < _iM->getArmorInventorySize(); ++i)
			{
				if (_iM->getVItem()[_iM->getArmorVNum(i)]->getItmeKind() == ITEM_ARMOR)
				{
					_belongEquipsNum++;
				}
			}
		break;
		case BUTTON_RELICS1: case BUTTON_RELICS2:
			_belongEquipsNum = 0;
		break;
	}
	//---------------------------------------- 버튼생성
	for (int i = 0; i < _belongEquipsNum + 1; ++i)
	{
		//예외처리: 항목이 없으면...
		if (_belongEquipsNum == 0)
		{
			//버튼삭제
			if (_button->getVButton().size() > 9)
			{
				for (int i = 9; i < _button->getVButton().size();)
				{
					_button->buttonRemoveOne(i);
				}
			}

			break;
		}

		//EMPTY 버튼생성
		if (i == _belongEquipsNum && _belongEquipsNum != 0)
		{
			_button->buttonSet("버튼아이템힐", buttonX, buttonY + (i * intervalY), "EMPTY", 20, 2);
			return;
		}

		//버튼생성
		switch (useKInd)
		{
			case EQUIPS_WEAPON:
				_button->buttonSet("버튼아이템힐", buttonX, buttonY + (i * intervalY), _iM->getVItem()[_iM->getWeaponVNum(i)]->getItemName(), 20, 2, true, _iM->getWeaponCount(i), 70);
			break;
			case BUTTON_HEAD:
				for (int i = 0; i < _iM->getArmorInventorySize(); ++i)
				{
					if (_iM->getVItem()[_iM->getArmorVNum(i)]->getItmeKind() == ITEM_HELMET)
					{
						if (_belongEquipsNum == 1)
						{
							_button->buttonSet("버튼아이템힐", buttonX, buttonY + (0 * intervalY), _iM->getVItem()[_iM->getArmorVNum(i)]->getItemName(), 20, 2, true, _iM->getArmorCount(i), 75);
						}
						else
						{
							_button->buttonSet("버튼아이템힐", buttonX, buttonY + (i * intervalY), _iM->getVItem()[_iM->getArmorVNum(i)]->getItemName(), 20, 2, true, _iM->getArmorCount(i), 75);
						}				
					}
				}
			break;
			case BUTTON_BODY:
				for (int i = 0; i < _iM->getArmorInventorySize(); ++i)
				{
					if (_iM->getVItem()[_iM->getArmorVNum(i)]->getItmeKind() == ITEM_ARMOR)
					{
						if (_belongEquipsNum == 1)
						{
							_button->buttonSet("버튼아이템힐", buttonX, buttonY + (0 * intervalY), _iM->getVItem()[_iM->getArmorVNum(i)]->getItemName(), 20, 2, true, _iM->getArmorCount(i), 75);
						}
						else
						{
							_button->buttonSet("버튼아이템힐", buttonX, buttonY + (i * intervalY), _iM->getVItem()[_iM->getArmorVNum(i)]->getItemName(), 20, 2, true, _iM->getArmorCount(i), 75);
						}
						
					}
				}
			break;
			case BUTTON_RELICS1: case BUTTON_RELICS2:
				//_button->buttonSet("버튼아이템힐", buttonX, buttonY + (i * intervalY), _iM->getVItem()[_iM->getArmorVNum(i)]->getItemName(), 20, 2, true, _iM->getWeaponCount(i));
			break;
		}	
	}
}