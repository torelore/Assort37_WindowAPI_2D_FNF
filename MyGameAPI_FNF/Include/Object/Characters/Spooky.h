#pragma once
#include "../Character.h"

class CSpooky :
	public CCharacter
{
	friend class CScene;

protected:
	CSpooky();
	CSpooky(const CSpooky& obj);
	virtual ~CSpooky();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(HDC hDC);
	virtual CSpooky* Clone();

public:
	virtual void MoveUp(float DeltaTime);
	virtual void MoveDown(float DeltaTime);
	virtual void MoveLeft(float DeltaTime);
	virtual void MoveRight(float DeltaTime);
	void MoveEnd();
};

