#include "stdafx.h"
#include "characterStatus.h"
#include "itemManager.h"


characterStatus::characterStatus()
{
}

characterStatus::~characterStatus()
{
}


HRESULT characterStatus::init()
{
	//��׶��� �̹���
	_bgImage = IMAGEMANAGER->findImage("ĳ���ʹɷ¸޴�");

	//������ ���̺� ���� �������� 
	int saveFileNum = INIDATA->loadDataInterger("gameData", "gameData", "fileNum");
	_selectPlayerNum = INIDATA->loadDataInterger("gameData", "inventory", "selectChar");
	fileLoad(saveFileNum, _selectPlayerNum, true);  //skgFile���� �ش� ĳ���� ���� ��������



	return S_OK;
}

void characterStatus::release()
{

}

void characterStatus::update() 
{




	//�ɼ� �޴�����
	if (KEYMANAGER->isOnceKeyDown(VK_BACK))
	{
		playerSlotRemove();
		playerStatusRemove();
		SCENEMANAGER->changeScene("����");
	}
}

void characterStatus::render() 
{
	_bgImage->render(getMemDC());			 //��׶��� �̹���

	playerSlotRender();						 //���� ������
	playerStatusRender(_selectPlayerNum);    //���� ������
}
