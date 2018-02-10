#pragma once
#include "gameNode.h"
#include "celes.h"
#include "Locke.h"
#include "shadow.h"
#include "Tina.h"

class BattleScene;
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
		_battleScene = (BattleScene*)SCENEMANAGER->findScene("��Ʋ��");
		
	}
};

