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
	fileLoad(INIDATA->loadDataInterger("gameData", "gameData", "fileNum"));

	//Ŀ��
	cursorInit(CUSOR_RIGHT, 950, 60);
	_cursorYNum = 6;


	return S_OK;
}

void abilitiesMenu::release()
{

}

void abilitiesMenu::update()
{

	//�ɼ� �޴�����
	if (KEYMANAGER->isOnceKeyDown(VK_BACK))
	{
		//_button->buttonRemove();
		//delete _button;
		SCENEMANAGER->changeScene("�ɼ�");
	}
}

void abilitiesMenu::render()
{
	_bgImage->render(getMemDC());  //��׶��� �̹���

	playerSlotRender();            //���� ������
	gameDataRender(false);		   //���� ������(�÷������/�÷��̽ð�/��)

}


