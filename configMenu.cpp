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
		tagConfigButton* tmpBgmBtn = new tagConfigButton;
		tagConfigButton* tmpEftBtn = new tagConfigButton;
		//image* tmpBgmBtn = new image;
		//image* tmpEftBtn = new image;
		char tmpStr1[128];
		wsprintf(tmpStr1, "���Ǳ�BGM��ư%d", i);
		char tmpStr2[128];
		wsprintf(tmpStr2, "���Ǳ�EFT��ư%d", i);
		//tmpBgmBtn = IMAGEMANAGER->findImage("���Ǳ׹�ư");
		//tmpEftBtn = IMAGEMANAGER->findImage("���Ǳ׹�ư");
		//��ư �̹��� ����
		tmpBgmBtn->btnImg = IMAGEMANAGER->addFrameImage(tmpStr1, ".//image//configMenu//configButton.bmp", 400, 65, 2, 1, true, RGB(255, 0, 255));
		tmpEftBtn->btnImg = IMAGEMANAGER->addFrameImage(tmpStr2, ".//image//configMenu//configButton.bmp", 400, 65, 2, 1, true, RGB(255, 0, 255));
		//��ư �̹��� ���� �ѷ��� �ؽ�Ʈ ����
		sprintf_s(tmpBgmBtn->btnTxt, sizeof(tmpBgmBtn->btnTxt), "%.2f", i*0.25);

		_bgmCtrlBtn.push_back(tmpBgmBtn);
		_eftCtrlBtn.push_back(tmpEftBtn);
	}
	//���� �⺻ ��ġ �����ϱ�
	for (int i = 0; i < MAXCONTROLBTN; ++i)
	{
		if (i < 3)
		{
			_bgmCtrlBtn[i]->btnImg->setX(230 * i  + _bgmCtrlBtn[i]->btnImg->getFrameWidth());
			_eftCtrlBtn[i]->btnImg->setX(230 * i  + _bgmCtrlBtn[i]->btnImg->getFrameWidth());
			_bgmCtrlBtn[i]->btnImg->setY(130  + _bgmCtrlBtn[i]->btnImg->getFrameHeight());
			_eftCtrlBtn[i]->btnImg->setY(330  + _eftCtrlBtn[i]->btnImg->getFrameHeight());
		}
		else
		{
			_bgmCtrlBtn[i]->btnImg->setX(230 * (i%3 + 1) + _bgmCtrlBtn[i]->btnImg->getFrameWidth() -100);
			_eftCtrlBtn[i]->btnImg->setX(230 * (i%3 + 1) + _bgmCtrlBtn[i]->btnImg->getFrameWidth() -100);
			_bgmCtrlBtn[i]->btnImg->setY(200  + _bgmCtrlBtn[i]->btnImg->getFrameHeight());
			_eftCtrlBtn[i]->btnImg->setY(400  + _eftCtrlBtn[i]->btnImg->getFrameHeight());
		}
	}
	_rcW = 146, _rcH = 60;
	_rcCTRLNum[0] = RectMake(15, 198, _rcW, _rcH);
	_rcCTRLNum[1] = RectMake(15, 394, _rcW, _rcH);

	_cursorIdx = 0;
	_cursor = new cursor;
	_cursor->init(CURSOR_RIGHT, _rcCTRLNum[_cursorIdx].left + 10, _rcCTRLNum[_cursorIdx].top + (_rcCTRLNum[_cursorIdx].bottom - _rcCTRLNum[_cursorIdx].top) / 2-10);

	//ó������ �ƹ��͵� ������ ���� �����̹Ƿ� ��� false �� �����Ѵ�.
	_isSelect[SELECT_BGM] = false;
	_isSelect[SELECT_EFFECT] = false;
	//�� ó������ BGM�� EFFEC �� �ִ� �ʿ� Ŀ���� ��µǾ�� �Ѵ�.
	_isSubject = true;

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
	if (_isSubject)	//Ŀ���� ������ subject �� �����Ѿ� �Ѵ�
	{
		_cursor->keyControlY(_rcCTRLNum[1].top - _rcCTRLNum[0].top, 2);
	}
	else			//Ŀ���� �������� title�� �����Ѿ� �Ѵ�(5 ���� �׸�)
	{
		//BGM ���ý� ��µǾ�� �ϴ� ��ġ
		if (_isSelect[SELECT_BGM])
		{
			//������ 3�� ��ư�� �ְ� �Ʒ����� 2�� ��ư�� �����ϱ� �б������� ������
			//_cursor->keyControlY(_rcCTRLNum[1].top - _rcCTRLNum[0].top, 2);
		}
		//EFFECT ���ý� ��µǾ�� �ϴ� ��ġ
		else if (_isSelect[SELECT_EFFECT])
		{
			//������ 3�� ��ư�� �ְ� �Ʒ����� 2�� ��ư�� �����ϱ� �б������� ������
		}
		//_cursor->keyControlX()
		//_cursor->keyControlY()
	}
	
	
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		//���� BGM �� �����شٸ�
		if (_cursor->getCursorYNum() == SELECT_BGM)
		{
			_isSelect[SELECT_BGM] = true;
		}
		if (_cursor->getCursorYNum() == SELECT_EFFECT)
		{
			_isSelect[SELECT_EFFECT] = true;
		}
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
		_bgmCtrlBtn[i]->btnImg->frameRender(getMemDC(), _bgmCtrlBtn[i]->btnImg->getX(), _bgmCtrlBtn[i]->btnImg->getY());
		_eftCtrlBtn[i]->btnImg->frameRender(getMemDC(), _eftCtrlBtn[i]->btnImg->getX(), _eftCtrlBtn[i]->btnImg->getY());
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