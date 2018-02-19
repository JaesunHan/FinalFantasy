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



	return S_OK;
}

void characterAbility::release()
{

}

void characterAbility::update()	
{




	//�ɼ� �޴�����
	if (KEYMANAGER->isOnceKeyDown(VK_BACK))
	{
		//��ư ���Ϳ��� ����
		//_button->buttonRemove();
		//delete _button;
		SCENEMANAGER->changeScene("�ɷ�ġ");
	}
}

void characterAbility::render()	
{
	_bgImage->render(getMemDC());  //��׶��� �̹���

	playerSlotRender();            //���� ������
}
