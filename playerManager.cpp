#include "stdafx.h"
#include "playerManager.h"
#include "BattleScene.h"
#include "battleCeles.h"
#include "battleLocke.h"
#include "battleShadow.h"
#include "battleTina.h"


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
void playerManager::setPlayerInfoToBattlePlayer()
{
	//���� ���� ���Ŵ����� ��ϵǾ� �ִ� ��Ʋ���� �����´�
	_battleScene = (BattleScene*)SCENEMANAGER->findScene("��Ʋ��");

	//================================== Start �� ��Ʋ���� ��Ʋ�÷��̾���� ������ �����Ѵ�.====================================
	battleCeles* bCeles = (battleCeles*)_battleScene->getCelesAddress();
	bCeles->setAllBattlePlayerInfo(_celes->getLv(), _celes->getCurEXP(), _celes->getMaxEXP(),
		_celes->getCurHP(), _celes->getMaxHP(), _celes->getCurMP(), _celes->getMaxMP(), _celes->getSpeed(),
		_celes->getStrength(), _celes->getMagic(), _celes->getMDef(), _celes->getADef(), _celes->getAttack(), _celes->getEvasion(), _celes->getMEvasion(), _celes->getStamina());
	bCeles->setPartyIdx(_celes->getPartyIdx());

	battleLocke* bLocke = (battleLocke*)_battleScene->getLockeAddress();
	bLocke->setAllBattlePlayerInfo(_locke->getLv(), _locke->getCurEXP(), _locke->getMaxEXP(),
		_locke->getCurHP(), _locke->getMaxHP(), _locke->getCurMP(), _locke->getMaxMP(), _locke->getSpeed(),
		_locke->getStrength(), _locke->getMagic(), _locke->getMDef(), _locke->getADef(), _locke->getAttack(), _locke->getEvasion(), _locke->getMEvasion(), _locke->getStamina());
	bLocke->setPartyIdx(_locke->getPartyIdx());

	battleShadow* bShadow = (battleShadow*)_battleScene->getShadowAddress();
	bShadow->setAllBattlePlayerInfo(_shadow->getLv(), _shadow->getCurEXP(), _shadow->getMaxEXP(),
		_shadow->getCurHP(), _shadow->getMaxHP(), _shadow->getCurMP(), _shadow->getMaxMP(), _shadow->getSpeed(),
		_shadow->getStrength(), _shadow->getMagic(), _shadow->getMDef(), _shadow->getADef(), _shadow->getAttack(), _shadow->getEvasion(), _shadow->getMEvasion(), _shadow->getStamina());
	bShadow->setPartyIdx(_shadow->getPartyIdx());

	battleTina* bTina = (battleTina*)_battleScene->getTinaAddress();
	bTina->setAllBattlePlayerInfo(_tina->getLv(), _tina->getCurEXP(), _tina->getMaxEXP(),
		_tina->getCurHP(), _tina->getMaxHP(), _tina->getCurMP(), _tina->getMaxMP(), _tina->getSpeed(),
		_tina->getStrength(), _tina->getMagic(), _tina->getMDef(), _tina->getADef(), _tina->getAttack(), _tina->getEvasion(), _tina->getMEvasion(), _tina->getStamina());
	bTina->setPartyIdx(_tina->getPartyIdx());
	//================================== End �� ��Ʋ���� ��Ʋ�÷��̾���� ������ �����Ѵ�.====================================
}