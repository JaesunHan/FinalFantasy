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
	buttonX = 150;
	buttonY = 10;
	_button = new fButton;
	for (int i = 0; i < 3; ++i)
	{
		if (i == 0) _button->buttonSet("��������", buttonX + (i * 210), buttonY);
		if (i == 1) _button->buttonSet("�����ܰ���", buttonX + (i * 210), buttonY);
		if (i == 2) _button->buttonSet("�����ܹ��", buttonX + (i * 210), buttonY);
	}


	//Ŀ��
	_cursorXNum = 3;
	cursorInit(CUSOR_RIGHT, buttonX - 50, buttonY + 20);



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
	cursorKeyControlX(210, _cursorXNum);

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
		//��ư ���Ϳ��� ����
		_button->buttonRemove();
		delete _button;
		SCENEMANAGER->changeScene("�ɷ�ġ");
	}
}

void characterAbility::render()	
{
	_bgImage->render(getMemDC());  //��׶��� �̹���
	_button->render();             //��ư
	cursorRender();                //Ŀ��

	playerSlotRender();            //���� ������
}

//��ư ���ϸ��̼� ����
void characterAbility::buttonOnActive()
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

//ĳ���ͺ� ��ų��ư ����
void characterAbility::skillButtonSet()
{

}