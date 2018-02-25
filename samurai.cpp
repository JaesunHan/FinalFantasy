#include "stdafx.h"
#include "samurai.h"
#include "battlePlayerMother.h"

samurai::samurai()
{
	//=================================================== 에너미 이미지 ==========================================================
	
	_img = IMAGEMANAGER->addFrameImage("samurai", ".\\image\\enemyImg\\samurai.bmp", 108, 103, 2, 1, true, RGB(255, 0, 255), true);
	
	//===========================================================================================================================

	//================================================= 에너미 이펙트 이미지 =====================================================
	
	IMAGEMANAGER->addImage("samurai기본공격이미지", ".\\image\\enemyEffect\\effect1.bmp", 1800, 130, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("samurai스킬공격이미지", ".\\image\\enemyEffect\\effect3.bmp", 800, 50, true, RGB(255, 0, 255), true);

	_atkEffect = new effect;
	_atkEffect->init(IMAGEMANAGER->findImage("samurai기본공격이미지"), 150, 130, 1.0f, 0.5f);

	_spellEffect = new effect;
	_spellEffect->init(IMAGEMANAGER->findImage("samurai스킬공격이미지"), 100, 50, 1.0f, 0.5f);

	EFFECTMANAGER->addEffect("samurai기본공격", ".\\image\\enemyEffect\\effect1.bmp", 1800, 130, 150, 130, 1.0f, 1.0f, 2);
	EFFECTMANAGER->addEffect("samurai스킬공격", ".\\image\\enemyEffect\\effect3.bmp", 800, 50, 100, 50, 1.0f, 1.0f, 2);
	
	//===========================================================================================================================
	
	//============================================== 기본공격 사운드 ==============================================

	SOUNDMANAGER->addSound("samurai기본공격", ".\\sound\\sfx\\2ESwordSlashLong.wav", true, false);

	//============================================================================================================

	//============================================== 스킬공격 사운드 ==============================================

	SOUNDMANAGER->addSound("samurai스킬공격", ".\\sound\\sfx\\7FMechDispatch.wav", true, false);

	//============================================================================================================

	_Lv = 40;										//레벨
	_maxEXP = RND->getFromIntTo(1500, 1600) * 100;	//현재 경험치, 최대 경험치
	_gold = RND->getFromIntTo(750, 850);			//돈

	_curHP = _maxHP = 3000;							//현재 체력, 최대 체력
	_curMP = _maxMP = 500;							//현재 마력, 최대 마력

	_attack = 13;									//물리 공격력
	_magic = 10;									//마법 공격력

	_m_Def = 20;									//마법 방어력
	_a_Def = 10;									//물리 방어력

	_speed = 20;									//공격 타이머

	_evasion = 0;									//회피율
	_hitRate = 100;									//명중률
	_block = 0;										//방어율

	_spellPower = _Lv - 10;							//마법력

	setItemDropRate(02, 04, 25, 25, 15, 10, 05, 06, 05, 02, 01);
	setItemString();
}


samurai::~samurai()
{

}

void samurai::update()
{
	Enemy::update();
	wsprintf(_basicAttack, "samurai기본공격");
	wsprintf(_skillAttack, "samurai스킬공격");
}

void samurai::render()
{
	Enemy::render();
	IMAGEMANAGER->findImage("samurai")->alphaFrameRender(getMemDC(), _x - _img->getFrameWidth() / 2, _y - _img->getFrameHeight() / 2, _frameX, 0, _alpha);
}


void samurai::bearSkill()
{

}
