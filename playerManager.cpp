#include "stdafx.h"
#include "playerManager.h"
#include "BattleScene.h"


playerManager::playerManager()
{
}


playerManager::~playerManager()
{

}

HRESULT playerManager::init()
{
	//각 플레이어들을 동적할당함 과 동시에 생성자가 호출되어 기본값으로 초기화 된다.
	_celes = new celes;
	_locke = new Locke;
	_shadow = new shadow;
	_tina = new Tina;
	

	return S_OK;
}
void playerManager::update() 
{

}
void playerManager::render() 
{

}
void playerManager::draw()	 
{

}
void playerManager::release()
{

}