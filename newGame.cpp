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


	//============================================================== ���̺� ���� �ε�
	int tmpSaveFileNum = 0;
	for (int i = 0; i < SAVEFILENUM; ++i)
	{
		char tmp[32];
		ZeroMemory(&tmp, sizeof(tmp));
		wsprintf(tmp, "saveFile%d", i);
		if (INIDATA->loadDataInterger(tmp, "fileInfo", "fileNum") != -1)
		{
			tmpSaveFileNum = i;
			break;
		}
	}
	
	switch (tmpSaveFileNum)  //������ �ִ� �ּ� ���̺� ���� �ε�
	{
		case 0:
			fileLoad(tmpSaveFileNum);
		break;
		case 1:
			fileLoad(tmpSaveFileNum);
		break;
		case 2:
			fileLoad(tmpSaveFileNum);
		break;
		case 3:
			fileLoad(tmpSaveFileNum);
		break;
	}
	//==============================================================


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
				_saveFileNum = INIDATA->loadDataInterger(numTemp, "fileInfo", "fileNum");

				if (_saveFileNum != -1)  //���̺� �����Ͱ� ������
				{
					_saveFileNum = _saveFileNum + 1;
					break;
				}
				else  //���̺� �����Ͱ� ������
				{
					_saveFileNum = 0;
				}
			}

			//================================== �������� ���� ================================== 
			saveIniPlayerData(_saveFileNum, 0, "TINA",   "Magician",        3, 63, 63, 27, 27);
			saveIniPlayerData(_saveFileNum, 1, "CELES",  "Rune Knight",     2, 56, 56, 21, 21);
			saveIniPlayerData(_saveFileNum, 2, "LOCK",   "Treasure Hunter", 2, 68, 68, 0, 0);
			saveIniPlayerData(_saveFileNum, 3, "SHADOW", "Assassin",        3, 72, 72, 0, 0);

			saveIniSlotGameData(_saveFileNum, "OVER WORLD",3000 , 0, 0);  //���ӵ�����: ���̺����Ͽ� ����
			saveIniGameData(_saveFileNum, "OVER WORLD");                  //���ӵ�����: �����ͺ��̽��� ����
			//================================== �������� ���� ================================== 

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

	if (_fileLoadOk[0]) playerSlotRender();  //�÷��̾� ����
	gameDataRender(true);  //���� ������(�÷������/�÷��̽ð�/��)

	textPrint(getMemDC(), SCENEMANAGER->getCurrentSceneName().c_str(), 100, 100);
}


