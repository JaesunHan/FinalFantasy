#include "stdafx.h"
#include "itemMenu.h"
#include "itemManager.h"


itemMenu::itemMenu()
{
}


itemMenu::~itemMenu()
{
}

HRESULT itemMenu::init()
{
	_bgImage = IMAGEMANAGER->findImage("�����۸޴�");

	//tmp ���� �������� (skgFile)
	fileLoad(0, -1, true);

	//�÷��̾� �ο���
	int saveFileNum = INIDATA->loadDataInterger("gameData", "gameData", "fileNum");
	int playerNum = INIDATA->loadDataBodyNum(saveFileNum);  //�÷��̾� �ο���

	//--------------------------------------- ��ư ---------------------------------------
	//----------------------------------------------------------------- ������
	int buttonX, buttonY;
	buttonX = 150;
	buttonY = 10;
	_button = new fButton;
	for (int i = 0; i < 3; ++i)
	{
		if (i == 0) _button->buttonSet("�����ܾ����ۻ��", buttonX + (i * 210), buttonY);
		if (i == 1) _button->buttonSet("�����ܾ���������", buttonX + (i * 210), buttonY);
		if (i == 2) _button->buttonSet("�����ܾ����۷���", buttonX + (i * 210), buttonY);
	}


	//---------------------- Ŀ�� ----------------------
	_cursorI = new cursor;
	_cursorXNum = 3;
	_cursorI->init(CURSOR_RIGHT, buttonX - 50, buttonY + 20);
	//---------------------- Ŀ�� ----------------------


	//----------------------------------------------------------------- �÷��̾�
	buttonX = 1000;
	buttonY = 100;
	for (int i = 0; i < playerNum; ++i)
	{
		//���̺����� �̸�
		TCHAR fileName[32];
		ZeroMemory(&fileName, sizeof(fileName));
		wsprintf(fileName, "saveFile%d", saveFileNum);

		//ĳ���� �ѹ�
		TCHAR playerNum[32];
		ZeroMemory(&playerNum, sizeof(playerNum));
		wsprintf(playerNum, "player%d", i);

		//�ش� ĳ���� ��ư����
		if (!strcmp(INIDATA->loadDataString(fileName, playerNum, "name"), "TINA"))
		{
			//��ư
			_button->buttonSet("��ư����", buttonX, buttonY + (i * 65), "TINA", 20, 1);

			//�÷��̾� ��ư �̹���
			_mTina.img = IMAGEMANAGER->findImage("miniTINA");
			_mTina.x = buttonX + 15;
			_mTina.y = buttonY + (i * 65) + 17;
			_mTina.ani = new animation;
			int arrAniPlayerImg[] = { 0, 1 };
			KEYANIMANAGER->addArrayFrameAnimation("�÷��̾��", "miniTINA", arrAniPlayerImg, 2, 1, true);
			_mTina.ani = KEYANIMANAGER->findAnimation("�÷��̾��");
			_mTina.aniStart = false;
		}
		else if (!strcmp(INIDATA->loadDataString(fileName, playerNum, "name"), "CELES"))
		{
			//��ư
			_button->buttonSet("��ư����", buttonX, buttonY + (i * 65), "CELES", 20, 1);

			//�÷��̾� ��ư �̹���
			_mLocke.img = IMAGEMANAGER->findImage("miniCELES");
			_mLocke.x = buttonX + 15;
			_mLocke.y = buttonY + (i * 65) + 17;
			_mLocke.ani = new animation;
			int arrAniPlayerImg[] = { 0, 1 };
			KEYANIMANAGER->addArrayFrameAnimation("�÷��̾��", "miniCELES", arrAniPlayerImg, 2, 1, true);
			_mLocke.ani = KEYANIMANAGER->findAnimation("�÷��̾��");
			_mLocke.aniStart = false;
		}
		else if (!strcmp(INIDATA->loadDataString(fileName, playerNum, "name"), "LOCKE"))
		{
			//��ư
			_button->buttonSet("��ư����", buttonX, buttonY + (i * 65), "LOCKE", 20, 1);

			//�÷��̾� ��ư �̹���
			_mCeles.img = IMAGEMANAGER->findImage("miniLOCKE");
			_mCeles.x = buttonX + 15;
			_mCeles.y = buttonY + (i * 65) + 17;
			_mCeles.ani = new animation;
			int arrAniPlayerImg[] = { 0, 1 };
			KEYANIMANAGER->addArrayFrameAnimation("�÷��̾��", "miniLOCKE", arrAniPlayerImg, 2, 1, true);
			_mCeles.ani = KEYANIMANAGER->findAnimation("�÷��̾��");
			_mCeles.aniStart = false;
		}
		else if (!strcmp(INIDATA->loadDataString(fileName, playerNum, "name"), "SHADOW"))
		{
			//��ư
			_button->buttonSet("��ư����", buttonX, buttonY + (i * 65), "SHADOW", 20, 1);

			//�÷��̾� ��ư �̹���
			_mShadow.img = IMAGEMANAGER->findImage("miniSHADOW");
			_mShadow.x = buttonX + 15;
			_mShadow.y = buttonY + (i * 65) +17;
			_mShadow.ani = new animation;
			int arrAniPlayerImg[] = { 0, 1 };
			KEYANIMANAGER->addArrayFrameAnimation("�÷��̾��", "miniSHADOW", arrAniPlayerImg, 2, 1, true);
			_mShadow.ani = KEYANIMANAGER->findAnimation("�÷��̾��");
			_mShadow.aniStart = false;
		}
	}

	//---------------------------------------------------------------- ������


	//_iM->saveInventory("skgFile");
	//_iM->loadInventory("skgFile");
	itemButtonSet(_iM->getItemInventorySize());



	//--------------------------------------- ��ư ---------------------------------------
	_itemButtonOn = false;  //�����۹�ư Ȱ��ȭ ����
	_charButtonOn = false;  //ĳ���͹�ư Ȱ��ȭ ����




	return S_OK;
}

