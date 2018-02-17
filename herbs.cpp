#include "stdafx.h"
#include "herbs.h"

herbs::herbs()
{
}

herbs::~herbs()
{

}

HRESULT herbs::init(itemKind itemKind, char itemName[MAXNAMESIZE], char description[MAXNAMESIZE], int price)
{
	expendablesItem::init(itemKind, itemName, description, price);
	

	return S_OK;
}

void herbs::release()																					  
{

}

void herbs::update()																					  
{

}
