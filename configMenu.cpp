#include "stdafx.h"
#include "configMenu.h"


configMenu::configMenu()
{
}


configMenu::~configMenu()
{
}

HRESULT configMenu::init()
{
	_bgImage = IMAGEMANAGER->findImage("�ε���Ӹ޴�");





	return S_OK;
}

void configMenu::release()
{

}

void configMenu::update()
{




	//�ɼ� �޴�����
	if (KEYMANAGER->isOnceKeyDown(VK_BACK))
	{
		//_button->buttonRemove();
		//delete _button;
		SCENEMANAGER->changeScene("�ɼ�");
	}
}

void configMenu::render()
{
	_bgImage->render(getMemDC());
}
