#include "stdafx.h"
#include "saveLoadMenu.h"
#include "itemManager.h"
#include "worldMapScene.h"


saveLoadMenu::saveLoadMenu()
{
}
saveLoadMenu::~saveLoadMenu()
{
}


HRESULT saveLoadMenu::init()
{
	_bgImage = IMAGEMANAGER->findImage("���̺�޴�");
	cursorInit(CUSOR_RIGHT, 50, 38);

	_cursorXNum = 4;
	_cursorYNum = 2;

	_button = new fButton;
	_button->buttonSet("��ư����", 65, 25, "FILE 1", 30);
	_button->buttonSet("��ư����", 255, 25, "FILE 2", 30);
	_button->buttonSet("��ư����", 445, 25, "FILE 3", 30);
	_button->buttonSet("��ư����", 635, 25, "FILE 4", 30);
	_button->buttonSet("��ư����", 1000, 187);
	_button->buttonSet("��ư��", 1000, 238);

	for (int i = 0; i < 4; ++i) _fileLoadOk[i] = false;
	_selectFileCount = 2;

	_saveFileSelect = false;
	_tmpLoasdSaveFileNum = 0;
	_resetCount = false;
	_resetCountSlotNum = -1;


	return S_OK;
}

void saveLoadMenu::release()
{

}

