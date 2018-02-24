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

	//Ŀ�� ��Ʈ��X: �޴���ư
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
	for (int i = _cursorXNum; i < _cursorXNum + 6; ++i)
	{
		if (i == _cursorI->getCursorPos() + 3) continue;
		_button->setVButtonAniStart(i, false);
	}


	//��ư ���ý�
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