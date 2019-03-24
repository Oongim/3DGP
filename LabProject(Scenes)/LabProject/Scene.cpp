#include "stdafx.h"
#include "Scene.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
CScene::CScene()
{
}

CScene::~CScene()
{
}

void CScene::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
}

void CScene::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
}

void CScene::BuildObjects()
{
}

void CScene::ReleaseObjects()
{
}

void CScene::CheckObjectByObjectCollisions()
{
	for (int i = 0; i < m_nObjects; i++) m_ppObjects[i]->m_pObjectCollided = NULL;
	for (int i = 0; i < m_nObjects; i++)
	{
		for (int j = (i + 1); j < m_nObjects; j++)
		{
			if (m_ppObjects[i]->m_xmOOBB.Intersects(m_ppObjects[j]->m_xmOOBB))
			{
				m_ppObjects[i]->m_pObjectCollided = m_ppObjects[j];
				m_ppObjects[j]->m_pObjectCollided = m_ppObjects[i];
			}
		}
	}
	for (int i = 0; i < m_nObjects; i++)
	{
		if (m_ppObjects[i]->m_pObjectCollided)
		{
			XMFLOAT3 xmf3MovingDirection = m_ppObjects[i]->m_xmf3MovingDirection;
			float fMovingSpeed = m_ppObjects[i]->m_fMovingSpeed;
			m_ppObjects[i]->m_xmf3MovingDirection = m_ppObjects[i]->m_pObjectCollided->m_xmf3MovingDirection;
			m_ppObjects[i]->m_fMovingSpeed = m_ppObjects[i]->m_pObjectCollided->m_fMovingSpeed;
			m_ppObjects[i]->m_pObjectCollided->m_xmf3MovingDirection = xmf3MovingDirection;
			m_ppObjects[i]->m_pObjectCollided->m_fMovingSpeed = fMovingSpeed;
			m_ppObjects[i]->m_pObjectCollided->m_pObjectCollided = NULL;
			m_ppObjects[i]->m_pObjectCollided = NULL;
		}
	}
}

void CScene::Animate(float fElapsedTime)
{
	for (int i = 0; i < m_nObjects; i++) m_ppObjects[i]->Animate(fElapsedTime);

	CheckObjectByObjectCollisions();
}

