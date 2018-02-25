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
	//��׶��� �̹���
	_bgImage = IMAGEMANAGER->findImage("ĳ�������޴�");

	//������ ���̺� ���� �������� 
	int saveFileNum = INIDATA->loadDataInterger("gameData", "gameData", "fileNum");
	_selectPlayerNum = INIDATA->loadDataInterger("gameData", "inventory", "selectChar");
	fileLoad(saveFileNum, _selectPlayerNum);  //skgFile���� �ش� ĳ���� ���� ��������

	//--------------------------------------- ��ư ---------------------------------------
	int buttonX, buttonY;
	buttonX = 150;
	buttonY = 10;
	_button = new fButton;
	//----------------------------------------------------------------- ��θ޴�
	for (int i = 0; i < 3; ++i)
	{
		if (i == 0) _button->buttonSet("�������������", buttonX + (i * 210), buttonY);
		if (i == 1) _button->buttonSet("�������������ȭ", buttonX + (i * 210), buttonY);
		if (i == 2) _button->buttonSet("��������񸮼�", buttonX + (i * 210), buttonY);
	}

	//---------------------- Ŀ�� ----------------------
	_cursorI = new cursor;
	_cursorXNum = 3;
	_cursorI->init(CURSOR_RIGHT, buttonX - 50, buttonY + 20);
	//---------------------- Ŀ�� ----------------------

	//----------------------------------------------------------------- �������
	equipsButtonSet(_iM->getWeaponInventorySize() + _iM->getArmorInventorySize());


	//--------------------------------------- ��ư ---------------------------------------

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
	//Ŀ��
	_cursorI->update();
	//��ư
	_button->update();

	//Ŀ�� ��Ʈ��
	if (!_equipButtonOn)  //�޴���ư
	{
		_cursorI->keyControlX(210, _cursorXNum);

		buttonOnActive();

	}
	else
	{
		if (!_selectEquip)  //������ư
		{
			_cursorI->keyControlXY(350, 70, 2, 6);
			buttonOnEquipsActive();
		}
		else  //������� ���ù�ư
		{
			_cursorI->keyControlY(70, _belongEquipsNum + 1);
			buttonOnItemActive();
		}

	}


	//�ɼ� �޴�����
	if (KEYMANAGER->isOnceKeyDown(VK_BACK))
	{
		_button->buttonRemove();
		delete _button;
		SCENEMANAGER->changeScene("���");
	}
}

void characterEquip::render() 
{
	_bgImage->render(getMemDC());
	_button->render();      //��ư
	_cursorI->render();  	//Ŀ�� 

	playerSlotRender(false);						    //���� ������
	char playerNum[256];
	sprintf(playerNum, "player%d", _selectPlayerNum);
	playerStatusEquipsRender(playerNum, _equipSetOk, changeMyWVNum, changeMyAVNum, changeMyHVNum, changeMySVNum, _isChangeValue);   //���� ������
}





