#pragma once
#include "gameNode.h"
#include "celes.h"
#include "Locke.h"
#include "shadow.h"
#include "Tina.h"

class BattleScene;
class battleCeles;
class battleLocke;
class battleShadow;
class battleTina;
class playerManager : public gameNode
{
private:
	//�� �÷��̾���� ������ ��� ���� ������
	celes* _celes;
	Locke* _locke;
	shadow* _shadow;
	Tina* _tina;

	BattleScene* _battleScene;

public:
	playerManager();
	~playerManager();

	HRESULT init();
	void update();
	void render();
	void draw();
	void release();

	//========================== ��Ʋ������ ��ȯ�Ǹ� �÷��̾� �Ŵ����� �� �Լ��� ȣ���Ͽ� ��Ʋ�÷��̾��� ������ �����Ѵ� ==================
	inline void setPlayerInfoToBattlePlayer()
	{
		//���� ���� ���Ŵ����� ��ϵǾ� �ִ� ��Ʋ���� �����´�
		_battleScene = (BattleScene*)SCENEMANAGER->findScene("��Ʋ��");

		//================================== Start �� ��Ʋ���� ��Ʋ�÷��̾���� ������ �����Ѵ�.====================================
		_battleScene->getCelesAddress()->setAllBattlePlayerInfo(_celes->getLv(), _celes->getCurEXP(), _celes->getMaxEXP(),
			_celes->getCurHP(), _celes->getMaxHP(), _celes->getCurMP(), _celes->getMaxMP(), _celes->getSpeed(),
			_celes->getStrength(), _celes->getMagic(), _celes->getMDef(), _celes->getADef(), _celes->getAttack(), _celes->getEvasion());

		_battleScene->getLockeAddress()->setAllBattlePlayerInfo(_locke->getLv(), _locke->getCurEXP(), _locke->getMaxEXP(),
			_locke->getCurHP(), _locke->getMaxHP(), _locke->getCurMP(), _locke->getMaxMP(), _locke->getSpeed(),
			_locke->getStrength(), _locke->getMagic(), _locke->getMDef(), _locke->getADef(), _locke->getAttack(), _locke->getEvasion());

		_battleScene->getShadowAddress()->setAllBattlePlayerInfo(_shadow->getLv(), _shadow->getCurEXP(), _shadow->getMaxEXP(),
			_shadow->getCurHP(), _shadow->getMaxHP(), _shadow->getCurMP(), _shadow->getMaxMP(), _shadow->getSpeed(),
			_shadow->getStrength(), _shadow->getMagic(), _shadow->getMDef(), _shadow->getADef(), _shadow->getAttack(), _shadow->getEvasion());

		_battleScene->getTinaAddress()->setAllBattlePlayerInfo(_tina->getLv(), _tina->getCurEXP(), _tina->getMaxEXP(),
			_tina->getCurHP(), _tina->getMaxHP(), _tina->getCurMP(), _tina->getMaxMP(), _tina->getSpeed(),
			_tina->getStrength(), _tina->getMagic(), _tina->getMDef(), _tina->getADef(), _tina->getAttack(), _tina->getEvasion());
		//================================== End �� ��Ʋ���� ��Ʋ�÷��̾���� ������ �����Ѵ�.====================================
	}
};