void CScene::Render(HDC hDCFrameBuffer, CCamera *pCamera)
{
	for (int i = 0; i < m_nObjects; i++) m_ppObjects[i]->Render(hDCFrameBuffer, pCamera);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
CPlayerScene::CPlayerScene()
{
}

CPlayerScene::~CPlayerScene()
{
}

void CPlayerScene::BuildObjects()
{
	CCubeMesh *pObjectCubeMesh = new CCubeMesh(4.0f, 4.0f, 4.0f);
	pObjectCubeMesh->SetOOBB(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(2.0f, 2.0f, 2.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));

	m_nObjects = 10;
	m_ppObjects = new CGameObject*[m_nObjects];

	m_ppObjects[0] = new CGameObject();
	m_ppObjects[0]->SetMesh(pObjectCubeMesh);
	m_ppObjects[0]->SetColor(RGB(255, 0, 0));
	m_ppObjects[0]->SetPosition(-13.5f, 0.0f, -14.0f);
	m_ppObjects[0]->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 1.0f));
	m_ppObjects[0]->SetRotationSpeed(90.0f);
	m_ppObjects[0]->SetMovingDirection(XMFLOAT3(1.0f, 0.0f, 0.0f));
	m_ppObjects[0]->SetMovingSpeed(10.5f);

	m_ppObjects[1] = new CGameObject();
	m_ppObjects[1]->SetMesh(pObjectCubeMesh);
	m_ppObjects[1]->SetColor(RGB(0, 0, 255));
	m_ppObjects[1]->SetPosition(+13.5f, 0.0f, -14.0f);
	m_ppObjects[1]->SetRotationAxis(XMFLOAT3(1.0f, 1.0f, 0.0f));
	m_ppObjects[1]->SetRotationSpeed(180.0f);
	m_ppObjects[1]->SetMovingDirection(XMFLOAT3(-1.0f, 0.0f, 0.0f));
	m_ppObjects[1]->SetMovingSpeed(8.8f);

	m_ppObjects[2] = new CGameObject();
	m_ppObjects[2]->SetMesh(pObjectCubeMesh);
	m_ppObjects[2]->SetColor(RGB(0, 255, 0));
	m_ppObjects[2]->SetPosition(0.0f, +5.0f, 20.0f);
	m_ppObjects[2]->SetRotationAxis(XMFLOAT3(1.0f, 1.0f, 0.0f));
	m_ppObjects[2]->SetRotationSpeed(30.15f);
	m_ppObjects[2]->SetMovingDirection(XMFLOAT3(1.0f, -1.0f, 0.0f));
	m_ppObjects[2]->SetMovingSpeed(5.2f);

	m_ppObjects[3] = new CGameObject();
	m_ppObjects[3]->SetMesh(pObjectCubeMesh);
	m_ppObjects[3]->SetColor(RGB(0, 255, 255));
	m_ppObjects[3]->SetPosition(0.0f, 0.0f, 0.0f);
	m_ppObjects[3]->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 1.0f));
	m_ppObjects[3]->SetRotationSpeed(40.6f);
	m_ppObjects[3]->SetMovingDirection(XMFLOAT3(0.0f, 0.0f, 1.0f));
	m_ppObjects[3]->SetMovingSpeed(20.4f);

	m_ppObjects[4] = new CGameObject();
	m_ppObjects[4]->SetMesh(pObjectCubeMesh);
	m_ppObjects[4]->SetColor(RGB(128, 0, 255));
	m_ppObjects[4]->SetPosition(10.0f, 0.0f, 0.0f);
	m_ppObjects[4]->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
	m_ppObjects[4]->SetRotationSpeed(50.06f);
	m_ppObjects[4]->SetMovingDirection(XMFLOAT3(0.0f, 1.0f, 1.0f));
	m_ppObjects[4]->SetMovingSpeed(6.4f);

	m_ppObjects[5] = new CGameObject();
	m_ppObjects[5]->SetMesh(pObjectCubeMesh);
	m_ppObjects[5]->SetColor(RGB(255, 0, 255));
	m_ppObjects[5]->SetPosition(-10.0f, 0.0f, -10.0f);
	m_ppObjects[5]->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
	m_ppObjects[5]->SetRotationSpeed(60.06f);
	m_ppObjects[5]->SetMovingDirection(XMFLOAT3(1.0f, 0.0f, 1.0f));
	m_ppObjects[5]->SetMovingSpeed(8.9f);

	m_ppObjects[6] = new CGameObject();
	m_ppObjects[6]->SetMesh(pObjectCubeMesh);
	m_ppObjects[6]->SetColor(RGB(255, 0, 255));
	m_ppObjects[6]->SetPosition(-10.0f, 10.0f, -10.0f);
	m_ppObjects[6]->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
	m_ppObjects[6]->SetRotationSpeed(60.06f);
	m_ppObjects[6]->SetMovingDirection(XMFLOAT3(1.0f, 1.0f, 1.0f));
	m_ppObjects[6]->SetMovingSpeed(9.7f);

	m_ppObjects[7] = new CGameObject();
	m_ppObjects[7]->SetMesh(pObjectCubeMesh);
	m_ppObjects[7]->SetColor(RGB(255, 0, 128));
	m_ppObjects[7]->SetPosition(-10.0f, 10.0f, -20.0f);
	m_ppObjects[7]->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
	m_ppObjects[7]->SetRotationSpeed(70.06f);
	m_ppObjects[7]->SetMovingDirection(XMFLOAT3(-1.0f, 1.0f, 1.0f));
	m_ppObjects[7]->SetMovingSpeed(15.6f);

	m_ppObjects[8] = new CGameObject();
	m_ppObjects[8]->SetMesh(pObjectCubeMesh);
	m_ppObjects[8]->SetColor(RGB(128, 0, 255));
	m_ppObjects[8]->SetPosition(-15.0f, 10.0f, -30.0f);
	m_ppObjects[8]->SetRotationAxis(XMFLOAT3(1.0f, 1.0f, 0.0f));
	m_ppObjects[8]->SetRotationSpeed(90.06f);
	m_ppObjects[8]->SetMovingDirection(XMFLOAT3(0.0f, 0.0f, -1.0f));
	m_ppObjects[8]->SetMovingSpeed(15.0f);

	m_ppObjects[9] = new CGameObject();
	m_ppObjects[9]->SetMesh(pObjectCubeMesh);
	m_ppObjects[9]->SetColor(RGB(255, 64, 64));
	m_ppObjects[9]->SetPosition(+15.0f, 10.0f, 0.0f);
	m_ppObjects[9]->SetRotationAxis(XMFLOAT3(1.0f, 1.0f, 0.0f));
	m_ppObjects[9]->SetRotationSpeed(90.06f);
	m_ppObjects[9]->SetMovingDirection(XMFLOAT3(-0.0f, 0.0f, -1.0f));
	m_ppObjects[9]->SetMovingSpeed(15.0f);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
