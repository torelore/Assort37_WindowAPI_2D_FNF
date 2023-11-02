#pragma once

#include "../GameObject.h"

class CButton_FreePlay :
	public CGameObject
{
	friend class CScene;

protected:
	CButton_FreePlay();
	CButton_FreePlay(const CButton_FreePlay& obj);
	virtual ~CButton_FreePlay();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC);
	virtual CButton_FreePlay* Clone();
	virtual bool ButtonScene(float InputTime);
};

