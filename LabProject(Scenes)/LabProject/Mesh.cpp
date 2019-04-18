#include "stdafx.h"
#include "Mesh.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
CPolygon::CPolygon(int nVertices)
{
	if (nVertices > 0)
	{
		m_nVertices = nVertices;
		m_pVertices = new CVertex[nVertices];
	}
}

CPolygon::~CPolygon()
{
	if (m_pVertices) delete[] m_pVertices;
}

void CPolygon::SetVertex(int nIndex, CVertex& vertex)
{
	if ((0 <= nIndex) && (nIndex < m_nVertices) && m_pVertices)
	{
		m_pVertices[nIndex] = vertex;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
CMesh::CMesh(int nPolygons)
{
	if (nPolygons > 0)
	{
		m_nPolygons = nPolygons;
		m_ppPolygons = new CPolygon*[nPolygons];
		m_nReferences = 0;
	}
}

CMesh::~CMesh(void)
{
	if (m_ppPolygons)
	{
		for (int i = 0; i < m_nPolygons; i++) if (m_ppPolygons[i]) delete m_ppPolygons[i];
		delete[] m_ppPolygons;
	}
}

void CMesh::SetPolygon(int nIndex, CPolygon *pPolygon)
{
	if ((0 <= nIndex) && (nIndex < m_nPolygons) && m_ppPolygons)
	{
		m_ppPolygons[nIndex] = pPolygon;
	}
}

void CMesh::Render(HDC hDCFrameBuffer, XMFLOAT4X4& xmf4x4World, CCamera *pCamera)
{
	XMFLOAT4X4 xmf4x4Transform = Matrix4x4::Multiply(xmf4x4World, pCamera->m_xmf4x4ViewProject);
	for (int j = 0; j < m_nPolygons; j++)
	{
		int nVertices = m_ppPolygons[j]->m_nVertices;
		CVertex *pVertices = m_ppPolygons[j]->m_pVertices;
		XMFLOAT3 xmf3Previous(-1.0f, 0.0f, 0.0f);
		for (int i = 0; i <= nVertices; i++)
		{
			CVertex vertex = pVertices[i % nVertices];
			//World/View/Projection Transformation(Perspective Divide)
			XMFLOAT3 xmf3Current = Vector3::TransformCoord(vertex.m_xmf3Position, xmf4x4Transform);
			if ((xmf3Current.z >= 0.0f) && (xmf3Current.z <= 1.0f))
			{
				//Screen Transformation
				xmf3Current.x = +xmf3Current.x * (pCamera->m_Viewport.m_nWidth * 0.5f) + pCamera->m_Viewport.m_xStart + (pCamera->m_Viewport.m_nWidth * 0.5f);
				xmf3Current.y = -xmf3Current.y * (pCamera->m_Viewport.m_nHeight * 0.5f) + pCamera->m_Viewport.m_yStart + (pCamera->m_Viewport.m_nHeight * 0.5f);

				if (xmf3Previous.x >= 0.0f)
				{
					::MoveToEx(hDCFrameBuffer, (long)xmf3Previous.x, (long)xmf3Previous.y, NULL);
					::LineTo(hDCFrameBuffer, (long)xmf3Current.x, (long)xmf3Current.y);
				}
				xmf3Previous = xmf3Current;
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
CRailMesh::CRailMesh(float fWidth, float fHeight, float fDepth) : CMesh(7)
{
	float fHalfWidth = fWidth * 0.5f;
	float fHalfHeight = fHeight * 0.5f;
	float fHalfDepth = fDepth * 0.5f;

	CPolygon *pBottomFace = new CPolygon(4);
	pBottomFace->SetVertex(0, CVertex(-fHalfWidth, -fHalfHeight, +fHalfDepth));
	pBottomFace->SetVertex(1, CVertex(+fHalfWidth, -fHalfHeight, +fHalfDepth));
	pBottomFace->SetVertex(2, CVertex(+fHalfWidth, -fHalfHeight, -fHalfDepth));
	pBottomFace->SetVertex(3, CVertex(-fHalfWidth, -fHalfHeight, -fHalfDepth));
	SetPolygon(0, pBottomFace);

	CPolygon *pFirstRailFace = new CPolygon(4);
	pFirstRailFace->SetVertex(0, CVertex(-fHalfWidth, -fHalfHeight / 3 * 2, +fHalfDepth / 4 + fHalfDepth / 2));
	pFirstRailFace->SetVertex(1, CVertex(+fHalfWidth, -fHalfHeight / 3 * 2, +fHalfDepth / 4 + fHalfDepth / 2));
	pFirstRailFace->SetVertex(2, CVertex(+fHalfWidth, -fHalfHeight / 3 * 2, -fHalfDepth / 4 + fHalfDepth / 2));
	pFirstRailFace->SetVertex(3, CVertex(-fHalfWidth, -fHalfHeight / 3 * 2, -fHalfDepth/4+fHalfDepth/2));
	SetPolygon(1, pFirstRailFace);

	CPolygon *pFirstRailfrontFace = new CPolygon(4);
	pFirstRailfrontFace->SetVertex(0, CVertex(-fHalfWidth, -fHalfHeight / 3 * 2, +fHalfDepth / 4 + fHalfDepth / 2));
	pFirstRailfrontFace->SetVertex(1, CVertex(+fHalfWidth, -fHalfHeight / 3 * 2, +fHalfDepth / 4 + fHalfDepth / 2));
	pFirstRailfrontFace->SetVertex(2, CVertex(+fHalfWidth, -fHalfHeight , +fHalfDepth / 4 + fHalfDepth / 2));
	pFirstRailfrontFace->SetVertex(3, CVertex(-fHalfWidth, -fHalfHeight, +fHalfDepth / 4 + fHalfDepth / 2));
	SetPolygon(2, pFirstRailfrontFace);

	CPolygon *pFirstRailBackFace = new CPolygon(4);
	pFirstRailBackFace->SetVertex(0, CVertex(-fHalfWidth, -fHalfHeight / 3 * 2, -fHalfDepth / 4 + fHalfDepth / 2));
	pFirstRailBackFace->SetVertex(1, CVertex(+fHalfWidth, -fHalfHeight / 3 * 2, -fHalfDepth / 4 + fHalfDepth / 2));
	pFirstRailBackFace->SetVertex(2, CVertex(+fHalfWidth, -fHalfHeight, -fHalfDepth / 4 + fHalfDepth / 2));
	pFirstRailBackFace->SetVertex(3, CVertex(-fHalfWidth, -fHalfHeight, -fHalfDepth / 4 + fHalfDepth / 2));
	SetPolygon(3, pFirstRailBackFace);

	CPolygon *pSecondRailFace = new CPolygon(4);
	pSecondRailFace->SetVertex(0, CVertex(-fHalfWidth, -fHalfHeight/3*2, +fHalfDepth/4-fHalfDepth/2));
	pSecondRailFace->SetVertex(1, CVertex(+fHalfWidth, -fHalfHeight/3*2, +fHalfDepth/4-fHalfDepth/2));
	pSecondRailFace->SetVertex(2, CVertex(+fHalfWidth, -fHalfHeight/3*2, -fHalfDepth/4-fHalfDepth/2));
	pSecondRailFace->SetVertex(3, CVertex(-fHalfWidth, -fHalfHeight/3*2, -fHalfDepth/4-fHalfDepth/2));
	SetPolygon(4, pSecondRailFace);

	CPolygon *pSecondRailfrontFace = new CPolygon(4);
	pSecondRailfrontFace->SetVertex(0, CVertex(-fHalfWidth, -fHalfHeight / 3 * 2, +fHalfDepth / 4 - fHalfDepth / 2));
	pSecondRailfrontFace->SetVertex(1, CVertex(+fHalfWidth, -fHalfHeight / 3 * 2, +fHalfDepth / 4 - fHalfDepth / 2));
	pSecondRailfrontFace->SetVertex(2, CVertex(+fHalfWidth, -fHalfHeight, +fHalfDepth / 4 - fHalfDepth / 2));
	pSecondRailfrontFace->SetVertex(3, CVertex(-fHalfWidth, -fHalfHeight, +fHalfDepth / 4 - fHalfDepth / 2));
	SetPolygon(5, pSecondRailfrontFace);

	CPolygon *pSecondRailBackFace = new CPolygon(4);
	pSecondRailBackFace->SetVertex(0, CVertex(-fHalfWidth, -fHalfHeight / 3 * 2, -fHalfDepth / 4 - fHalfDepth / 2));
	pSecondRailBackFace->SetVertex(1, CVertex(+fHalfWidth, -fHalfHeight / 3 * 2, -fHalfDepth / 4 - fHalfDepth / 2));
	pSecondRailBackFace->SetVertex(2, CVertex(+fHalfWidth, -fHalfHeight, -fHalfDepth / 4 - fHalfDepth / 2));
	pSecondRailBackFace->SetVertex(3, CVertex(-fHalfWidth, -fHalfHeight, -fHalfDepth / 4 - fHalfDepth / 2));
	SetPolygon(6, pSecondRailBackFace);
}

CRailMesh::~CRailMesh(void)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
CWallMesh::CWallMesh(float fWidth, float fHeight, float fDepth, int nSubRects) : CMesh((4 * nSubRects * nSubRects) + 2)
{
	float fHalfWidth = fWidth * 0.5f;
	float fHalfHeight = fHeight * 0.5f;
	float fHalfDepth = fDepth * 0.5f;
	float fCellWidth = fWidth * (1.0f / nSubRects);
	float fCellHeight = fHeight * (1.0f / nSubRects);
	float fCellDepth = fDepth * (1.0f / nSubRects);

	int k = 0;
	CPolygon *pLeftFace;
	for (int i = 0; i < nSubRects; i++)
	{
		for (int j = 0; j < nSubRects; j++)
		{
			pLeftFace = new CPolygon(4);
			pLeftFace->SetVertex(0, CVertex(-fHalfWidth, -fHalfHeight+(i*fCellHeight), -fHalfDepth+(j*fCellDepth)));
			pLeftFace->SetVertex(1, CVertex(-fHalfWidth, -fHalfHeight+((i+1)*fCellHeight), -fHalfDepth+(j*fCellDepth)));
			pLeftFace->SetVertex(2, CVertex(-fHalfWidth, -fHalfHeight+((i+1)*fCellHeight), -fHalfDepth+((j+1)*fCellDepth)));
			pLeftFace->SetVertex(3, CVertex(-fHalfWidth, -fHalfHeight+(i*fCellHeight), -fHalfDepth+((j+1)*fCellDepth)));
			SetPolygon(k++, pLeftFace);
		}
	}

	CPolygon *pRightFace;
	for (int i = 0; i < nSubRects; i++)
	{
		for (int j = 0; j < nSubRects; j++)
		{
			pRightFace = new CPolygon(4);
			pRightFace->SetVertex(0, CVertex(+fHalfWidth, -fHalfHeight + (i*fCellHeight), -fHalfDepth + (j*fCellDepth)));
			pRightFace->SetVertex(1, CVertex(+fHalfWidth, -fHalfHeight + ((i + 1)*fCellHeight), -fHalfDepth + (j*fCellDepth)));
			pRightFace->SetVertex(2, CVertex(+fHalfWidth, -fHalfHeight + ((i + 1)*fCellHeight), -fHalfDepth + ((j + 1)*fCellDepth)));
			pRightFace->SetVertex(3, CVertex(+fHalfWidth, -fHalfHeight + (i*fCellHeight), -fHalfDepth + ((j + 1)*fCellDepth)));
			SetPolygon(k++, pRightFace);
		}
	}

	CPolygon *pTopFace;
	for (int i = 0; i < nSubRects; i++)
	{
		for (int j = 0; j < nSubRects; j++)
		{
			pTopFace = new CPolygon(4);
			pTopFace->SetVertex(0, CVertex(-fHalfWidth + (i*fCellWidth), +fHalfHeight, -fHalfDepth + (j*fCellDepth)));
			pTopFace->SetVertex(1, CVertex(-fHalfWidth + ((i + 1)*fCellWidth), +fHalfHeight, -fHalfDepth + (j*fCellDepth)));
			pTopFace->SetVertex(2, CVertex(-fHalfWidth + ((i + 1)*fCellWidth), +fHalfHeight, -fHalfDepth + ((j + 1)*fCellDepth)));
			pTopFace->SetVertex(3, CVertex(-fHalfWidth + (i*fCellWidth), +fHalfHeight, -fHalfDepth + ((j + 1)*fCellDepth)));
			SetPolygon(k++, pTopFace);
		}
	}

	CPolygon *pBottomFace;
	for (int i = 0; i < nSubRects; i++)
	{
		for (int j = 0; j < nSubRects; j++)
		{
			pBottomFace = new CPolygon(4);
			pBottomFace->SetVertex(0, CVertex(-fHalfWidth + (i*fCellWidth), -fHalfHeight, -fHalfDepth + (j*fCellDepth)));
			pBottomFace->SetVertex(1, CVertex(-fHalfWidth + ((i + 1)*fCellWidth), -fHalfHeight, -fHalfDepth + (j*fCellDepth)));
			pBottomFace->SetVertex(2, CVertex(-fHalfWidth + ((i + 1)*fCellWidth), -fHalfHeight, -fHalfDepth + ((j + 1)*fCellDepth)));
			pBottomFace->SetVertex(3, CVertex(-fHalfWidth + (i*fCellWidth), -fHalfHeight, -fHalfDepth + ((j + 1)*fCellDepth)));
			SetPolygon(k++, pBottomFace);
		}
	}

	CPolygon *pFrontFace = new CPolygon(4);
	pFrontFace->SetVertex(0, CVertex(-fHalfWidth, +fHalfHeight, -fHalfDepth));
	pFrontFace->SetVertex(1, CVertex(+fHalfWidth, +fHalfHeight, -fHalfDepth));
	pFrontFace->SetVertex(2, CVertex(+fHalfWidth, -fHalfHeight, -fHalfDepth));
	pFrontFace->SetVertex(3, CVertex(-fHalfWidth, -fHalfHeight, -fHalfDepth));
	SetPolygon(k++, pFrontFace);

	CPolygon *pBackFace = new CPolygon(4);
	pBackFace->SetVertex(0, CVertex(-fHalfWidth, -fHalfHeight, +fHalfDepth));
	pBackFace->SetVertex(1, CVertex(+fHalfWidth, -fHalfHeight, +fHalfDepth));
	pBackFace->SetVertex(2, CVertex(+fHalfWidth, +fHalfHeight, +fHalfDepth));
	pBackFace->SetVertex(3, CVertex(-fHalfWidth, +fHalfHeight, +fHalfDepth));
	SetPolygon(k++, pBackFace);
}

CWallMesh::~CWallMesh(void)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
CAirplaneMesh::CAirplaneMesh(float fWidth, float fHeight, float fDepth) : CMesh(24)
{
	float fx = fWidth*0.5f, fy = fHeight*0.5f, fz = fDepth*0.5f;

	float x1 = fx * 0.2f, y1 = fy * 0.2f, x2 = fx * 0.1f, y3 = fy * 0.3f, y2 = ((y1 - (fy - y3)) / x1)*x2 + (fy - y3);
	int i = 0;

	//Upper Plane
	CPolygon *pFace = new CPolygon(3);
	pFace->SetVertex(0, CVertex(0.0f, +(fy + y3), -fz));
	pFace->SetVertex(1, CVertex(+x1, -y1, -fz));
	pFace->SetVertex(2, CVertex(0.0f, 0.0f, -fz));
	SetPolygon(i++, pFace);

	pFace = new CPolygon(3);
	pFace->SetVertex(0, CVertex(0.0f, +(fy + y3), -fz));
	pFace->SetVertex(1, CVertex(0.0f, 0.0f, -fz));
	pFace->SetVertex(2, CVertex(-x1, -y1, -fz));
	SetPolygon(i++, pFace);

	pFace = new CPolygon(3);
	pFace->SetVertex(0, CVertex(+x2, +y2, -fz));
	pFace->SetVertex(1, CVertex(+fx, -y3, -fz));
	pFace->SetVertex(2, CVertex(+x1, -y1, -fz));
	SetPolygon(i++, pFace);

	pFace = new CPolygon(3);
	pFace->SetVertex(0, CVertex(-x2, +y2, -fz));
	pFace->SetVertex(1, CVertex(-x1, -y1, -fz));
	pFace->SetVertex(2, CVertex(-fx, -y3, -fz));
	SetPolygon(i++, pFace);

	//Lower Plane
	pFace = new CPolygon(3);
	pFace->SetVertex(0, CVertex(0.0f, +(fy + y3), +fz));
	pFace->SetVertex(1, CVertex(0.0f, 0.0f, +fz));
	pFace->SetVertex(2, CVertex(+x1, -y1, +fz));
	SetPolygon(i++, pFace);

	pFace = new CPolygon(3);
	pFace->SetVertex(0, CVertex(0.0f, +(fy + y3), +fz));
	pFace->SetVertex(1, CVertex(-x1, -y1, +fz));
	pFace->SetVertex(2, CVertex(0.0f, 0.0f, +fz));
	SetPolygon(i++, pFace);

	pFace = new CPolygon(3);
	pFace->SetVertex(0, CVertex(+x2, +y2, +fz));
	pFace->SetVertex(1, CVertex(+x1, -y1, +fz));
	pFace->SetVertex(2, CVertex(+fx, -y3, +fz));
	SetPolygon(i++, pFace);

	pFace = new CPolygon(3);
	pFace->SetVertex(0, CVertex(-x2, +y2, +fz));
	pFace->SetVertex(1, CVertex(-fx, -y3, +fz));
	pFace->SetVertex(2, CVertex(-x1, -y1, +fz));
	SetPolygon(i++, pFace);

	//Right Plane
	pFace = new CPolygon(3);
	pFace->SetVertex(0, CVertex(0.0f, +(fy + y3), -fz));
	pFace->SetVertex(1, CVertex(0.0f, +(fy + y3), +fz));
	pFace->SetVertex(2, CVertex(+x2, +y2, -fz));
	SetPolygon(i++, pFace);

	pFace = new CPolygon(3);
	pFace->SetVertex(0, CVertex(+x2, +y2, -fz));
	pFace->SetVertex(1, CVertex(0.0f, +(fy + y3), +fz));
	pFace->SetVertex(2, CVertex(+x2, +y2, +fz));
	SetPolygon(i++, pFace);

	pFace = new CPolygon(3);
	pFace->SetVertex(0, CVertex(+x2, +y2, -fz));
	pFace->SetVertex(1, CVertex(+x2, +y2, +fz));
	pFace->SetVertex(2, CVertex(+fx, -y3, -fz));
	SetPolygon(i++, pFace);

	pFace = new CPolygon(3);
	pFace->SetVertex(0, CVertex(+fx, -y3, -fz));
	pFace->SetVertex(1, CVertex(+x2, +y2, +fz));
	pFace->SetVertex(2, CVertex(+fx, -y3, +fz));
	SetPolygon(i++, pFace);

	//Back/Right Plane
	pFace = new CPolygon(3);
	pFace->SetVertex(0, CVertex(+x1, -y1, -fz));
	pFace->SetVertex(1, CVertex(+fx, -y3, -fz));
	pFace->SetVertex(2, CVertex(+fx, -y3, +fz));
	SetPolygon(i++, pFace);

	pFace = new CPolygon(3);
	pFace->SetVertex(0, CVertex(+x1, -y1, -fz));
	pFace->SetVertex(1, CVertex(+fx, -y3, +fz));
	pFace->SetVertex(2, CVertex(+x1, -y1, +fz));
	SetPolygon(i++, pFace);

	pFace = new CPolygon(3);
	pFace->SetVertex(0, CVertex(0.0f, 0.0f, -fz));
	pFace->SetVertex(1, CVertex(+x1, -y1, -fz));
	pFace->SetVertex(2, CVertex(+x1, -y1, +fz));
	SetPolygon(i++, pFace);

	pFace = new CPolygon(3);
	pFace->SetVertex(0, CVertex(0.0f, 0.0f, -fz));
	pFace->SetVertex(1, CVertex(+x1, -y1, +fz));
	pFace->SetVertex(2, CVertex(0.0f, 0.0f, +fz));
	SetPolygon(i++, pFace);

	//Left Plane
	pFace = new CPolygon(3);
	pFace->SetVertex(0, CVertex(0.0f, +(fy + y3), +fz));
	pFace->SetVertex(1, CVertex(0.0f, +(fy + y3), -fz));
	pFace->SetVertex(2, CVertex(-x2, +y2, -fz));
	SetPolygon(i++, pFace);

	pFace = new CPolygon(3);
	pFace->SetVertex(0, CVertex(0.0f, +(fy + y3), +fz));
	pFace->SetVertex(1, CVertex(-x2, +y2, -fz));
	pFace->SetVertex(2, CVertex(-x2, +y2, +fz));
	SetPolygon(i++, pFace);

	pFace = new CPolygon(3);
	pFace->SetVertex(0, CVertex(-x2, +y2, +fz));
	pFace->SetVertex(1, CVertex(-x2, +y2, -fz));
	pFace->SetVertex(2, CVertex(-fx, -y3, -fz));
	SetPolygon(i++, pFace);

	pFace = new CPolygon(3);
	pFace->SetVertex(0, CVertex(-x2, +y2, +fz));
	pFace->SetVertex(1, CVertex(-fx, -y3, -fz));
	pFace->SetVertex(2, CVertex(-fx, -y3, +fz));
	SetPolygon(i++, pFace);

	//Back/Left Plane
	pFace = new CPolygon(3);
	pFace->SetVertex(0, CVertex(0.0f, 0.0f, -fz));
	pFace->SetVertex(1, CVertex(0.0f, 0.0f, +fz));
	pFace->SetVertex(2, CVertex(-x1, -y1, +fz));
	SetPolygon(i++, pFace);

	pFace = new CPolygon(3);
	pFace->SetVertex(0, CVertex(0.0f, 0.0f, -fz));
	pFace->SetVertex(1, CVertex(-x1, -y1, +fz));
	pFace->SetVertex(2, CVertex(-x1, -y1, -fz));
	SetPolygon(i++, pFace);

	pFace = new CPolygon(3);
	pFace->SetVertex(0, CVertex(-x1, -y1, -fz));
	pFace->SetVertex(1, CVertex(-x1, -y1, +fz));
	pFace->SetVertex(2, CVertex(-fx, -y3, +fz));
	SetPolygon(i++, pFace);

	pFace = new CPolygon(3);
	pFace->SetVertex(0, CVertex(-x1, -y1, -fz));
	pFace->SetVertex(1, CVertex(-fx, -y3, +fz));
	pFace->SetVertex(2, CVertex(-fx, -y3, -fz));
	SetPolygon(i++, pFace);
}

CAirplaneMesh::~CAirplaneMesh()
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
CTerrainMesh::CTerrainMesh(float fWidth, float fHeight, float fDepth, int nSubRects) : CMesh((nSubRects * nSubRects))
{
	float fHalfWidth = fWidth * 0.5f;
	float fHalfHeight = fHeight * 0.5f;
	float fHalfDepth = fDepth * 0.5f;
	float fCellWidth = fWidth * (1.0f / nSubRects);
	float fCellHeight = fHeight * (1.0f / nSubRects);
	float fCellDepth = fDepth * (1.0f / nSubRects);

	for (int i = 0, k = 0; i < nSubRects; i++)
	{
		for (int j = 0; j < nSubRects; j++)
		{
			CPolygon *pPolygon = new CPolygon(4);
			pPolygon->SetVertex(0, CVertex(-fHalfWidth + (i*fCellWidth), 0.0f, -fHalfDepth + (j*fCellDepth)));
			pPolygon->SetVertex(1, CVertex(-fHalfWidth + ((i + 1)*fCellWidth), 0.0f, -fHalfDepth + (j*fCellDepth)));
			pPolygon->SetVertex(2, CVertex(-fHalfWidth + ((i + 1)*fCellWidth), 0.0f, -fHalfDepth + ((j + 1)*fCellDepth)));
			pPolygon->SetVertex(3, CVertex(-fHalfWidth + (i*fCellWidth), 0.0f, -fHalfDepth + ((j + 1)*fCellDepth)));
			SetPolygon(k++, pPolygon);
		}
	}
}

CTerrainMesh::~CTerrainMesh(void)
{
}
