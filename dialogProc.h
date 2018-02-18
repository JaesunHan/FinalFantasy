#pragma once
#include "stdafx.h"
#include "mapTool.h"

BOOL CALLBACK newTileProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	int mapSizeX = 0;
	int mapSizeY = 0;
	mapTool* pThis = (mapTool*)GetWindowLongPtr(hDlg, GWLP_USERDATA);

	switch (iMessage)
	{
	case WM_INITDIALOG:

		SetWindowPos(hDlg, HWND_TOP, 100, 100, 0, 0, SWP_NOSIZE);
		SetWindowLongPtr(hDlg, GWLP_USERDATA, (LONG_PTR)lParam);
		pThis = (mapTool*)lParam;
		pThis->setHandleNewTile(hDlg);
		break;

	case WM_COMMAND:

		switch (LOWORD(wParam))
		{
		case IDOK:
			mapSizeX = GetDlgItemInt(hDlg, IDC_EDIT1, NULL, FALSE);
			mapSizeY = GetDlgItemInt(hDlg, IDC_EDIT2, NULL, FALSE);
			pThis->createDefaultMap(PointMake(mapSizeX, mapSizeY));
		case IDCANCEL:
			EndDialog(pThis->getHandleNewTile(), 0);
			return TRUE;
		}

		return FALSE;
	case WM_CLOSE:
		EndDialog(hDlg, IDOK);
		return TRUE;
	}
	return FALSE;

}

BOOL CALLBACK selectTerrainTileSetProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	int selectPos = 0;
	char selectImageKey[1024] = "";
	mapTool* pThis = (mapTool*)GetWindowLongPtr(hDlg, GWLP_USERDATA);

	switch (iMessage)
	{
	case WM_INITDIALOG:

		SetWindowPos(hDlg, HWND_TOP, WINSIZEX + 3, 0, 0, 0, SWP_NOSIZE);
		SetWindowLongPtr(hDlg, GWLP_USERDATA, (LONG_PTR)lParam);
		pThis = (mapTool*)lParam;
		pThis->setHandleSelTerrain(hDlg);
		SendMessage(GetDlgItem(hDlg, IDC_LIST1), LB_ADDSTRING, 0, (LPARAM)"worldTerrain");
		SendMessage(GetDlgItem(hDlg, IDC_LIST1), LB_ADDSTRING, 0, (LPARAM)"townTerrain1");
		SendMessage(GetDlgItem(hDlg, IDC_LIST1), LB_ADDSTRING, 0, (LPARAM)"townTerrain2");
		SendMessage(GetDlgItem(hDlg, IDC_LIST1), LB_ADDSTRING, 0, (LPARAM)"townTerrain3");
		SendMessage(GetDlgItem(hDlg, IDC_LIST1), LB_ADDSTRING, 0, (LPARAM)"tempTile");
		SendMessage(GetDlgItem(hDlg, IDC_LIST1), LB_ADDSTRING, 0, (LPARAM)"testTileSet");

		selectPos = SendMessage(GetDlgItem(hDlg, IDC_LIST1), LB_FINDSTRINGEXACT, 0, (LPARAM)pThis->getTerrainTileImageKey().c_str());
		SendMessage(GetDlgItem(hDlg, IDC_LIST1), LB_SETCURSEL, (WPARAM)selectPos, 0);
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_LIST1:
			switch (HIWORD(wParam))
			{
			case LBN_SELCHANGE:
				selectPos = SendMessage(GetDlgItem(hDlg, IDC_LIST1), LB_GETCURSEL, 0, 0);
				SendMessage(GetDlgItem(hDlg, IDC_LIST1), LB_GETTEXT, (WPARAM)selectPos, (LPARAM)selectImageKey);
				pThis->setTerrainTileImageKey(selectImageKey);
				pThis->terrainTileSetInit();
				pThis->setSelectMode(MODE_TERRAIN_SELECT);
				pThis->getSelTerrainTile().selectTerrain(pThis->getFirstTerrainTile());
			default:
				break;
			}
			break;
		}

		return FALSE;
	case WM_CLOSE:
		pThis->setHandleSelTerrain(NULL);
		EndDialog(hDlg, IDOK);
		return TRUE;
	}
	return FALSE;
}