CCollisionScene::CCollisionScene()
{
}

CCollisionScene::~CCollisionScene()
{
}

void CCollisionScene::BuildObjects()
{
	float fHalfWidth = 45.0f, fHalfHeight = 45.0f, fHalfDepth = 110.0f;
	CWallMesh *pWallCubeMesh = new CWallMesh(fHalfWidth * 2.0f, fHalfHeight * 2.0f, fHalfDepth * 2.0f, 30);
	pWallCubeMesh->SetOOBB(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(fHalfWidth, fHalfHeight, fHalfDepth * 0.3f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));

	m_pWallsObject = new CWallsObject();
	m_pWallsObject->SetPosition(0.0f, 0.0f, 0.0f);
	m_pWallsObject->SetMesh(pWallCubeMesh);
	m_pWallsObject->SetColor(RGB(0, 0, 0));
	m_pWallsObject->m_pxmf4WallPlanes[0] = XMFLOAT4(+1.0f, 0.0f, 0.0f, fHalfWidth);
	m_pWallsObject->m_pxmf4WallPlanes[1] = XMFLOAT4(-1.0f, 0.0f, 0.0f, fHalfWidth);
	m_pWallsObject->m_pxmf4WallPlanes[2] = XMFLOAT4(0.0f, +1.0f, 0.0f, fHalfHeight);
	m_pWallsObject->m_pxmf4WallPlanes[3] = XMFLOAT4(0.0f, -1.0f, 0.0f, fHalfHeight);
	m_pWallsObject->m_pxmf4WallPlanes[4] = XMFLOAT4(0.0f, 0.0f, +1.0f, fHalfDepth);
	m_pWallsObject->m_pxmf4WallPlanes[5] = XMFLOAT4(0.0f, 0.0f, -1.0f, fHalfDepth);

	CCubeMesh *pObjectCubeMesh = new CCubeMesh(4.0f, 4.0f, 4.0f);
	pObjectCubeMesh->SetOOBB(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(2.0f, 2.0f, 2.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));

	m_nObjects = 10;
	m_ppObjects = new CGameObject*[m_nObjects];

	m_ppObjects[0] = new CGameObject();
	m_ppObjects[0]->SetMesh(pObjectCubeMesh);
	m_ppObjects[0]->SetColor(RGB(255, 0, 0));
	m_ppObjects[0]->SetPosition(-13.5f, 0.0f, -14.0f);
	m_ppObjects[0]->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 1.0f));
	m_ppObjects[0]->SetRotationSpeed(90.0f);
	m_ppObjects[0]->SetMovingDirection(XMFLOAT3(1.0f, 0.0f, 0.0f));
	m_ppObjects[0]->SetMovingSpeed(10.5f);

	m_ppObjects[1] = new CGameObject();
	m_ppObjects[1]->SetMesh(pObjectCubeMesh);
	m_ppObjects[1]->SetColor(RGB(0, 0, 255));
	m_ppObjects[1]->SetPosition(+13.5f, 0.0f, -14.0f);
	m_ppObjects[1]->SetRotationAxis(XMFLOAT3(1.0f, 1.0f, 0.0f));
	m_ppObjects[1]->SetRotationSpeed(180.0f);
	m_ppObjects[1]->SetMovingDirection(XMFLOAT3(-1.0f, 0.0f, 0.0f));
	m_ppObjects[1]->SetMovingSpeed(8.8f);

	m_ppObjects[2] = new CGameObject();
	m_ppObjects[2]->SetMesh(pObjectCubeMesh);
	m_ppObjects[2]->SetColor(RGB(0, 255, 0));
	m_ppObjects[2]->SetPosition(0.0f, +5.0f, 20.0f);
	m_ppObjects[2]->SetRotationAxis(XMFLOAT3(1.0f, 1.0f, 0.0f));
	m_ppObjects[2]->SetRotationSpeed(30.15f);
	m_ppObjects[2]->SetMovingDirection(XMFLOAT3(1.0f, -1.0f, 0.0f));
	m_ppObjects[2]->SetMovingSpeed(5.2f);

	m_ppObjects[3] = new CGameObject();
	m_ppObjects[3]->SetMesh(pObjectCubeMesh);
	m_ppObjects[3]->SetColor(RGB(0, 255, 255));
	m_ppObjects[3]->SetPosition(0.0f, 0.0f, 0.0f);
	m_ppObjects[3]->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 1.0f));
	m_ppObjects[3]->SetRotationSpeed(40.6f);
	m_ppObjects[3]->SetMovingDirection(XMFLOAT3(0.0f, 0.0f, 1.0f));
	m_ppObjects[3]->SetMovingSpeed(20.4f);

	m_ppObjects[4] = new CGameObject();
	m_ppObjects[4]->SetMesh(pObjectCubeMesh);
	m_ppObjects[4]->SetColor(RGB(128, 0, 255));
	m_ppObjects[4]->SetPosition(10.0f, 0.0f, 0.0f);
	m_ppObjects[4]->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
	m_ppObjects[4]->SetRotationSpeed(50.06f);
	m_ppObjects[4]->SetMovingDirection(XMFLOAT3(0.0f, 1.0f, 1.0f));
	m_ppObjects[4]->SetMovingSpeed(6.4f);

	m_ppObjects[5] = new CGameObject();
	m_ppObjects[5]->SetMesh(pObjectCubeMesh);
	m_ppObjects[5]->SetColor(RGB(255, 0, 255));
	m_ppObjects[5]->SetPosition(-10.0f, 0.0f, -10.0f);
	m_ppObjects[5]->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
	m_ppObjects[5]->SetRotationSpeed(60.06f);
	m_ppObjects[5]->SetMovingDirection(XMFLOAT3(1.0f, 0.0f, 1.0f));
	m_ppObjects[5]->SetMovingSpeed(8.9f);

	m_ppObjects[6] = new CGameObject();
	m_ppObjects[6]->SetMesh(pObjectCubeMesh);
	m_ppObjects[6]->SetColor(RGB(255, 0, 255));
	m_ppObjects[6]->SetPosition(-10.0f, 10.0f, -10.0f);
	m_ppObjects[6]->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
	m_ppObjects[6]->SetRotationSpeed(60.06f);
	m_ppObjects[6]->SetMovingDirection(XMFLOAT3(1.0f, 1.0f, 1.0f));
	m_ppObjects[6]->SetMovingSpeed(9.7f);

	m_ppObjects[7] = new CGameObject();
	m_ppObjects[7]->SetMesh(pObjectCubeMesh);
	m_ppObjects[7]->SetColor(RGB(255, 0, 128));
	m_ppObjects[7]->SetPosition(-10.0f, 10.0f, -20.0f);
	m_ppObjects[7]->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
	m_ppObjects[7]->SetRotationSpeed(70.06f);
	m_ppObjects[7]->SetMovingDirection(XMFLOAT3(-1.0f, 1.0f, 1.0f));
	m_ppObjects[7]->SetMovingSpeed(15.6f);

	m_ppObjects[8] = new CGameObject();
	m_ppObjects[8]->SetMesh(pObjectCubeMesh);
	m_ppObjects[8]->SetColor(RGB(128, 0, 255));
	m_ppObjects[8]->SetPosition(-15.0f, 10.0f, -30.0f);
	m_ppObjects[8]->SetRotationAxis(XMFLOAT3(1.0f, 1.0f, 0.0f));
	m_ppObjects[8]->SetRotationSpeed(90.06f);
	m_ppObjects[8]->SetMovingDirection(XMFLOAT3(0.0f, 0.0f, -1.0f));
	m_ppObjects[8]->SetMovingSpeed(15.0f);

	m_ppObjects[9] = new CGameObject();
	m_ppObjects[9]->SetMesh(pObjectCubeMesh);
	m_ppObjects[9]->SetColor(RGB(255, 64, 64));
	m_ppObjects[9]->SetPosition(+15.0f, 10.0f, 0.0f);
	m_ppObjects[9]->SetRotationAxis(XMFLOAT3(1.0f, 1.0f, 0.0f));
	m_ppObjects[9]->SetRotationSpeed(90.06f);
	m_ppObjects[9]->SetMovingDirection(XMFLOAT3(-0.0f, 0.0f, -1.0f));
	m_ppObjects[9]->SetMovingSpeed(15.0f);
}

