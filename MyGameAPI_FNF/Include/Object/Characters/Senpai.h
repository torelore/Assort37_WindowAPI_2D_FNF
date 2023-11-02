#pragma once
#include "../Character.h"

class CSenpai :
	public CCharacter
{
	friend class CScene;

protected:
	CSenpai();
	CSenpai(const CSenpai& obj);
	virtual ~CSenpai();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(HDC hDC);
	virtual CSenpai* Clone();

public:
	virtual void MoveUp(float DeltaTime);
	virtual void MoveDown(float DeltaTime);
	virtual void MoveLeft(float DeltaTime);
	virtual void MoveRight(float DeltaTime);
	void MoveEnd();
};

