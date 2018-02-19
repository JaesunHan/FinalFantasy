#include "stdafx.h"
#include "playerManager.h"
#include "BattleScene.h"
#include "battleCeles.h"
#include "battleLocke.h"
#include "battleShadow.h"
#include "battleTina.h"
#include "itemManager.h"
//#include "weaponItem.h"
//#include "newGame.h"
//#include "loadGame.h"

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

	//_vPlayer.push_back(_celes);
	//_vPlayer.push_back(_locke);
	//_vPlayer.push_back(_shadow);
	//_vPlayer.push_back(_tina);
	//_isNewGame = false;

	//if (SCENEMANAGER->findScene("������"))
	//{
	//	//���� �� ������ �����ϸ� ���ο� �����͸� ���Ͽ� �����Ѵ�
	//	if (SCENEMANAGER->getCurrentSceneName() == "������")
	//	{
	//		//saveNewGameData();
	//	}
	//}
	//
	//if (SCENEMANAGER->findScene("�ε����"))
	//{
	//	//���� �ߴ� ������ �ε��ϸ� ���Ͽ��� �����͸� �о�´�.
	//	if (SCENEMANAGER->getCurrentSceneName() == "�ε����")
	//	{
	//		//loadGameData();
	//	}
	//}

	return S_OK;
}
void playerManager::update() 
{
	//else return;
	char fileName[128];
	wsprintf(fileName, "gameData");
	//���� ���� ��ȣ �޾ƿ���
	//INIDATA->loadDataInterger(fileName, "gameData", "gameStart");
	if (INIDATA->loadDataInterger(fileName, "gameData", "gameStart"))
	{
		loadGameData();
		INIDATA->addData("gameData", "gameStart", 0);
		INIDATA->iniSave(fileName);
	}
	// �� ���� �����ϸ� saveGameData()ȣ��
	//if (SCENEMANAGER->getCurrentSceneName() == "������")
	//{
	//	newGame* ng = (newGame*)SCENEMANAGER->findScene("������");
	//	//�������� �����ߴٴ� ��ȣ�̴�
	//	if (ng->getIsGameStart())
	//	{
	//		loadNewGameData();
	//	}
	//}
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
	//������ �׽�Ʈ������, �׳� �⺻ ������ �ѱ����� 
	//���߿� ���� ���Ӹ��� ���Ÿ� �� �κ��� _vPlayer �� ������ �����ؾ� �ȴ�
	//ex) bCels	->setAllBattlePlayerInfo(_vPlayer[i(????)]->getLov(), _vPlayer[i]->getCurExp(), .........);
	//�䷱������
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

		INIDATA->addData(playerSubject, "myWeapon", _vPlayer[i]->getWeapon()->getItemName());

		INIDATA->iniSave(gameSaveFileName);

	}
	
}

void playerManager::loadGameData()
{
	TCHAR gameFileName[256];
	wsprintf(gameFileName, "tempFile");

	for (int i = 0; i < MAXPLAYERNUMBER; ++i)
	{
		playerMother* tempPlayer = new playerMother;
		TCHAR playerSubject[256];
		wsprintf(playerSubject, "player%d", i);
		TCHAR str[256];
		//wsprintf(str, "%s", INIDATA->loadDataString(gameFileName, playerSubject, "name");
		tempPlayer->setName(INIDATA->loadDataString(gameFileName, playerSubject, "name"));
		tempPlayer->setJob(INIDATA->loadDataString(gameFileName, playerSubject, "job"));
		tempPlayer->setCurEXP(INIDATA->loadDataInterger(gameFileName, playerSubject, "curExp"));
		tempPlayer->setCurHP(INIDATA->loadDataInterger(gameFileName, playerSubject, "curHp"));
		tempPlayer->setCurMP(INIDATA->loadDataInterger(gameFileName, playerSubject, "curMp"));
		tempPlayer->setLv(INIDATA->loadDataInterger(gameFileName, playerSubject, "level"));
		tempPlayer->setMaxEXP(INIDATA->loadDataInterger(gameFileName, playerSubject, "maxExp"));
		tempPlayer->setMaxHP(INIDATA->loadDataInterger(gameFileName, playerSubject, "maxHp"));
		tempPlayer->setMaxMP(INIDATA->loadDataInterger(gameFileName, playerSubject, "maxMp"));
		tempPlayer->setPartyIdx(INIDATA->loadDataInterger(gameFileName, playerSubject, "partyIdx"));
		tempPlayer->setADef(INIDATA->loadDataInterger(gameFileName, playerSubject, "attackDefence"));
		tempPlayer->setMDef(INIDATA->loadDataInterger(gameFileName, playerSubject, "magicDefence"));
		tempPlayer->setAttack(INIDATA->loadDataInterger(gameFileName, playerSubject, "attack"));
		tempPlayer->setEvasion(INIDATA->loadDataInterger(gameFileName, playerSubject, "evasion"));
		tempPlayer->setMagic(INIDATA->loadDataInterger(gameFileName, playerSubject, "magic"));
		tempPlayer->setMEvasion(INIDATA->loadDataInterger(gameFileName, playerSubject, "magicEvasion"));
		tempPlayer->setSpeed(INIDATA->loadDataInterger(gameFileName, playerSubject, "speed"));
		tempPlayer->setStamina(INIDATA->loadDataInterger(gameFileName, playerSubject, "stamina"));
		tempPlayer->setStrength(INIDATA->loadDataInterger(gameFileName, playerSubject, "strength"));
		TCHAR weaponName[256];
		wsprintf(weaponName,"%s", INIDATA->loadDataInterger(gameFileName, playerSubject, "strength"));
		if (strcmp(weaponName, "DefaultWeapon"))
		{
			weaponItem* temWeapon = new weaponItem;
			temWeapon->init(ITEM_WEAPON, "DefaultWeapon", "���ָ԰��ݹ����̴�", 0, 10, 100);
			tempPlayer->setWeaponItem(temWeapon);
		}
		else
		{
			for (int i = 0; i < _itemManager->getVItem().size(); ++i)
			{
				if (strcmp(weaponName, _itemManager->getVItem()[i]->getItemName()))
				{

				}
			}
		}
		_vPlayer.push_back(tempPlayer);
	}

}
