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
	//각 플레이어들을 동적할당함 과 동시에 생성자가 호출되어 기본값으로 초기화 된다.
	_celes = new celes;
	_locke = new Locke;
	_shadow = new shadow;
	_tina = new Tina;

	//_vPlayer.push_back(_celes);
	//_vPlayer.push_back(_locke);
	//_vPlayer.push_back(_shadow);
	//_vPlayer.push_back(_tina);
	//_isNewGame = false;

	//if (SCENEMANAGER->findScene("뉴게임"))
	//{
	//	//만약 새 게임을 시작하면 새로운 데이터를 파일에 저장한다
	//	if (SCENEMANAGER->getCurrentSceneName() == "뉴게임")
	//	{
	//		//saveNewGameData();
	//	}
	//}
	//
	//if (SCENEMANAGER->findScene("로드게임"))
	//{
	//	//원래 했던 게임을 로드하면 파일에서 데이터를 읽어온다.
	//	if (SCENEMANAGER->getCurrentSceneName() == "로드게임")
	//	{
	//		//loadGameData();
	//	}
	//}

	int a = maxExpValue[0];

	return S_OK;
}
void playerManager::update() 
{
	//else return;
	char fileName[128];
	wsprintf(fileName, "gameData");
	//게임 시작 신호 받아오기
	if (INIDATA->loadDataInterger(fileName, "gameData", "gameStart"))
	{
		loadGameData();
		INIDATA->addData("gameData", "gameStart", "0");
		INIDATA->iniSave(fileName);
	}
	//무기가 잘 바뀌는지 테스트 해봄
	if (KEYMANAGER->isOnceKeyDown('C'))
	{
		int rndNum = RND->getFromIntTo(11, 20);
		if (_itemManager->getVItem()[rndNum]->getItmeKind() == ITEM_WEAPON)
		{
			_vPlayer[0]->setWeaponItem((weaponItem*)_itemManager->getVItem()[rndNum]);
		}
	}

	//플레이어가 렙업했으면 렙업한 정보를 저장한다.
	playerLevelUp();

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
	//먼저 현재 씬매니저에 등록되어 있는 배틀씬을 가져온다
	_battleScene = (BattleScene*)SCENEMANAGER->findScene("배틀씬");

	//================================== Start 그 배틀씬의 배틀플레이어들의 정보를 저장한다.====================================
	battleCeles* bCeles = (battleCeles*)_battleScene->getCelesAddress();
	
	bCeles->setAllBattlePlayerInfo(_celes->getLv(), _celes->getCurEXP(), _celes->getMaxEXP(),
		_celes->getCurHP(), _celes->getMaxHP(), _celes->getCurMP(), _celes->getMaxMP(), _celes->getSpeed(),
		_celes->getStrength(), _celes->getMagic(), _celes->getMDef(), _celes->getADef(), _celes->getAttack(), _celes->getEvasion(), _celes->getMEvasion(), _celes->getStamina());
	bCeles->setPartyIdx(_celes->getPartyIdx());
	bCeles->setPlayerDefaultPosition();
	bCeles->setWeapon(_celes->getWeapon());
	bCeles->setArmor(_celes->getArmor());
	bCeles->setHelmet(_celes->getHelmet());
	bCeles->setSubWeapon(_celes->getSubWeapon());
	
	battleLocke* bLocke = (battleLocke*)_battleScene->getLockeAddress();
	bLocke->setAllBattlePlayerInfo(_locke->getLv(), _locke->getCurEXP(), _locke->getMaxEXP(),
		_locke->getCurHP(), _locke->getMaxHP(), _locke->getCurMP(), _locke->getMaxMP(), _locke->getSpeed(),
		_locke->getStrength(), _locke->getMagic(), _locke->getMDef(), _locke->getADef(), _locke->getAttack(), _locke->getEvasion(), _locke->getMEvasion(), _locke->getStamina());
	bLocke->setPartyIdx(_locke->getPartyIdx());
	bLocke->setPlayerDefaultPosition();
	bLocke->setWeapon(_locke->getWeapon());
	bLocke->setArmor(_locke->getArmor());
	bLocke->setHelmet(_locke->getHelmet());
	bLocke->setSubWeapon(_locke->getSubWeapon());

	battleShadow* bShadow = (battleShadow*)_battleScene->getShadowAddress();
	bShadow->setAllBattlePlayerInfo(_shadow->getLv(), _shadow->getCurEXP(), _shadow->getMaxEXP(),
		_shadow->getCurHP(), _shadow->getMaxHP(), _shadow->getCurMP(), _shadow->getMaxMP(), _shadow->getSpeed(),
		_shadow->getStrength(), _shadow->getMagic(), _shadow->getMDef(), _shadow->getADef(), _shadow->getAttack(), _shadow->getEvasion(), _shadow->getMEvasion(), _shadow->getStamina());
	bShadow->setPartyIdx(_shadow->getPartyIdx());
	bShadow->setPlayerDefaultPosition();
	bShadow->setWeapon(_shadow->getWeapon());
	bShadow->setArmor(_shadow->getArmor());
	bShadow->setHelmet(_shadow->getHelmet());
	bShadow->setSubWeapon(_shadow->getSubWeapon());
	
	battleTina* bTina = (battleTina*)_battleScene->getTinaAddress();
	bTina->setAllBattlePlayerInfo(_tina->getLv(), _tina->getCurEXP(), _tina->getMaxEXP(),
		_tina->getCurHP(), _tina->getMaxHP(), _tina->getCurMP(), _tina->getMaxMP(), _tina->getSpeed(),
		_tina->getStrength(), _tina->getMagic(), _tina->getMDef(), _tina->getADef(), _tina->getAttack(), _tina->getEvasion(), _tina->getMEvasion(), _tina->getStamina());
	bTina->setPartyIdx(_tina->getPartyIdx());
	bTina->setPlayerDefaultPosition();
	bTina->setWeapon(_tina->getWeapon());
	bTina->setArmor(_tina->getArmor());
	bTina->setHelmet(_tina->getHelmet());
	bTina->setSubWeapon(_tina->getSubWeapon());
	
	//================================== End 그 배틀씬의 배틀플레이어들의 정보를 저장한다.====================================
}