void CCollisionScene::ReleaseObjects()
{
	CScene::ReleaseObjects();

	if (m_pWallsObject) delete m_pWallsObject;
}

void CCollisionScene::CheckObjectByWallCollisions()
{
	for (int i = 0; i < m_nObjects; i++)
	{
		ContainmentType containType = m_pWallsObject->m_xmOOBB.Contains(m_ppObjects[i]->m_xmOOBB);
		switch (containType)
		{
		case DISJOINT:
		{
			int nPlaneIndex = -1;
			for (int j = 0; j < 6; j++)
			{
				PlaneIntersectionType intersectType = m_ppObjects[i]->m_xmOOBB.Intersects(XMLoadFloat4(&m_pWallsObject->m_pxmf4WallPlanes[j]));
				if (intersectType == BACK)
				{
					nPlaneIndex = j;
					break;
				}
			}
			if (nPlaneIndex != -1)
			{
				XMVECTOR xmvNormal = XMVectorSet(m_pWallsObject->m_pxmf4WallPlanes[nPlaneIndex].x, m_pWallsObject->m_pxmf4WallPlanes[nPlaneIndex].y, m_pWallsObject->m_pxmf4WallPlanes[nPlaneIndex].z, 0.0f);
				XMVECTOR xmvReflect = XMVector3Reflect(XMLoadFloat3(&m_ppObjects[i]->m_xmf3MovingDirection), xmvNormal);
				XMStoreFloat3(&m_ppObjects[i]->m_xmf3MovingDirection, xmvReflect);
			}
			break;
		}
		case INTERSECTS:
		{
			int nPlaneIndex = -1;
			for (int j = 0; j < 6; j++)
			{
				PlaneIntersectionType intersectType = m_ppObjects[i]->m_xmOOBB.Intersects(XMLoadFloat4(&m_pWallsObject->m_pxmf4WallPlanes[j]));
				if (intersectType == INTERSECTING)
				{
					nPlaneIndex = j;
					break;
				}
			}
			if (nPlaneIndex != -1)
			{
				XMVECTOR xmvNormal = XMVectorSet(m_pWallsObject->m_pxmf4WallPlanes[nPlaneIndex].x, m_pWallsObject->m_pxmf4WallPlanes[nPlaneIndex].y, m_pWallsObject->m_pxmf4WallPlanes[nPlaneIndex].z, 0.0f);
				XMVECTOR xmvReflect = XMVector3Reflect(XMLoadFloat3(&m_ppObjects[i]->m_xmf3MovingDirection), xmvNormal);
				XMStoreFloat3(&m_ppObjects[i]->m_xmf3MovingDirection, xmvReflect);
			}
			break;
		}
		case CONTAINS:
			break;
		}
	}
}

