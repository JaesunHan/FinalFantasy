#include "stdafx.h"
#include "equipMenu.h"


equipMenu::equipMenu()
{
}


equipMenu::~equipMenu()
{
}

HRESULT equipMenu::init()
{
	_bgImage = IMAGEMANAGER->findImage("�ε���Ӹ޴�");




	return S_OK;
}

void equipMenu::release()
{

}

void equipMenu::update()
{




	//�ɼ� �޴�����
	if (KEYMANAGER->isOnceKeyDown(VK_BACK))
	{
		//_button->buttonRemove();
		//delete _button;
		SCENEMANAGER->changeScene("�ɼ�");
	}
}

void equipMenu::render()
{
	_bgImage->render(getMemDC());
}