//새 게임을 시작하면 기본적으로 생성한 플레이어들의 정보를 파일에 저장한다.
/*
void playerManager::saveNewGameData()
{
	////먼저 newGame 클래스를 받아온다
	//newGame* ng = new newGame;
	//ng = (newGame*)SCENEMANAGER->findScene("뉴게임");
	//int saveFileNum = ng->getSaveFileNum();
	
	//현재 저장하려는 파일 넘버를 받아온다.
	TCHAR gameDataFileName[256];
	wsprintf(gameDataFileName, "%s", "gameData");
	int saveFileNum = INIDATA->loadDataInterger(gameDataFileName, "gameData", "fileNum");

	TCHAR gameSaveFileName[256];
	wsprintf(gameSaveFileName, "saveFile%d", saveFileNum);
	
	//반복문을 돌면서 벡터의 플레이어를 파일에 저장한다.
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
*/

void playerManager::loadGameData()
{
	_vPlayer.clear();
	TCHAR gameFileName[256];
	wsprintf(gameFileName, "skgFile");

	//tempFile 에서 데이터 읽어오기
	for (int i = 0; i < MAXPLAYERNUMBER; ++i)
	{
		playerMother* tempPlayer = new playerMother;
		TCHAR playerSubject[256];
		wsprintf(playerSubject, "player%d", i);
		TCHAR str[256];
		tempPlayer->setName(INIDATA->loadDataString(gameFileName, playerSubject, "name"));
		tempPlayer->setJob(INIDATA->loadDataString(gameFileName, playerSubject, "job"));
		tempPlayer->setCurEXP(INIDATA->loadDataInterger(gameFileName, playerSubject, "exp"));
		tempPlayer->setCurHP(INIDATA->loadDataInterger(gameFileName, playerSubject, "hp"));
		tempPlayer->setCurMP(INIDATA->loadDataInterger(gameFileName, playerSubject, "mp"));
		tempPlayer->setLv(INIDATA->loadDataInterger(gameFileName, playerSubject, "level"));
		tempPlayer->setMaxEXP(INIDATA->loadDataInterger(gameFileName, playerSubject, "maxExp"));
		tempPlayer->setMaxHP(INIDATA->loadDataInterger(gameFileName, playerSubject, "maxHp"));
		tempPlayer->setMaxMP(INIDATA->loadDataInterger(gameFileName, playerSubject, "maxMp"));
		tempPlayer->setPartyIdx(INIDATA->loadDataInterger(gameFileName, playerSubject, "partyIdx"));
		tempPlayer->setADef(INIDATA->loadDataInterger(gameFileName, playerSubject, "attackDefence"));
		tempPlayer->setMDef(INIDATA->loadDataInterger(gameFileName, playerSubject, "magicDefence"));
		tempPlayer->setAttack(INIDATA->loadDataInterger(gameFileName, playerSubject, "attack"));
		tempPlayer->setEvasion(INIDATA->loadDataInterger(gameFileName, playerSubject, "evation"));
		tempPlayer->setMagic(INIDATA->loadDataInterger(gameFileName, playerSubject, "magic"));
		tempPlayer->setMEvasion(INIDATA->loadDataInterger(gameFileName, playerSubject, "magicEvation"));
		tempPlayer->setSpeed(INIDATA->loadDataInterger(gameFileName, playerSubject, "speed"));
		tempPlayer->setStamina(INIDATA->loadDataInterger(gameFileName, playerSubject, "stamina"));
		tempPlayer->setStrength(INIDATA->loadDataInterger(gameFileName, playerSubject, "strength"));
		int weaponNum = INIDATA->loadDataInterger(gameFileName, playerSubject, "myWeapon");
		int armorNum = INIDATA->loadDataInterger(gameFileName, playerSubject, "myArmor");
		int helmetNum = INIDATA->loadDataInterger(gameFileName, playerSubject, "myHelmet");
		int subWeaponNum = INIDATA->loadDataInterger(gameFileName, playerSubject, "mySubWeapon");
		//테스트용 아이템 번호
		//int weaponNum = 12;
		//int armorNum = 23;
		//int helmetNum = 28;
		//int subWeaponNum = 33;
		searchPlayerItem(weaponNum, armorNum, helmetNum, subWeaponNum, tempPlayer);

		_vPlayer.push_back(tempPlayer);

		//개발 초반에, 배틀씬에 플레이어 정보를 넘길 때 전역변수로 생성한 플레이어들을 이용해서 넘기는 걸로 해놔서....
		//어쩔수 없이 이런 방법으로...
		if (!strcmp("TINA", tempPlayer->getName()))
		{
			_tina = (Tina*)tempPlayer;
		}
		else if (!strcmp("LOCKE", tempPlayer->getName()))
		{
			_locke = (Locke*)tempPlayer;
		}
		else if (!strcmp("CELES", tempPlayer->getName()))
		{
			_celes = (celes*)tempPlayer;
		}
		else if (!strcmp("SHADOW", tempPlayer->getName()))
		{
			_shadow = (shadow*)tempPlayer;
		}
	}
}

