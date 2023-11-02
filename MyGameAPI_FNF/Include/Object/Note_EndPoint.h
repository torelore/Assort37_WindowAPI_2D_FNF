#pragma once

#include "GameObject.h"
#include "Character.h"

class CNote_EndPoint :
	public CGameObject
{
	friend class CScene;
	friend class CBoyFriend;

protected:
	CNote_EndPoint();
	CNote_EndPoint(const CNote_EndPoint& obj);
	virtual ~CNote_EndPoint();

private :
	ENote_Owner		m_Owner;
	ENote_Type		m_Type;
	CCharacter*		m_OwnerCharacter;

public :
	void SetOwner(const ENote_Owner& Owner) {
		m_Owner = Owner;
	}

	void SetType(const ENote_Type& Type) {
		m_Type = Type;
	}

	void SetCharacter(CCharacter* Character) {
		m_OwnerCharacter = Character;
	}

	void SetInfo(const ENote_Owner& Owner, const ENote_Type& Type);

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(HDC hDC);
	virtual CNote_EndPoint* Clone();

public:
	void CollisionBegin(class CCollider* Src, class CCollider* Dest, float DeltaTime);
	void NoteEnd();
	bool PlayerInput(const ENote_Type& Type);
};

