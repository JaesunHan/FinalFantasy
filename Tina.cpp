#include "stdafx.h"
#include "Tina.h"


Tina::Tina()
{
	playerMother::playerMother();
	wsprintf(_name, "TINA");
	wsprintf(_job, "Magician");
	_Lv = 3, _curEXP = 96; _maxEXP = 96;
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
