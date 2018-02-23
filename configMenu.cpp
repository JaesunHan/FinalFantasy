#include "stdafx.h"
#include "configMenu.h"
//#include "playerManager.h"


configMenu::configMenu()
{
}


configMenu::~configMenu()
{
}

HRESULT configMenu::init()
{
	_bgImage = IMAGEMANAGER->findImage("���Ǳ׸޴�");

	
	

	//��� �������� ��ư�� �����ϱ�(BGM, EFFECT)
	for (int i = 0; i < MAXCONTROLBTN; ++i)
	{
		image* tmpBgmBtn = new image;
		image* tmpEftBtn = new image;
		char tmpStr1[128];
		wsprintf(tmpStr1, "���Ǳ�BGM��ư%d", i);
		char tmpStr2[128];
		wsprintf(tmpStr2, "���Ǳ�EFT��ư%d", i);
		//tmpBgmBtn = IMAGEMANAGER->findImage("���Ǳ׹�ư");
		//tmpEftBtn = IMAGEMANAGER->findImage("���Ǳ׹�ư");
		tmpBgmBtn = IMAGEMANAGER->addFrameImage(tmpStr1, ".//image//configMenu//configButton.bmp", 400, 65, 2, 1, true, RGB(255, 0, 255));
		tmpEftBtn = IMAGEMANAGER->addFrameImage(tmpStr2, ".//image//configMenu//configButton.bmp", 400, 65, 2, 1, true, RGB(255, 0, 255));

		_bgmCtrlBtn.push_back(tmpBgmBtn);
		_eftCtrlBtn.push_back(tmpEftBtn);
	}
	//���� �⺻ ��ġ �����ϱ�
	for (int i = 0; i < MAXCONTROLBTN; ++i)
	{
		if (i < 3)
		{
			_bgmCtrlBtn[i]->setX(230 * i  + _bgmCtrlBtn[i]->getFrameWidth());
			_eftCtrlBtn[i]->setX(230 * i  + _bgmCtrlBtn[i]->getFrameWidth());
			_bgmCtrlBtn[i]->setY(130  + _bgmCtrlBtn[i]->getFrameHeight());
			_eftCtrlBtn[i]->setY(330  + _eftCtrlBtn[i]->getFrameHeight());
		}
		else
		{
			_bgmCtrlBtn[i]->setX(230 * (i%3 + 1) + _bgmCtrlBtn[i]->getFrameWidth() -100);
			_eftCtrlBtn[i]->setX(230 * (i%3 + 1) + _bgmCtrlBtn[i]->getFrameWidth() -100);
			_bgmCtrlBtn[i]->setY(200  + _bgmCtrlBtn[i]->getFrameHeight());
			_eftCtrlBtn[i]->setY(400  + _eftCtrlBtn[i]->getFrameHeight());
		}
	}
	_rcW = 146, _rcH = 60;
	_rcCTRLNum[0] = RectMake(15, 198, _rcW, _rcH);
	_rcCTRLNum[1] = RectMake(15, 394, _rcW, _rcH);

	_cursorIdx = 0;
	_cursor = new cursor;
	_cursor->init(CURSOR_RIGHT, _rcCTRLNum[_cursorIdx].left + 10, _rcCTRLNum[_cursorIdx].top + (_rcCTRLNum[_cursorIdx].bottom - _rcCTRLNum[_cursorIdx].top) / 2-10);

	

	//������ ������!
	//for (int i = 0; i < 2; ++i)
	//{
	//	_rcCTRLNum[i] = RectMake(15, 130 * (i+1) + 80, _rcW, _rcH);
	//}
	//Tina* testTina = new Tina;
	//_pm->searchPlayerItem(12, 23, 28, 33, testTina);
	return S_OK;
}

void configMenu::release()
{

}

void configMenu::update()
{
	//�Ʒ� ���� ������ 
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		_cursorIdx++;
		//�ִ� �ε��� ������ ū ���� ���� �ִ� �ε��� ������ ����
		if (_cursorIdx >= MAXCURSORPOS)	_cursorIdx = MAXCURSORPOS - 1;
		_cursor->keyControlY()
	}
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		_cursorIdx--;
		//�ּ� �ε��� ������ ���� ���� ���� �ּ� �ε��� ������ ����
		if (_cursorIdx < 0)	_cursorIdx = 0;
	}



	//�ɼ� �޴�����
	if (KEYMANAGER->isOnceKeyDown(VK_BACK))
	{
		//_button->buttonRemove();
		//delete _button;
		SCENEMANAGER->changeScene("�ɼ�");
	}

	_cursor->update();


}

void configMenu::render()
{
	_bgImage->render(getMemDC());

	for (int i = 0; i < MAXCONTROLBTN; ++i)
	{
		_bgmCtrlBtn[i]->frameRender(getMemDC(), _bgmCtrlBtn[i]->getX(), _bgmCtrlBtn[i]->getY());
		_eftCtrlBtn[i]->frameRender(getMemDC(), _eftCtrlBtn[i]->getX(), _eftCtrlBtn[i]->getY());
	}

	if (KEYMANAGER->isStayKeyDown('G'))
	{
		for (int i = 0; i < 2; ++i)
		{
			Rectangle(getMemDC(), _rcCTRLNum[i].left, _rcCTRLNum[i].top, _rcCTRLNum[i].right, _rcCTRLNum[i].bottom);
		}
	}
	_cursor->render();
}

//�׽�Ʈ �غ� ���׵�\
1. ��ư10���� ����ε� ��ġ�� ��µǴ���\
2. Ŀ�� ��¿� ��Ʈ�� �����ġ üũ!