//�޴����ý�
void characterEquip::buttonOnActive()
{
	//��ư ���ϸ��̼� Ȱ��ȭ
	_button->setVButtonAniStart(_cursorI->getCursorXNum(), true);
	for (int i = 0; i < _cursorXNum; ++i)
	{
		if (i == _cursorI->getCursorXNum()) continue;
		_button->setVButtonAniStart(i, false);
	}


	//��� �޴���ư ���ý�
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

//����ý�
void characterEquip::buttonOnEquipsActive()
{
	//��ư ���ϸ��̼� Ȱ��ȭ
	_button->setVButtonAniStart(_cursorI->getCursorPos() + 3, true);
	for (int i = _cursorXNum; i < _button->getVButton().size(); ++i)
	{
		if (i == _cursorI->getCursorPos() + 3) continue;
		_button->setVButtonAniStart(i, false);
	}


	//�ٸ� ��ư�� �����ϸ�
	if (_previousCusor != _cursorI->getCursorPos() && _belongSelectOK)
	{
		//��ư����
		if (_button->getVButton().size() > 9)
		{
			for (int i = 9; i < _button->getVButton().size();)
			{
				_button->buttonRemoveOne(i);
			}
		}

		_belongSelectOK = false;
	}


	//��ư ���ý�
	if (!_belongSelectOK)
	{
		//��ư����
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


	//����� ��ư����(��������...)
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN) && _belongSelectOK)
	{
		_cursorI->init(CURSOR_RIGHT, 950, 120);
		_selectEquip = true;
	}


	//�ڷ� ���ư���
	if (KEYMANAGER->isOnceKeyDown(VK_BACK))
	{
		_cursorI->init(CURSOR_RIGHT, 100, 30);
		_equipButtonOn = false;


		//��ư ���ϸ��̼� STOP
		for (int i = _cursorXNum; i < _button->getVButton().size(); ++i)
		{
			_button->setVButtonAniStart(i, false);
		}
	}
}

void characterEquip::buttonOnItemActive()
{
	_equipSetOk = false; 


	//��ư ���ϸ��̼� Ȱ��ȭ
	_button->setVButtonAniStart(9 + _cursorI->getCursorYNum(), true);
	for (int i = 9; i < _button->getVButton().size(); ++i)
	{
		if (i == _cursorI->getCursorYNum() + 9) continue;
		_button->setVButtonAniStart(i, false);
	}

	//��������� �ɷ�ġ �ʱ�ȭ 
	if (_cursorI->getCursorYNum() == _preCursor) _isChangeValue = true;  
	else _isChangeValue = false;



	//�ش� ��� ����
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


	//��� �����ϸ�
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{		
		//�ʱ�ȭ
		changeMyWVNum = -1;
		changeMyAVNum = -1;
		changeMyHVNum = -1;
		changeMySVNum = -1;

		//�������� ���ε�
		this->init();

		_equipSetOk = true;  	//������� �ɷ�ġ tmp���� ���� �ʱ�ȭ
	}


	//�ڷ� ���ư���
	if (KEYMANAGER->isOnceKeyDown(VK_BACK))
	{
		_cursorI->init(CURSOR_RIGHT, 300, 125);
		_selectEquip = false;
		_isChangeValue = false;
	}
}