void saveLoadMenu::update()	
{
	cursorUpdate();
	_button->update();


	if (!_saveFileSelect)
	{
		//Ŀ����ġ ����
		if (!_cursor.cursorReset)
		{
			cursorResetXY(50, 38);
			_cursor.currentXNum = 0;
		}

		//Ŀ�� ��Ʈ��X  
		cursorKeyControlX(190, _cursorXNum);

		//����
		switch (_cursor.currentXNum)
		{
		case 0:
			//��ư ���ϸ��̼� Ȱ��ȭ
			_button->setVButtonAniStart(_cursor.currentXNum, true);
			for (int i = 0; i < _cursorXNum; ++i)
			{
				if (i == _cursor.currentXNum) continue;
				_button->setVButtonAniStart(i, false);
			}
			//���ù�ư���� �̵�
			if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
			{
				//����ī��Ʈ �ʱ�ȭ
				if (!_resetCount)
				{
					_selectFileCount = 2;
					_resetCount = true;
				}
				if (_resetCountSlotNum != _cursor.currentXNum)
				{
					_selectFileCount = 2;
					_resetCountSlotNum = _cursor.currentXNum;
				}

				//���ӵ�����: �����ͺ��̽��� ����
				saveIniGameData(0);

				//���̺����� ���
				_fileLoadOk[0] = true;
				fileLoad(0);
			
				_selectFileCount--;


				if (_selectFileCount <= 0)
				{
					_saveFileSelect = true;
					_cursor.cursorReset = false;
					_selectFileCount = 2;

					_tmpLoasdSaveFileNum = _cursor.currentXNum;
					_resetCount = false;
				}
			}
			break;
		case 1:
			//��ư ���ϸ��̼� Ȱ��ȭ
			_button->setVButtonAniStart(_cursor.currentXNum, true);
			for (int i = 0; i < _cursorXNum; ++i)
			{
				if (i == _cursor.currentXNum) continue;
				_button->setVButtonAniStart(i, false);
			}
			//���ù�ư���� �̵�
			if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
			{
				//����ī��Ʈ �ʱ�ȭ
				if (!_resetCount)
				{
					_selectFileCount = 2;
					_resetCount = true;
				}
				if (_resetCountSlotNum != _cursor.currentXNum)
				{
					_selectFileCount = 2;
					_resetCountSlotNum = _cursor.currentXNum;
				}

				//���ӵ�����: �����ͺ��̽��� ����
				saveIniGameData(1);

				//���̺����� ���
				_fileLoadOk[1] = true;
				fileLoad(1);
	
				_selectFileCount--;


				if (_selectFileCount <= 0)
				{
					_saveFileSelect = true;
					_cursor.cursorReset = false;
					_selectFileCount = 2;

					_tmpLoasdSaveFileNum = _cursor.currentXNum;
					_resetCount = false;
				}

			}
			break;
		case 2:
			//��ư ���ϸ��̼� Ȱ��ȭ
			_button->setVButtonAniStart(_cursor.currentXNum, true);
			for (int i = 0; i < _cursorXNum; ++i)
			{
				if (i == _cursor.currentXNum) continue;
				_button->setVButtonAniStart(i, false);
			}
			//���ù�ư���� �̵�
			if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
			{
				//����ī��Ʈ �ʱ�ȭ
				if (!_resetCount)
				{
					_selectFileCount = 2;
					_resetCount = true;
					_resetCountSlotNum = _cursor.currentXNum;
				}
				if (_resetCountSlotNum != _cursor.currentXNum)
				{
					_selectFileCount = 2;
				}

				//���ӵ�����: �����ͺ��̽��� ����
				saveIniGameData(2);

				//���̺����� ���
				_fileLoadOk[2] = true;
				fileLoad(2);
				_selectFileCount--;


				if (_selectFileCount <= 0)
				{
					_saveFileSelect = true;
					_cursor.cursorReset = false;
					_selectFileCount = 2;

					_tmpLoasdSaveFileNum = _cursor.currentXNum;
					_resetCount = false;
				}
			}
			break;
		case 3:
			//��ư ���ϸ��̼� Ȱ��ȭ
			_button->setVButtonAniStart(_cursor.currentXNum, true);
			for (int i = 0; i < _cursorXNum; ++i)
			{
				if (i == _cursor.currentXNum) continue;
				_button->setVButtonAniStart(i, false);
			}
			//���ù�ư���� �̵�
			if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
			{
				//����ī��Ʈ �ʱ�ȭ
				if (!_resetCount)
				{
					_selectFileCount = 2;
					_resetCount = true;
					_resetCountSlotNum = _cursor.currentXNum;
				}
				if (_resetCountSlotNum != _cursor.currentXNum)
				{
					_selectFileCount = 2;
				}

				//���ӵ�����: �����ͺ��̽��� ����
				saveIniGameData(3);

				//���̺����� ���
				_fileLoadOk[3] = true;
				fileLoad(3);
				_selectFileCount--;


				if (_selectFileCount <= 0)
				{
					_saveFileSelect = true;
					_cursor.cursorReset = false;
					_selectFileCount = 2;

					_tmpLoasdSaveFileNum = _cursor.currentXNum;
					_resetCount = false;
				}

			}
			break;
		}
	}
	else //YES&NO ��ư ����
	{
		//Ŀ����ġ ����
		if (!_cursor.cursorReset)
		{
			cursorResetXY(950, 190);
			_cursor.currentYNum = 0;
		}

		//Ŀ�� ��Ʈ��Y
		cursorKeyControlY(51, _cursorYNum);

		//����
		switch (_cursor.currentYNum)
		{
		case 0:
			//��ư ���ϸ��̼� Ȱ��ȭ
			_button->setVButtonAniStart(_cursor.currentYNum + _cursorXNum, true);
			for (int i = _cursorXNum; i < _cursorXNum + _cursorYNum; ++i)
			{
				if (i == _cursor.currentYNum + _cursorXNum) continue;
				_button->setVButtonAniStart(i, false);
			}

			if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
			{
				_saveFileSelect = false;

				//�÷��̽ð� ����
				char tmpTime[16];
				ZeroMemory(&tmpTime, sizeof(tmpTime));
				sprintf(tmpTime, "%f", _gameTotalTime);
				INIDATA->addData("gameData", "playTime", tmpTime);
				INIDATA->iniSave("skgFile");

				//tmpFile -> saveFile copy
				fileCopySaveFile(_cursor.currentXNum);


				_saveFileSelect = false;
				_cursor.cursorReset = false;
				_button->setVButtonAniStart(4, false);
				_button->setVButtonAniStart(5, false);	

				//�ɼ�â����...
				_button->buttonRemove();
				delete _button;
				playerSlotRemove();
				SCENEMANAGER->changeSceneType0("�ɼ�");
			}
			break;
		case 1:
			//��ư ���ϸ��̼� Ȱ��ȭ
			_button->setVButtonAniStart(_cursor.currentYNum + _cursorXNum, true);
			for (int i = _cursorXNum; i < _cursorXNum + _cursorYNum; ++i)
			{
				if (i == _cursor.currentYNum + _cursorXNum) continue;
				_button->setVButtonAniStart(i, false);
			}
			//���ϼ��� ��ư���� �̵�
			if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
			{
				_saveFileSelect = false;
				_cursor.cursorReset = false;
				_button->setVButtonAniStart(4, false);
				_button->setVButtonAniStart(5, false);
			}
			break;
		}
	}


	//�ɼǸ޴� ������
	if (KEYMANAGER->isOnceKeyDown(VK_BACK))
	{
		_button->buttonRemove();
		delete _button;
		playerSlotRemove();
		SCENEMANAGER->changeSceneType0("�ɼ�");
	}
}

void saveLoadMenu::render()
{
	_bgImage->render(getMemDC());
	_button->render();
	cursorRender();

	playerSlotRender();
	gameDataRender(false);  //���� ������(�÷������/�÷��̽ð�/��)
}