void itemMenu::release()
{

}

void itemMenu::update()
{
	//Ŀ��
	_cursorI->update();
	//��ư
	_button->update();


	//Ŀ�� ��Ʈ��X: �޴���ư
	if (!_itemButtonOn)
	{
		_cursorI->keyControlX(210, _cursorXNum);

		buttonOnActive();
	}
	else
	{
		if (!_charButtonOn)
		{
			_cursorI->keyControlXY(250, 65, 3, 5);

			//����
			buttonOnActiveItem();
		}
		else
		{
			_cursorI->keyControlY(65, 4);

			buttonOnActiveCharacter();
		}
		
	}



	//�ɼ� �޴�����
	if (KEYMANAGER->isOnceKeyDown(VK_BACK))
	{
		_button->buttonRemove();
		delete _button;
		SCENEMANAGER->changeScene("�ɼ�");
	}
}

void itemMenu::render()
{
	_bgImage->render(getMemDC());

	//--------------------------------- ��ư ---------------------------------
	//��ư
	_button->render();             
	//�÷��̾� ��ư �̹���
	_mTina.img->aniRender(getMemDC(), _mTina.x, _mTina.y, _mTina.ani);
	_mLocke.img->aniRender(getMemDC(), _mLocke.x, _mLocke.y, _mLocke.ani);
	_mCeles.img->aniRender(getMemDC(), _mCeles.x, _mCeles.y, _mCeles.ani);
	_mShadow.img->aniRender(getMemDC(), _mShadow.x, _mShadow.y, _mShadow.ani);
	//--------------------------------- ��ư ---------------------------------

	itemDescriptionRender(_cursorI->getCursorPos());      //������ ����

	_cursorI->render();

}


//��ư ���ϸ��̼� ����
void itemMenu::buttonOnActive()
{
	//��ư ���ϸ��̼� Ȱ��ȭ
	_button->setVButtonAniStart(_cursorI->getCursorXNum(), true);
	for (int i = 0; i < _cursorXNum; ++i)
	{
		if (i == _cursorI->getCursorXNum()) continue;
		_button->setVButtonAniStart(i, false);
	}


	//��� �޴���ư ���ý�
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		_cursorI->init(CURSOR_RIGHT, 50 , 160);
		_itemButtonOn = true;
	}

}

