#include "stdafx.h"
#include "playerManager.h"
#include "BattleScene.h"
#include "battleCeles.h"
#include "battleLocke.h"
#include "battleShadow.h"
#include "battleTina.h"
#include "weaponItem.h"
#include "newGame.h"
#include "loadGame.h"

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

	_vPlayer.push_back(_celes);
	_vPlayer.push_back(_locke);
	_vPlayer.push_back(_shadow);
	_vPlayer.push_back(_tina);
	_isNewGame = false;

	if (SCENEMANAGER->findScene("������"))
	{
		//���� �� ������ �����ϸ� ���ο� �����͸� ���Ͽ� �����Ѵ�
		if (SCENEMANAGER->getCurrentSceneName() == "������")
		{
			saveNewGameData();
		}
	}

	if (SCENEMANAGER->findScene("�ε����"))
	{
		//���� �ߴ� ������ �ε��ϸ� ���Ͽ��� �����͸� �о�´�.
		if (SCENEMANAGER->getCurrentSceneName() == "�ε����")
		{
			loadGameData();
		}
	}

	return S_OK;
}
void playerManager::update() 
{
	// �� ���� �����ϸ� saveGameData()ȣ��
	if (SCENEMANAGER->getCurrentSceneName() == "������")
	{
		if (!_isNewGame)
		{
			saveNewGameData();
			_isNewGame = true;
		}
	}
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
	bCeles->setPlayerDefaultPosition();
	bCeles->setWeapon(_celes->getWeapon());
	
	battleLocke* bLocke = (battleLocke*)_battleScene->getLockeAddress();
	bLocke->setAllBattlePlayerInfo(_locke->getLv(), _locke->getCurEXP(), _locke->getMaxEXP(),
		_locke->getCurHP(), _locke->getMaxHP(), _locke->getCurMP(), _locke->getMaxMP(), _locke->getSpeed(),
		_locke->getStrength(), _locke->getMagic(), _locke->getMDef(), _locke->getADef(), _locke->getAttack(), _locke->getEvasion(), _locke->getMEvasion(), _locke->getStamina());
	bLocke->setPartyIdx(_locke->getPartyIdx());
	bLocke->setPlayerDefaultPosition();
	bLocke->setWeapon(_locke->getWeapon());

	battleShadow* bShadow = (battleShadow*)_battleScene->getShadowAddress();
	bShadow->setAllBattlePlayerInfo(_shadow->getLv(), _shadow->getCurEXP(), _shadow->getMaxEXP(),
		_shadow->getCurHP(), _shadow->getMaxHP(), _shadow->getCurMP(), _shadow->getMaxMP(), _shadow->getSpeed(),
		_shadow->getStrength(), _shadow->getMagic(), _shadow->getMDef(), _shadow->getADef(), _shadow->getAttack(), _shadow->getEvasion(), _shadow->getMEvasion(), _shadow->getStamina());
	bShadow->setPartyIdx(_shadow->getPartyIdx());
	bShadow->setPlayerDefaultPosition();
	bShadow->setWeapon(_shadow->getWeapon());
	
	battleTina* bTina = (battleTina*)_battleScene->getTinaAddress();
	bTina->setAllBattlePlayerInfo(_tina->getLv(), _tina->getCurEXP(), _tina->getMaxEXP(),
		_tina->getCurHP(), _tina->getMaxHP(), _tina->getCurMP(), _tina->getMaxMP(), _tina->getSpeed(),
		_tina->getStrength(), _tina->getMagic(), _tina->getMDef(), _tina->getADef(), _tina->getAttack(), _tina->getEvasion(), _tina->getMEvasion(), _tina->getStamina());
	bTina->setPartyIdx(_tina->getPartyIdx());
	bTina->setPlayerDefaultPosition();
	bTina->setWeapon(_tina->getWeapon());
	
	//================================== End �� ��Ʋ���� ��Ʋ�÷��̾���� ������ �����Ѵ�.====================================
}

