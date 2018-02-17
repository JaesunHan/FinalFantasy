#include "stdafx.h"
#include "aStar.h"


aStar::aStar()
{
}


aStar::~aStar()
{
}


HRESULT aStar::init(tile* map, int numX, int numY, tile start, tile end)
{
	this->release();

	for (int i = 0; i < numX*numY; ++i)
	{
		_vTotalList.push_back(map[i]);
	}

	_startTile = _currentTile = start;

	_endTile = end;
	_tileX = numX;
	_tileY = numY;

	return S_OK;
}

void aStar::release()
{
	_vTotalList.clear();
	_vOpenList.clear();
	_vCloseList.clear();

}

vector<tile> aStar::addOpenList(tile currentTile)
{
	int startX = currentTile.getIndex().x - 1;
	int startY = currentTile.getIndex().y - 1;

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; j++)
		{
			//����ó��
			if (startX + j < 0 || startY + i< 0) continue;
			if (startX + j >= _tileX - 1 || startY + i >= _tileY - 1) continue;

			//�밢�� ����ó��
			if (j == 0 && i == 0)
			{
				continue;
				//tile temp = _vTotalList[startX + (startY + 1)* _tileX];
				//tile temp2 = _vTotalList[startX + 1 + (startY)*_tileX];
				//if (!temp.getIsOpen()) continue;
				//if (!temp2.getIsOpen()) continue;
			}
			if (j == 2 && i == 0)
			{
				continue;
				//tile temp = _vTotalList[startX + (startY + 1)* _tileX];
				//tile temp2 = _vTotalList[startX + 1 + (startY)* _tileX];
				//if (!temp.getIsOpen()) continue;
				//if (!temp2.getIsOpen()) continue;
			}
			if (j == 2 && i == 2)
			{
				continue;
				//tile temp = _vTotalList[startX + 2 + (startY + 1)*_tileX];
				//tile temp2 = _vTotalList[startX + 1 + (startY + 2)*_tileX];
				//if (!temp.getIsOpen()) continue;
				//if (!temp2.getIsOpen()) continue;
			}
			if (j == 0 && i == 2)
			{
				continue;
				//tile temp = _vTotalList[startX + 1 + (startY + 2)];
				//tile temp2 = _vTotalList[startX + (startY + 1)*_tileX];
				//if (!temp.getIsOpen()) continue;
				//if (!temp2.getIsOpen()) continue;
			}

			tile node = _vTotalList[(startY*_tileX) + startX + j + (i*_tileX)];

			if (!node.getIsOpen()) continue;
			if (node.getIndex().x == _startTile.getIndex().x &&
				node.getIndex().y == _startTile.getIndex().y) continue;

			//����Ÿ�� ����
			tile* tempNode = new tile;
			(*tempNode) = currentTile;
			node.setParentNode(tempNode);

			//�ֺ� Ÿ�� ����
			bool addObj = true;

			for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
			{
				//�̹� ����
				if ((*_viOpenList).getIndex().x == node.getIndex().x &&
					(*_viOpenList).getIndex().y == node.getIndex().y)
				{
					addObj = false;
					break;
				}
			}
			if (!addObj) continue;

			_vOpenList.push_back(node);
		}
	}

	return _vOpenList;
}

vector<tile> aStar::pathFinder(tile current)
{
	//start == end ����ó��
	if (_startTile.getIndex().x == _endTile.getIndex().x &&
		_startTile.getIndex().y == _endTile.getIndex().y) return _vCloseList;

	int addOpenListNum = addOpenList(current).size();
	float tempTotalCost = INT_MAX;
	tile tempTile;

	for (int i = 0; i < addOpenListNum; ++i)
	{
		//H�� ����
		_vOpenList[i].setCostToGoal(abs(_endTile.getIndex().x - _vOpenList[i].getIndex().x) +
			abs(_endTile.getIndex().y - _vOpenList[i].getIndex().y) * 10);


		//G�� ����
		POINT center1 = PointMake(_vOpenList[i].getParentNode()->getCenterPt().x, _vOpenList[i].getParentNode()->getCenterPt().y);
		POINT center2 = PointMake(_vOpenList[i].getCenterPt().x, _vOpenList[i].getCenterPt().y);

		_vOpenList[i].setCostFromStart((getDistance(center1.x, center1.y, center2.x, center2.y) > TILE_SIZEX) ? 14 : 10);


		//F�� ����
		_vOpenList[i].setTotalCost(_vOpenList[i].getCostToGoal() + _vOpenList[i].getCostFromStart());


		//F�� ��
		if (tempTotalCost > _vOpenList[i].getTotalCost())
		{
			tempTotalCost = _vOpenList[i].getTotalCost();
			tempTile = _vOpenList[i];
		}

		bool addObj = true;
		for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
		{
			if ((*_viOpenList).getIndex().x == tempTile.getIndex().x &&
				(*_viOpenList).getIndex().y == tempTile.getIndex().y)
			{
				addObj = false;
				break;
			}
		}

		tempTile.setIsOpen(false);
		_vOpenList[i].setIsOpen(false);
		for (int i = 0; i < _vTotalList.size(); ++i)
		{
			if (_vTotalList[i].getIndex().x == tempTile.getIndex().x &&
				_vTotalList[i].getIndex().y == tempTile.getIndex().y)
			{
				_vTotalList[i].setIsOpen(false);
				break;
			}
		}

		if (!addObj) continue;
		_vOpenList.push_back(tempTile);
	}

	//
	if (tempTile.getIndex().x == _endTile.getIndex().x &&
		tempTile.getIndex().y == _endTile.getIndex().y)
	{
		_vCloseList.push_back(tempTile);
		while (!(tempTile.getIndex().x == _startTile.getIndex().x &&
			tempTile.getIndex().y == _startTile.getIndex().y))
		{
			_vCloseList.push_back((*tempTile.getParentNode()));
			tempTile = (*tempTile.getParentNode());
		}
		_vCloseList.erase(_vCloseList.end() - 1);
		return _vCloseList;
	}

	for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
	{
		//�ִܰ�� ���� ����Ʈ���� ����
		if ((*_viOpenList).getIndex().x == tempTile.getIndex().x &&
			(*_viOpenList).getIndex().y == tempTile.getIndex().y)
		{
			_viOpenList = _vOpenList.erase(_viOpenList);
			break;
		}

	}

	_currentTile = tempTile;


	return pathFinder(_currentTile);// ���
}

