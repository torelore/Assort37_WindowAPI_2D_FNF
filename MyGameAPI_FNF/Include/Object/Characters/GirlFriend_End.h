#pragma once

#include "../Character.h"

class CGirlFriend_End :
	public CCharacter
{
	friend class CScene;

protected:
	CGirlFriend_End();
	CGirlFriend_End(const CGirlFriend_End& obj);
	virtual ~CGirlFriend_End();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC);
	virtual CGirlFriend_End* Clone();

public :
	void SetAnimationCleared(bool IsCleared);

private :
	void MoveLeft(float DeltaTime);
	void MoveRight(float DeltaTime);
	void EnterPressed(float DeltaTime);
};