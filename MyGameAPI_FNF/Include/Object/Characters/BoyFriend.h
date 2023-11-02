#pragma once
#include "../Character.h"
#include "../Note_EndPoint.h"

class CBoyFriend :
	public CCharacter
{
	friend class CScene;

protected :
	CBoyFriend();
	CBoyFriend(const CBoyFriend& obj);
	virtual ~CBoyFriend();

public :
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(HDC hDC);
	virtual CBoyFriend* Clone();
	virtual float SetDamage(float Damage);

private :
	int m_NoteCount;
	CNote_EndPoint* m_UpEndPoint;
	CNote_EndPoint* m_DownEndPoint;
	CNote_EndPoint* m_LeftEndPoint;
	CNote_EndPoint* m_RightEndPoint;

public :
	void SetUpEndPoint(CNote_EndPoint* UpEndPoint) {
		m_UpEndPoint = UpEndPoint;
	}
	void SetDownEndPoint(CNote_EndPoint* DownEndPoint) {
		m_DownEndPoint = DownEndPoint;
	}
	void SetLeftEndPoint(CNote_EndPoint* LeftEndPoint) {
		m_LeftEndPoint = LeftEndPoint;
	}
	void SetRightEndPoint(CNote_EndPoint* RightEndPoint) {
		m_RightEndPoint = RightEndPoint;
	}

private:
	void MoveUp(float DeltaTime);
	void MoveDown(float DeltaTime);
	void MoveLeft(float DeltaTime);
	void MoveRight(float DeltaTime);
	void MoveEnd();
	void EnterPressed(float DeltaTime);

public :
	void MoveUpWrong();
	void MoveDownWrong();
	void MoveLeftWrong();
	void MoveRightWrong();
};

