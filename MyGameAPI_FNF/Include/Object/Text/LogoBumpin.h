#pragma once

#include "../GameObject.h"

class CLogoBumpin :
	public CGameObject
{
	friend class CScene;

protected:
	CLogoBumpin();
	CLogoBumpin(const CLogoBumpin& obj);
	virtual ~CLogoBumpin();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC);
	virtual CLogoBumpin* Clone();
};

