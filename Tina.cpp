#include "stdafx.h"
#include "Tina.h"


Tina::Tina()
{
	playerMother::playerMother();
	wsprintf(_name, "TINA");
	wsprintf(_job, "Magician");
	_Lv = 3, _curEXP = 96; _maxEXP = 208;
	_curHP = 40 + 23, _maxHP = 40 + 23, _curMP = 16 + 11, _maxMP = 16 + 11;
	_strength = 31, _speed = 33, _stamina = 28;
	_magic = 39, _attack = 12, _a_Def = 42;
	_m_Def = 33, _evasion = 5, _m_evasion = 7;
	_partyIdx = 0;
	
	//임시값(스펠파워에 대한 자료가 없어성 ㅜㅠ)
	_spellPower = _Lv;


	
}


Tina::~Tina()
{
}
void Tina::setTinaMagic()
{
	//======================== 마법 공격 세팅===================
	//마법 공격 1 - 물 공격
	magic* tmpMagic = new magic;
	IMAGEMANAGER->addFrameImage("Tina::Water Magic", "./image/playerImg/playerEffectImage/playerSkill1.bmp", 1463, 119, 7, 1, true, RGB(255, 0, 255));
	tmpMagic->init("Tina::Water Magic", "./image/playerImg/playerEffectImage/playerSkill1.bmp", "수룡!", 22, 5, 150, 0, 0);
	_myUsableMagic.push_back(tmpMagic);

	//마법 공격 2 - 아군 힐
	tmpMagic = new magic;
	IMAGEMANAGER->addFrameImage("Tina::Heal Magic", "./image/playerImg/playerEffectImage/playerSkill2.bmp", 445, 45, 5, 1, true, RGB(255, 0, 255));
	tmpMagic->init("Tina::Heal Magic", "./image/playerImg/playerEffectImage/playerSkill2.bmp", "힐!", 66, 40, 0, 1, 0);
	_myUsableMagic.push_back(tmpMagic);

	//마법 공격 3 - 아군 되살리기
	tmpMagic = new magic;
	IMAGEMANAGER->addFrameImage("Tina::Revive Magic", "./image/playerImg/playerEffectImage/playerSkill8.bmp", 6110, 242, 26, 1, true, RGB(255, 0, 255));
	tmpMagic->init("Tina::Revive Magic", "./image/playerImg/playerEffectImage/playerSkill8.bmp", "리바이브!", 30, 30, 0, 0, 1);
	_myUsableMagic.push_back(tmpMagic);
}