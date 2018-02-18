#include "stdafx.h"
#include "abilitiesMenu.h"


abilitiesMenu::abilitiesMenu()
{
}


abilitiesMenu::~abilitiesMenu()
{
}



HRESULT abilitiesMenu::init()
{
	//��׶��� �̹���
	_bgImage = IMAGEMANAGER->findImage("�ɷ¸޴�");

	//������ ���̺� ���� �������� 
	int saveFileNum = INIDATA->loadDataInterger("gameData", "gameData", "fileNum");
	fileLoad(saveFileNum);
	int playerNum = INIDATA->loadDataBodyNum(saveFileNum);

	//��ư
	int buttonX, buttonY;
	buttonX = 1000;
	buttonY = 100;
	_button = new fButton;
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
			_button->buttonSet("��ư����", buttonX, buttonY + (i * 65), "TINA", 30);
		else if (!strcmp(INIDATA->loadDataString(fileName, playerNum, "name"), "CELES"))
			_button->buttonSet("��ư����", buttonX, buttonY + (i * 65), "CELES", 30);
		else if (!strcmp(INIDATA->loadDataString(fileName, playerNum, "name"), "LOCK"))
			_button->buttonSet("��ư����", buttonX, buttonY + (i * 65), "LOCK", 30);
		else if (!strcmp(INIDATA->loadDataString(fileName, playerNum, "name"), "SHADOW"))
			_button->buttonSet("��ư����", buttonX, buttonY + (i * 65), "SHADOW", 30);
	}



	//Ŀ��
	_cursorYNum = playerNum;
	cursorInit(CUSOR_RIGHT, buttonX - 50, buttonY + 20);





	return S_OK;
}

void abilitiesMenu::release()
{

}

void abilitiesMenu::update()
{
	//Ŀ��
	cursorUpdate();
	cursorKeyControlY(65, _cursorYNum);

	//��ư
	_button->update();






	//�ɼ� �޴�����
	if (KEYMANAGER->isOnceKeyDown(VK_BACK))
	{
		//��ư ���Ϳ��� ����
		_button->buttonRemove();
		delete _button;
		SCENEMANAGER->changeScene("�ɼ�");
	}
}

void abilitiesMenu::render()
{
	_bgImage->render(getMemDC());  //��׶��� �̹���
	cursorRender();                //Ŀ��
	_button->render();             //��ư

	playerSlotRender();            //���� ������
	gameDataRender(false);		   //���� ������(�÷������/�÷��̽ð�/��)
}