//���ⱳü
void characterEquip::weaponChange(string equiptype, bool chageOn)
{
	//���� �÷��̾�
	char tmpPlayerNum[32];
	sprintf(tmpPlayerNum, "player%d", _selectPlayerNum);

	//���� ���
	char tmpSelectEquip[32];
	ZeroMemory(&tmpSelectEquip, sizeof(tmpSelectEquip));

	//��ü�� ��� �����۳ѹ�
	int mountingEquip = 0;

	//��ü�� ��� �����۳ѹ�
	//int changeEquipNum = 0;
	char changeEqNum[CHARBUFFSHORT];
	ZeroMemory(&changeEqNum, sizeof(changeEqNum));

	//������ ���� ��������
	int minusWeaponEquip = 0;

	//���Ÿ�� ��ȯ
	int equipType = 0;
	if		(!strcmp(equiptype.c_str(), "myWeapon"))	equipType = BUTTON_RIGHTHAND;
	else if (!strcmp(equiptype.c_str(), "mySubWeapon"))	equipType = BUTTON_LEFTHAND;
	else if (!strcmp(equiptype.c_str(), "myHelmet"))	equipType = BUTTON_HEAD;
	else if (!strcmp(equiptype.c_str(), "myArmor"))		equipType = BUTTON_BODY;

	mountingEquip = INIDATA->loadDataInterger("skgFile", tmpPlayerNum, equiptype.c_str());						//�����Ǿ��ִ� ��� ItemNum


	int changeEquipVNum = 0;  //��ü������� ���ͳѹ�

	switch (equipType)
	{
	case BUTTON_RIGHTHAND: case BUTTON_LEFTHAND:
		//��ü�� ����� �����۳ѹ�
		for (int i = 0; i < _iM->getWeaponInventorySize(); ++i)
		{
			if (!strcmp(_button->getButtonText(_cursorI->getCursorYNum() + 9), _iM->getVItem()[_iM->getWeaponVNum(i)]->getItemName()))
			{
				if (equipType == BUTTON_RIGHTHAND)
				{
					changeMyWVNum = _iM->getVItem()[_iM->getWeaponVNum(i)]->getItemNumber();  //��ü�� ��� ItemNum
					sprintf(changeEqNum, "%d", changeMyWVNum);
				}
				else
				{
					changeMySVNum = _iM->getVItem()[_iM->getWeaponVNum(i)]->getItemNumber();  //��ü�� ��� ItemNum
					sprintf(changeEqNum, "%d", changeMySVNum);
				}
			
			}
		}

		//����� ��������� �����ϰ� ����
		if (!chageOn) return;

		//��ü������� ���ͳѹ�
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


		//����ó��: ���Ⱑ �ƴϸ�...
		if (_iM->getVItem()[_iM->getWeaponVNum(changeEquipVNum)]->getItmeKind() != ITEM_WEAPON &&
			_iM->getVItem()[_iM->getWeaponVNum(changeEquipVNum)]->getItmeKind() != ITEM_SUB_WEAPON) break;


		minusWeaponEquip = _iM->getWeaponCount(changeEquipVNum) - 1;	 //���õ� ��� -> �������� 
	

		if (minusWeaponEquip <= 0)
		{
			_iM->changeWeaponNumber(_iM->getVItem()[_iM->getWeaponVNum(changeEquipVNum)]->getItemName(), -1);
		}
		else
		{
			if (equipType == BUTTON_RIGHTHAND)
			{
				itemSave(MENUITEM_WEAPON, (changeMyWVNum - 1), minusWeaponEquip);  //���õ� ��� -> �������� ����
			}
			else
			{
				itemSave(MENUITEM_WEAPON, (changeMySVNum - 1), minusWeaponEquip);  //���õ� ��� -> �������� ����
			}

		}

		itemSave(MENUITEM_WEAPON, (mountingEquip - 1), 1);				 //�����Ǿ��ִ� ��� -> �������� ����
		INIDATA->addData(tmpPlayerNum, equiptype.c_str(), changeEqNum);  //��ü�� ��� ����
		INIDATA->iniSave("skgFile");
		break;
	case BUTTON_HEAD: case BUTTON_BODY:

		//��ü�� ����� �����۳ѹ�
		for (int i = 0; i < _iM->getArmorInventorySize(); ++i)
		{
			if (!strcmp(_button->getButtonText(_cursorI->getCursorYNum() + 9), _iM->getVItem()[_iM->getArmorVNum(i)]->getItemName()))
			{

				if (equipType == BUTTON_HEAD)
				{
					changeMyHVNum = _iM->getVItem()[_iM->getArmorVNum(i)]->getItemNumber();  //��ü�� ��� ItemNum
					sprintf(changeEqNum, "%d", changeMyHVNum);
				}
				else
				{
					changeMySVNum = _iM->getVItem()[_iM->getArmorVNum(i)]->getItemNumber();  //��ü�� ��� ItemNum
					sprintf(changeEqNum, "%d", changeMySVNum);
				}
		
			}
		}

		//����� ��������� �����ϰ� ����
		if (!chageOn) return;
	
		//��ü������� ���ͳѹ�
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

		//����ó��: ������ �ƴϸ�...
		if (_iM->getVItem()[_iM->getArmorVNum(changeEquipVNum)]->getItmeKind() != ITEM_HELMET &&
			_iM->getVItem()[_iM->getArmorVNum(changeEquipVNum)]->getItmeKind() != ITEM_ARMOR) break;


		minusWeaponEquip = _iM->getArmorCount(changeEquipVNum) - 1;	 //���õ� ��� -> �������� 

		if (minusWeaponEquip <= 0)
		{
			_iM->changeArmorNumber(_iM->getVItem()[_iM->getArmorVNum(changeEquipVNum)]->getItemName(), -1);
			//_iM->changeArmorNumber(changeEquipVNum, -1);  //����ó��(������ ���ͻ���) -> ������ ��!!!
		}
		else
		{
			if (equipType == BUTTON_HEAD)
			{
				itemSave(MENUITEM_ARMOR, (changeMyHVNum - 1), minusWeaponEquip);  //���õ� ��� -> �������� ����
			}
			else
			{
				itemSave(MENUITEM_ARMOR, (changeMySVNum - 1), minusWeaponEquip);  //���õ� ��� -> �������� ����
			}
		}

		itemSave(MENUITEM_ARMOR, (mountingEquip - 1), 1);				 //�����Ǿ��ִ� ��� -> �������� ����
		INIDATA->addData(tmpPlayerNum, equiptype.c_str(), changeEqNum);  //��ü�� ��� ����
		INIDATA->iniSave("skgFile");

		break;
	}



}


