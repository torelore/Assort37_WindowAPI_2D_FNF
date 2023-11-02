#pragma once
#include "../Character.h"

class CGirlFriend_Title :
    public CCharacter
{
	friend class CScene;

protected:
	CGirlFriend_Title();
	CGirlFriend_Title(const CGirlFriend_Title& obj);
	virtual ~CGirlFriend_Title();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC);
	virtual CGirlFriend_Title* Clone();
};

