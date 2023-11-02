#pragma once

#include "../GameObject.h"
class CButton_Diffi_Arrow :
	public CGameObject
{
	friend class CScene;

protected:
	CButton_Diffi_Arrow();
	CButton_Diffi_Arrow(const CButton_Diffi_Arrow& obj);
	virtual ~CButton_Diffi_Arrow();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC);
	virtual CButton_Diffi_Arrow* Clone();
	virtual bool ButtonScene(float InputTime);

private :
	bool m_IsLeft;

public :
	void SetIsLeft() {
		m_IsLeft = true;
		ChangeAnimation("LEFT_ARROW");
	}

	void SetIsRight() {
		m_IsLeft = false;
		ChangeAnimation("RIGHT_ARROW");
	}

public :
	void LeftPressed(float DeltaTime);
	void RightPressed(float DeltaTime);

private :
	void PushEnd();
};

