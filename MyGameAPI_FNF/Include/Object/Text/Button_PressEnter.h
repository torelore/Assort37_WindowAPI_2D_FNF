#pragma once

#include "../GameObject.h"

class CButton_PressEnter :
	public CGameObject
{
	friend class CScene;

protected:
	CButton_PressEnter();
	CButton_PressEnter(const CButton_PressEnter& obj);
	virtual ~CButton_PressEnter();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC);
	virtual CButton_PressEnter* Clone();

public :
	void EnterPressed(float DeltaTime);
};

