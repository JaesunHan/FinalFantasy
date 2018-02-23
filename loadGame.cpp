#include "stdafx.h"
#include "loadGame.h"
#include "itemManager.h"
#include "worldMapScene.h"


loadGame::loadGame()
{
}


loadGame::~loadGame()
{
}


HRESULT loadGame::init()
{
	_bgImage = IMAGEMANAGER->findImage("�ε�޴�");
	cursorInit(CUSOR_RIGHT, 50, 38);

	_cursorXNum = 4;
	_cursorYNum = 2;

	_button = new fButton;
	_button->buttonSet("��ư����", 65, 25,  "FILE 1", 30);
	_button->buttonSet("��ư����", 255, 25, "FILE 2", 30);
	_button->buttonSet("��ư����", 445, 25, "FILE 3", 30);
	_button->buttonSet("��ư����", 635, 25, "FILE 4", 30);
	_button->buttonSet("��ư����", 1000, 187);
	_button->buttonSet("��ư��", 1000, 238);

	for(int i = 0; i < 4; ++i) 	_fileLoadOk[i] = false;
	_selectFileCount = 2;

	_saveFileSelect = false;



	return S_OK;
}

void loadGame::release()
{

}

void loadGame::update()
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
					//���ӵ�����: �����ͺ��̽��� ����
					saveIniGameData(0);                

					//���̺����� ���
					fileLoad(0);
					_selectFileCount--;

					//���̺������� ������...
					if (!_fileLoadOk[0])
					{
						_selectFileCount = 2;
						_saveFileSelect = false;
						playerSlotRemove();
					}
					else
					{
						if (_selectFileCount <= 0)
						{
							_saveFileSelect = true;
							_cursor.cursorReset = false;
							_selectFileCount = 2;
						}
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
					//���ӵ�����: �����ͺ��̽��� ����
					saveIniGameData(1);

					//���̺����� ���
					fileLoad(1);
					_selectFileCount--;

					//���̺������� ������...
					if (!_fileLoadOk[1])
					{
						_selectFileCount = 2;
						_saveFileSelect = false;
						playerSlotRemove();
					}
					else
					{
						if (_selectFileCount <= 0)
						{
							_saveFileSelect = true;
							_cursor.cursorReset = false;
							_selectFileCount = 2;
						}
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
					//���ӵ�����: �����ͺ��̽��� ����
					saveIniGameData(2);

					//���̺����� ���
					fileLoad(2);
					_selectFileCount--;

					//���̺������� ������...
					if (!_fileLoadOk[2])
					{
						_selectFileCount = 2;
						_saveFileSelect = false;
						playerSlotRemove();
					}
					else
					{
						if (_selectFileCount <= 0)
						{
							_saveFileSelect = true;
							_cursor.cursorReset = false;
							_selectFileCount = 2;
						}
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
					//���ӵ�����: �����ͺ��̽��� ����
					saveIniGameData(3);

					//���̺����� ���
					fileLoad(3);
					_selectFileCount--;

					//���̺������� ������...
					if (!_fileLoadOk[3])
					{
						_selectFileCount = 2;
						_saveFileSelect = false;
						playerSlotRemove();
					}
					else
					{
						if (_selectFileCount <= 0)
						{
							_saveFileSelect = true;
							_cursor.cursorReset = false;
							_selectFileCount = 2;
						}
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
					_button->buttonRemove();
					delete _button;

					_saveFileSelect = false;

					//�÷��̾� ���̺����� �ε带 ���� ��ȣ�� 
					INIDATA->addData("gameData", "gameStart", "1");
					INIDATA->iniSave("gameData");

					//�������Ͽ� �ε�� ���� ����
					fileCopyTmpFile(_cursor.currentXNum);

					SCENEMANAGER->changeScene("����ʾ�");
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
		SCENEMANAGER->changeScene("Ÿ��Ʋ", false);
	}
}

void loadGame::render()
{
	_bgImage->render(getMemDC());
	_button->render();
	cursorRender();

	playerSlotRender();
	gameDataRender(false);  //���� ������(�÷������/�÷��̽ð�/��)
}


