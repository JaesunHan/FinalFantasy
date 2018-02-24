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

	playerSlotRender(false);						//���� ������
	playerStatusEquipsRender(_selectPlayerNum);     //���� ������


	//------------------------------------------------------------------- test
	char testBuff[32];
	textPrint(getMemDC(), itoa(_previousCusor, testBuff, 10), 100, 100);
	//textPrint(getMemDC(), itoa(_cursorI->getCursorPos(), testBuff, 10), 100, 120);
	//textPrint(getMemDC(), itoa(_belongEquipsNum, testBuff, 10), 100, 140);
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
			_belongSelectOK = true;

			break;
		case BUTTON_HEAD: case BUTTON_BODY:

			belongEquiopsButtonSet(EQUIPS_ARMOR);
			_belongSelectOK = true;

			break;
		case BUTTON_RELICS1: case BUTTON_RELICS2:

			belongEquiopsButtonSet(EQUIPS_RELICS);
			_belongSelectOK = true;

			break;
		}

		_previousCusor = _cursorI->getCursorPos();
	}







	//����� ��ư����(��������...)
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		_cursorI->init(CURSOR_RIGHT, 950, 120);
		_selectEquip = true;
	}


	//�ڷ� ���ư���
	if (KEYMANAGER->isOnceKeyDown(VK_BACK))
	{
		_cursorI->init(CURSOR_RIGHT, 100, 30);
		_equipButtonOn = false;
	}
}

void characterEquip::buttonOnItemActive()
{
	//��ư ���ϸ��̼� Ȱ��ȭ
	_button->setVButtonAniStart(9 + _cursorI->getCursorYNum(), true);
	for (int i = 9; i < _button->getVButton().size(); ++i)
	{
		if (i == _cursorI->getCursorYNum() + 9) continue;
		_button->setVButtonAniStart(i, false);
	}


	//��� �����ϸ�
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		//�ش� ��� ����
		switch (_cursorI->getCursorYNum())
		{
			case 0:
				//������ ��� �����ϱ�
				//tmpPartyIdx = INIDATA->loadDataInterger("skgFile", "player0", "partyIdx");
				//_iM->useItemInMenu(tmpPartyIdx, _selectItemNum);
				//��� �����ϱ�
			break;
			case 1:

			break;
			case 2:

			break;
			case 3:

			break;
			case 4:

			break;
			case 5:

			break;
		}
	}


	//�ڷ� ���ư���
	if (KEYMANAGER->isOnceKeyDown(VK_BACK))
	{
		_cursorI->init(CURSOR_RIGHT, 300, 125);
		_selectEquip = false;
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

	//========================== ��ư���� ==========================
	//---------------------------------------- ��ư����
	switch (useKInd)
	{
		case EQUIPS_WEAPON:
			_belongEquipsNum = _iM->getWeaponInventorySize();
		break;
		case EQUIPS_ARMOR:
			_belongEquipsNum = _iM->getWeaponInventorySize();
		break;
		case EQUIPS_RELICS:
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
		if (i == _belongEquipsNum)
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
			case EQUIPS_ARMOR:
				_button->buttonSet("��ư��������", buttonX, buttonY + (i * intervalY), _iM->getVItem()[_iM->getArmorVNum(i)]->getItemName(), 20, 2, true, _iM->getWeaponCount(i), 70);
			break;
			case EQUIPS_RELICS:
				//_button->buttonSet("��ư��������", buttonX, buttonY + (i * intervalY), _iM->getVItem()[_iM->getArmorVNum(i)]->getItemName(), 20, 2, true, _iM->getWeaponCount(i));
			break;
		}	
	}
}