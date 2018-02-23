#include "stdafx.h"
#include "shadow.h"
#include "weaponItem.h"

shadow::shadow()
{
	playerMother::playerMother();
	wsprintf(_name, "SHADOW");
	wsprintf(_job, "Assassin");
	_Lv = 3, _curEXP = 96; _maxEXP = 208;
	_curHP = 51 + 23, _maxHP = 51 + 23, _curMP = 6 + 11, _maxMP = 6 + 11;
	_strength = 39, _speed = 38, _stamina = 30;
	_magic = 33, _attack = 23, _a_Def = 47;
	_evasion = 28, _m_Def = 25, _m_evasion = 9;
	_partyIdx = 3;

	_spellPower = _Lv;


	
}


shadow::~shadow()
{
}

void shadow::setShadowMagic()
{
	//========================= 마법 공격 세팅 ======================
	//마법 공격 1 - 그림자 공격
	magic* tmpMagic = new magic;
	IMAGEMANAGER->addFrameImage("Shadow::Bio Magic", "./image/playerImg/playerEffectImage/playerSkill7.bmp", 960, 1152, 5, 6, true, RGB(255, 0, 255));
	tmpMagic->init("Shadow::Bio Magic", "./image/playerImg/playerEffectImage/playerSkill7.bmp", "바이오!", 53, 26, 120, 0, 0);
	_myUsableMagic.push_back(tmpMagic);
	//마법공격 2 - 홀리 공격
	tmpMagic = new magic;
	IMAGEMANAGER->addFrameImage("Shadow::Holy Magic", "./image/playerImg/playerEffectImage/playerSkill6.bmp", 472, 126, 8, 1, true, RGB(255, 0, 255));
	tmpMagic->init("Shadow::Holy Magic", "./image/playerImg/playerEffectImage/playerSkill6.bmp", "홀리!", 108, 40, 150, 0, 0);
	_myUsableMagic.push_back(tmpMagic);
}