void CCollisionScene::Animate(float fElapsedTime)
{
	m_pWallsObject->Animate(fElapsedTime);
	if (m_pWallsObject->m_xmOOBB.Contains(XMLoadFloat3(&m_pPlayer->m_xmf3Position)) == DISJOINT) m_pWallsObject->SetPosition(m_pPlayer->m_xmf3Position);

	CheckObjectByWallCollisions();

	CScene::Animate(fElapsedTime);
}

void CCollisionScene::Render(HDC hDCFrameBuffer, CCamera *pCamera)
{
	m_pWallsObject->Render(hDCFrameBuffer, pCamera);

	CScene::Render(hDCFrameBuffer, pCamera);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
CExplosionScene::CExplosionScene()
{
}

CExplosionScene::~CExplosionScene()
{
}

void CExplosionScene::BuildObjects()
{
	CExplosiveObject::PrepareExplosion();

	float fHalfWidth = 45.0f, fHalfHeight = 45.0f, fHalfDepth = 110.0f;
	CWallMesh *pWallCubeMesh = new CWallMesh(fHalfWidth * 2.0f, fHalfHeight * 2.0f, fHalfDepth * 2.0f, 30);
	pWallCubeMesh->SetOOBB(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(fHalfWidth, fHalfHeight, fHalfDepth * 0.3f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));

	m_pWallsObject = new CWallsObject();
	m_pWallsObject->SetPosition(0.0f, 0.0f, 0.0f);
	m_pWallsObject->SetMesh(pWallCubeMesh);
	m_pWallsObject->SetColor(RGB(0, 0, 0));
	m_pWallsObject->m_pxmf4WallPlanes[0] = XMFLOAT4(+1.0f, 0.0f, 0.0f, fHalfWidth);
	m_pWallsObject->m_pxmf4WallPlanes[1] = XMFLOAT4(-1.0f, 0.0f, 0.0f, fHalfWidth);
	m_pWallsObject->m_pxmf4WallPlanes[2] = XMFLOAT4(0.0f, +1.0f, 0.0f, fHalfHeight);
	m_pWallsObject->m_pxmf4WallPlanes[3] = XMFLOAT4(0.0f, -1.0f, 0.0f, fHalfHeight);
	m_pWallsObject->m_pxmf4WallPlanes[4] = XMFLOAT4(0.0f, 0.0f, +1.0f, fHalfDepth);
	m_pWallsObject->m_pxmf4WallPlanes[5] = XMFLOAT4(0.0f, 0.0f, -1.0f, fHalfDepth);

	CCubeMesh *pObjectCubeMesh = new CCubeMesh(4.0f, 4.0f, 4.0f);
	pObjectCubeMesh->SetOOBB(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(2.0f, 2.0f, 2.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));

	m_nObjects = 10;
	m_ppObjects = new CGameObject*[m_nObjects];

	m_ppObjects[0] = new CExplosiveObject();
	m_ppObjects[0]->SetMesh(pObjectCubeMesh);
	m_ppObjects[0]->SetColor(RGB(255, 0, 0));
	m_ppObjects[0]->SetPosition(-13.5f, 0.0f, -14.0f);
	m_ppObjects[0]->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 1.0f));
	m_ppObjects[0]->SetRotationSpeed(90.0f);
	m_ppObjects[0]->SetMovingDirection(XMFLOAT3(1.0f, 0.0f, 0.0f));
	m_ppObjects[0]->SetMovingSpeed(10.5f);

	m_ppObjects[1] = new CExplosiveObject();
	m_ppObjects[1]->SetMesh(pObjectCubeMesh);
	m_ppObjects[1]->SetColor(RGB(0, 0, 255));
	m_ppObjects[1]->SetPosition(+13.5f, 0.0f, -14.0f);
	m_ppObjects[1]->SetRotationAxis(XMFLOAT3(1.0f, 1.0f, 0.0f));
	m_ppObjects[1]->SetRotationSpeed(180.0f);
	m_ppObjects[1]->SetMovingDirection(XMFLOAT3(-1.0f, 0.0f, 0.0f));
	m_ppObjects[1]->SetMovingSpeed(8.8f);

	m_ppObjects[2] = new CExplosiveObject();
	m_ppObjects[2]->SetMesh(pObjectCubeMesh);
	m_ppObjects[2]->SetColor(RGB(0, 255, 0));
	m_ppObjects[2]->SetPosition(0.0f, +5.0f, 20.0f);
	m_ppObjects[2]->SetRotationAxis(XMFLOAT3(1.0f, 1.0f, 0.0f));
	m_ppObjects[2]->SetRotationSpeed(30.15f);
	m_ppObjects[2]->SetMovingDirection(XMFLOAT3(1.0f, -1.0f, 0.0f));
	m_ppObjects[2]->SetMovingSpeed(5.2f);

	m_ppObjects[3] = new CExplosiveObject();
	m_ppObjects[3]->SetMesh(pObjectCubeMesh);
	m_ppObjects[3]->SetColor(RGB(0, 255, 255));
	m_ppObjects[3]->SetPosition(0.0f, 0.0f, 0.0f);
	m_ppObjects[3]->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 1.0f));
	m_ppObjects[3]->SetRotationSpeed(40.6f);
	m_ppObjects[3]->SetMovingDirection(XMFLOAT3(0.0f, 0.0f, 1.0f));
	m_ppObjects[3]->SetMovingSpeed(20.4f);

	m_ppObjects[4] = new CExplosiveObject();
	m_ppObjects[4]->SetMesh(pObjectCubeMesh);
	m_ppObjects[4]->SetColor(RGB(128, 0, 255));
	m_ppObjects[4]->SetPosition(10.0f, 0.0f, 0.0f);
	m_ppObjects[4]->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
	m_ppObjects[4]->SetRotationSpeed(50.06f);
	m_ppObjects[4]->SetMovingDirection(XMFLOAT3(0.0f, 1.0f, 1.0f));
	m_ppObjects[4]->SetMovingSpeed(6.4f);

	m_ppObjects[5] = new CExplosiveObject();
	m_ppObjects[5]->SetMesh(pObjectCubeMesh);
	m_ppObjects[5]->SetColor(RGB(255, 0, 255));
	m_ppObjects[5]->SetPosition(-10.0f, 0.0f, -10.0f);
	m_ppObjects[5]->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
	m_ppObjects[5]->SetRotationSpeed(60.06f);
	m_ppObjects[5]->SetMovingDirection(XMFLOAT3(1.0f, 0.0f, 1.0f));
	m_ppObjects[5]->SetMovingSpeed(8.9f);

	m_ppObjects[6] = new CExplosiveObject();
	m_ppObjects[6]->SetMesh(pObjectCubeMesh);
	m_ppObjects[6]->SetColor(RGB(255, 0, 255));
	m_ppObjects[6]->SetPosition(-10.0f, 10.0f, -10.0f);
	m_ppObjects[6]->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
	m_ppObjects[6]->SetRotationSpeed(60.06f);
	m_ppObjects[6]->SetMovingDirection(XMFLOAT3(1.0f, 1.0f, 1.0f));
	m_ppObjects[6]->SetMovingSpeed(9.7f);

	m_ppObjects[7] = new CExplosiveObject();
	m_ppObjects[7]->SetMesh(pObjectCubeMesh);
	m_ppObjects[7]->SetColor(RGB(255, 0, 128));
	m_ppObjects[7]->SetPosition(-10.0f, 10.0f, -20.0f);
	m_ppObjects[7]->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
	m_ppObjects[7]->SetRotationSpeed(70.06f);
	m_ppObjects[7]->SetMovingDirection(XMFLOAT3(-1.0f, 1.0f, 1.0f));
	m_ppObjects[7]->SetMovingSpeed(15.6f);

	m_ppObjects[8] = new CExplosiveObject();
	m_ppObjects[8]->SetMesh(pObjectCubeMesh);
	m_ppObjects[8]->SetColor(RGB(128, 0, 255));
	m_ppObjects[8]->SetPosition(-15.0f, 10.0f, -30.0f);
	m_ppObjects[8]->SetRotationAxis(XMFLOAT3(1.0f, 1.0f, 0.0f));
	m_ppObjects[8]->SetRotationSpeed(90.06f);
	m_ppObjects[8]->SetMovingDirection(XMFLOAT3(0.0f, 0.0f, -1.0f));
	m_ppObjects[8]->SetMovingSpeed(15.0f);

	m_ppObjects[9] = new CExplosiveObject();
	m_ppObjects[9]->SetMesh(pObjectCubeMesh);
	m_ppObjects[9]->SetColor(RGB(255, 64, 64));
	m_ppObjects[9]->SetPosition(+15.0f, 10.0f, 0.0f);
	m_ppObjects[9]->SetRotationAxis(XMFLOAT3(1.0f, 1.0f, 0.0f));
	m_ppObjects[9]->SetRotationSpeed(90.06f);
	m_ppObjects[9]->SetMovingDirection(XMFLOAT3(-0.0f, 0.0f, -1.0f));
}

