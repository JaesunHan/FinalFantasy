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
	//각 플레이어들을 동적할당함 과 동시에 생성자가 호출되어 기본값으로 초기화 된다.
	_celes = new celes;
	_locke = new Locke;
	_shadow = new shadow;
	_tina = new Tina;

	_vPlayer.push_back(_celes);
	_vPlayer.push_back(_locke);
	_vPlayer.push_back(_shadow);
	_vPlayer.push_back(_tina);
	_isNewGame = false;

	if (SCENEMANAGER->findScene("뉴게임"))
	{
		//만약 새 게임을 시작하면 새로운 데이터를 파일에 저장한다
		if (SCENEMANAGER->getCurrentSceneName() == "뉴게임")
		{
			saveNewGameData();
		}
	}

	if (SCENEMANAGER->findScene("로드게임"))
	{
		//원래 했던 게임을 로드하면 파일에서 데이터를 읽어온다.
		if (SCENEMANAGER->getCurrentSceneName() == "로드게임")
		{
			loadGameData();
		}
	}

	return S_OK;
}
void playerManager::update() 
{
	// 새 게임 시작하면 saveGameData()호출
	if (SCENEMANAGER->getCurrentSceneName() == "뉴게임")
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
	
	//================================== End 그 배틀씬의 배틀플레이어들의 정보를 저장한다.====================================
}

//새 게임을 시작하면 기본적으로 생성한 플레이어들의 정보를 파일에 저장한다.
void playerManager::saveNewGameData()
{
	////먼저 newGame 클래스르르 받아온다
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

		INIDATA->iniSave(gameSaveFileName);

	}
	
}

void playerManager::loadGameData()
{
	loadGame* lg = new loadGame;
	lg = (loadGame*)SCENEMANAGER->findScene("로드게임");
	int saveFileNum = lg->getSaveFileNum();
}
