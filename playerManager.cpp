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
	//�� �÷��̾���� �����Ҵ��� �� ���ÿ� �����ڰ� ȣ��Ǿ� �⺻������ �ʱ�ȭ �ȴ�.
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