#include "stdafx.h"
#include "characterAbility.h"


characterAbility::characterAbility()
{
}


characterAbility::~characterAbility()
{
}


HRESULT characterAbility::init()
{
	//백그라운드 이미지
	_bgImage = IMAGEMANAGER->findImage("캐릭터능력메뉴");

	//선택한 세이브 파일 가져오기 
	int saveFileNum = INIDATA->loadDataInterger("gameData", "gameData", "fileNum");
	int selectPlayerNum = INIDATA->loadDataInterger("gameData", "inventory", "selectChar");
	fileLoad(saveFileNum, selectPlayerNum);



	return S_OK;
}

void characterAbility::release()
{

}

void characterAbility::update()	
{




	//옵션 메뉴가기
	if (KEYMANAGER->isOnceKeyDown(VK_BACK))
	{
		//버튼 벡터에서 삭제
		//_button->buttonRemove();
		//delete _button;
		SCENEMANAGER->changeScene("능력치");
	}
}

void characterAbility::render()	
{
	_bgImage->render(getMemDC());  //백그라운드 이미지

	playerSlotRender();            //슬롯 데이터
}
