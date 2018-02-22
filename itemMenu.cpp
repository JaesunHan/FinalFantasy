#include "stdafx.h"
#include "itemMenu.h"


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
	_cursorXNum = 3;
	cursorInit(CUSOR_RIGHT, buttonX - 50, buttonY + 20);
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

	//----------------------------------------------------------------- ������
	itemButtonSet(0);



	//--------------------------------------- ��ư ---------------------------------------




	return S_OK;
}

void itemMenu::release()
{

}

void itemMenu::update()
{
	//Ŀ��
	cursorUpdate();

	//Ŀ�� ��Ʈ��X  
	cursorKeyControlX(210, _cursorXNum);

	//��ư
	_button->update();

	//����
	switch (_cursor.currentXNum)
	{
		case 0:
			buttonOnActive();
		break;
		case 1:
			buttonOnActive();
		break;
		case 2:
			buttonOnActive();
		break;
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

	cursorRender();                //Ŀ��
}


//��ư ���ϸ��̼� ����
void itemMenu::buttonOnActive()
{
	//��ư ���ϸ��̼� Ȱ��ȭ
	_button->setVButtonAniStart(_cursor.currentXNum, true);
	for (int i = 0; i < _cursorXNum; ++i)
	{
		if (i == _cursor.currentXNum) continue;
		_button->setVButtonAniStart(i, false);
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{

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
				_button->buttonSet("��ư��������", buttonX + (i * intervalX),
					buttonY, "Positon", 30, 1);
			break;
			case 3: case 4: case 5:
				_button->buttonSet("��ư��������", buttonX + ((i - 3) * intervalX),
					buttonY + (1 * intervalY), "Positon", 30, 1);
			break;
			case 6: case 7: case 8:
				_button->buttonSet("��ư��������", buttonX + ((i - 6) * intervalX),
					buttonY + (2 * intervalY), "Positon", 30, 1);
			break;
			case 9: case 10: case 11:
				_button->buttonSet("��ư��������", buttonX + ((i - 9) * intervalX),
					buttonY + (3 * intervalY), "Positon", 30, 1);
			break;
			case 12: case 13: case 14:
				_button->buttonSet("��ư��������", buttonX + ((i - 12) * intervalX),
					buttonY + (4 * intervalY), "Positon", 30, 1);
			break;
			case 15: case 16: case 17:
				_button->buttonSet("��ư��������", buttonX + ((i - 15) * intervalX),
					buttonY + (5 * intervalY), "Positon", 30, 1);
			break;
		}
	}



}