void CExplosionScene::ReleaseObjects()
{
	if (CExplosiveObject::m_pExplosionMesh) CExplosiveObject::m_pExplosionMesh->Release();

	CCollisionScene::ReleaseObjects();
}

void CExplosionScene::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	switch (nMessageID)
	{
		case WM_KEYDOWN:
			switch (wParam)
			{
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
				{
					CExplosiveObject *pExplosiveObject = (CExplosiveObject *)m_ppObjects[int(wParam - '1')];
					pExplosiveObject->m_bBlowingUp = true;
					break;
				}
				case 'A':
					for (int i = 0; i < m_nObjects; i++)
					{
						CExplosiveObject *pExplosiveObject = (CExplosiveObject *)m_ppObjects[i];
						pExplosiveObject->m_bBlowingUp = true;
					}
					break;
				default:
					break;
			}
			break;
		default:
			break;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
CRunAwayScene::CRunAwayScene()
{
}

CRunAwayScene::~CRunAwayScene()
{
}

void CRunAwayScene::BuildObjects()
{
	float fHalfWidth = 100.0f, fHalfHeight = 0.0f, fHalfDepth = 100.0f;
	CTerrainMesh *pTerrainMesh = new CTerrainMesh(fHalfWidth * 2.0f, fHalfHeight * 2.0f, fHalfDepth * 2.0f, 100);
	pTerrainMesh->SetOOBB(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(fHalfWidth, fHalfHeight, fHalfDepth * 0.3f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));

	m_pTerrainObject = new CTerrainObject();
	m_pTerrainObject->SetPosition(0.0f, 0.0f, 0.0f);
	m_pTerrainObject->SetMesh(pTerrainMesh);
	m_pTerrainObject->SetColor(RGB(0, 0, 0));

	CCubeMesh *pObjectCubeMesh = new CCubeMesh(4.0f, 4.0f, 4.0f);
	pObjectCubeMesh->SetOOBB(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(2.0f, 2.0f, 2.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));

	m_nObjects = 31;
	m_ppObjects = new CGameObject*[m_nObjects];

	for (int i = 0; i < m_nObjects; i++)
	{
		m_ppObjects[i] = new CFollowerObject(m_pPlayer);
		m_ppObjects[i]->SetMesh(pObjectCubeMesh);
		m_ppObjects[i]->SetColor(RGB(0, 0, 255));
		m_ppObjects[i]->SetMovingSpeed(2.0f);
	}
	m_ppObjects[0]->SetPosition(-31, 0.5f, 3);
	m_ppObjects[1]->SetPosition(20.6f, 0.5f, 38.6f);
	m_ppObjects[2]->SetPosition(-32.37f, 0.5f, -28.24f);
	m_ppObjects[3]->SetPosition(7.1, 0.5f, -27.8f);
	m_ppObjects[4]->SetPosition(-24.32, 0.5f, 15.09f);
	m_ppObjects[5]->SetPosition(23.66, 0.5f, 21.14f);
	m_ppObjects[6]->SetPosition(12.1, 0.5f, 2.6f);
	m_ppObjects[7]->SetPosition(15.63, 0.5f, 17.11f);
	m_ppObjects[8]->SetPosition(-0.7, 0.5f, 33.6f);
	m_ppObjects[9]->SetPosition(-11.7, 0.5f, 4.4f);
	m_ppObjects[10]->SetPosition(-32.4, 0.5f, 31.4f);
	m_ppObjects[11]->SetPosition(-20.31, 0.5f, -11.1f);
	m_ppObjects[12]->SetPosition(-13.59, 0.5f, 27.54f);
	m_ppObjects[13]->SetPosition(-20.76, 0.5f, -20.03f);
	m_ppObjects[14]->SetPosition(11, 0.5f, -6.9f);
	m_ppObjects[15]->SetPosition(25.6, 0.5f, 7.8f);
	m_ppObjects[16]->SetPosition(19.74, 0.5f, -30.1f);
	m_ppObjects[17]->SetPosition(21.1, 0.5f, -10.9f);
	m_ppObjects[18]->SetPosition(37.44, 0.5f, -18.267f);
	m_ppObjects[19]->SetPosition(28.73, 0.5f, 1.25f);
	m_ppObjects[20]->SetPosition(40.7, 0.5f, 7.1f);
	m_ppObjects[21]->SetPosition(-5.501, 0.5f, 16.603f);
	m_ppObjects[22]->SetPosition(30.9, 0.5f, 30.7f);
	m_ppObjects[23]->SetPosition(27.03, 0.5f, -27.01f);
	m_ppObjects[24]->SetPosition(-8.56, 0.5f, -33.5f);
	m_ppObjects[25]->SetPosition(14.1, 0.5f, 31.8f);
	m_ppObjects[26]->SetPosition(-15.79, 0.5f, -36.63f);
	m_ppObjects[27]->SetPosition(-7.35, 0.5f, -20.1f);
	m_ppObjects[28]->SetPosition(-35.6, 0.5f, -16);
	m_ppObjects[29]->SetPosition(-17.8, 0.5f, 37.6f);
	m_ppObjects[30]->SetPosition(-26.51, 0.5f, -39.65f);
}

void CRunAwayScene::ReleaseObjects()
{
	CScene::ReleaseObjects();

	if (m_pTerrainObject) delete m_pTerrainObject;
}

void CRunAwayScene::Animate(float fElapsedTime)
{
	CScene::Animate(fElapsedTime);

	CScene::CheckObjectByObjectCollisions();
}

void CRunAwayScene::Render(HDC hDCFrameBuffer, CCamera *pCamera)
{
	m_pTerrainObject->Render(hDCFrameBuffer, pCamera);

	CScene::Render(hDCFrameBuffer, pCamera);
}
