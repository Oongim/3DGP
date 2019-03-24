#pragma once

//-----------------------------------------------------------------------------
// File: GameFramework.h
//-----------------------------------------------------------------------------

#ifndef _GAME_APPLICATION_FRAMEWORK_H_
#define _GAME_APPLICATION_FRAMEWORK_H_

#include "stdafx.h"

#include "GameObject.h"

#define FULLSCREEN_WIDTH	640
#define FULLSCREEN_HEIGHT	480

class CGameFramework
{
public:
	CGameFramework(void);
	~CGameFramework(void);

	bool OnCreate(HINSTANCE hInstance, HWND hMainWnd);
	void OnDestroy();
	void FrameAdvance();
	void SetActive(bool bActive) { m_bActive = bActive; }
	void ResetDisplay(int nClientWidth=0, int nClientHeight=0);

private:
	HINSTANCE					m_hInstance;
	HWND						m_hWnd; 
	HMENU						m_hMenu;

    HDC							m_hDCFrameBuffer;   
    HBITMAP						m_hBitmapFrameBuffer;   
    HBITMAP						m_hBitmapSelect;     

	void BuildFrameBuffer();
	void ClearFrameBuffer(DWORD dwColor);
	void PresentFrameBuffer();

	void BuildObjects();
	void ReleaseObjects();
	void SetupGameState();
	void SetupRenderStates();
	void AnimateObjects();
	void ProcessInput();

	void DrawObject(CGameObject *pObject);
	void DrawPrimitive(CPolygon *pPolygon, CGameObject *pObject);

    bool						m_bActive;          

	ULONG						m_xViewport;          	
    ULONG						m_yViewport;          	
    ULONG						m_cxViewport;      	
    ULONG						m_cyViewport;     	

	CCamera						*m_pCamera;

	int							m_nObjects;
	CGameObject					*m_pObjects;

	CMesh *BuildCubeMesh(void);
};

#endif 

