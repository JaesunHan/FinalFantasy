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

	int a = maxExpValue[0];

	return S_OK;
}
void playerManager::update() 
{
	//else return;
	char fileName[128];
	wsprintf(fileName, "gameData");
	//���� ���� ��ȣ �޾ƿ���
	if (INIDATA->loadDataInterger(fileName, "gameData", "gameStart"))
	{
		loadGameData();
		INIDATA->addData("gameData", "gameStart", "0");
		INIDATA->iniSave(fileName);
	}
	//���Ⱑ �� �ٲ���� �׽�Ʈ �غ�
	if (KEYMANAGER->isOnceKeyDown('C'))
	{
		int rndNum = RND->getFromIntTo(11, 20);
		if (_itemManager->getVItem()[rndNum]->getItmeKind() == ITEM_WEAPON)
		{
			_vPlayer[0]->setWeaponItem((weaponItem*)_itemManager->getVItem()[rndNum]);
		}
	}

	//�÷��̾ ���������� ������ ������ �����Ѵ�.
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
	
	//================================== End �� ��Ʋ���� ��Ʋ�÷��̾���� ������ �����Ѵ�.====================================
}

//�� ������ �����ϸ� �⺻������ ������ �÷��̾���� ������ ���Ͽ� �����Ѵ�.
/*
void playerManager::saveNewGameData()
{
	////���� newGame Ŭ������ �޾ƿ´�
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
*/

void playerManager::loadGameData()
{
	_vPlayer.clear();
	TCHAR gameFileName[256];
	wsprintf(gameFileName, "skgFile");

	//tempFile ���� ������ �о����
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
		//�׽�Ʈ�� ������ ��ȣ
		//int weaponNum = 12;
		//int armorNum = 23;
		//int helmetNum = 28;
		//int subWeaponNum = 33;
		searchPlayerItem(weaponNum, armorNum, helmetNum, subWeaponNum, tempPlayer);

		_vPlayer.push_back(tempPlayer);

		//���� �ʹݿ�, ��Ʋ���� �÷��̾� ������ �ѱ� �� ���������� ������ �÷��̾���� �̿��ؼ� �ѱ�� �ɷ� �س���....
		//��¿�� ���� �̷� �������...
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
	//�� ������ ��ȣ�� 0�̸� �⺻����� �����ϰ�
	if (weaponNum == 0)
	{
		//�⺻���� �������� �����ؼ�
		weaponItem* temWeapon = new weaponItem;
		temWeapon->init(0, ITEM_WEAPON, "DefaultWeapon", "���ָ԰��ݹ����̴�", 0, 10, 100);
		tempPlayer->setDefaultWeapon(temWeapon);
	}

	if (armorNum == -1)
	{
		//�⺻ ���� ����
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
		//================= ���� ������ ===================
		//itemMother * tempItem = (itemMother*)_itemManager->getVItem()[i];
		//�����۸���Ʈ�� �ѹ��� ����������� ������ �ѹ��� ������
		if (_itemManager->getVItem()[i]->getItemNumber() == weaponNum)
		{
			//���� �������� �÷��̾� ������ ����
			weaponItem* tempItem = (weaponItem*)_itemManager->getVItem()[i];
			
			tempPlayer->setWeaponItem(tempItem);
		}
		if (_itemManager->getVItem()[i]->getItemNumber() == armorNum)
		{
			//���� �������� �÷��̾� ������ ����
			armorItem* tempItem = (armorItem*)_itemManager->getVItem()[i];

			tempPlayer->setArmor(tempItem);
		}
		if (_itemManager->getVItem()[i]->getItemNumber() == helmetNum)
		{
			//���� �������� �÷��̾� ������ ����
			armorItem* tempItem = (armorItem*)_itemManager->getVItem()[i];

			tempPlayer->setHelmet(tempItem);
		}
		if (_itemManager->getVItem()[i]->getItemNumber() == subWeapon)
		{
			//�������� �������� �÷��̾� ������ ����
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
		//�� �� �����ؾߵ�
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