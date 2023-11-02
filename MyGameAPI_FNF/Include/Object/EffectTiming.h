#pragma once

#include "GameObject.h"

class CEffectTiming :
	public CGameObject
{
	friend class CScene;
	friend class CScene_GamePlay;

protected:
	CEffectTiming();
	CEffectTiming(const CEffectTiming& obj);
	virtual ~CEffectTiming();

private:
	float	m_DirX;
	float	m_SpeedX;

public:
	void SetDirX(float DirX) {
		m_DirX = DirX;
	}

	void SetSpeedX(float SpeedX) {
		m_SpeedX = SpeedX;
	}

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(HDC hDC);
	virtual CEffectTiming* Clone();

public:
	void AnimationFinish();
	void SetNoteRate(const ENote_Rate& Rate);
};