BOOL CALLBACK selectObjectTileSetProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	int selectPos = 0;
	static char selectImageKey[256] = "";
	mapTool* pThis = (mapTool*)GetWindowLongPtr(hDlg, GWLP_USERDATA);

	HDC hdc;
	PAINTSTRUCT ps;
	RECT rc;
	POINT ptMouse;

	switch (iMessage)
	{
	case WM_INITDIALOG:		// ���̾�α� �ڽ� ó�� ������ ȣ��
		SetWindowPos(hDlg, HWND_TOP, WINSIZEX + 3, 0, 0, 0, SWP_NOSIZE);		// �������� ũ��� ��ġ�� ����
		SetWindowLongPtr(hDlg, GWLP_USERDATA, (LONG_PTR)lParam);
		pThis = (mapTool*)lParam;												//CreateDialogParam, DialogBoxParam�Լ��� ���� ���޹��� ������ ����
		pThis->setHandleSelObject(hDlg);
		// �޺� �ڽ��� ������Ʈ �̹��� Ű ���� ����
		SendMessage(GetDlgItem(hDlg, IDC_LIST1), LB_ADDSTRING, 0, (LPARAM)"townHouse1");
		SendMessage(GetDlgItem(hDlg, IDC_LIST1), LB_ADDSTRING, 0, (LPARAM)"townHouse2");
		SendMessage(GetDlgItem(hDlg, IDC_LIST1), LB_ADDSTRING, 0, (LPARAM)"townHouse3");
		SendMessage(GetDlgItem(hDlg, IDC_LIST1), LB_ADDSTRING, 0, (LPARAM)"townHouse4");
		SendMessage(GetDlgItem(hDlg, IDC_LIST1), LB_ADDSTRING, 0, (LPARAM)"townHouse5");
		SendMessage(GetDlgItem(hDlg, IDC_LIST1), LB_ADDSTRING, 0, (LPARAM)"townHouse6");
		SendMessage(GetDlgItem(hDlg, IDC_LIST1), LB_ADDSTRING, 0, (LPARAM)"townObject1");
		SendMessage(GetDlgItem(hDlg, IDC_LIST1), LB_ADDSTRING, 0, (LPARAM)"townObject2");
		SendMessage(GetDlgItem(hDlg, IDC_LIST1), LB_ADDSTRING, 0, (LPARAM)"townObject3");
		SendMessage(GetDlgItem(hDlg, IDC_LIST1), LB_ADDSTRING, 0, (LPARAM)"worldObject");

		selectPos = SendMessage(GetDlgItem(hDlg, IDC_LIST1), LB_FINDSTRINGEXACT, 0, (LPARAM)pThis->getObjectTileImageKey().c_str());
		SendMessage(GetDlgItem(hDlg, IDC_LIST1), LB_SETCURSEL, (WPARAM)selectPos, 0);

		//GetDlgItemText(hDlg, IDC_COMBO1, selectImageKey, 256);
		break;

	/*case WM_PAINT:		// ���̾�α� �ڽ��� �̹����� �׸��� ȣ��, invalidateRect�Լ��� ���� ȣ�� ����
		hdc = BeginPaint(hDlg, &ps);

		//pThis->getObjTileImage()->render(hdc, 11, 38);
		if (selectImageKey[0] != '\0')
		{
			for (int i = 0; i < pThis->getObjectTileSetSize().x * pThis->getObjectTileSetSize().y; i++)
			{
				pThis->getObjectTileSet()[i].render(hdc, -11, -38);
			}
		}

		EndPaint(hDlg, &ps);
		break;*/

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_LIST1:					// ����Ʈ�ڽ� ���� �κ�
			switch (HIWORD(wParam))
			{
			case LBN_SELCHANGE:				// ����Ʈ�ڽ����� ������ ��
				selectPos = SendMessage(GetDlgItem(hDlg, IDC_LIST1), LB_GETCURSEL, 0, 0);
				SendMessage(GetDlgItem(hDlg, IDC_LIST1), LB_GETTEXT, (WPARAM)selectPos, (LPARAM)selectImageKey);
				pThis->setObjectTileImageKey(selectImageKey);
				pThis->objectTileSetInit();
				pThis->setSelectMode(MODE_OBJECT_SELECT);
				pThis->getSelObjectTile().selectObject(pThis->getFirstObjectTile());
				//SetWindowPos(hDlg, HWND_TOP, WINSIZEX + 3, 160, pThis->getObjTileImage()->getWidth() + 50, pThis->getObjTileImage()->getHeight() + 88, NULL);
				//GetClientRect(hDlg, &rc);
				//InvalidateRect(hDlg, &rc, TRUE);
				break;
			}
			break;
		}
		return FALSE;
	/*case WM_KEYDOWN:		// Ű �Է��� �߻��� ���
		switch (wParam)
		{
		case VK_LBUTTON:
			for (int i = 0; i < pThis->getObjectTileSetSize().x * pThis->getObjectTileSetSize().y; i++)
			{
				if (PtInRect(&RectMakeCenter(pThis->getObjectTileSet()[i].getCenterPt().x, pThis->getObjectTileSet()[i].getCenterPt().y, TILE_SIZEX, TILE_SIZEY), ptMouse))
				{
					pThis->setSelObjectTile(pThis->getObjectTileSet()[i]);
				}
				pThis->getObjectTileSet()[i].render(hdc, -11, -38);
			}
			break;

		}
		break;
	case WM_MOUSEMOVE:
		ptMouse.x = static_cast<float>LOWORD(lParam);
		ptMouse.y = static_cast<float>HIWORD(lParam);
		break;*/
	case WM_CLOSE:		// ���� ��ư Ŭ����
		pThis->setHandleSelObject(NULL);
		EndDialog(hDlg, IDOK);
		return TRUE;
	}
	return FALSE;
}