//�� ������ �����ϸ� �⺻������ ������ �÷��̾���� ������ ���Ͽ� �����Ѵ�.
void playerManager::saveNewGameData()
{
	////���� newGame Ŭ�������� �޾ƿ´�
	//newGame* ng = new newGame;
	//ng = (newGame*)SCENEMANAGER->findScene("������");
	//int saveFileNum = ng->getSaveFileNum();
	
	//���� �����Ϸ��� ���� �ѹ��� �޾ƿ´�.
	TCHAR gameDataFileName[256];
	wsprintf(gameDataFileName, "%s", "gameData");
	int saveFileNum = INIDATA->loadDataInterger(gameDataFileName, "gameData", "fileNum");

	TCHAR gameSaveFileName[256];
	wsprintf(gameSaveFileName, "saveFile%d", saveFileNum);
	
	//�ݺ����� ���鼭 ������ �÷��̾ ���Ͽ� �����Ѵ�.
	for (int i = 0; i < MAXPLAYERNUMBER; ++i)
	{
		TCHAR str[256];
		TCHAR playerSubject[256];
		wsprintf(playerSubject, "player%d", i);
		INIDATA->addData(playerSubject, "name", _vPlayer[i]->getName());
		INIDATA->addData(playerSubject, "job", _vPlayer[i]->getJob());

		ZeroMemory(str, sizeof(str));
		wsprintf(str, "%d", _vPlayer[i]->getLv());
		INIDATA->addData(playerSubject, "level", str);

		ZeroMemory(str, sizeof(str));
		wsprintf(str, "%d", _vPlayer[i]->getCurHP());
		INIDATA->addData(playerSubject, "hp", str);

		ZeroMemory(str, sizeof(str));
		wsprintf(str, "%d", _vPlayer[i]->getMaxHP());
		INIDATA->addData(playerSubject, "maxHp", str);

		ZeroMemory(str, sizeof(str));
		wsprintf(str, "%d", _vPlayer[i]->getCurMP());
		INIDATA->addData(playerSubject, "mp", str);

		ZeroMemory(str, sizeof(str));
		wsprintf(str, "%d", _vPlayer[i]->getMaxMP());
		INIDATA->addData(playerSubject, "maxMp", str);

		ZeroMemory(str, sizeof(str));
		wsprintf(str, "%d", _vPlayer[i]->getCurEXP());
		INIDATA->addData(playerSubject, "exp", str);

		ZeroMemory(str, sizeof(str));
		wsprintf(str, "%d", _vPlayer[i]->getMaxEXP());
		INIDATA->addData(playerSubject, "maxExp", str);

		ZeroMemory(str, sizeof(str));
		wsprintf(str, "%d", _vPlayer[i]->getStrength());
		INIDATA->addData(playerSubject, "strength", str);

		ZeroMemory(str, sizeof(str));
		wsprintf(str, "%d", _vPlayer[i]->getSpeed());
		INIDATA->addData(playerSubject, "speed", str);

		ZeroMemory(str, sizeof(str));
		wsprintf(str, "%d", _vPlayer[i]->getStamina());
		INIDATA->addData(playerSubject, "stamina", str);

		ZeroMemory(str, sizeof(str));
		wsprintf(str, "%d", _vPlayer[i]->getMagic());
		INIDATA->addData(playerSubject, "magic", str);

		ZeroMemory(str, sizeof(str));
		wsprintf(str, "%d", _vPlayer[i]->getAttack());
		INIDATA->addData(playerSubject, "attack", str);

		ZeroMemory(str, sizeof(str));
		wsprintf(str, "%d", _vPlayer[i]->getADef());
		INIDATA->addData(playerSubject, "attackDefence", str);

		ZeroMemory(str, sizeof(str));
		wsprintf(str, "%d", _vPlayer[i]->getMDef());
		INIDATA->addData(playerSubject, "magicDefence", str);

		ZeroMemory(str, sizeof(str));
		wsprintf(str, "%d", _vPlayer[i]->getEvasion());
		INIDATA->addData(playerSubject, "evasion", str);

		ZeroMemory(str, sizeof(str));
		wsprintf(str, "%d", _vPlayer[i]->getMEvasion());
		INIDATA->addData(playerSubject, "magicEvasion", str);

		ZeroMemory(str, sizeof(str));
		wsprintf(str, "%d", _vPlayer[i]->getPartyIdx());
		INIDATA->addData(playerSubject, "partyIdx", str);

		INIDATA->iniSave(gameSaveFileName);

	}
	
}

void playerManager::loadGameData()
{
	loadGame* lg = new loadGame;
	lg = (loadGame*)SCENEMANAGER->findScene("�ε����");
	int saveFileNum = lg->getSaveFileNum();
}
