#include "stdafx.h"
#include "statusMenu.h"


statusMenu::statusMenu()
{
}


statusMenu::~statusMenu()
{
}

HRESULT statusMenu::init()
{
	_bgImage = IMAGEMANAGER->findImage("�ε���Ӹ޴�");




	return S_OK;
}

void statusMenu::release()
{

}

void statusMenu::update()
{




	//�ɼ� �޴�����
	if (KEYMANAGER->isOnceKeyDown(VK_BACK))
	{
		//_button->buttonRemove();
		//delete _button;
		SCENEMANAGER->changeScene("�ɼ�");
	}
}

void statusMenu::render()
{
	_bgImage->render(getMemDC());
}
