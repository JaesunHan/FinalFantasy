#pragma once
#include "singletonBase.h"
#include <vector>
#include <map>

#define ELEMENTNUM 8 + 1

struct tagElements
{
	string characterName;
	string currentHP;
	string maxHP;
	string currentMP;
	string maxMP;
	string steps;
	string gil;
	string currentScene;
};

//elements == 속성들 
class elements
{
public:
	const char* characterName;
	int currentHP;
	int maxHP;
	int currentMP;
	int maxMP;
	int steps;
	int gil;
	const char* currentScene;

	elements() {};
	~elements() {};
};

//내부 싱글톤 DB 만들어둔다
class database : public singletonBase <database>
{
private:
	typedef vector<string> arrElements;
	typedef vector<string>::iterator iterElements;

	typedef map<string, elements*> arrElement;
	typedef map<string, elements*>::iterator iterElement;

private:
	arrElement _mTotalElement;


public:
	HRESULT init();
	void release();

	void saveDatabase(tagElements playerElements);
	void loadDatabase(string name);

	//속성에 대한 접근자
	elements* getElementData(string str) { return _mTotalElement.find(str)->second; }

	//설정자
	void setElementDataCurrentHP(string str, float currentHp);
	void setElementDataMaxHP(string str, float maxHp);
	void setElementDataCurrentMP(string str, float currentMP);
	void setElementDataMaxMP(string str, float maxMP);
	void setElementDataSteps(string str, float steps);
	void setElementDataGil(string str, float gil);
	void setElementDataCurrentScene(string str, const char* currentScene);


	database();
	~database();
};

