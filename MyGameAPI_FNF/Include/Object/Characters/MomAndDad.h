#pragma once
#include "../Character.h"

class CMomAndDad :
	public CCharacter
{
	friend class CScene;

protected:
	CMomAndDad();
	CMomAndDad(const CMomAndDad& obj);
	virtual ~CMomAndDad();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(HDC hDC);
	virtual CMomAndDad* Clone();

public:
	virtual void MoveUp(float DeltaTime);
	virtual void MoveDown(float DeltaTime);
	virtual void MoveLeft(float DeltaTime);
	virtual void MoveRight(float DeltaTime);
	void MoveEnd();
};