//��� ��ư ����
void characterEquip::equipsButtonSet(int buttonNum)
{
	//��ư��ġ
	int buttonX = 350;
	int buttonY = 110;
	int intervalX = 350;
	int intervalY = 70;
	
    //������ �÷��̾� ��ȣ
	char tmpSelectPlayer[128];
	sprintf(tmpSelectPlayer, "player%d", _selectPlayerNum);


	//������ ��ư & �̸�
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			int tmpEquipNum = 0;  //�ε����� �������� ����

			switch (j)
			{
				case 0:
					switch (i)
					{
						case 0:
							tmpEquipNum = INIDATA->loadDataInterger("skgFile", tmpSelectPlayer, "myWeapon");
							_button->buttonSet("��ư��������", buttonX + (j * intervalX), buttonY + (i * intervalY),
								_iM->getVItem()[itemGetNum(tmpEquipNum)]->getItemName(), 20, 2);  //��ü���������� ����[�ε����������� �����۳ѹ��� Ž���� ���ͳѹ�]->�̸� 
						break;
						case 1:
							tmpEquipNum = INIDATA->loadDataInterger("skgFile", tmpSelectPlayer, "myHelmet");
							_button->buttonSet("��ư��������", buttonX + (j * intervalX), buttonY + (i * intervalY),
								_iM->getVItem()[itemGetNum(tmpEquipNum)]->getItemName(), 20, 2);  //��ü���������� ����[�ε����������� �����۳ѹ��� Ž���� ���ͳѹ�]->�̸� 
						break;
						case 2:
							//tmpEquipNum = INIDATA->loadDataInterger("skgFile", tmpSelectPlayer, "myArmor");
							_button->buttonSet("��ư��������", buttonX + (j * intervalX), buttonY + (i * intervalY),
								"", 20, 2);  //��ü���������� ���Ϳ��� �����۳ѹ��� �̸��޾ƿ� 
						break;
					}
				break;
				case 1:
					switch (i)
					{
						case 0:
							tmpEquipNum = INIDATA->loadDataInterger("skgFile", tmpSelectPlayer, "mySubWeapon");
							_button->buttonSet("��ư��������", buttonX + (j * intervalX), buttonY + (i * intervalY),
								_iM->getVItem()[itemGetNum(tmpEquipNum)]->getItemName(), 20, 2);  //��ü���������� ����[�ε����������� �����۳ѹ��� Ž���� ���ͳѹ�]->�̸� 
						break;
						case 1:
							tmpEquipNum = INIDATA->loadDataInterger("skgFile", tmpSelectPlayer, "myArmor");
							_button->buttonSet("��ư��������", buttonX + (j * intervalX), buttonY + (i * intervalY),
								_iM->getVItem()[itemGetNum(tmpEquipNum)]->getItemName(), 20, 2);  //��ü���������� ����[�ε����������� �����۳ѹ��� Ž���� ���ͳѹ�]->�̸� 
						break;
						case 2:
							//tmpEquipNum = INIDATA->loadDataInterger("skgFile", tmpSelectPlayer, "myArmor");
							_button->buttonSet("��ư��������", buttonX + (j * intervalX), buttonY + (i * intervalY),
								"", 20, 2);  //��ü���������� ���Ϳ��� �����۳ѹ��� �̸��޾ƿ� 
						break;
					}
				break;

			}

		}
	}

}