void playerManager::searchPlayerItem(int weaponNum, int armorNum, int helmetNum, int subWeapon, playerMother* tempPlayer)
{
	//그 아이템 번호가 0이면 기본무기로 저장하고
	if (weaponNum == 0)
	{
		//기본무기 아이템을 생성해서
		weaponItem* temWeapon = new weaponItem;
		temWeapon->init(0, ITEM_WEAPON, "DefaultWeapon", "맨주먹공격무기이다", 0, 10, 100);
		tempPlayer->setDefaultWeapon(temWeapon);
	}

	if (armorNum == -1)
	{
		//기본 갑옷 세팅
		armorItem* tempArmor = new armorItem;
		tempArmor->init(-1, ITEM_ARMOR, "", "", 0, 0, 0);
		tempPlayer->setArmor(tempArmor);
	}

	if (helmetNum == -2)
	{
		armorItem* tempHelmet = new armorItem;
		tempHelmet->init(-2, ITEM_HELMET, "", "", 0, 0, 0);
		tempPlayer->setHelmet(tempHelmet);
	}

	if (subWeapon == -3)
	{
		armorItem* tempSubWeapon = new armorItem;
		tempSubWeapon->init(-3, ITEM_SUB_WEAPON, "", "", 0, 0, 0);
		tempPlayer->setSubWeapon(tempSubWeapon);
	}
	for (int i = 0; i < _itemManager->getVItem().size(); ++i)
	{
		//================= 무기 아이템 ===================
		//itemMother * tempItem = (itemMother*)_itemManager->getVItem()[i];
		//아이템리스트의 넘버와 무기아이템의 아이템 넘버가 같을때
		if (_itemManager->getVItem()[i]->getItemNumber() == weaponNum)
		{
			//무기 아이템을 플레이어 정보에 저장
			weaponItem* tempItem = (weaponItem*)_itemManager->getVItem()[i];
			
			tempPlayer->setWeaponItem(tempItem);
		}
		if (_itemManager->getVItem()[i]->getItemNumber() == armorNum)
		{
			//갑옷 아이템을 플레이어 정보에 저장
			armorItem* tempItem = (armorItem*)_itemManager->getVItem()[i];

			tempPlayer->setArmor(tempItem);
		}
		if (_itemManager->getVItem()[i]->getItemNumber() == helmetNum)
		{
			//투구 아이템을 플레이어 정보에 저장
			armorItem* tempItem = (armorItem*)_itemManager->getVItem()[i];

			tempPlayer->setHelmet(tempItem);
		}
		if (_itemManager->getVItem()[i]->getItemNumber() == subWeapon)
		{
			//보조무기 아이템을 플레이어 정보에 저장
			armorItem* tempItem = (armorItem*)_itemManager->getVItem()[i];

			tempPlayer->setSubWeapon(tempItem);
		}
	}
}

