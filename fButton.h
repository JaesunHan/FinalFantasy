#pragma once
#include "gameNode.h"
#include <vector>


struct tagButton
{
	image* img;             //��ư �̹���
	float x, y;             //��ư ��ġ
	float centerX, centerY; //��ư �߽���
	bool aniStart;          //��ư ���Ͻ���
	animation* ani;         //��ư ���ϸ��̼�
	char* text;             //��ư ����
	float textSize;         //��ư ���� ũ��
	bool textOn;            //��ư ���� ��¿���
};


class fButton : public gameNode
{
private:
	typedef vector<tagButton>			    vButton;
	typedef vector<tagButton>::iterator     viButton;

protected:
	//======== button ========
	vButton   _vButton;
	viButton  _viButton;
	int       _buttonNum;
	

	tagButton _button;
	//======== button ========


public:
	//================================ button ===============================
	HRESULT init();
	void buttonSet(string keyName, float x, float y);
	void buttonSet(string keyName, float x, float y, char* buttonText, float textSize = 10);
	void release();
	void update();
	void render();
	void buttonRemove();
	void buttonRemoveOne(int buttonNum);
	//================================ button ===============================

	//=========================== getter & setter ===========================
	vButton getVButton() { return _vButton; }
	void setVButtonAniStart(int num, bool aniStart) { _vButton[num].aniStart = aniStart; }
	int getButtonNum() { return _buttonNum; }
	char* getButtonText(int num) { return _vButton[num].text; }
	//=========================== getter & setter ===========================

	fButton();
	~fButton();
};
