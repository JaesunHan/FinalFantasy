#include "stdafx.h"
#include "optionMenu.h"


optionMenu::optionMenu()
{
}


optionMenu::~optionMenu()
{
}


HRESULT optionMenu::init()
{
	_bgImage = IMAGEMANAGER->findImage("�ɼǸ޴�");
	cursorInit(CUSOR_RIGHT, 950, 60);

	_button = new fButton;

	_button->buttonSet("��ư��Ÿ��", 1000, 50, "Items", 30);
	_button->buttonSet("��ư��Ÿ��", 1000, 100, "Abilities", 30);
	_button->buttonSet("��ư��Ÿ��", 1000, 150, "Equips", 30);
	_button->buttonSet("��ư��Ÿ��", 1000, 200, "Status", 30);
	_button->buttonSet("��ư��Ÿ��", 1000, 250, "Save", 30);
	_button->buttonSet("��ư��Ÿ��", 1000, 300, "Config", 30);


	return S_OK;
}

void optionMenu::release()
{

}

void optionMenu::update() 
{
	cursorUpdate();
	_button->update();

	cursorKeyControl(50, 6);

	//����
	switch (_cursor.currentNum)
	{
		case 0:
			//��ư ���ϸ��̼� Ȱ��ȭ
			_button->setVButtonAniStart(_cursor.currentNum, true);
			for (int i = 0; i < 6; ++i)
			{
				if (i == _cursor.currentNum) continue;
				_button->setVButtonAniStart(i, false);
			}

			if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
			{
				_button->buttonRemove();
				delete _button;
				SCENEMANAGER->changeScene("������");
			}
		break;
		case 1:
			//��ư ���ϸ��̼� Ȱ��ȭ
			_button->setVButtonAniStart(_cursor.currentNum, true);
			for (int i = 0; i < 6; ++i)
			{
				if (i == _cursor.currentNum) continue;
				_button->setVButtonAniStart(i, false);
			}

			if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
			{
				_button->buttonRemove();
				delete _button;
				SCENEMANAGER->changeScene("�ɷ�ġ");
			}
		break;
		case 2:
			//��ư ���ϸ��̼� Ȱ��ȭ
			_button->setVButtonAniStart(_cursor.currentNum, true);
			for (int i = 0; i < 6; ++i)
			{
				if (i == _cursor.currentNum) continue;
				_button->setVButtonAniStart(i, false);
			}

			if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
			{
				_button->buttonRemove();
				delete _button;
				SCENEMANAGER->changeScene("���");
			}
		break;
		case 3:
			//��ư ���ϸ��̼� Ȱ��ȭ
			_button->setVButtonAniStart(_cursor.currentNum, true);
			for (int i = 0; i < 6; ++i)
			{
				if (i == _cursor.currentNum) continue;
				_button->setVButtonAniStart(i, false);
			}

			if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
			{
				_button->buttonRemove();
				delete _button;
				SCENEMANAGER->changeScene("����");
			}
		break;
		case 4:
			//��ư ���ϸ��̼� Ȱ��ȭ
			_button->setVButtonAniStart(_cursor.currentNum, true);
			for (int i = 0; i < 6; ++i)
			{
				if (i == _cursor.currentNum) continue;
				_button->setVButtonAniStart(i, false);
			}

			if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
			{
				_button->buttonRemove();
				delete _button;
				SCENEMANAGER->changeScene("���̺�ε�");
			}
		break;
		case 5:
			//��ư ���ϸ��̼� Ȱ��ȭ
			_button->setVButtonAniStart(_cursor.currentNum, true);
			for (int i = 0; i < 6; ++i)
			{
				if (i == _cursor.currentNum) continue;
				_button->setVButtonAniStart(i, false);
			}

			if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
			{
				_button->buttonRemove();
				delete _button;
				SCENEMANAGER->changeScene("����");
			}
		break;
	}

	//�ɼ� �޴�����
	if (KEYMANAGER->isOnceKeyDown(VK_BACK))
	{
		_button->buttonRemove();
		delete _button;
		SCENEMANAGER->changeScene("����ʾ�", false);
	}
}

void optionMenu::render()
{
	_bgImage->render(getMemDC());
	cursorRender();
	_button->render();
}
