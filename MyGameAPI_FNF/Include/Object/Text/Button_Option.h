#pragma once

#include "../GameObject.h"

class CButton_Option :
	public CGameObject
{
	friend class CScene;

protected:
	CButton_Option();
	CButton_Option(const CButton_Option& obj);
	virtual ~CButton_Option();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC);
	virtual CButton_Option* Clone();
};

