#include "stdafx.h"
#include "fButton.h"


fButton::fButton()
	: _buttonNum(0)
{
}
fButton::~fButton()
{
}

HRESULT fButton::init()
{

	return S_OK;
}

void fButton::release()
{

}


//						 버튼이미지 키값  위치XY
void fButton::buttonSet(string keyName, float x, float y)
{
	//-------------------------------------------- keyName 형변환
	char temp[128];
	ZeroMemory(&temp, sizeof(temp));
	sprintf(temp, "%s", keyName.c_str());
	//--------------------------------------------

	//-------------------------------------------- animationKeyName
	char aniTemp[32];
	ZeroMemory(&aniTemp, sizeof(aniTemp));
	sprintf(aniTemp, "%s%d", "버튼시작", _buttonNum);
	//--------------------------------------------

	tagButton _button;
	ZeroMemory(&_button, sizeof(_button));

	_button.img = IMAGEMANAGER->findImage(keyName);
	_button.x = x;
	_button.y = y;
	_button.aniStart = false;
	_button.textOn = false;
	_button.ani = new animation;
	int arrAni[] = { 0, 1 };
	KEYANIMANAGER->addArrayFrameAnimation(aniTemp, temp, arrAni, 2, 2, true);
	_button.ani = KEYANIMANAGER->findAnimation(aniTemp);

	_vButton.push_back(_button);

	_buttonNum++;
}

//					    버튼이미지 키값  위치XY           텍스트            텍스트크기
void fButton::buttonSet(string keyName, float x, float y, char* buttonText, float textSize, int textSortType, bool isAddText, int subTextNum, int textIntervalX)
{
	//-------------------------------------------- keyName 형변환
	char temp[128];
	ZeroMemory(&temp, sizeof(temp));
	sprintf(temp, "%s", keyName.c_str());
	//--------------------------------------------

	//-------------------------------------------- animationKeyName
	char aniTemp[32];
	ZeroMemory(&aniTemp, sizeof(aniTemp));
	sprintf(aniTemp, "%s%d", "버튼시작", _buttonNum);
	//--------------------------------------------

	tagButton _button;
	ZeroMemory(&_button, sizeof(_button));


	_button.img = IMAGEMANAGER->findImage(keyName);
	_button.x = x;
	_button.y = y;
	_button.textSize = textSize;
	_button.centerX = _button.x + (_button.img->getFrameWidth() / 2);
	_button.centerY = _button.y + (_button.img->getFrameHeight() / 2) - (textSize / 2);
	_button.aniStart = false;
	_button.textOn = true;
	_button.ani = new animation;
	_button.text = buttonText;
	_button.textSort = textSortType;
	int arrAni[] = { 0, 1 };
	KEYANIMANAGER->addArrayFrameAnimation(aniTemp, temp, arrAni, 2, 2, true);
	_button.ani = KEYANIMANAGER->findAnimation(aniTemp);

	if (isAddText) wsprintf(_button.subText, "%d", subTextNum);
	_button.isAddText = isAddText;
	_button.textIntervalX = textIntervalX;


	_vButton.push_back(_button);

	_buttonNum++;
}

void fButton::update()
{
	for (int i = 0; i < _vButton.size(); ++i)
	{
		if (_vButton[i].aniStart)  //에니메이션 Play
		{
			if (!_vButton[i].ani->isPlay()) _vButton[i].ani->start();
		}
		else  //에니메이션 Stop
		{
			if (_vButton[i].ani->isPlay()) _vButton[i].ani->stop();
		}
	}


	KEYANIMANAGER->update();
}

void fButton::render()
{
	for (int i = 0; i < _vButton.size(); ++i)
	{
		_vButton[i].img->aniRender(getMemDC(), _vButton[i].x, _vButton[i].y, _vButton[i].ani);
		if (_vButton[i].textOn)
		{
			switch (_vButton[i].textSort)
			{
				case 0:
					textPrint(getMemDC(), _vButton[i].text, _vButton[i].centerX, _vButton[i].centerY, _vButton[i].textSize, 20, "Viner Hand ITC");
				break;
				case 1:
					textPrint(getMemDC(), _vButton[i].text, _vButton[i].centerX - 40, _vButton[i].centerY - 5, _vButton[i].textSize, 20, "Viner Hand ITC", RGB(255, 255, 255), false);
				break;
				case 2:
					textPrint(getMemDC(), _vButton[i].text, _vButton[i].centerX - 50, _vButton[i].centerY, _vButton[i].textSize, 20, "휴먼모음T", RGB(255, 255, 255), false);
				break;
			}
		}		
		if (_vButton[i].isAddText)
		{
			textPrint(getMemDC(), _vButton[i].subText, _vButton[i].centerX + _vButton[i].textIntervalX, _vButton[i].centerY, _vButton[i].textSize, 20, "휴먼모음T", RGB(0, 0, 0), false);
		}

		if (KEYMANAGER->isToggleKey(VK_TAB))
		{
			char tmpI[16];
			sprintf(tmpI, "%d", i);
			textPrint(getMemDC(), tmpI, _vButton[i].x, _vButton[i].y, _vButton[i].textSize, 10, "휴먼모음T", RGB(255, 255, 255), false);
		}
			

	}
}

void fButton::buttonRemove()
{
	if (_vButton.size() != 0)
	{
		for (int i = 0; i < _vButton.size(); ++i)
		{
			_vButton[i].img = NULL;
			_vButton.erase(_vButton.begin() + i);
		}
	}

	KEYANIMANAGER->deleteAll();
	_vButton.clear();
}

void fButton::buttonRemoveOne(int buttonNum)
{
	//_vButton[buttonNum].img = NULL;
	//SAFE_DELETE(_vButton[buttonNum].ani);
	_vButton.erase(_vButton.begin() + buttonNum);
}

