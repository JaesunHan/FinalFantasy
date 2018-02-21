#include "stdafx.h"
#include "bossAtma.h"
#include "battlePlayerMother.h"

bossAtma::bossAtma()
{
	//=================================================== 에너미 이미지 ==========================================================
	
	_img = IMAGEMANAGER->addFrameImage("bossAtma", ".\\image\\enemyImg\\bossAtma.bmp", 1000, 500, 2, 1, true, RGB(255, 0, 255), true);
	
	//===========================================================================================================================

	//================================================= 에너미 이펙트 이미지 =====================================================
	
	IMAGEMANAGER->addImage("bossAtma기본공격이미지", ".\\image\\enemyEffect\\effect4.bmp", 304, 64, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("bossAtma스킬공격이미지1", ".\\image\\enemyEffect\\effect11.bmp", 583, 102, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("bossAtma스킬공격이미지2", ".\\image\\enemyEffect\\effect6.bmp", 2100, 100, true, RGB(255, 0, 255), true);

	_atkEffect = new effect;
	_atkEffect->init(IMAGEMANAGER->findImage("bossAtma기본공격이미지"), 76, 64, 1.0f, 0.5f);

	_spellEffect = new effect;
	_spellEffect->init(IMAGEMANAGER->findImage("bossAtma스킬공격이미지1"), 53, 102, 1.0f, 0.5f);

	_spellEffect2 = new effect;
	_spellEffect2->init(IMAGEMANAGER->findImage("bossAtma스킬공격이미지2"), 100, 100, 1.0f, 0.5f);

	EFFECTMANAGER->addEffect("bossAtma기본공격이펙트", ".\\image\\enemyEffect\\effect4.bmp", 304, 64, 76, 64, 1.0f, 1.0f, 2);
	EFFECTMANAGER->addEffect("bossAtma스킬공격이펙트", ".\\image\\enemyEffect\\effect11.bmp", 583, 102, 53, 102, 1.0f, 1.0f, 2);
	EFFECTMANAGER->addEffect("bossAtma스킬공격이펙트2", ".\\image\\enemyEffect\\effect6.bmp", 2100, 100, 100, 100, 1.0f, 1.0f, 2);
	
	//===========================================================================================================================
	
	//============================================== 기본공격 사운드 ==============================================

	SOUNDMANAGER->addSound("bossAtma기본공격sound", ".\\sound\\sfx\\16Fire1.wav", true, false);

	//============================================================================================================

	//============================================== 스킬공격 사운드 ==============================================

	SOUNDMANAGER->addSound("bossAtma스킬공격1sound", ".\\sound\\sfx\\13Explosion.wav", true, false);
	SOUNDMANAGER->addSound("bossAtma스킬공격2sound", ".\\sound\\sfx\\15Bolt3.wav", true, false);

	//============================================================================================================

	_Lv = 67;										//레벨
	_maxEXP = 0;	 								//현재 경험치, 최대 경험치
	_gold = 0;										//돈

	_curHP = _maxHP = 55000;						//현재 체력, 최대 체력
	_curMP = _maxMP = 19000;						//현재 마력, 최대 마력

	_attack = 20;									//물리 공격력
	_magic = 10;									//마법 공격력

	_m_Def = 70;									//마법 방어력
	_a_Def = 75;									//물리 방어력

	_speed = 63;									//공격 타이머

	_evasion = 0;									//회피율
	_hitRate = 100;									//명중률
	_block = 0;										//방어율

	_spellPower = (_Lv / 3) * 2;					//마법력
}


bossAtma::~bossAtma()
{

}

void bossAtma::update()
{
	Enemy::update();
	wsprintf(_basicAttack, "bossAtma기본공격");
	wsprintf(_skillAttack, "bossAtma스킬공격");
}

void bossAtma::render()
{
	Enemy::render();
	IMAGEMANAGER->findImage("bossAtma")->alphaFrameRender(getMemDC(), _x - _img->getFrameWidth() / 2, _y - _img->getFrameHeight() / 2, _frameX, 0, _alpha);
}


void bossAtma::bearSkill()
{

}
