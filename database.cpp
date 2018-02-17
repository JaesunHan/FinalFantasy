#include "stdafx.h"
#include "database.h"


database::database()
{
}


database::~database()
{

}

HRESULT database::init()
{
	loadDatabase("database.txt");

	return S_OK;
}

void database::release()
{

}


void database::loadDatabase(string name)
{
	arrElements vTemp;
	vTemp = TXTDATA->txtLoad(name.c_str());

	string str;
	int count = 0;

	for (int i = 0; i < vTemp.size(); ++i)
	{
		//칸막이를 찾았으면
		if (vTemp[i] == "|")
		{
			elements* em = new elements;
			str = vTemp[i + 1];

			_mTotalElement.insert(pair<string, elements*>(vTemp[i + 1], em));

			if (i != 0) count += ELEMENTNUM;  //이상하면 볼것 (ELEMENTNUM -> 1)
			continue;
		}

		iterElement mIter = _mTotalElement.find(str);

		if      (i == count + 1) mIter->second->characterName = vTemp[i].c_str();
		else if (i == count + 2) mIter->second->currentHP = atoi(vTemp[i].c_str());
		else if (i == count + 3) mIter->second->maxHP = atoi(vTemp[i].c_str());
		else if (i == count + 4) mIter->second->currentMP = atoi(vTemp[i].c_str());
		else if (i == count + 5) mIter->second->maxMP = atoi(vTemp[i].c_str());
		else if (i == count + 6) mIter->second->steps = atoi(vTemp[i].c_str());
		else if (i == count + 7) mIter->second->gil = atoi(vTemp[i].c_str());
		else if (i == count + 8) mIter->second->currentScene = vTemp[i].c_str();
	}

	vTemp.clear();
}

void database::saveDatabase(tagElements playerElements)
{
	arrElements vTemp;

	//tagElements sTemp;
	//sTemp.characterName   = "TINA";
	//sTemp.currentHP		= "56";
	//sTemp.maxMP			= "56";
	//sTemp.currentMP		= "27";
	//sTemp.maxMP			= "27";
	//sTemp.gil				= "3000";
	//sTemp.steps			= "0";
	//sTemp.currentScene    = "forest"; 

	vTemp.push_back("|");
	vTemp.push_back(playerElements.characterName);
	vTemp.push_back(playerElements.currentHP);
	vTemp.push_back(playerElements.maxMP);
	vTemp.push_back(playerElements.currentMP);
	vTemp.push_back(playerElements.maxMP);
	vTemp.push_back(playerElements.gil);
	vTemp.push_back(playerElements.steps);
	vTemp.push_back(playerElements.currentScene);


	TXTDATA->txtSave("database", vTemp);
}


void database::setElementDataCurrentHP(string str, float currentHP)	  
{
	iterElement mIter = _mTotalElement.find(str);

	mIter->second->currentHP = currentHP;
}

void database::setElementDataMaxHP(string str, float maxHP)  
{
	iterElement mIter = _mTotalElement.find(str);

	mIter->second->maxHP = maxHP;
}

void database::setElementDataCurrentMP(string str, float currentMP)
{
	iterElement mIter = _mTotalElement.find(str);

	mIter->second->currentMP = currentMP;
}

void database::setElementDataMaxMP(string str, float maxMP)
{
	iterElement mIter = _mTotalElement.find(str);

	mIter->second->maxMP = maxMP;
}

void database::setElementDataSteps(string str, float steps)
{
	iterElement mIter = _mTotalElement.find(str);

	mIter->second->steps = steps;
}

void database::setElementDataGil(string str, float gil)
{
	iterElement mIter = _mTotalElement.find(str);

	mIter->second->gil = gil;
}

void database::setElementDataCurrentScene(string str, const char* currentScene)
{
	iterElement mIter = _mTotalElement.find(str);

	mIter->second->currentScene = currentScene;
}
