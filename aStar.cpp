#include "stdafx.h"
#include "aStar.h"


aStar::aStar()
{
}


aStar::~aStar()
{
}

HRESULT aStar::init(int enemyPosX, int enemyPosY, int playerPosX, int playerPosY)
{
	////��Ÿ�Ϸκ��� ��ǥ�� �޾ƿ´�.
	//setTiles(enemyPosX, enemyPosY, playerPosX, playerPosY);


	return S_OK;
}

void aStar::setTiles(int enemyPosX, int enemyPosY, int playerPosX, int playerPosY)
{
	//�� ���� �ʱ�ȭ
	//���ʹ� ���� a*�� �ҷ����� ���ٵ� ������ ���͵��� �ʱ�ȭ ���־�� �Ұ� ����.
	//..�Ƹ���
	_vTotalList.clear();
	_vOpenList.clear();
	_vCloseList.clear();

	//���ʹ� ���忡�� �i�ƿ��°��̴� ��ŸƮ Ÿ���� ��ǥ�� ���ʹ̷κ��� �޾ƿ��°�. 


	_startTile = new tile;
	_startTile->init(PointMake(enemyPosX / TILEWIDTH, enemyPosY / TILEHEIGHT)); //��ǥ�� �޾Ƽ� XŸ�� ũ��� �����ָ� ���� Ÿ���� ��ġ�� ����
	_startTile->setAttribute("start");


	_endTile = new tile;
	_endTile->init(PointMake(playerPosX / TILEWIDTH, playerPosY / TILEHEIGHT)); //�÷��̾� ��ǥ �޾Ƽ� YŸ�� ũ��� �����־� ���� Ÿ���� ��ġ�� �޾ƿ´�.
	_endTile->setAttribute("end");


	_currentTile = _startTile;

	for (int i = 0; i < TILENUMY; ++i)
	{
		for (int j = 0; j < TILENUMX; ++j)
		{	//ij�� ���Ƽ� ���� Ÿ���� �ε����� ��ŸƮŸ���϶�
			if (j == _startTile->getIndex().x && i == _startTile->getIndex().y)
			{
				_vTotalList.push_back(_startTile);
			}
			continue;
			//���� ������ ���� Ÿ���� �ε����� ����Ÿ���϶�
			if (j == _endTile->getIndex().x && i == _endTile->getIndex().y)
			{
				_vTotalList.push_back(_endTile);
			}
			continue;

			//�׿� Ÿ�ϵ��� node�� ����.
			tile* _node = new tile;
			_node->init(PointMake(j, i));
			_vTotalList.push_back(_node);

		}
	}
}

vector<tile*> aStar::addOpenList(tile * currentTile)
{
	int startX = currentTile->getIndex().x - 1;
	int startY = currentTile->getIndex().y - 1;

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			//1���� �迭������ Ư�� Ÿ�� �ε����� ���ϴ� ����
			tile* _node = _vTotalList[(startY * TILENUMX) + startX + j + (i * TILENUMX)];

			if (!_node->getIsOpen()) continue;
			//if(_node->getAttribute() == "���̶�� ��!!") attribute �� �߰��Ǹ� �߰��Ұ�
			if (startX + j < 0) continue;  //X�� 0���� ������ �粸��
			if (startY + i < 0) continue;  //y�� 0 ���� ������ �粸��
			if (startX + j >= TILENUMX) continue; //X�� Ÿ�� X������ �������� Ŀ���ų� �������� �粸��
			if (startY + i >= TILENUMY) continue; //y�� Ÿ�� Y������ �������� Ŀ���ų� �������� �粸��


												  //���� Ÿ���� ��� �������ش�.
			_node->setParentNode(_currentTile);

			//�ֺ� Ÿ���� �����ϸ鼭 ü�������� ������ �˼� �ְ� ������ �Ұ�����
			bool addObj = true;


			for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
			{
				if (*_viOpenList == _node)
				{
					addObj = false;
					break;
				}
			}

			if (!addObj) continue;

			_vOpenList.push_back(_node);
		}

	}

	return _vOpenList;
}

void aStar::pathFinder(tile * currentTile)
{
	//���ϱ� ���� ������ ��κ���� �����صд�
	float tempTotalCost = 5000;
	tile* tempTile = NULL;

	for (int i = 0; i < addOpenList(currentTile).size(); ++i)
	{
		_vOpenList[i]->setCostToGoal(
			abs(_endTile->getIndex().x - _vOpenList[i]->getIndex().x +
				abs(_endTile->getIndex().y - _vOpenList[i]->getIndex().y)) * 10);


		//����Ÿ���� ����ִ� �༮
		POINT center1 = _vOpenList[i]->getParentNode()->getCenterPt();
		POINT center2 = _vOpenList[i]->getCenterPt();

		_vOpenList[i]->setCostFromStart((getDistance(center1.x, center1.y, center2.x, center2.y) > TILEWIDTH) ? 14 : 10);

		_vOpenList[i]->setTotalCost(_vOpenList[i]->getCostToGoal() + _vOpenList[i]->getCostFromStart());


	}
}

void aStar::release()
{
}

void aStar::update()
{
}

void aStar::render()
{
}
