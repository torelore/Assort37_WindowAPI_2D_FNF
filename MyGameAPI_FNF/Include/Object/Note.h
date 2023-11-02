#pragma once
#include "GameObject.h"
class CNote :
	public CGameObject
{
	friend class CScene;

protected:
	CNote();
	CNote(const CNote& obj);
	virtual ~CNote();

protected:
	Vector2		m_Dir;
	float		m_Distance;
	ENote_Type	m_NoteType;
	ENote_Owner m_Owner;

	bool		m_IsCollEndPoint;

public:
	void SetNoteType(ENote_Type Type) {
		m_NoteType = Type;
	}

	void SetDir(float x, float y)
	{
		m_Dir.x = x;
		m_Dir.y = y;
	}

	void SetDir(float Angle)
	{
		m_Dir.x = cosf(DegreeToRadian(Angle));
		m_Dir.y = sinf(DegreeToRadian(Angle));
	}

	void SetDistance(float Distance)
	{
		m_Distance = Distance;
	}

	void SetNoteOwner(const ENote_Owner& Owner) {
		m_Owner = Owner;
	}

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(HDC hDC);
	virtual CNote* Clone();

public:
	void CollisionBegin(class CCollider* Src, class CCollider* Dest, float DeltaTime);
	void CollisionEnd(class CCollider* Src, class CCollider* Dest, float DeltaTime);
	ENote_Rate GetNoteRate() const;
	void NoteRate_Sick();
	void NoteRate_Good();
	void NoteRate_Bad();
	void NoteRate_Shit();

private :
	void PopThis();
};

