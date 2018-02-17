#include "stdafx.h"
#include "newGame.h"


newGame::newGame()
{
}


newGame::~newGame()
{
}


HRESULT newGame::init()
{
	_bgImage = IMAGEMANAGER->findImage("�����Ӹ޴�");
	cursorInit(CUSOR_RIGHT, 950, 190);

	_button = new fButton;
	_button->buttonSet("��ư����", 1000, 187);
	_button->buttonSet("��ư��", 1000, 238);

	_saveFileNum = SAVEFILENUM;  //���̺����� ����

	fileLoad(0);


	return S_OK;
}

void newGame::release()
{

}

void newGame::update()
{
	cursorUpdate();
	_button->update();

	cursorKeyControlY(51, 2);

	//����
	switch (_cursor.currentYNum)
	{
	case 0:
		//��ư ���ϸ��̼� Ȱ��ȭ
		_button->setVButtonAniStart(0, true);
		_button->setVButtonAniStart(1, false);

		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{

			//���̺������� ���ٸ� saveFile0.ini && ������ �ִٸ� saveFile1 ~ 3.ini ������ ���� 
			for (int i = SAVEFILENUM; i >= 0; --i)
			{
				char numTemp[12];
				sprintf(numTemp, "saveFile%d", i);
				_saveFileNum = INIDATA->loadDataInterger(numTemp, "fileInfo", "num");

				if (_saveFileNum != -1)
				{
					_saveFileNum = _saveFileNum + 1;
					break;
				}
				else
				{
					_saveFileNum = 0;
				}
			}

			//�������� ����
			char saveFileNum[4];
			sprintf(saveFileNum, "%d", _saveFileNum);
			INIDATA->addData("fileInfo", "num", saveFileNum);
			INIDATA->addData("player0", "name", "TINA");
			INIDATA->addData("player0", "job", "Magician");
			INIDATA->addData("player0", "level", "3");
			INIDATA->addData("player0", "hp", "63");
			INIDATA->addData("player0", "maxHp", "63");
			INIDATA->addData("player0", "mp", "27");
			INIDATA->addData("player0", "maxMp", "27");

			char saveFileName[16];
			sprintf(saveFileName, "saveFile%d", _saveFileNum);
			INIDATA->iniSave(saveFileName);

			//��ư���� 
			_button->buttonRemove();
			delete _button;
			//���̵�
			SCENEMANAGER->changeScene("����ʾ�");
		}
		break;
	case 1:
		//��ư ���ϸ��̼� Ȱ��ȭ
		_button->setVButtonAniStart(1, true);
		_button->setVButtonAniStart(0, false);

		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{
			//��ư���� 
			_button->buttonRemove();
			delete _button;
			//���̵�
			SCENEMANAGER->changeScene("Ÿ��Ʋ");
		}
		break;
	}
}

void newGame::render()
{
	_bgImage->render(getMemDC());
	_button->render();
	cursorRender();

	if (_fileLoadOk[0]) playerSlotRender();
}


