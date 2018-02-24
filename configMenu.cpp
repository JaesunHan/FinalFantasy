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
	_bgImage = IMAGEMANAGER->findImage("컨피그메뉴");

	
	

	//모든 볼륨조절 버튼을 세팅하기(BGM, EFFECT)
	for (int i = 0; i < MAXCONTROLBTN; ++i)
	{
		tagConfigButton* tmpBgmBtn = new tagConfigButton;
		tagConfigButton* tmpEftBtn = new tagConfigButton;
		//image* tmpBgmBtn = new image;
		//image* tmpEftBtn = new image;
		char tmpStr1[128];
		wsprintf(tmpStr1, "컨피그BGM버튼%d", i);
		char tmpStr2[128];
		wsprintf(tmpStr2, "컨피그EFT버튼%d", i);
		//tmpBgmBtn = IMAGEMANAGER->findImage("컨피그버튼");
		//tmpEftBtn = IMAGEMANAGER->findImage("컨피그버튼");
		//버튼 이미지 세팅
		tmpBgmBtn->btnImg = IMAGEMANAGER->addFrameImage(tmpStr1, ".//image//configMenu//configButton.bmp", 400, 65, 2, 1, true, RGB(255, 0, 255));
		tmpEftBtn->btnImg = IMAGEMANAGER->addFrameImage(tmpStr2, ".//image//configMenu//configButton.bmp", 400, 65, 2, 1, true, RGB(255, 0, 255));
		//버튼 이미지 위에 뿌려질 텍스트 세팅
		sprintf_s(tmpBgmBtn->btnTxt, sizeof(tmpBgmBtn->btnTxt), "%.2f", i*0.25);

		_bgmCtrlBtn.push_back(tmpBgmBtn);
		_eftCtrlBtn.push_back(tmpEftBtn);
	}
	//이제 기본 위치 세팅하기
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

	//처음에는 아무것도 선택을 안한 상태이므로 모두 false 로 세팅한다.
	_isSelect[SELECT_BGM] = false;
	_isSelect[SELECT_EFFECT] = false;
	//맨 처음에는 BGM와 EFFEC 가 있는 쪽에 커서가 출력되어야 한다.
	_isSubject = true;

	//연산은 버린다!
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
	if (_isSubject)	//커서가 왼쪽의 subject 를 가리켜야 한다
	{
		_cursor->keyControlY(_rcCTRLNum[1].top - _rcCTRLNum[0].top, 2);
	}
	else			//커서가 오른쪽의 title을 가리켜야 한다(5 개의 항목)
	{
		//BGM 선택시 출력되어야 하는 위치
		if (_isSelect[SELECT_BGM])
		{
			//윗줄은 3개 버튼이 있고 아랫줄은 2개 버튼이 있으니까 분기점으로 나눈다
			//_cursor->keyControlY(_rcCTRLNum[1].top - _rcCTRLNum[0].top, 2);
		}
		//EFFECT 선택시 출력되어야 하는 위치
		else if (_isSelect[SELECT_EFFECT])
		{
			//윗줄은 3개 버튼이 있고 아랫줄은 2개 버튼이 있으니까 분기점으로 나눈다
		}
		//_cursor->keyControlX()
		//_cursor->keyControlY()
	}
	
	
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		//만약 BGM 을 선택해다면
		if (_cursor->getCursorYNum() == SELECT_BGM)
		{
			_isSelect[SELECT_BGM] = true;
		}
		if (_cursor->getCursorYNum() == SELECT_EFFECT)
		{
			_isSelect[SELECT_EFFECT] = true;
		}
	}

	//옵션 메뉴가기
	if (KEYMANAGER->isOnceKeyDown(VK_BACK))
	{
		//_button->buttonRemove();
		//delete _button;
		SCENEMANAGER->changeScene("옵션");
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

//테스트 해볼 사항들\
1. 버튼10개가 제대로된 위치에 출력되는지\
2. 커서 출력용 렉트의 출력위치 체크!