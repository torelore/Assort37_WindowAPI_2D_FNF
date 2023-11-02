#pragma once
#include "ScrollMap.h"

class CTrain :
	public CScrollMap
{
	friend class CScene;


protected:
	CTrain();
	virtual ~CTrain();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void PrevRender();
	virtual void Render(HDC hDC);
	virtual void Save(FILE* pFile);
	virtual void Load(FILE* pFile);
};

