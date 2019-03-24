#include "StdAfx.h"
#include "GameObject.h"

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
	if (m_pVertices) delete [] m_pVertices; 
}

void CPolygon::SetVertex(int nIndex, CVertex vertex)
{
	if ((0 <= nIndex) && (nIndex < m_nVertices) && m_pVertices)
	{
		m_pVertices[nIndex] = vertex;
	}
}

CMesh::CMesh(int nPolygons)
{
	if (nPolygons > 0)
	{
		m_nPolygons = nPolygons;
		m_ppPolygons = new CPolygon * [nPolygons];
		m_nReferences = 0;
	}
}

CMesh::~CMesh(void)
{
	if (m_ppPolygons)
	{
		for (int i = 0; i < m_nPolygons; i++) if (m_ppPolygons[i]) delete m_ppPolygons[i];
		delete [] m_ppPolygons;
	}
}

void CMesh::SetPolygon(int nIndex, CPolygon *pPolygon)
{
	if ((0 <= nIndex) && (nIndex < m_nPolygons) && m_ppPolygons)
	{
		m_ppPolygons[nIndex] = pPolygon;
	}
}

CGameObject::~CGameObject(void)
{
	if (m_pMesh) m_pMesh->Release();
}

