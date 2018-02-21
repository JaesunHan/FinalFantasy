#include "stdafx.h"
#include "newGame.h"
#include "itemManager.h"


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

				//����ó��: ���̺������� 4���� ��� -> file0���� ����
				if (_saveFileNum >= 3)
				{
					_saveFileNum = 0;
					break;  
				}
				if (_saveFileNum != -1)  //���̺� �����Ͱ� ������
				{
					_saveFileNum = _saveFileNum + 1;
					break;
				}
				else  //���̺� �����Ͱ� ������ || ���̺� �����Ͱ� Full�̸�
				{
					_saveFileNum = 0;
				}
			}

			//================================== �������� ���� ================================== 
			saveIniPlayerData(_saveFileNum, 0, "TINA",   "Magician",         3, 63, 63, 27, 27, maxExpValue[2],
				maxExpValue[3], 31, 33, 28, 39, 12, 42, 33, 5, 7, 0, "0", "-1", "-2", "-3", true);
			saveIniPlayerData(_saveFileNum, 1, "LOCKE", "Treasure Hunter",   3, 71, 71, 18, 18, maxExpValue[2],
				maxExpValue[3], 37, 40, 31, 28, 14, 46, 23, 15, 2, 1, "0", "-1", "-2", "-3", true);
			saveIniPlayerData(_saveFileNum, 2, "CELES",  "Rune Knight",      3, 67, 67, 26, 26, maxExpValue[2],
				maxExpValue[3], 34, 34, 31, 36, 16, 44, 31, 7, 9, 2, "0", "-1", "-2", "-3", true);
			saveIniPlayerData(_saveFileNum, 3, "SHADOW", "Assassin",         3, 74, 74, 17, 17, maxExpValue[2],
				maxExpValue[3], 39, 38, 30, 33, 23, 47, 25, 28, 9, 3, "0", "-1", "-2", "-3", true);

			saveIniSlotGameData(_saveFileNum, "OVER WORLD",3000 , 0, true);			//���ӵ�����: ���̺����Ͽ� ����
			saveIniGameData(_saveFileNum, "OVER WORLD");							//���ӵ�����: �����ͺ��̽��� ����

			//������ ����
			itemSave(MENUITEM_ITEM, 1, 2, true, _saveFileNum);
			itemSave(MENUITEM_ITEM, 2, 2, true, _saveFileNum);
			itemSave(MENUITEM_ARMOR, 2, 2, true, _saveFileNum);
			itemSave(MENUITEM_WEAPON, 2, 2, true, _saveFileNum);
			//================================== �������� ���� ================================== 

			//��ư���� 
			_button->buttonRemove();
			delete _button;

			//�÷��̾� ���̺����� �ε带 ���� ��ȣ��
			INIDATA->addData("gameData", "gameStart", "1");
			INIDATA->iniSave("gameData");

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
}


