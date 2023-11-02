#pragma once
#include "../Character.h"

class CGirlFriend :
	public CCharacter
{
	friend class CScene;

protected:
	CGirlFriend();
	CGirlFriend(const CGirlFriend& obj);
	virtual ~CGirlFriend();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(HDC hDC);
	virtual CGirlFriend* Clone();

public:
	virtual void MoveUp(float DeltaTime);
	virtual void MoveDown(float DeltaTime);
	virtual void MoveLeft(float DeltaTime);
	virtual void MoveRight(float DeltaTime);
	void MoveEnd();

};
