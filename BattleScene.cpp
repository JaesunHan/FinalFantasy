#include "stdafx.h"
#include "BattleScene.h"
#include "playerManager.h"
#include "worldMapScene.h"
#include "playerImproveInfo.h"
#include "itemManager.h"

BattleScene::BattleScene()
{
}


BattleScene::~BattleScene()
{

}

HRESULT BattleScene::init()
{
	//수치들 초기화
	_menuNum = 0;
	_enemyNum = 4;
	_playerSelectNum = 0;
	_itemSelectNum = 0;
	_magicSelectNum = 0;
	_messageCounter = 0;
	_victoryCounter = 0;
	_dialogueCounter = 0;
	_gameOver = 0;
	_damage = 0;
	_counterRoll = true;
	_playerTurn = false;
	_enemySelect = false;
	_playerSelect = false;
	_itemSelect = false;
	_magicSelect = false;
	_sfx01 = true;
	_sfx02 = false;
	_isDamaged = false;
	_victory = false;
	_hit = false;
	_dialogue = false;
	_changeScene = false;
	//폰트 추가
	AddFontResourceEx(
		"SDMiSaeng.ttf", 	// font file name
		FR_PRIVATE,         // font characteristics
		NULL            	// reserved
	);
	//UI이미지 추가
	IMAGEMANAGER->addImage("battleBG", ".\\image\\battlebackground\\Plains.bmp", 1200, 640, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("battleUI", ".\\image\\userInterface\\menuBackground.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("battleUI2", ".\\image\\userInterface\\menuBackground(950x128).bmp", 950, 128, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("progressBarBottom", ".\\image\\userInterface\\progressBarBottom.bmp", 150, 17, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("progressBarTop", ".\\image\\userInterface\\progressBarTop.bmp", 170, 23, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("progressBarComplete", ".\\image\\userInterface\\progressBarComplete.bmp", 150, 17, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("fingerArrowRt", ".\\image\\userInterface\\fingerArrowRt.bmp", 25, 25, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("fingerArrowLt", ".\\image\\userInterface\\fingerArrowLt.bmp", 25, 25, true, RGB(255, 0, 255));
	//플레이어 얼굴 이미지 추가
	IMAGEMANAGER->addImage("tinaFace00", ".\\image\\playerImg\\tina\\tina_face.bmp", 56, 38, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("lockeFace00", ".\\image\\playerImg\\locke\\locke_face.bmp", 56, 38, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("celesFace00", ".\\image\\playerImg\\celes\\celes_face.bmp", 56, 38, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("shadowFace00", ".\\image\\playerImg\\shadow\\shadow_face.bmp", 56, 38, true, RGB(255, 0, 255));
	//음악 추가
	SOUNDMANAGER->addSound("battleBGM", ".\\sound\\battleSound\\05 - Battle Theme.mp3", true, true);	//CH_BGM
	SOUNDMANAGER->addSound("fanfareBGM", ".\\sound\\battleSound\\06 - Fanfare.mp3", true, true);		//CH_BGM
	SOUNDMANAGER->addSound("battleMenuOpen", ".\\sound\\sfx\\battleMenuOpen.wav", false, false);		//CH_EFFECT03
	SOUNDMANAGER->addSound("menuSelectLow", ".\\sound\\sfx\\menuSelectLow.wav", false, false);			//CH_EFFECT01
	SOUNDMANAGER->addSound("monsterDeath", ".\\sound\\sfx\\monsterDeath.wav", false, false);			//CH_EFFECT02
	SOUNDMANAGER->addSound("miss", ".\\sound\\sfx\\miss.wav", false, false);							//CH_SOKKONGGU->미스시에 플레이어의 공격 사운드를 멈추기 위해
	SOUNDMANAGER->addSound("runAway", ".\\sound\\sfx\\runAway.wav", false, false);						//CH_EFFECT05
	SOUNDMANAGER->play("battleBGM", CH_BGM, 1.0f);

	tagBattleCharacters temp;
	//플레이어 동적 할당 후 벡터에 담기
	for (int i = 0; i < 4; ++i)
	{
		switch (i)
		{
		case(0):
			temp.characterType = TINA;
			temp.player = new battleTina;
			break;
		case(1):
			temp.characterType = LOCKE;
			temp.player = new battleLocke;
			break;
		case(2):
			temp.characterType = CELES;
			temp.player = new battleCeles;
			break;
		case(3):
			temp.characterType = SHADOW;
			temp.player = new battleShadow;
			break;
		}
		temp.ATBcounter = 25000 + RND->getInt(10000);
		temp.menuSelect = BATTLE_NULL;
		temp.magicSelect = 0;
		temp.itemSelect = 0;
		temp.playerSelect = 0;
		temp.turnStart = false;
		temp.selectAction = false;
		temp.attackReady = false;
		temp.isDead = false;
		_battleCharacters.push_back(temp);
	}
	//배틀 플레이어에 플레이어 데이터 복사
	_pm->loadGameData();
	_pm->setPlayerInfoToBattlePlayer();
	//최대 몬스터 랜덤 지정
	_maxMonster = RND->getInt(3) + 1;
	//에너미 동적할당 후 벡터에 담기
	for (int i = 0; i < _maxMonster; ++i)
	{
		int monsterType = RND->getInt(3);
		temp.characterType = i + 4;
		temp.ATBcounter = 0;
		temp.enemy = new guard;
		//switch (monsterType)
		//{
		//case(0):
		//	temp.enemy = new Bear;
		//	break;
		//case(1):
		//	temp.enemy = new DarkWind;
		//	break;
		//case(2):
		//	temp.enemy = new VectorPup;
		//	break;
		//}
		_battleCharacters.push_back(temp);
	}
	//에너미 클래스 init 및 플레이어 주소 어드레쓰 링크
	for (int i = 0; i < _maxMonster; ++i)
	{
		_battleCharacters[i + 4].enemy->init(350 + (240 / _maxMonster * (_maxMonster - 1)) * cosf(PI2 / _maxMonster * i + PI / 2), 350 - (240 / _maxMonster * (_maxMonster - 1)) * sinf(PI2 / _maxMonster * i + PI / 2));
		_battleCharacters[i + 4].enemy->setBattleTinaMemoryAddressLink(_battleCharacters[0].player);
		_battleCharacters[i + 4].enemy->setBattleLockeMemoryAddressLink(_battleCharacters[1].player);
		_battleCharacters[i + 4].enemy->setBattleShadowMemoryAddressLink(_battleCharacters[2].player);
		_battleCharacters[i + 4].enemy->setBattleCelesMemoryAddressLink(_battleCharacters[3].player);
	}
	//아이템 매니져에 플레이어 주소 넘기기
	_im->setBattleTinaMemoryAddressLink(_battleCharacters[0].player);
	_im->setBattleRockeMemoryAddressLink(_battleCharacters[1].player);
	_im->setBattleCelesMemoryAddressLink(_battleCharacters[2].player);
	_im->setBattleShadowMemoryAddressLink(_battleCharacters[3].player);
	//플레이어에 배틀씬 주소 넘기기 
	for (int i = 0; i < 4; ++i)
	{
		_battleCharacters[i].player->setBattleScene(this);
	}
	//플레이어 인덱스 순서에 맞게 조정
	for (int j = 0; j < 4; ++j)
	{
		for (int i = j; i < 4; ++i)
		{
			if (i != j && _battleCharacters[i].player->getPartyIdx() == j)
			{
				swap(_battleCharacters[j], _battleCharacters[i]);
				break;
			}
		}
	}
	return S_OK;
}

void BattleScene::release()
{
	SOUNDMANAGER->releaseAllSound();
	EFFECTMANAGER->release();
	for (int i = 0; i < _battleTurn.size(); ++i)
	{
		_battleTurn.pop();
	}
	_battleCharacters.clear();
}

void BattleScene::update() 
{
	ATBGauzeTimer();
	playerMenuSelect();
	updateWhenCharacterTurn();
	playerFrameUpdate();
	victoryCondition();
	soundControl();
	gameOverCondition();
	sceneChange();
}

void BattleScene::render() 
{
	IMAGEMANAGER->findImage("battleBG")->render(getMemDC());

	characterDraw();
	drawUI(); 
	renderDamage(60);
	victoryMessage();

	EFFECTMANAGER->render();
}
//배틀 타이머 돌리는 함수
void BattleScene::ATBGauzeTimer()
{
	if (_victory == false)
	{
		if (_counterRoll == true)
		{
			//ATB 카운터에 캐릭터 스피드에 따라 계산된 값을 더해준다.
			for (int i = 0; i < _battleCharacters.size(); ++i)
			{
				if (_battleCharacters[i].characterType <= 3)//플레이어일때
				{
					if (_battleCharacters[i].player->getCurHP() <= 0) continue;
					_battleCharacters[i].ATBcounter += 96 * (_battleCharacters[i].player->getSpeed() + 20) / 32;
				}
				if (_battleCharacters[i].characterType > 3)//적일때
				{
					if (_battleCharacters[i].enemy->getCurHP() <= 0) continue;
					_battleCharacters[i].ATBcounter += 96 * (_battleCharacters[i].enemy->getSpeed() + 20) / 32;
				}
			}
			//타이머가 차면 에너미를 큐에 넣어둔다
			for (int i = 4; i < _battleCharacters.size(); ++i)
			{
				if (_battleCharacters[i].ATBcounter > 65535 && _battleCharacters[i].turnStart == false)
				{
					_battleTurn.push(&_battleCharacters[i]);
					_battleCharacters[i].turnStart = true;
					_battleCharacters[i].enemy->setTurnEnd(false);
				}
			}
		}
	}
}
//캐릭터의 턴이 되면 해당 캐릭터의 업데이트를 돌리는 함수
void BattleScene::updateWhenCharacterTurn()
{
	if (_battleTurn.size() > 0 && _battleTurn.front()->characterType <= 3)
	{
		for (int i = 0; i < 1; ++i)
		{
			//플레이어가 죽었으면 턴을 넘김
			if (_battleTurn.front()->player->getCurHP() <= 0)
			{
				_battleTurn.front()->ATBcounter = 0;
				_battleTurn.front()->turnStart = false;
				_battleTurn.front()->selectAction = false;
				_battleTurn.front()->attackReady = false;
				_battleTurn.front()->menuSelect = BATTLE_NULL;
				_battleTurn.pop();
				break;
			}
			//플레이어 선택이 공격일 경우
			if (_battleTurn.front()->menuSelect == BATTLE_ATTACK)
			{
				//플레이어 공격 전 에너미 선택 처리
				if (_battleTurn.front()->attackReady == false)
				{
					//플레이어에 선택한 에너미 주소 할당 //해당 에너미가 죽었을 경우엔 살아있는애로 할당
					if (_battleTurn.front()->enemy != NULL)
					{
						if (_battleTurn.front()->enemy->getCurHP() > 0)
						{
							_battleTurn.front()->player->setTargetEnemy(_battleTurn.front()->enemy);
						}
						else
						{
							for (int i = 0; i < _maxMonster; ++i)
							{
								if (_battleCharacters[i + 4].enemy->getCurHP() > 0)
								{
									_battleTurn.front()->enemy = _battleCharacters[i + 4].enemy;
									_battleTurn.front()->player->setTargetEnemy(_battleCharacters[i + 4].enemy);
									break;
								}
							}
						}
					}
					//플레이어 상태를 어택으로
					if (_battleTurn.front()->player->getStatus() == BATTLE_PLAYER_ATTACK_STANDBY) _battleTurn.front()->player->setStatus(BATTLE_PLAYER_ATTACK);
					//플레이어 공격 준비 완료
					_battleTurn.front()->attackReady = true;
				}
				_battleTurn.front()->player->update();
				//턴 종료시 큐에서 삭제
				if (_battleTurn.front()->player->getTurnEnd() == true)
				{
					_battleTurn.front()->ATBcounter = 0;
					_battleTurn.front()->turnStart = false;
					_battleTurn.front()->selectAction = false;
					_battleTurn.front()->attackReady = false;
					_battleTurn.front()->menuSelect = BATTLE_NULL;
					if (_victory == false) _battleTurn.pop();
				}
				break;
			}
			//플레이어 선택이 마법일 경우
			if (_battleTurn.front()->menuSelect == BATTLE_MAGIC_ATTACK || _battleTurn.front()->menuSelect == BATTLE_MAGIC_HEAL)
			{
				//플레이어 공격 전 에너미 선택 처리
				if (_battleTurn.front()->attackReady == false && _battleTurn.front()->menuSelect == BATTLE_MAGIC_ATTACK)
				{
					//플레이어에 선택한 에너미 주소 할당 //해당 에너미가 죽었을 경우엔 살아있는애로 할당
					if (_battleTurn.front()->enemy != NULL)
					{
						if (_battleTurn.front()->enemy->getCurHP() > 0)
						{
							_battleTurn.front()->player->setMEnemyTarget(_battleTurn.front()->enemy);
						}
						else
						{
							for (int i = 0; i < _maxMonster; ++i)
							{
								if (_battleCharacters[i + 4].enemy->getCurHP() > 0)
								{
									_battleTurn.front()->enemy = _battleCharacters[i + 4].enemy;
									_battleTurn.front()->player->setMEnemyTarget(_battleCharacters[i + 4].enemy);
									break;
								}
							}
						}
					}
					//플레이어 상태를 마법 어택으로
					if (_battleTurn.front()->player->getStatus() == BATTLE_PLAYER_MAGIC_ATTACK_STANDBY) _battleTurn.front()->player->setStatus(BATTLE_PLAYER_MAGIC_ATTACK);
					//플레이어 공격 준비 완료
					_battleTurn.front()->attackReady = true;
				}
				else if (_battleTurn.front()->attackReady == false && _battleTurn.front()->menuSelect == BATTLE_MAGIC_HEAL)
				{
					//플레이어 마법 대상 주소 넘기기
					_battleTurn.front()->player->setMAllyTarget(_battleCharacters[_battleTurn.front()->playerSelect].player);
					//플레이어 상태를 마법 어택으로
					if (_battleTurn.front()->player->getStatus() == BATTLE_PLAYER_MAGIC_ATTACK_STANDBY) _battleTurn.front()->player->setStatus(BATTLE_PLAYER_MAGIC_ATTACK);
					//플레이어 공격 준비 완료
					_battleTurn.front()->attackReady = true;
				}
				_battleTurn.front()->player->update();
				//턴 종료시 큐에서 삭제
				if (_battleTurn.front()->player->getTurnEnd() == true)
				{
					_battleTurn.front()->ATBcounter = 0;
					_battleTurn.front()->turnStart = false;
					_battleTurn.front()->selectAction = false;
					_battleTurn.front()->attackReady = false;
					_battleTurn.front()->menuSelect = BATTLE_NULL;
					if (_victory == false) _battleTurn.pop();
				}
				break;
			}
			//플레이어 선택이 아이템일 경우
			if (_battleTurn.front()->menuSelect == BATTLE_ITEM)
			{
				if (_battleTurn.front()->attackReady == false)
				{
					//플레이어 마법 대상 주소 넘기기
					_battleTurn.front()->player->setMAllyTarget(_battleCharacters[_battleTurn.front()->playerSelect].player);
					//플레이어 상태를 마법 어택으로
					if (_battleTurn.front()->player->getStatus() == BATTLE_PLAYER_ATTACK_STANDBY) _battleTurn.front()->player->setStatus(BATTLE_PLAYER_ITEM);
					//플레이어 공격 준비 완료
					_battleTurn.front()->attackReady = true;
				}
				_battleTurn.front()->player->update();
				//턴 종료시 큐에서 삭제
				if (_battleTurn.front()->player->getTurnEnd() == true)
				{
					_battleTurn.front()->ATBcounter = 0;
					_battleTurn.front()->turnStart = false;
					_battleTurn.front()->selectAction = false;
					_battleTurn.front()->attackReady = false;
					_battleTurn.front()->menuSelect = BATTLE_NULL;
					if (_victory == false) _battleTurn.pop();
				}
				break;
			}
			//플레이어 선택이 도망일 경우
			if (_battleTurn.front()->menuSelect == BATTLE_ESCAPE)
			{
				if (RND->getInt(3) == 0)	//도망 성공
				{
					SOUNDMANAGER->play("runAway", CH_EFFECT05, 1.0f);
					while (1)
					{
						if (SOUNDMANAGER->isPlaySound(CH_EFFECT05) == false)
						{
							break;
						}
					}
					((worldMapScene*)SCENEMANAGER->findScene("월드맵씬"))->setIsEscape(true);
					_changeScene = true;
				}
				else						//도망 실패
				{
					_menuNum = 0;
					_battleTurn.front()->player->setStatus(BATTLE_PLAYER_IDLE);
					_battleTurn.front()->ATBcounter = 0;
					_battleTurn.front()->turnStart = false;
					_battleTurn.front()->selectAction = false;
					_battleTurn.front()->attackReady = false;
					_battleTurn.front()->menuSelect = BATTLE_NULL;
					_battleTurn.pop();
				}
				break;
			}
		}
	}
	//적의 턴일 때
	if (_battleTurn.size() > 0 && _battleTurn.front()->characterType > 3)
	{
		//적이 죽었으면 턴을 넘김
		if (_battleTurn.front()->enemy->getCurHP() <= 0)
		{
			_battleTurn.pop();
		}
		else
		{
			//적 공격 전 사전준비
			if (_battleTurn.front()->attackReady == false)
			{
				int targetPlayer = RND->getInt(4);
				for (int i = 0; i < 4; ++i)
				{
					if (_battleCharacters[targetPlayer].player->getCurHP() <= 0)
					{
						targetPlayer++;
						if (targetPlayer > 3) targetPlayer = 0;
					}
					else
					{
						break;
					}
				}
				_battleTurn.front()->enemy->setTargetMemoryAddressLink(_battleCharacters[targetPlayer].player);
				_battleTurn.front()->attackReady = true;
			}
			//적 턴에 업데이트 돌림
			_battleTurn.front()->enemy->update();
			//턴 종료시 큐에서 삭제
			if (_battleTurn.front()->enemy->getTurnEnd() == true)
			{
				_battleTurn.front()->ATBcounter = 0;
				_battleTurn.front()->turnStart = false;
				_battleTurn.front()->attackReady = false;
				if (_gameOver == 0) _battleTurn.pop();
			}
		}
	}
}
//플레이어 메뉴 선택 함수
void BattleScene::playerMenuSelect()
{
	if (_victory == false)
	{
		//플레이어 ATB 카운터가 차면 플레이어 메뉴 선택
		for (int i = 0; i < 4; ++i)
		{
			if (_battleCharacters[i].selectAction == true) continue;
			if (_battleCharacters[i].selectAction == false && _battleCharacters[i].ATBcounter > 65535) _battleCharacters[i].ATBcounter = 65536;
			if (_battleCharacters[i].ATBcounter > 65535 && _playerTurn == false)
			{
				_sfx01 = false;
				_playerTurn = true;
				_menuNum = 0;
				_currentTurn = i;
				_battleCharacters[i].player->setTurnEnd(false);
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			if (_playerSelect == true)
			{
				_playerSelectNum--;
				if (_playerSelectNum < 0) _playerSelectNum = 3;
				SOUNDMANAGER->play("menuSelectLow", CH_EFFECT01, 1.0f);
				if (_menuNum == BATTLE_MAGIC)
				{
					if (_battleCharacters[_currentTurn].player->getMyUsableMagic()[_magicSelectNum]->getIsRevive() == true)
					{
						for (int i = 0; i < 4; ++i)
						{
							if (_battleCharacters[_playerSelectNum].player->getCurHP() > 0)
							{
								_playerSelectNum--;
								if (_playerSelectNum < 0) _playerSelectNum = 3;
							}
							else
							{
								break;
							}
						}
					}
					if (_battleCharacters[_currentTurn].player->getMyUsableMagic()[_magicSelectNum]->getIsHeal() == true)
					{
						for (int i = 0; i < 4; ++i)
						{
							if (_battleCharacters[_playerSelectNum].player->getCurHP() <= 0)
							{
								_playerSelectNum--;
								if (_playerSelectNum < 0) _playerSelectNum = 3;
							}
							else
							{
								break;
							}
						}
					}
				}
				else if (_menuNum == BATTLE_ITEM)
				{
					if (((expendablesItem*)_im->getVItem()[_im->getItemVNum(_itemSelectNum)])->getIsReviveItem() == true)
					{
						for (int i = 0; i < 4; ++i)
						{
							if (_battleCharacters[_playerSelectNum].player->getCurHP() > 0)
							{
								_playerSelectNum--;
								if (_playerSelectNum < 0) _playerSelectNum = 3;
							}
							else
							{
								break;
							}
						}
					}
					else
					{
						for (int i = 0; i < 4; ++i)
						{
							if (_battleCharacters[_playerSelectNum].player->getCurHP() <= 0)
							{
								_playerSelectNum--;
								if (_playerSelectNum < 0) _playerSelectNum = 3;
							}
							else
							{
								break;
							}
						}
					}
				}
			}
			else if (_enemySelect == true)
			{
				_enemyNum--;
				if (_enemyNum < 4) _enemyNum = _maxMonster + 3;
				SOUNDMANAGER->play("menuSelectLow", CH_EFFECT01, 1.0f);
				for (int i = 0; i < _maxMonster; ++i)
				{
					if (_battleCharacters[_enemyNum].enemy->getCurHP() <= 0)
					{
						_enemyNum--;
						if (_enemyNum < 4) _enemyNum = _maxMonster + 3;
					}
					else
					{
						break;
					}
				}
			}
			else if (_magicSelect == true)
			{
				if (_magicSelectNum > 0) _magicSelectNum--;
				SOUNDMANAGER->play("menuSelectLow", CH_EFFECT01, 1.0f);
			}
			else if (_itemSelect == true)
			{
				if (_itemSelectNum > 0) _itemSelectNum--;
				SOUNDMANAGER->play("menuSelectLow", CH_EFFECT01, 1.0f);
			}
			else if (_playerTurn == true)
			{
				_menuNum--;
				SOUNDMANAGER->play("menuSelectLow", CH_EFFECT01, 1.0f);
				if (_menuNum < 0) _menuNum = 4;
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			if (_playerSelect == true)
			{
				_playerSelectNum++;
				if (_playerSelectNum > 3) _playerSelectNum = 0;
				SOUNDMANAGER->play("menuSelectLow", CH_EFFECT01, 1.0f);
				if (_menuNum == BATTLE_MAGIC)
				{
					if (_battleCharacters[_currentTurn].player->getMyUsableMagic()[_magicSelectNum]->getIsRevive() == true)
					{
						for (int i = 0; i < 4; ++i)
						{
							if (_battleCharacters[_playerSelectNum].player->getCurHP() > 0)
							{
								_playerSelectNum++;
								if (_playerSelectNum > 3) _playerSelectNum = 0;
							}
							else
							{
								break;
							}
						}
					}
					if (_battleCharacters[_currentTurn].player->getMyUsableMagic()[_magicSelectNum]->getIsHeal() == true)
					{
						for (int i = 0; i < 4; ++i)
						{
							if (_battleCharacters[_playerSelectNum].player->getCurHP() <= 0)
							{
								_playerSelectNum++;
								if (_playerSelectNum > 3) _playerSelectNum = 0;
							}
							else
							{
								break;
							}
						}
					}
				}
				else if (_menuNum == BATTLE_ITEM)
				{
					if (((expendablesItem*)_im->getVItem()[_im->getItemVNum(_itemSelectNum)])->getIsReviveItem() == true)
					{
						for (int i = 0; i < 4; ++i)
						{
							if (_battleCharacters[_playerSelectNum].player->getCurHP() > 0)
							{
								_playerSelectNum--;
								if (_playerSelectNum < 0) _playerSelectNum = 3;
							}
							else
							{
								break;
							}
						}
					}
					else
					{
						for (int i = 0; i < 4; ++i)
						{
							if (_battleCharacters[_playerSelectNum].player->getCurHP() <= 0)
							{
								_playerSelectNum--;
								if (_playerSelectNum < 0) _playerSelectNum = 3;
							}
							else
							{
								break;
							}
						}
					}
				}
			}
			else if (_enemySelect == true)
			{
				_enemyNum++;
				if (_enemyNum > _maxMonster + 3) _enemyNum = 4;
				SOUNDMANAGER->play("menuSelectLow", CH_EFFECT01, 1.0f);
				for (int i = 0; i < _maxMonster; ++i)
				{
					if (_battleCharacters[_enemyNum].enemy->getCurHP() <= 0)
					{
						_enemyNum++;
						if (_enemyNum > _maxMonster + 3) _enemyNum = 4;
					}
					else
					{
						break;
					}
				}
			}
			else if (_magicSelect == true)
			{
				if (_magicSelectNum < _battleCharacters[_currentTurn].player->getMyUsableMagic().size() - 1) _magicSelectNum++;
				SOUNDMANAGER->play("menuSelectLow", CH_EFFECT01, 1.0f);
			}
			else if (_itemSelect == true)
			{
				if (_itemSelectNum < _im->getItemInventorySize() - 1) _itemSelectNum++;
				SOUNDMANAGER->play("menuSelectLow", CH_EFFECT01, 1.0f);
			}
			else if (_playerTurn == true)
			{
				_menuNum++;
				SOUNDMANAGER->play("menuSelectLow", CH_EFFECT01, 1.0f);
				if (_menuNum > 4) _menuNum = 0;
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_BACK))
		{
			if (_playerSelect == true)
			{
				_playerSelectNum = 0;
				SOUNDMANAGER->play("menuSelectLow", CH_EFFECT01, 1.0f);
				_counterRoll = true;
				_playerSelect = false;
				_itemSelect = false;
				_magicSelect = false;
			}
			else if (_enemySelect == true)
			{
				_enemyNum = 4;
				SOUNDMANAGER->play("menuSelectLow", CH_EFFECT01, 1.0f);
				_enemySelect = false;
			}
			else if (_magicSelect == true)
			{
				_magicSelectNum = 0;
				SOUNDMANAGER->play("menuSelectLow", CH_EFFECT01, 1.0f);
				_counterRoll = true;
				_magicSelect = false;
			}
			else if (_itemSelect == true)
			{
				_itemSelectNum = 0;
				SOUNDMANAGER->play("menuSelectLow", CH_EFFECT01, 1.0f);
				_counterRoll = true;
				_itemSelect = false;
			}
			else if (_playerTurn == true)
			{
				_menuNum = 0;
				_sfx01 = false;
				while (1)
				{
					_currentTurn++;
					if (_currentTurn > 3) _currentTurn = 0;
					if (_battleCharacters[_currentTurn].selectAction == true) continue;
					if (_battleCharacters[_currentTurn].ATBcounter < 65535) continue;
					else break;
				}
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_TAB))
		{
			if (_playerTurn == true)
			{
				_menuNum = 0;
				_counterRoll = true;
				_playerSelect = false;
				_enemySelect = false;
				_itemSelect = false;
				_magicSelect = false;
				_sfx01 = false;
				while (1)
				{
					_currentTurn++;
					if (_currentTurn > 3) _currentTurn = 0;
					if (_battleCharacters[_currentTurn].selectAction == true) continue;
					if (_battleCharacters[_currentTurn].ATBcounter < 65535) continue;
					else break;
				}
			}
		}
		if (_playerTurn == true && _battleCharacters[_currentTurn].player->getCurHP() <= 0)
		{
			_menuNum = 0;
			_counterRoll = true;
			_playerSelect = false;
			_enemySelect = false;
			_itemSelect = false;
			_magicSelect = false;
			_playerTurn = false;
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		if (_victory == false)
		{
			if (_playerSelect == true)
			{
				switch (_menuNum)
				{
				case(BATTLE_ATTACK):
					break;
				case(BATTLE_MAGIC):
					_battleCharacters[_currentTurn].playerSelect = _playerSelectNum;
					_battleCharacters[_currentTurn].magicSelect = _magicSelectNum;
					_battleCharacters[_currentTurn].player->setCurMP(_battleCharacters[_currentTurn].player->getCurMP() - _battleCharacters[_currentTurn].player->getMyUsableMagic()[_magicSelectNum]->getManaCost());
					_battleCharacters[_currentTurn].player->setStatus(BATTLE_PLAYER_MAGIC_ATTACK_STANDBY);
					_battleCharacters[_currentTurn].selectAction = true;
					_battleCharacters[_currentTurn].menuSelect = BATTLE_MAGIC_HEAL;
					_battleTurn.push(&_battleCharacters[_currentTurn]);
					_magicSelectNum = 0;
					_playerSelectNum = 0;
					_magicSelect = false;
					_playerSelect = false;
					_playerTurn = false;
					_counterRoll = true;
					break;
				case(BATTLE_SKILL):
					break;
				case(BATTLE_ITEM):
					_battleCharacters[_currentTurn].itemSelect = _itemSelectNum;
					_battleCharacters[_currentTurn].player->setStatus(BATTLE_PLAYER_ATTACK_STANDBY);
					_battleCharacters[_currentTurn].selectAction = true;
					_battleCharacters[_currentTurn].menuSelect = BATTLE_ITEM;
					_battleTurn.push(&_battleCharacters[_currentTurn]);
					_itemSelectNum = 0;
					_playerSelectNum = 0;
					_itemSelect = false;
					_playerSelect = false;
					_playerTurn = false;
					_counterRoll = true;
					break;
				case(BATTLE_ESCAPE):
					break;
				}
			}
			else if (_enemySelect == true || _itemSelect == true)
			{
				SOUNDMANAGER->play("menuSelectLow", CH_EFFECT01, 1.0f);
				_battleCharacters[_currentTurn].enemy = _battleCharacters[_enemyNum].enemy;
				switch (_menuNum)
				{
				case(BATTLE_ATTACK):
					_battleCharacters[_currentTurn].player->setStatus(BATTLE_PLAYER_ATTACK_STANDBY);
					_battleCharacters[_currentTurn].selectAction = true;
					_battleCharacters[_currentTurn].menuSelect = BATTLE_ATTACK;
					_battleTurn.push(&_battleCharacters[_currentTurn]);
					_enemyNum = 4;
					_enemySelect = false;
					_playerTurn = false;
					break;
				case(BATTLE_MAGIC):
					_battleCharacters[_currentTurn].magicSelect = _magicSelectNum;
					_battleCharacters[_currentTurn].player->setStatus(BATTLE_PLAYER_MAGIC_ATTACK_STANDBY);
					_battleCharacters[_currentTurn].player->setCurMP(_battleCharacters[_currentTurn].player->getCurMP() - _battleCharacters[_currentTurn].player->getMyUsableMagic()[_magicSelectNum]->getManaCost());
					_battleCharacters[_currentTurn].selectAction = true;
					_battleCharacters[_currentTurn].menuSelect = BATTLE_MAGIC_ATTACK;
					_battleTurn.push(&_battleCharacters[_currentTurn]);
					_enemyNum = 4;
					_magicSelectNum = 0;
					_magicSelect = false;
					_enemySelect = false;
					_playerTurn = false;
					_counterRoll = true;
					break;
				case(BATTLE_SKILL):
					break;
				case(BATTLE_ITEM):
					if (((expendablesItem*)_im->getVItem()[_im->getItemVNum(_itemSelectNum)])->getIsInBattle() == true)
					{
						_playerSelectNum = 0;
						if (((expendablesItem*)_im->getVItem()[_im->getItemVNum(_itemSelectNum)])->getIsReviveItem() == true)
						{
							for (int i = 0; i < 4; ++i)
							{
								if (_battleCharacters[_playerSelectNum].player->getCurHP() > 0)
								{
									_playerSelectNum--;
									if (_playerSelectNum < 0) _playerSelectNum = 3;
									if (i == 3)
									{
										_playerSelect = false;
									}
								}
								else
								{
									_playerSelect = true;
									break;
								}
							}
						}
						else
						{
							for (int i = 0; i < 4; ++i)
							{
								if (_battleCharacters[_playerSelectNum].player->getCurHP() <= 0)
								{
									_playerSelectNum--;
									if (_playerSelectNum < 0) _playerSelectNum = 3;
									if (i == 3)
									{
										_playerSelect = false;
									}
								}
								else
								{
									_playerSelect = true;
									break;
								}
							}
						}
					}
					break;
				case(BATTLE_ESCAPE):
					break;
				}
			}
			else if (_magicSelect == true)
			{
				SOUNDMANAGER->play("menuSelectLow", CH_EFFECT01, 1.0f);
				_battleCharacters[_currentTurn].player->setSelectMagic(_battleCharacters[_currentTurn].player->getMyUsableMagic()[_magicSelectNum]);
				if (_battleCharacters[_currentTurn].player->getMyUsableMagic()[_magicSelectNum]->getIsRevive() == true)// && _battleCharacters[_currentTurn].player->getMyUsableMagic()[_magicSelectNum]->getManaCost() <= _battleCharacters[_currentTurn].player->getCurMP())
				{
					_playerSelectNum = 0;
					for (int i = 0; i < 4; ++i)
					{
						if (_battleCharacters[_playerSelectNum].player->getCurHP() > 0)
						{
							_playerSelectNum++;
							if (_playerSelectNum > 3) _playerSelectNum = 0;
						}
						else
						{
							_counterRoll = false;
							_playerSelect = true;
							break;
						}
						_counterRoll = true;
						_playerSelect = false;
						_magicSelect = false;
					}
				}
				else if (_battleCharacters[_currentTurn].player->getMyUsableMagic()[_magicSelectNum]->getIsHeal() == true)// && _battleCharacters[_currentTurn].player->getMyUsableMagic()[_magicSelectNum]->getManaCost() <= _battleCharacters[_currentTurn].player->getCurMP())
				{
					_playerSelectNum = 0;
					for (int i = 0; i < 4; ++i)
					{
						if (_battleCharacters[_playerSelectNum].player->getCurHP() <= 0)
						{
							_playerSelectNum++;
							if (_playerSelectNum > 3) _playerSelectNum = 0;
						}
						else
						{
							_counterRoll = false;
							_playerSelect = true;
							break;
						}
						_counterRoll = true;
						_playerSelect = false;
						_magicSelect = false;
					}
				}
				else if (_battleCharacters[_currentTurn].player->getMyUsableMagic()[_magicSelectNum]->getIsHeal() == false && _battleCharacters[_currentTurn].player->getMyUsableMagic()[_magicSelectNum]->getManaCost() <= _battleCharacters[_currentTurn].player->getCurMP())
				{
					_enemySelect = true;
					_enemyNum = 4;
					for (int i = 0; i < _maxMonster; ++i)
					{
						if (_battleCharacters[_enemyNum].enemy->getCurHP() <= 0)
						{
							_enemyNum++;
							if (_enemyNum > _maxMonster + 3) _enemyNum = 4;
						}
						else
						{
							break;
						}
					}
				}
			}
			else if (_playerTurn == true)
			{
				SOUNDMANAGER->play("menuSelectLow", CH_EFFECT01, 1.0f);
				switch (_menuNum)
				{
				case(BATTLE_ATTACK):
					_enemySelect = true;
					_enemyNum = 4;
					for (int i = 0; i < _maxMonster; ++i)
					{
						if (_battleCharacters[_enemyNum].enemy->getCurHP() <= 0)
						{
							_enemyNum++;
							if (_enemyNum > _maxMonster + 3) _enemyNum = 4;
						}
						else
						{
							break;
						}
					}
					break;
				case(BATTLE_MAGIC):
					_counterRoll = false;
					_magicSelect = true;
					break;
				case(BATTLE_SKILL):
					break;
				case(BATTLE_ITEM):
					_counterRoll = false;
					_itemSelect = true;
					break;
				case(BATTLE_ESCAPE):
					_battleCharacters[_currentTurn].player->setStatus(BATTLE_PLAYER_ATTACK_STANDBY);
					_battleCharacters[_currentTurn].selectAction = true;
					_battleCharacters[_currentTurn].menuSelect = BATTLE_ESCAPE;
					_battleTurn.push(&_battleCharacters[_currentTurn]);
					_enemySelect = false;
					_playerTurn = false;
					break;
				}
			}
		}
		else if (_victory == true)
		{
			_dialogueCounter++;
			if (_dialogueCounter == 4 || _dialogueCounter == 7 || _dialogueCounter == 10 || _dialogueCounter == 13)
			{
				_dialogueCounter += 2;
			}
			_messageCounter = 0;
		}
	}
	
	if (KEYMANAGER->isOnceKeyDown('R'))
	{
		_im->changeItemNumber("메가엘릭서", 5);
	}
	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		_im->useItemInBattle(ITEM_TINA, 1);
	}
}
//캐릭터 그리는 함수
void BattleScene::characterDraw()
{
	//플레이어 및 에너미 랜더
	for (int i = 0; i < _battleCharacters.size(); ++i)
	{
		if (_battleCharacters[i].characterType > 3)
		{
			if (_battleCharacters[i].enemy->getCurHP() <= 0 && _battleCharacters[i].isDead == false)
			{
				if (_battleCharacters[i].enemy->getAlpha() == 255)
				{
					SOUNDMANAGER->play("monsterDeath", CH_EFFECT02, 1.0f);
				}
				_battleCharacters[i].enemy->setAlpha(_battleCharacters[i].enemy->getAlpha() - 15);
				if (_battleCharacters[i].enemy->getAlpha() <= 5)
				{
					_battleCharacters[i].isDead = true;
				}
			}
			if (_battleCharacters[i].isDead == true) continue;
			_battleCharacters[i].enemy->render();
			char enemyHp[128];
			wsprintf(enemyHp, "%d", _battleCharacters[i].enemy->getCurHP());
			TextOut(getMemDC(), _battleCharacters[i].enemy->getX(), _battleCharacters[i].enemy->getY(), enemyHp, strlen(enemyHp));
		}
		if (_battleCharacters[i].characterType <= 3)
		{
			_battleCharacters[i].player->render();
		}
	}
}
//UI 그리는 함수
void BattleScene::drawUI()
{
	SetTextColor(getMemDC(), RGB(255, 255, 255));
	//UI 랜더
	for (int i = 0; i < 4; ++i)
	{
		IMAGEMANAGER->findImage("battleUI")->enlargeRender(getMemDC(), WINSIZEX - 250, 160 * i, 250, 160);
		RECT nameRC = { WINSIZEX - 235, 160 * i + 35, WINSIZEX - 100, 160 * i + 65 };
		RECT hpRC = { WINSIZEX - 200, 160 * i + 80, WINSIZEX - 15, 160 * i + 100 };
		RECT mpRC = { WINSIZEX - 200, 160 * i + 100, WINSIZEX - 15, 160 * i + 120 };
		char hpStr[128];
		char mpStr[128];
		wsprintf(hpStr, "체력 : %d / %d", _battleCharacters[i].player->getCurHP(), _battleCharacters[i].player->getMaxHP());
		wsprintf(mpStr, "마력 : %d / %d", _battleCharacters[i].player->getCurMP(), _battleCharacters[i].player->getMaxMP());
		switch (_battleCharacters[i].characterType)
		{
		case(TINA):
			IMAGEMANAGER->findImage("tinaFace00")->enlargeRender(getMemDC(), WINSIZEX - 100, 160 * i + 20, 84, 57);
			drawText(30, "소꽁구", nameRC, DT_CENTER);
			drawText(20, hpStr, hpRC, DT_LEFT);
			drawText(20, mpStr, mpRC, DT_LEFT);
			break;
		case(LOCKE):
			IMAGEMANAGER->findImage("lockeFace00")->enlargeRender(getMemDC(), WINSIZEX - 100, 160 * i + 20, 84, 57);
			drawText(30, "로크", nameRC, DT_CENTER);
			drawText(20, hpStr, hpRC, DT_LEFT);
			drawText(20, mpStr, mpRC, DT_LEFT);
			break;
		case(CELES):
			IMAGEMANAGER->findImage("celesFace00")->enlargeRender(getMemDC(), WINSIZEX - 100, 160 * i + 20, 84, 57);
			drawText(30, "세리스", nameRC, DT_CENTER);
			drawText(20, hpStr, hpRC, DT_LEFT);
			drawText(20, mpStr, mpRC, DT_LEFT);
			break;
		case(SHADOW):
			IMAGEMANAGER->findImage("shadowFace00")->enlargeRender(getMemDC(), WINSIZEX - 100, 160 * i + 20, 84, 57);
			drawText(30, "쉐도우", nameRC, DT_CENTER);
			drawText(20, hpStr, hpRC, DT_LEFT);
			drawText(20, mpStr, mpRC, DT_LEFT);
			break;
		}
		//프로그레스 바 랜더
		if (_battleCharacters[i].ATBcounter > 65535)
		{
			IMAGEMANAGER->findImage("progressBarComplete")->enlargeRender(getMemDC(), WINSIZEX - 197, 160 * i + 121, 144, 17);
		}
		else
		{
			IMAGEMANAGER->findImage("progressBarBottom")->enlargeRender(getMemDC(), WINSIZEX - 197, 160 * i + 121, 144 * _battleCharacters[i].ATBcounter / 65536, 17);
		}
		IMAGEMANAGER->findImage("progressBarTop")->render(getMemDC(), WINSIZEX - 210, 160 * i + 120);
		//배틀 메뉴 랜더
		newFont = CreateFont(30, 0, 0, 0, 1000, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("Sandoll 미생"));
		oldFont = (HFONT)SelectObject(getMemDC(), newFont);
		if (_playerSelect == true)
		{
			IMAGEMANAGER->findImage("fingerArrowRt")->render(getMemDC(), _battleCharacters[_playerSelectNum].player->getPosX() - 30, _battleCharacters[_playerSelectNum].player->getPosY() + 20);
		}
		else if (_enemySelect == true)
		{
			IMAGEMANAGER->findImage("fingerArrowLt")->render(getMemDC(), _battleCharacters[_enemyNum].enemy->getX() + _battleCharacters[_enemyNum].enemy->getImageWidth() / 2, _battleCharacters[_enemyNum].enemy->getY());
		}
		else if (i == _currentTurn && _magicSelect == true)
		{
			char magicName[5][64];
			char magicMP[5][16];
			RECT itemRC[5];
			itemRC[0] = { WINSIZEX - 250, 160 * i + 5, WINSIZEX - 115, 160 * i + 35 };
			itemRC[1] = { WINSIZEX - 250, 160 * i + 35, WINSIZEX - 115, 160 * i + 65 };
			itemRC[2] = { WINSIZEX - 250, 160 * i + 65, WINSIZEX - 115, 160 * i + 95 };
			itemRC[3] = { WINSIZEX - 250, 160 * i + 95, WINSIZEX - 115, 160 * i + 125 };
			itemRC[4] = { WINSIZEX - 250, 160 * i + 125, WINSIZEX - 115, 160 * i + 155 };
			if (_magicSelectNum > 1)
			{
				wsprintf(magicName[0], _battleCharacters[_currentTurn].player->getMyUsableMagic()[_magicSelectNum - 2]->getMagicName());
				wsprintf(magicMP[0], "%d", _battleCharacters[_currentTurn].player->getMyUsableMagic()[_magicSelectNum - 2]->getManaCost());
			}
			if (_magicSelectNum > 0)
			{
				wsprintf(magicName[1], _battleCharacters[_currentTurn].player->getMyUsableMagic()[_magicSelectNum - 1]->getMagicName());
				wsprintf(magicMP[1], "%d", _battleCharacters[_currentTurn].player->getMyUsableMagic()[_magicSelectNum - 1]->getManaCost());
			}
			wsprintf(magicName[2], _battleCharacters[_currentTurn].player->getMyUsableMagic()[_magicSelectNum]->getMagicName());
			wsprintf(magicMP[2], "%d", _battleCharacters[_currentTurn].player->getMyUsableMagic()[_magicSelectNum]->getManaCost());
			if (_magicSelectNum + 1 <  _battleCharacters[_currentTurn].player->getMyUsableMagic().size())
			{
				wsprintf(magicName[3], _battleCharacters[_currentTurn].player->getMyUsableMagic()[_magicSelectNum + 1]->getMagicName());
				wsprintf(magicMP[3], "%d", _battleCharacters[_currentTurn].player->getMyUsableMagic()[_magicSelectNum + 1]->getManaCost());
			}
			if (_magicSelectNum + 2 <  _battleCharacters[_currentTurn].player->getMyUsableMagic().size())
			{
				wsprintf(magicName[4], _battleCharacters[_currentTurn].player->getMyUsableMagic()[_magicSelectNum + 2]->getMagicName());
				wsprintf(magicMP[4], "%d", _battleCharacters[_currentTurn].player->getMyUsableMagic()[_magicSelectNum + 2]->getManaCost());
			}
			switch (_battleCharacters[_currentTurn].characterType)
			{
			case(TINA):
				IMAGEMANAGER->findImage("battleUI")->enlargeRender(getMemDC(), WINSIZEX - 300, 160 * i, 200, 160);
				break;
			case(LOCKE):
				IMAGEMANAGER->findImage("battleUI")->enlargeRender(getMemDC(), WINSIZEX - 300, 160 * i, 200, 160);
				break;
			case(CELES):
				IMAGEMANAGER->findImage("battleUI")->enlargeRender(getMemDC(), WINSIZEX - 300, 160 * i, 200, 160);
				break;
			case(SHADOW):
				IMAGEMANAGER->findImage("battleUI")->enlargeRender(getMemDC(), WINSIZEX - 300, 160 * i, 200, 160);
				break;
			}
			for (int j = 0; j < 5; ++j)
			{
				drawText(30, magicName[j], itemRC[j], DT_LEFT);
				drawText(30, magicMP[j], itemRC[j], DT_RIGHT);
			}
			IMAGEMANAGER->findImage("fingerArrowRt")->render(getMemDC(), WINSIZEX - 290, 160 * i + 5 + 60);
		}
		else if (i == _currentTurn && _itemSelect == true)
		{
			char itemName[5][64];
			char itemCount[5][16];
			RECT itemRC[5];
			itemRC[0] = { WINSIZEX - 250, 160 * i + 5, WINSIZEX - 115, 160 * i + 35 };
			itemRC[1] = { WINSIZEX - 250, 160 * i + 35, WINSIZEX - 115, 160 * i + 65 };
			itemRC[2] = { WINSIZEX - 250, 160 * i + 65, WINSIZEX - 115, 160 * i + 95 };
			itemRC[3] = { WINSIZEX - 250, 160 * i + 95, WINSIZEX - 115, 160 * i + 125 };
			itemRC[4] = { WINSIZEX - 250, 160 * i + 125, WINSIZEX - 115, 160 * i + 155 };
			if (_itemSelectNum > 1)
			{
				wsprintf(itemName[0], _im->getVItem()[_im->getItemVNum(_itemSelectNum - 2)]->getItemName());
				wsprintf(itemCount[0], "%d", _im->getItemCount(_itemSelectNum - 2));
			}
			if (_itemSelectNum > 0)
			{
				wsprintf(itemName[1], _im->getVItem()[_im->getItemVNum(_itemSelectNum - 1)]->getItemName());
				wsprintf(itemCount[1], "%d", _im->getItemCount(_itemSelectNum - 1));
			}
			wsprintf(itemName[2], _im->getVItem()[_im->getItemVNum(_itemSelectNum)]->getItemName());
			wsprintf(itemCount[2], "%d", _im->getItemCount(_itemSelectNum));
			if (_itemSelectNum + 1 < _im->getItemInventorySize())
			{
				wsprintf(itemName[3], _im->getVItem()[_im->getItemVNum(_itemSelectNum + 1)]->getItemName());
				wsprintf(itemCount[3], "%d", _im->getItemCount(_itemSelectNum + 1));
			}
			if (_itemSelectNum + 2 < _im->getItemInventorySize())
			{
				wsprintf(itemName[4], _im->getVItem()[_im->getItemVNum(_itemSelectNum + 2)]->getItemName());
				wsprintf(itemCount[4], "%d", _im->getItemCount(_itemSelectNum + 2));
			}
			switch (_battleCharacters[_currentTurn].characterType)
			{
			case(TINA):
				IMAGEMANAGER->findImage("battleUI")->enlargeRender(getMemDC(), WINSIZEX - 300, 160 * i, 200, 160);
				break;
			case(LOCKE):
				IMAGEMANAGER->findImage("battleUI")->enlargeRender(getMemDC(), WINSIZEX - 300, 160 * i, 200, 160);
				break;
			case(CELES):
				IMAGEMANAGER->findImage("battleUI")->enlargeRender(getMemDC(), WINSIZEX - 300, 160 * i, 200, 160);
				break;
			case(SHADOW):
				IMAGEMANAGER->findImage("battleUI")->enlargeRender(getMemDC(), WINSIZEX - 300, 160 * i, 200, 160);
				break;
			}
			for (int j = 0; j < 5; ++j)
			{
				drawText(30, itemName[j], itemRC[j], DT_LEFT);
				drawText(30, itemCount[j], itemRC[j], DT_RIGHT);
			}
			IMAGEMANAGER->findImage("fingerArrowRt")->render(getMemDC(), WINSIZEX - 290, 160 * i + 5 + 60);
		}
		else if (_playerTurn == true && i == _currentTurn)
		{
			char attackMenu[] = "공격";
			char magicMenu[] = "마법";
			char itemMenu[] = "아이템";
			char escapeMenu[] = "도망";
			char tinaMenu[] = "변신";
			char lockeMenu[] = "훔치기";
			char celesMenu[] = "마법흡수";
			char shadowMenu[] = "던지기";
			RECT attackMenuRC = { WINSIZEX - 200, 160 * i + 5, WINSIZEX - 115, 160 * i + 35 };
			RECT magicMenuRC = { WINSIZEX - 200, 160 * i + 35, WINSIZEX - 115, 160 * i + 65 };
			RECT skillMenuRC = { WINSIZEX - 200, 160 * i + 65, WINSIZEX - 115, 160 * i + 95 };
			RECT itemMenuRC = { WINSIZEX - 200, 160 * i + 95, WINSIZEX - 115, 160 * i + 125 };
			RECT escapeMenuRC = { WINSIZEX - 200, 160 * i + 125, WINSIZEX - 115, 160 * i + 155 };
			switch (_battleCharacters[_currentTurn].characterType)
			{
			case(TINA):
				IMAGEMANAGER->findImage("battleUI")->enlargeRender(getMemDC(), WINSIZEX - 250, 160 * i, 150, 160);
				DrawText(getMemDC(), attackMenu, -1, &attackMenuRC, DT_LEFT | DT_WORDBREAK);
				DrawText(getMemDC(), magicMenu, -1, &magicMenuRC, DT_LEFT | DT_WORDBREAK);
				DrawText(getMemDC(), tinaMenu, -1, &skillMenuRC, DT_LEFT | DT_WORDBREAK);
				DrawText(getMemDC(), itemMenu, -1, &itemMenuRC, DT_LEFT | DT_WORDBREAK);
				DrawText(getMemDC(), escapeMenu, -1, &escapeMenuRC, DT_LEFT | DT_WORDBREAK);
				break;
			case(LOCKE):
				IMAGEMANAGER->findImage("battleUI")->enlargeRender(getMemDC(), WINSIZEX - 250, 160 * i, 150, 160);
				DrawText(getMemDC(), attackMenu, -1, &attackMenuRC, DT_LEFT | DT_WORDBREAK);
				DrawText(getMemDC(), magicMenu, -1, &magicMenuRC, DT_LEFT | DT_WORDBREAK);
				DrawText(getMemDC(), lockeMenu, -1, &skillMenuRC, DT_LEFT | DT_WORDBREAK);
				DrawText(getMemDC(), itemMenu, -1, &itemMenuRC, DT_LEFT | DT_WORDBREAK);
				DrawText(getMemDC(), escapeMenu, -1, &escapeMenuRC, DT_LEFT | DT_WORDBREAK);
				break;
			case(CELES):
				IMAGEMANAGER->findImage("battleUI")->enlargeRender(getMemDC(), WINSIZEX - 250, 160 * i, 150, 160);
				DrawText(getMemDC(), attackMenu, -1, &attackMenuRC, DT_LEFT | DT_WORDBREAK);
				DrawText(getMemDC(), magicMenu, -1, &magicMenuRC, DT_LEFT | DT_WORDBREAK);
				DrawText(getMemDC(), celesMenu, -1, &skillMenuRC, DT_LEFT | DT_WORDBREAK);
				DrawText(getMemDC(), itemMenu, -1, &itemMenuRC, DT_LEFT | DT_WORDBREAK);
				DrawText(getMemDC(), escapeMenu, -1, &escapeMenuRC, DT_LEFT | DT_WORDBREAK);
				break;
			case(SHADOW):
				IMAGEMANAGER->findImage("battleUI")->enlargeRender(getMemDC(), WINSIZEX - 250, 160 * i, 150, 160);
				DrawText(getMemDC(), attackMenu, -1, &attackMenuRC, DT_LEFT | DT_WORDBREAK);
				DrawText(getMemDC(), magicMenu, -1, &magicMenuRC, DT_LEFT | DT_WORDBREAK);
				DrawText(getMemDC(), shadowMenu, -1, &skillMenuRC, DT_LEFT | DT_WORDBREAK);
				DrawText(getMemDC(), itemMenu, -1, &itemMenuRC, DT_LEFT | DT_WORDBREAK);
				DrawText(getMemDC(), escapeMenu, -1, &escapeMenuRC, DT_LEFT | DT_WORDBREAK);
				break;
			}
			SelectObject(getMemDC(), oldFont);
			DeleteObject(oldFont);
			DeleteObject(newFont);
			IMAGEMANAGER->findImage("fingerArrowRt")->render(getMemDC(), WINSIZEX - 240, 160 * i + 5 + (_menuNum * 30));
		}
	}
	char test[128];
	wsprintf(test, "%d", _position);
	TextOut(getMemDC(), 500, 0, test, strlen(test));
}
//플레이어 애니메이션 프레임 업데이트
void BattleScene::playerFrameUpdate()
{
	//플레이어 애니메이션 프레임 업데이트
	for (int i = 0; i < 4; ++i)
	{
		_battleCharacters[i].player->animationFrameUpdate();
	}
}
//사운드 컨트롤
void BattleScene::soundControl()
{
	SOUNDMANAGER->getChannel(CH_BGM)->getPosition(&_position, FMOD_TIMEUNIT_MS);
	if (_victory == false)
	{
		if (_position >= 56800)
		{
			SOUNDMANAGER->getChannel(CH_BGM)->setPosition(4000, FMOD_TIMEUNIT_MS);
		}
	}
	if (_victory == true)
	{
		if (_victoryCounter >= 100 && _position >= 32500)
		{
			SOUNDMANAGER->getChannel(CH_BGM)->setPosition(3900, FMOD_TIMEUNIT_MS);
		}
	}
	if (_sfx01 == false)
	{
		SOUNDMANAGER->play("battleMenuOpen", CH_EFFECT03, 1.0f);
		_sfx01 = true;
	}
}
//데미지 렌더
void BattleScene::renderDamage(int endPoint)
{
	if (_isDamaged == true)
	{
		_messageCounter++;
		char tempDamage[128];
		wsprintf(tempDamage, "%d", (int)_damage);
		if (_hit == true) drawText(30, tempDamage, _damageRC, DT_CENTER);
		else
		{
			if (_messageCounter < 2)
			{
				SOUNDMANAGER->play("miss", CH_SOKKONGGU, 1.0f);
			}
			drawText(30, "miss", _damageRC, DT_CENTER);
		}
		if (_messageCounter > endPoint)
		{
			_messageCounter = 0;
			_isDamaged = false;
		}
	}
}
//전투 종료시 메시지 표시
void BattleScene::victoryMessage()
{
	RECT tempDialogueRC = { 25, 48, WINSIZEX - 275, 80 };
	if (_victoryCounter > 70 && _dialogueCounter < 20)
	{
		bool skip;
		skip = false;
		_messageCounter++;
		switch (_dialogueCounter)
		{
		case(1):
			if (_dialogue == true)
			{
				for (int j = 0; j < 4; ++j)
				{
					for (int i = 0; i < 4; ++i)
					{
						if (j == 0 && _battleCharacters[i].characterType != TINA) continue;
						if (j == 1 && _battleCharacters[i].characterType != LOCKE) continue;
						if (j == 2 && _battleCharacters[i].characterType != CELES) continue;
						if (j == 3 && _battleCharacters[i].characterType != SHADOW) continue;
						char playerNum[128];
						char body[128];
						wsprintf(playerNum, "player%d", j);
						wsprintf(body, "%d", _battleCharacters[i].player->getCurHP());
						INIDATA->addData(playerNum, "hp", body);
						INIDATA->iniSave("skgFile");
						break;
					}
				}
				_dialogue = false;
			}
			drawText(32, "팀 소꽁구 승리!", tempDialogueRC, DT_CENTER, true);
			break;
		case(2):
			if (_dialogue == true)
			{
				for (int j = 0; j < 4; ++j)
				{
					for (int i = 0; i < 4; ++i)
					{
						if (j == 0 && _battleCharacters[i].characterType != TINA) continue;
						if (j == 1 && _battleCharacters[i].characterType != LOCKE) continue;
						if (j == 2 && _battleCharacters[i].characterType != CELES) continue;
						if (j == 3 && _battleCharacters[i].characterType != SHADOW) continue;
						char playerNum[128];
						char body[128];
						wsprintf(playerNum, "player%d", j);
						wsprintf(body, "%d", _battleCharacters[i].player->getCurMP());
						INIDATA->addData(playerNum, "mp", body);
						INIDATA->iniSave("skgFile");
						break;
					}
				}
				_dialogue = false;
			}
			drawText(32, "소꽁구 만세!", tempDialogueRC, DT_CENTER, true);
			break;
		case(3):
			int exp;
			exp = 0;
			for (int i = 0; i < _maxMonster; ++i)
			{
				exp += _battleCharacters[i + 4].enemy->getMaxEXP();
			}
			if (_dialogue == true)
			{
				for (int j = 0; j < 4; ++j)
				{
					for (int i = 0; i < 4; ++i)
					{
						if (j == 0 && _battleCharacters[i].characterType != TINA) continue;
						if (j == 1 && _battleCharacters[i].characterType != LOCKE) continue;
						if (j == 2 && _battleCharacters[i].characterType != CELES) continue;
						if (j == 3 && _battleCharacters[i].characterType != SHADOW) continue;
						_battleCharacters[i].player->setCurEXP(_battleCharacters[i].player->getCurEXP() + exp);
						char playerNum[128];
						char body[128];
						wsprintf(playerNum, "player%d", j);
						wsprintf(body, "%d", _battleCharacters[i].player->getCurEXP() + exp);
						INIDATA->addData(playerNum, "exp", body);
						INIDATA->iniSave("skgFile");
						break;
					}
				}
				_dialogue = false;
			}
			wsprintf(_message0, "경험치를 %d 만큼 얻었다.", exp);
			drawText(32, _message0, tempDialogueRC, DT_CENTER, true);
			break;
		case(4):
			if (_dialogue == true)
			{
				for (int i = 0; i < 4; ++i)
				{
					if (_battleCharacters[i].characterType != TINA) continue;
					for (int j = _battleCharacters[i].player->getLv(); j < MAXLV; ++j)
					{
						if (_battleCharacters[i].player->getCurEXP() >= maxExpValue[j] && _battleCharacters[i].player->getCurEXP() < maxExpValue[j + 1])
						{
							wsprintf(_message0, "소꽁구는 레벨이 %d 올랐다!", j + 1 - _battleCharacters[i].player->getLv());
							int tempIncreasedHP;
							int tempIncreasedMP;
							tempIncreasedHP = 0;
							tempIncreasedMP = 0;
							for (int k = _battleCharacters[i].player->getLv(); k < j + 1; ++k)
							{
								tempIncreasedHP += improveHPValue[k];
								tempIncreasedMP += improveMPValue[k];
							}
							wsprintf(_message1, "소꽁구는 HP가 %d 상승했다.", tempIncreasedHP);
							wsprintf(_message2, "소꽁구는 MP가 %d 상승했다.", tempIncreasedMP);
							break;
						}
						if (_battleCharacters[i].player->getCurEXP() < maxExpValue[j])
						{
							_dialogueCounter = 6;
							skip = true;
							break;
						}
					}
					break;
				}
				_dialogue = false;
			}
			drawText(32, _message0, tempDialogueRC, DT_CENTER, true);
			break;
		case(5):
			drawText(32, _message1, tempDialogueRC, DT_CENTER, true);
			break;
		case(6):
			drawText(32, _message2, tempDialogueRC, DT_CENTER, true);
			break;
		case(7):
			if (_dialogue == true)
			{
				for (int i = 0; i < 4; ++i)
				{
					if (_battleCharacters[i].characterType != LOCKE) continue;
					for (int j = _battleCharacters[i].player->getLv(); j < MAXLV; ++j)
					{
						if (_battleCharacters[i].player->getCurEXP() >= maxExpValue[j] && _battleCharacters[i].player->getCurEXP() < maxExpValue[j + 1])
						{
							wsprintf(_message0, "로크는 레벨이 %d 올랐다!", j + 1 - _battleCharacters[i].player->getLv());
							int tempIncreasedHP;
							int tempIncreasedMP;
							tempIncreasedHP = 0;
							tempIncreasedMP = 0;
							for (int k = _battleCharacters[i].player->getLv(); k < j + 1; ++k)
							{
								tempIncreasedHP += improveHPValue[k];
								tempIncreasedMP += improveMPValue[k];
							}
							wsprintf(_message1, "로크는 HP가 %d 상승했다.", tempIncreasedHP);
							wsprintf(_message2, "로크는 MP가 %d 상승했다.", tempIncreasedMP);
							break;
						}
						if (_battleCharacters[i].player->getCurEXP() < maxExpValue[j])
						{
							_dialogueCounter = 9;
							skip = true;
							break;
						}
					}
					break;
				}
				_dialogue = false;
			}
			drawText(32, _message0, tempDialogueRC, DT_CENTER, true);
			break;
		case(8):
			drawText(32, _message1, tempDialogueRC, DT_CENTER, true);
			break;
		case(9):
			drawText(32, _message2, tempDialogueRC, DT_CENTER, true);
			break;
		case(10):
			if (_dialogue == true)
			{
				for (int i = 0; i < 4; ++i)
				{
					if (_battleCharacters[i].characterType != CELES) continue;
					for (int j = _battleCharacters[i].player->getLv(); j < MAXLV; ++j)
					{
						if (_battleCharacters[i].player->getCurEXP() >= maxExpValue[j] && _battleCharacters[i].player->getCurEXP() < maxExpValue[j + 1])
						{
							wsprintf(_message0, "세리스는 레벨이 %d 올랐다!", j + 1 - _battleCharacters[i].player->getLv());
							int tempIncreasedHP;
							int tempIncreasedMP;
							tempIncreasedHP = 0;
							tempIncreasedMP = 0;
							for (int k = _battleCharacters[i].player->getLv(); k < j + 1; ++k)
							{
								tempIncreasedHP += improveHPValue[k];
								tempIncreasedMP += improveMPValue[k];
							}
							wsprintf(_message1, "세리스는 HP가 %d 상승했다.", tempIncreasedHP);
							wsprintf(_message2, "세리스는 MP가 %d 상승했다.", tempIncreasedMP);
							break;
						}
						if (_battleCharacters[i].player->getCurEXP() < maxExpValue[j])
						{
							_dialogueCounter = 12;
							skip = true;
							break;
						}
					}
					break;
				}
				_dialogue = false;
			}
			drawText(32, _message0, tempDialogueRC, DT_CENTER, true);
			break;
		case(11):
			drawText(32, _message1, tempDialogueRC, DT_CENTER, true);
			break;
		case(12):
			drawText(32, _message2, tempDialogueRC, DT_CENTER, true);
			break;
		case(13):
			if (_dialogue == true)
			{
				for (int i = 0; i < 4; ++i)
				{
					if (_battleCharacters[i].characterType != SHADOW) continue;
					for (int j = _battleCharacters[i].player->getLv(); j < MAXLV; ++j)
					{
						if (_battleCharacters[i].player->getCurEXP() >= maxExpValue[j] && _battleCharacters[i].player->getCurEXP() < maxExpValue[j + 1])
						{
							wsprintf(_message0, "쉐도우는 레벨이 %d 올랐다!", j + 1 - _battleCharacters[i].player->getLv());
							int tempIncreasedHP;
							int tempIncreasedMP;
							tempIncreasedHP = 0;
							tempIncreasedMP = 0;
							for (int k = _battleCharacters[i].player->getLv(); k < j + 1; ++k)
							{
								tempIncreasedHP += improveHPValue[k];
								tempIncreasedMP += improveMPValue[k];
							}
							wsprintf(_message1, "쉐도우는 HP가 %d 상승했다.", tempIncreasedHP);
							wsprintf(_message2, "쉐도우는 MP가 %d 상승했다.", tempIncreasedMP);
							break;
						}
						if (_battleCharacters[i].player->getCurEXP() < maxExpValue[j])
						{
							_dialogueCounter = 15;
							skip = true;
							break;
						}
					}
					break;
				}
				_dialogue = false;
			}
			drawText(32, _message0, tempDialogueRC, DT_CENTER, true);
			break;
		case(14):
			drawText(32, _message1, tempDialogueRC, DT_CENTER, true);
			break;
		case(15):
			drawText(32, _message2, tempDialogueRC, DT_CENTER, true);
			break;
		case(16):
			int gold;
			gold = 0;
			for (int i = 0; i < _maxMonster; ++i)
			{
				gold += _battleCharacters[4 + i].enemy->getGold();
			}
			if (_dialogue == true)
			{
				_im->setMoney(_im->getMoney() + gold);
				_dialogue = false;
			}
			wsprintf(_message0, "%d Gil을 얻었다.", gold);
			drawText(32, _message0, tempDialogueRC, DT_CENTER, true);
			break;
		case(17):
			if (_dialogue == true)
			{
				if (RND->getInt(2) == 0)
				{
					wsprintf(_message0, "%s 을(를) 얻었다.", _battleCharacters[4].enemy->getItemName());
					if (_im->getItemKind(_battleCharacters[4].enemy->getItemName()) == ITEM_EXPENDABLE)
					{
						_im->changeItemNumber(_battleCharacters[4].enemy->getItemName(), 1);
					}
					else if (_im->getItemKind(_battleCharacters[4].enemy->getItemName()) == ITEM_WEAPON)
					{
						_im->changeItemNumber(_battleCharacters[4].enemy->getItemName(), 1);
					}
				}
				else
				{
					skip = true;
				}
				_dialogue = false;
			}
			drawText(32, _message0, tempDialogueRC, DT_CENTER, true);
			break;
		case(18):
			if (_dialogue == true)
			{
				if (RND->getInt(2) == 0 && _maxMonster >= 2)
				{
					wsprintf(_message0, "%s 을(를) 얻었다.", _battleCharacters[4].enemy->getItemName());
					if (_im->getItemKind(_battleCharacters[4].enemy->getItemName()) == ITEM_EXPENDABLE)
					{
						_im->changeItemNumber(_battleCharacters[4].enemy->getItemName(), 1);
					}
					else if (_im->getItemKind(_battleCharacters[4].enemy->getItemName()) == ITEM_WEAPON)
					{
						_im->changeItemNumber(_battleCharacters[4].enemy->getItemName(), 1);
					}
				}
				else
				{
					skip = true;
				}
				_dialogue = false;
			}
			drawText(32, _message0, tempDialogueRC, DT_CENTER, true);
			break;
		case(19):
			if (_dialogue == true)
			{
				if (RND->getInt(2) == 0 && _maxMonster >= 3)
				{
					wsprintf(_message0, "%s 을(를) 얻었다.", _battleCharacters[4].enemy->getItemName());
					if (_im->getItemKind(_battleCharacters[4].enemy->getItemName()) == ITEM_EXPENDABLE)
					{
						_im->changeItemNumber(_battleCharacters[4].enemy->getItemName(), 1);
					}
					else if (_im->getItemKind(_battleCharacters[4].enemy->getItemName()) == ITEM_WEAPON)
					{
						_im->changeItemNumber(_battleCharacters[4].enemy->getItemName(), 1);
					}
				}
				else
				{
					skip = true;
				}
				_dialogue = false;
			}
			drawText(32, _message0, tempDialogueRC, DT_CENTER, true);
			break;
		}
		if (skip == true)
		{
			_messageCounter = 0;
			_dialogueCounter++;
			_dialogue = true;
		}
		if (_messageCounter > 60)
		{
			_messageCounter = 0;
			_dialogueCounter++;
			_dialogue = true;
		}
	}
}
//승리 조건
void BattleScene::victoryCondition()
{
	for (int i = 0; i < _maxMonster; ++i)
	{
		_victory = false;
		if (_battleCharacters[i + 4].enemy->getCurHP() > 0)
		{
			break;
		}
		_victory = true;
	}
	if (_victory == true)
	{
		_victoryCounter++;
	}
	if (_victoryCounter == 50)
	{
		SOUNDMANAGER->play("fanfareBGM", CH_BGM, 1.0f);
		for (int i = 0; i < 4; ++i)
		{
			if (_battleCharacters[i].player->getCurHP() > 0)
			{
				_battleCharacters[i].player->setStatus(BATTLE_PLAYER_WIN_BEFORE);
			}
		}
		_dialogueCounter++;
		_dialogue = true;
	}
	if (_dialogueCounter >= 18)
	{
		_changeScene = true;
	}
}
//게임 오버 조건
void BattleScene::gameOverCondition()
{
	int deathCount = 0;
	for (int i = 0; i < 4; ++i)
	{
		if (_battleCharacters[i].player->getCurHP() <= 0)
		{
			_battleCharacters[i].ATBcounter = 0;
			_battleCharacters[i].player->setCurHP(0);
			_battleCharacters[i].player->setStatus(BATTLE_PLAYER_DEAD);
			deathCount++;
		}
		if (deathCount == 4 && _gameOver == 0)
		{
			_gameOver = 1;
		}
	}
	if (_gameOver > 0)
	{
		_gameOver++;
	}
	if (_gameOver > 100)
	{
		this->release();
		SCENEMANAGER->changeSceneType0("게임오버");
	}
}
//씬 전환
void BattleScene::sceneChange()
{
	if (_changeScene == true)
	{
		_im->saveInventory("skgFile");
		_pm->playerLevelUp();
		this->release();
		((worldMapScene*)SCENEMANAGER->findScene("월드맵씬"))->resetIsEncounter();
		SCENEMANAGER->changeSceneType0("월드맵씬", false);
	}
}
//텍스트 그리는 함수
void BattleScene::drawText(int fontSize, char* str, RECT rc, int position, bool dialogue)
{
	if (dialogue == true)
	{
		IMAGEMANAGER->findImage("battleUI2")->render(getMemDC(), 0, 0);
	}
	newFont = CreateFont(fontSize, 0, 0, 0, 1000, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("Sandoll 미생"));
	oldFont = (HFONT)SelectObject(getMemDC(), newFont);
	DrawText(getMemDC(), str, -1, &rc, position | DT_WORDBREAK);
	SelectObject(getMemDC(), oldFont);
	DeleteObject(oldFont);
	DeleteObject(newFont);
}
//플레이어 물리 공격 함수
void BattleScene::playerAttack()
{
	//플레이어 공격 알고리즘 계산
	_damageRC = { _battleTurn.front()->enemy->getX() - 200, _battleTurn.front()->enemy->getY() + _battleTurn.front()->enemy->getImageHeight() / 2, _battleTurn.front()->enemy->getX() + 200, _battleTurn.front()->enemy->getY() + _battleTurn.front()->enemy->getImageHeight() / 2 + 30 };
	float BlockValue = (255 - (float)_battleTurn.front()->enemy->getMDef() * 2) + 1;
	if (BlockValue > 255) BlockValue = 255;
	if (BlockValue < 1) BlockValue = 1;
	if ((_battleTurn.front()->player->getHitRate() * BlockValue / 256) > RND->getFromFloatTo(0, 0.99f))
	{
		_hit = true;
	}
	else
	{
		_hit = false;
	}
	if (_hit == true)
	{
		float Vigor2 = _battleTurn.front()->player->getStrength() * 2;
		if (Vigor2 > 255) Vigor2 = 255;
		float Attack = _battleTurn.front()->player->getAttack() + Vigor2;
		_damage = (float)_battleTurn.front()->player->getAttack() + (((float)_battleTurn.front()->player->getLv() * (float)_battleTurn.front()->player->getLv() * Attack) / 256) * 3 / 2;
		_damage = (_damage * (float)RND->getFromIntTo(224, 255) / 256) + 1;
		_damage = (_damage * (255 - (float)_battleTurn.front()->enemy->getADef()) / 256) + 1;
		_battleTurn.front()->enemy->setCurHP(_battleTurn.front()->enemy->getCurHP() - _damage);
		if (_battleTurn.front()->enemy->getCurHP() < 0) _battleTurn.front()->enemy->setCurHP(0);
	}
	_isDamaged = true;
}
//플레이어 마법 공격 함수
void BattleScene::playerMagicAttack()
{
	//플레이어 마법 공격 알고리즘 계산
	_damageRC = { _battleTurn.front()->enemy->getX() - 200, _battleTurn.front()->enemy->getY() + _battleTurn.front()->enemy->getImageHeight() / 2, _battleTurn.front()->enemy->getX() + 200, _battleTurn.front()->enemy->getY() + _battleTurn.front()->enemy->getImageHeight() / 2 + 30 };
	float BlockValue = (255 - (float)_battleTurn.front()->enemy->getMDef() * 2) + 1;
	if (BlockValue > 255) BlockValue = 255;
	if (BlockValue < 1) BlockValue = 1;
	if ((_battleTurn.front()->player->getHitRate() * BlockValue / 256) > RND->getFromFloatTo(0, 0.99f))
	{
		_hit = true;                                                                  //맞았다!
	}
	else
	{
		_hit = false;                                                                  //빗나감 ㅠㅠ
	}
	if (_hit == true)                                                                  //맞앗으면 데미지 공식 적용
	{
		//스킬 데미지 공식
		float spellPower;
		spellPower = (float)_battleTurn.front()->player->getMyUsableMagic()[_battleTurn.front()->magicSelect]->getAbilityPower();
		_damage = spellPower * 4 + ((float)_battleTurn.front()->player->getLv() * (float)_battleTurn.front()->player->getMagic() * spellPower / 32);
		_damage = (_damage * (float)RND->getFromIntTo(224, 255) / 256) + 1;
		_damage = (_damage * (255 - (float)_battleTurn.front()->enemy->getMDef()) / 256) + 1;
		_battleTurn.front()->enemy->setCurHP(_battleTurn.front()->enemy->getCurHP() - _damage);
		if (_battleTurn.front()->enemy->getCurHP() < 0) _battleTurn.front()->enemy->setCurHP(0);
	}
	_isDamaged = true;
}