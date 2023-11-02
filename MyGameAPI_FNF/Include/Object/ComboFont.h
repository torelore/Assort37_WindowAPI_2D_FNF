#pragma once

#include "GameObject.h"
#include "../UI/NumberWidget.h"

class CComboFont :
	public CGameObject
{
	friend class CScene;
	friend class CScene_GamePlay;

protected:
	CComboFont();
	CComboFont(const CComboFont& obj);
	virtual ~CComboFont();

private:
	CNumberWidget* m_NumberWidget;

	float	m_DirX;
	float	m_SpeedX;

public :
	void SetDirX(float DirX) {
		m_DirX = DirX;
	}

	void SetSpeedX(float SpeedX) {
		m_SpeedX = SpeedX;
	}

public:
	void SetComboNumber(int Combo)
	{
		m_NumberWidget->SetNumber(Combo);
	}

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(HDC hDC);
	virtual CComboFont* Clone();
};