//������� ��ư ����
void characterEquip::belongEquiopsButtonSet(int useKInd)
{
	//��ư��ġ
	int buttonX = 1000;
	int buttonY = 100;
	int intervalY = 70;

	//������ �÷��̾� ��ȣ
	char tmpSelectPlayer[128];
	sprintf(tmpSelectPlayer, "player%d", _selectPlayerNum);

	_belongEquipsNum = 0;

	//========================== ��ư���� ==========================
	//---------------------------------------- ��ư����
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
	//---------------------------------------- ��ư����
	for (int i = 0; i < _belongEquipsNum + 1; ++i)
	{
		//����ó��: �׸��� ������...
		if (_belongEquipsNum == 0)
		{
			//��ư����
			if (_button->getVButton().size() > 9)
			{
				for (int i = 9; i < _button->getVButton().size();)
				{
					_button->buttonRemoveOne(i);
				}
			}

			break;
		}

		//EMPTY ��ư����
		if (i == _belongEquipsNum && _belongEquipsNum != 0)
		{
			_button->buttonSet("��ư��������", buttonX, buttonY + (i * intervalY), "EMPTY", 20, 2);
			return;
		}

		//��ư����
		switch (useKInd)
		{
			case EQUIPS_WEAPON:
				_button->buttonSet("��ư��������", buttonX, buttonY + (i * intervalY), _iM->getVItem()[_iM->getWeaponVNum(i)]->getItemName(), 20, 2, true, _iM->getWeaponCount(i), 70);
			break;
			case BUTTON_HEAD:
				for (int i = 0; i < _iM->getArmorInventorySize(); ++i)
				{
					if (_iM->getVItem()[_iM->getArmorVNum(i)]->getItmeKind() == ITEM_HELMET)
					{
						if (_belongEquipsNum == 1)
						{
							_button->buttonSet("��ư��������", buttonX, buttonY + (0 * intervalY), _iM->getVItem()[_iM->getArmorVNum(i)]->getItemName(), 20, 2, true, _iM->getArmorCount(i), 75);
						}
						else
						{
							_button->buttonSet("��ư��������", buttonX, buttonY + (i * intervalY), _iM->getVItem()[_iM->getArmorVNum(i)]->getItemName(), 20, 2, true, _iM->getArmorCount(i), 75);
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
							_button->buttonSet("��ư��������", buttonX, buttonY + (0 * intervalY), _iM->getVItem()[_iM->getArmorVNum(i)]->getItemName(), 20, 2, true, _iM->getArmorCount(i), 75);
						}
						else
						{
							_button->buttonSet("��ư��������", buttonX, buttonY + (i * intervalY), _iM->getVItem()[_iM->getArmorVNum(i)]->getItemName(), 20, 2, true, _iM->getArmorCount(i), 75);
						}
						
					}
				}
			break;
			case BUTTON_RELICS1: case BUTTON_RELICS2:
				//_button->buttonSet("��ư��������", buttonX, buttonY + (i * intervalY), _iM->getVItem()[_iM->getArmorVNum(i)]->getItemName(), 20, 2, true, _iM->getWeaponCount(i));
			break;
		}	
	}
}