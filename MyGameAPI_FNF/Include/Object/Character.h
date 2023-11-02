#pragma once
#include "GameObject.h"
class CCharacter :
	public CGameObject
{
	friend class CScene;

protected:
	CCharacter();
	CCharacter(const CCharacter& obj);
	virtual ~CCharacter();

protected:
	CharacterInfo	m_CharacterInfo;
	std::list<NoteInfo> m_listNotes;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(HDC hDC);
	virtual CCharacter* Clone();
	virtual float SetDamage(float Damage);

public:
	virtual void MoveUp(float DeltaTime);
	virtual void MoveDown(float DeltaTime);
	virtual void MoveLeft(float DeltaTime);
	virtual void MoveRight(float DeltaTime);

public :
	void SetNotes(std::list<NoteInfo> NoteList) {
		m_listNotes = NoteList;
	}
};