void playerManager::playerLevelUp()
{
	char fileName[256];
	wsprintf(fileName, "%s", "skgFile");

	for (int i = 0; i < MAXPLAYERNUMBER; ++i)
	{
		char subjectName[256];
		wsprintf(subjectName, "player%d", i);
		int curExp = INIDATA->loadDataInterger(fileName, subjectName, "exp");
		int maxExp = INIDATA->loadDataInterger(fileName, subjectName, "maxExp");

		int curHP = INIDATA->loadDataInterger(fileName, subjectName, "hp");
		int maxHP = INIDATA->loadDataInterger(fileName, subjectName, "maxHp");
		int curMP = INIDATA->loadDataInterger(fileName, subjectName, "mp");
		int maxMP = INIDATA->loadDataInterger(fileName, subjectName, "maxMp");
		int lv = INIDATA->loadDataInterger(fileName, subjectName, "level");
		//이 때 렙업해야됨
		if (curExp >= maxExp)
		{
			lv += 1;	maxExp = maxExpValue[lv];
			for (int i =0; i<lv; ++i)
			{
				maxHP += improveHPValue[i];
				maxMP += improveMPValue[i];
			}
			curHP += improveHPValue[lv - 1];
			curMP += improveMPValue[lv - 1];

			char strMaxExp[256];
			wsprintf(strMaxExp, "%d", maxExp);
			char strLv[256];
			wsprintf(strLv, "%d", lv);
			char strCurHP[256];
			wsprintf(strCurHP, "%d", curHP);
			char strMaxHP[256];
			wsprintf(strMaxHP, "%d", maxHP);
			char strCurMP[256];
			wsprintf(strCurMP, "%d", curMP);
			char strMaxMP[256];
			wsprintf(strMaxMP, "%d", maxMP);

			INIDATA->addData(subjectName, "maxExp", strMaxExp);
			INIDATA->addData(subjectName, "level", strLv);
			INIDATA->addData(subjectName, "hp", strCurHP);
			INIDATA->addData(subjectName, "maxHp", strMaxHP);
			INIDATA->addData(subjectName, "mp", strCurMP);
			INIDATA->addData(subjectName, "maxMp", strMaxMP);

			INIDATA->iniSave(fileName);
		}
	}
}