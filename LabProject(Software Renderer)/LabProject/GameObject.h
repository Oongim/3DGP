#pragma once

#define DegreeToRadian(x)	((x)*3.1415926535/180.0)

class CPoint
{
public:
	CPoint() { x = y = z = 0.0f; }
    CPoint(float x, float y, float z) { this->x = x; this->y = y; this->z = z; }

	float					x;
	float					y;
	float					z;
};

class CVertex
{
public:
	CVertex() { }
    CVertex(float x, float y, float z, DWORD dwColor=0x00000000) { m_vPosition = CPoint(x, y, z); m_dwColor = dwColor; }

    CPoint					m_vPosition;  
	DWORD					m_dwColor;   
};

class CPolygon
{
public:
	CPolygon(int nVertices);
	virtual ~CPolygon();

    int						m_nVertices;     
    CVertex					*m_pVertices;   

	void SetVertex(int nIndex, CVertex vertex);
};

class CMesh
{
public:
	CMesh(int nPolygons);
	virtual ~CMesh();

	int						m_nReferences;
	void AddRef() { m_nReferences++; }
	void Release() { m_nReferences--; if (!m_nReferences) delete this; }

    int						m_nPolygons;     
    CPolygon				**m_ppPolygons;   

	void SetPolygon(int nIndex, CPolygon *pPolygon);
};

class CGameObject
{
public:
	CGameObject() { m_pMesh = NULL; m_fxScale = m_fyScale = m_fzScale = 1.0f; m_fxRotation = m_fyRotation = m_fzRotation = 0.0f; m_fxPosition = m_fyPosition = m_fzPosition = 0.0f; }
	~CGameObject(void);

	float					m_fxScale;
	float					m_fyScale;
	float					m_fzScale;

	float					m_fxRotation;
	float					m_fyRotation;
	float					m_fzRotation;

	float					m_fxPosition;
	float					m_fyPosition;
	float					m_fzPosition;

    CMesh					*m_pMesh;        

	void SetMesh(CMesh *pMesh) { m_pMesh = pMesh; if (pMesh) pMesh->AddRef(); }
	void SetScale(float fxScale, float fyScale, float fzScale) { m_fxScale = fxScale; m_fyScale = fyScale; m_fzScale = fzScale; }
	void SetRotation(float fxRotation, float fyRotation, float fzRotation) { m_fxRotation = fxRotation; m_fyRotation = fyRotation; m_fzRotation = fzRotation; }
	void SetPosition(float fxPosition, float fyPosition, float fzPosition) { m_fxPosition = fxPosition; m_fyPosition = fyPosition; m_fzPosition = fzPosition; }
	void Rotate(float fxRotation, float fyRotation, float fzRotation) { m_fxRotation += fxRotation; m_fyRotation += fyRotation; m_fzRotation += fzRotation; }
};

class CCamera
{
public:
	CCamera() { m_fxRotation = m_fyRotation = m_fzRotation = 0.0f; m_fxPosition = m_fyPosition = m_fzPosition = 0.0f; }
	~CCamera(void);

	float					m_fxRotation;
	float					m_fyRotation;
	float					m_fzRotation;

	float					m_fxPosition;
	float					m_fyPosition;
	float					m_fzPosition;

	void Rotate(float fxRotation, float fyRotation, float fzRotation) { m_fxRotation = fxRotation; m_fyRotation = fyRotation; m_fzRotation = fzRotation; }
	void SetPosition(float fxPosition, float fyPosition, float fzPosition) { m_fxPosition = fxPosition; m_fyPosition = fyPosition; m_fzPosition = fzPosition; }
};
