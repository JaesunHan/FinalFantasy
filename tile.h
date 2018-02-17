#pragma once
#include "gameNode.h"
#include "tileInfo.h"

/********************************************************/
/* Ÿ�� ��ü Ŭ����										*/
/* �۾��� : ��ȣ��										*/
/********************************************************/

class tile : public gameNode
{
private:
	POINT _centerPt;
	POINT _index;
	//RECT _tileRc;

	BOOL _isChecked;
	ATTRIBUTE _terrainAttribute;
	ATTRIBUTE _objectAttribute;

private:
	TERRAIN _terrain;
	OBJECT _object;

private:
	string _terrainImageKey;
	string _objectImageKey;

	POINT _terrainFramePos;
	POINT _objectFramePos;

	//===============A*�� ���� Ÿ�� FGH��� ���� �߰�===============================//
	//2018.2.10 ����ȯ
private:
	float _totalCost;
	float _costFromStart;
	float _costToGoal;

	bool _isOpen;			//���� �ִ� Ÿ������ ����
	tile* _parentNode;		//��� ���ŵǴ� ���� �ִܰŸ� Ÿ��

	string _attribute;		//Ÿ���� �Ӽ��� ��Ʈ�� 


public:
	tile();
	~tile();

	HRESULT init(POINT center);
	void release(void);
	void update(void);
	void render(HDC hdc, int destX, int destY);

	void terrainRender(HDC hdc, int destX, int destY);
	void objectRender(HDC hdc, int destX, int destY);
	void afterObjectRender(HDC hdc, int destX, int destY);
	void attributeRender(HDC hdc, int destX, int destY);

	void selectTerrain(tile sour);
	void selectObject(tile sour);

	void setTerrain(tile sour);
	void setObject(tile sour);
	void eraseObject(void);

	void updateTerrainAttr(void);
	void updateObjectAttr(void);

	//======================= ������ & ������ =======================
	inline void setCenterPt(POINT center) { _centerPt = center; }
	inline POINT getCenterPt(void) { return _centerPt; }

	inline void setIndex(POINT id) { _index = id; }
	inline POINT getIndex(void) { return _index; }

	//inline void setTileRect(RECT rc) { _tileRc = rc; }
	//inline RECT getTileRect(void) { return _tileRc; }

	inline void setIsChecked(BOOL isChecked) { _isChecked = isChecked; }
	inline BOOL getIsChecked(void) { return _isChecked; }

	inline void setTerrainAttr(ATTRIBUTE attr) { _terrainAttribute = attr; }
	inline ATTRIBUTE getTerrainAttr(void) { return _terrainAttribute; }

	inline void setObjectAttr(ATTRIBUTE attr) { _objectAttribute = attr; }
	inline ATTRIBUTE getObjectAttr(void) { return _objectAttribute; }

	inline void setTerrain(TERRAIN terrain) { _terrain = terrain; }
	inline TERRAIN getTerrain(void) { return _terrain; }

	inline void setObject(OBJECT obj) { _object = obj; }
	inline OBJECT getObject(void) { return _object; }

	inline void setTerrainImageKey(string imageKey) { _terrainImageKey = imageKey; }
	inline string getTerrainImageKey(void) { return _terrainImageKey; }

	inline void setObjectImageKey(string imageKey) { _objectImageKey = imageKey; }
	inline string getObjectImageKey(void) { return _objectImageKey; }

	inline void setTerrainFramePos(POINT framePos) { _terrainFramePos = framePos; }
	inline POINT getTerrainFramePos(void) { return _terrainFramePos; }

	inline void setObjectFramePos(POINT framePos) { _objectFramePos = framePos; }
	inline POINT getObjectFramePos(void) { return _objectFramePos; }

	//===========A*�� ���� ���� ������ �߰� ================//
	//2018.2.10 ����ȯ

	void setTotalCost(float totalCost) { _totalCost = totalCost; }
	float getTotalCost() { return _totalCost; }

	void setCostToGoal(float costToGoal) { _costToGoal = costToGoal; }
	float getCostToGoal() { return _costToGoal; }

	void setCostFromStart(float costFromStart) { _costFromStart = costFromStart; }
	float getCostFromStart() { return _costFromStart; }

	void setParentNode(tile* t) { _parentNode = t; }
	tile* getParentNode() { return _parentNode; }

	void setIsOpen(bool isOpen) { _isOpen = isOpen; }
	bool getIsOpen() { return _isOpen; }

	void setAttribute(string attribute) { _attribute = attribute; }
	string getAttribute() { return _attribute; }



};

