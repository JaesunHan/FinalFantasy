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
	//==============�������� ������ Ÿ���� �Դ´�!============
	_gameEndTime = TIMEMANAGER->getWorldTime();
	_gameTotalTime = _gameEndTime - _gameStartTime;
	//==============�������� ������ Ÿ���� �Դ´�!============

	//��׶��� �̹���
	_bgImage = IMAGEMANAGER->findImage("�ɼǸ޴�");

	//Ŀ��
	_cursorXNum = 2;
	_cursorYNum = 6;
	cursorInit(CUSOR_RIGHT, 950, 60);
	_cursorReset = false;

	//���� �߰�
	menu::init();

	//tmp ���� �������� (skgFile)
	fileLoad(0, -1, true);

	//��ư
	_button = new fButton;
	_button->buttonSet("��ư��Ÿ��", 1000, 50, "Items", 30);
	_button->buttonSet("��ư��Ÿ��", 1000, 100, "Abilities", 30);
	_button->buttonSet("��ư��Ÿ��", 1000, 150, "Equips", 30);
	_button->buttonSet("��ư��Ÿ��", 1000, 200, "Status", 30);
	_button->buttonSet("��ư��Ÿ��", 1000, 250, "Save", 30);
	_button->buttonSet("��ư��Ÿ��", 1000, 300, "Config", 30);


	//���Ժ���
	_changeSlotNum	 = -1;
	_previousSlotNum = -1;
	_slotSelectCount = 2;
	_isSlotReload = false;


	return S_OK;
}

void optionMenu::release()
{

}

void optionMenu::update() 
{
	//Ÿ�̸� 
	_gameTotalTime += TIMEMANAGER->getElapsedTime();

	cursorUpdate();
	_button->update();

	//Ŀ�� ��Ʈ��X  
	cursorKeyControlX(920, _cursorXNum, true);

	if (_cursor.currentXNum == 0)
	{
		if (!_cursorReset)
		{
			//���� ���ϸ��̼� ����
			for (int i = 0; i < 4; ++i)
			{
				playerSlotAniStart(i, false);
				playerSlotUpdate();
			}

			cursorResetXY(950, 60);
			_cursor.currentYNum = 0;
			_cursorReset = true;
		}

		cursorKeyControlY(50, _cursorYNum);

		//����
		switch (_cursor.currentYNum)
		{
		case 0:
			//��ư ���ϸ��̼� Ȱ��ȭ
			_button->setVButtonAniStart(_cursor.currentYNum, true);
			for (int i = 0; i < _cursorYNum; ++i)
			{
				if (i == _cursor.currentYNum) continue;
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
			_button->setVButtonAniStart(_cursor.currentYNum, true);
			for (int i = 0; i < _cursorYNum; ++i)
			{
				if (i == _cursor.currentYNum) continue;
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
			_button->setVButtonAniStart(_cursor.currentYNum, true);
			for (int i = 0; i < _cursorYNum; ++i)
			{
				if (i == _cursor.currentYNum) continue;
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
			_button->setVButtonAniStart(_cursor.currentYNum, true);
			for (int i = 0; i < _cursorYNum; ++i)
			{
				if (i == _cursor.currentYNum) continue;
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
			_button->setVButtonAniStart(_cursor.currentYNum, true);
			for (int i = 0; i < _cursorYNum; ++i)
			{
				if (i == _cursor.currentYNum) continue;
				_button->setVButtonAniStart(i, false);
			}

			//if (_isSavePoint)
			{
				if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
				{
					_button->buttonRemove();
					delete _button;
					SCENEMANAGER->changeScene("���̺�ε�");
				}
			}
			break;
		case 5:
			//��ư ���ϸ��̼� Ȱ��ȭ
			_button->setVButtonAniStart(_cursor.currentYNum, true);
			for (int i = 0; i < _cursorYNum; ++i)
			{
				if (i == _cursor.currentYNum) continue;
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

		//�ɼǸ޴� ������
		if (KEYMANAGER->isOnceKeyDown(VK_BACK))
		{
			_button->buttonRemove();
			delete _button;
			SCENEMANAGER->changeScene(_currentSceneName, false);
		}
	}
	else
	{
		if (_cursorReset)
		{
			//��ư ���ϸ��̼� ����
			for (int i = 0; i < _cursorYNum; ++i)
			{
				_button->setVButtonAniStart(i, false);
			}

			cursorResetXY(30, 150);
			_cursor.currentYNum = 0;
			_cursorReset = false;
		}

		cursorKeyControlY(137, 4);
		playerSlotUpdate();

		//����
		switch (_cursor.currentYNum)
		{
			case 0:
				//��ư ���ϸ��̼� Ȱ��ȭ
				slotAniOn();
				
				//���� ����
				slotChangeKey();
			break;
			case 1:
				//��ư ���ϸ��̼� Ȱ��ȭ
				slotAniOn();

				//���Լ���
				slotChangeKey();
			break;
			case 2:
				//��ư ���ϸ��̼� Ȱ��ȭ
				slotAniOn();

				//���Լ���
				slotChangeKey();
			break;
			case 3:
				//��ư ���ϸ��̼� Ȱ��ȭ
				slotAniOn();

				//���Լ���
				slotChangeKey();
			break;
		}

		//�������� �ε�
		if (_isSlotReload)
		{
			playerSlotRemove();
			fileLoad(0, -1, true);
			_isSlotReload = false;
		}
	}


}

void optionMenu::render()
{
	_bgImage->render(getMemDC());
	_button->render();
	playerSlotRender();
	cursorRender();

	gameDataRender(false);  //���� ������(�÷������/�÷��̽ð�/��)
	gamePlayTime();			//���� �÷��� Ÿ��
}

void optionMenu::slotAniOn()
{
	if (_previousSlotNum != _cursor.currentYNum)
	{
		playerSlotAniStart(_cursor.currentYNum, true);

		for (int i = 0; i < 4; ++i)
		{
			if (i == _cursor.currentYNum) continue;
			playerSlotAniStart(i, false);
		}
	}
}

void optionMenu::slotChangeKey()
{
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		_slotSelectCount--;

		if (_slotSelectCount <= 0)
		{
			_changeSlotNum = _cursor.currentYNum;
			slotChange(_changeSlotNum, _previousSlotNum);

			//�ʱ�ȭ
			_slotSelectCount = 2;
			_isSlotReload = true;
			_previousSlotNum = -1;
			_changeSlotNum = -1;

		}
		else
		{
			slotSelect(_cursor.currentYNum);
			_previousSlotNum = slotSelect(_cursor.currentYNum);
		}
	}
}