void itemMenu::buttonOnActiveItem()
{
	//��ư ���ϸ��̼� Ȱ��ȭ
	_button->setVButtonAniStart(_cursorI->getCursorPos() + 7, true);
	for (int i = 7; i < _button->getButtonNum(); ++i)
	{
		if (i == _cursorI->getCursorPos() + 7) continue;
		_button->setVButtonAniStart(i, false);
	}


	//������ ��ư ���ý�
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		_cursorI->init(CURSOR_RIGHT, 950, 120);
		_charButtonOn = true;
	}


	//������
	if (KEYMANAGER->isOnceKeyDown(VK_BACK))
	{
		_cursorI->init(CURSOR_RIGHT, 150 - 50, 10 + 20);
		_itemButtonOn = false;
	}
}

void itemMenu::buttonOnActiveCharacter()
{
	//��ư ���ϸ��̼� Ȱ��ȭ
	_button->setVButtonAniStart(_cursorI->getCursorYNum() + 3, true);
	for (int i = 3; i < 7; ++i)
	{
		if (i == _cursorI->getCursorYNum() + 3) continue;
		_button->setVButtonAniStart(i, false);
	}

	//������ ��ư ���ý�
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
	

	}

	//ĳ���� ����
	switch (_cursorI->getCursorPos())
	{
		case 0:

		break;
		case 1:

		break;
		case 2:

		break;
		case 3:

		break;
		case 4:

		break;
	}

	//������
	if (KEYMANAGER->isOnceKeyDown(VK_BACK))
	{
		_cursorI->init(CURSOR_RIGHT, 50, 160);
		_charButtonOn = false;
	}
}

//������ ��ư ����
void itemMenu::itemButtonSet(int buttonNum)
{
	//����ó��: �������� ������...
	if (buttonNum <= 0) return;

	int buttonX = 100;
	int buttonY = 150;



	//��ư
	for (int i = 0; i < buttonNum; ++i)
	{
		int intervalX = 250;
		int intervalY = 70;

		switch (i)
		{
			case 0: case 1: case 2:
				//������ ��ư & �̸�
				_button->buttonSet("��ư��������", buttonX + (i * intervalX),
					buttonY, _iM->getVItem()[itemGetNum(_iM->getItemVNum(i))]->getItemName(), 20, 2, true, _iM->getItemCount(i));
			break;
			case 3: case 4: case 5:
				_button->buttonSet("��ư��������", buttonX + ((i - 3) * intervalX),
					buttonY + (1 * intervalY), _iM->getVItem()[itemGetNum(_iM->getItemVNum(i))]->getItemName(), 20, 2, true, _iM->getItemCount(i));
			break;
			case 6: case 7: case 8:
				_button->buttonSet("��ư��������", buttonX + ((i - 6) * intervalX),
					buttonY + (2 * intervalY), _iM->getVItem()[itemGetNum(_iM->getItemVNum(i))]->getItemName(), 20, 2, true, _iM->getItemCount(_iM->getVItem()[i]->getItemNumber()));
			break;
			case 9: case 10: case 11:
				_button->buttonSet("��ư��������", buttonX + ((i - 9) * intervalX),
					buttonY + (3 * intervalY), _iM->getVItem()[itemGetNum(_iM->getItemVNum(i))]->getItemName(), 20, 2, true, _iM->getItemCount(_iM->getVItem()[i]->getItemNumber()));
			break;
			case 12: case 13: case 14:
				_button->buttonSet("��ư��������", buttonX + ((i - 12) * intervalX),
					buttonY + (4 * intervalY), _iM->getVItem()[itemGetNum(_iM->getItemVNum(i))]->getItemName(), 20, 2, true, _iM->getItemCount(_iM->getVItem()[i]->getItemNumber()));
			break;
			case 15: case 16: case 17:
				_button->buttonSet("��ư��������", buttonX + ((i - 15) * intervalX),
					buttonY + (5 * intervalY), _iM->getVItem()[itemGetNum(_iM->getItemVNum(i))]->getItemName(), 20, 2, true, _iM->getItemCount(_iM->getVItem()[i]->getItemNumber()));
			break;
		}
	}

}


void itemMenu::itemDescriptionRender(int itemNum)
{
	textPrint(getMemDC(), _iM->getVItem()[itemGetNum(_iM->getItemVNum(itemNum))]->getItemDescription(), 50, 520, 20, 20, "HY�߰��", COLOR_BLUE, false);
}