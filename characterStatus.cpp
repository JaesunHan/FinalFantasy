#include "stdafx.h"
#include "characterStatus.h"


characterStatus::characterStatus()
{
}

characterStatus::~characterStatus()
{
}


HRESULT characterStatus::init()
{
	//백그라운드 이미지
	_bgImage = IMAGEMANAGER->findImage("캐릭터능력메뉴");

	//선택한 세이브 파일 가져오기 
	int saveFileNum = INIDATA->loadDataInterger("gameData", "gameData", "fileNum");
	_selectPlayerNum = INIDATA->loadDataInterger("gameData", "inventory", "selectChar");
	fileLoad(saveFileNum, _selectPlayerNum, true);



	return S_OK;
}

void characterStatus::release()
{

}

void characterStatus::update() 
{




	//옵션 메뉴가기
	if (KEYMANAGER->isOnceKeyDown(VK_BACK))
	{
		playerSlotRemove();
		playerStatusRemove();
		SCENEMANAGER->changeScene("상태");
	}
}

void characterStatus::render() 
{
	_bgImage->render(getMemDC());			 //백그라운드 이미지

	playerSlotRender();						 //슬롯 데이터
	playerStatusRender(_selectPlayerNum);    //상태 데이터
}
