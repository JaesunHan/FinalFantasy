#include "stdafx.h"
#include "characterAbility.h"


characterAbility::characterAbility()
{
}


characterAbility::~characterAbility()
{
}


HRESULT characterAbility::init()
{
	//��׶��� �̹���
	_bgImage = IMAGEMANAGER->findImage("ĳ���ʹɷ¸޴�");

	//������ ���̺� ���� �������� 
	int saveFileNum = INIDATA->loadDataInterger("gameData", "gameData", "fileNum");
	int selectPlayerNum = INIDATA->loadDataInterger("gameData", "inventory", "selectChar");
	fileLoad(saveFileNum, selectPlayerNum);

	//��ư
	int buttonX, buttonY;
	buttonX = 100;
	buttonY = 25;
	_button = new fButton;
	for (int i = 0; i < 3; ++i)
	{
		if (i == 0) _button->buttonSet("��������", buttonX + (i * 150), buttonY);
		if (i == 1) _button->buttonSet("�����ܸ���", buttonX + (i * 150), buttonY);
		if (i == 2) _button->buttonSet("�����ܷ���", buttonX + (i * 150), buttonY);
	}


	//Ŀ��
	cursorInit(CUSOR_RIGHT, buttonX - 50, buttonY + 10);



	return S_OK;
}

void characterAbility::release()
{

}

void characterAbility::update()	
{
	//Ŀ��
	cursorUpdate();

	//Ŀ�� ��Ʈ��X  
	cursorKeyControlX(150, 3);



	//�ɼ� �޴�����
	if (KEYMANAGER->isOnceKeyDown(VK_BACK))
	{
		//��ư ���Ϳ��� ����
		_button->buttonRemove();
		delete _button;
		SCENEMANAGER->changeScene("�ɷ�ġ");
	}
}

void characterAbility::render()	
{
	_bgImage->render(getMemDC());  //��׶��� �̹���
	cursorRender();                //Ŀ��
	_button->render();             //��ư

	playerSlotRender();            //���� ������
}
