#include "Spooky.h"

CSpooky::CSpooky()
{
}

CSpooky::CSpooky(const CSpooky& obj) :
    CCharacter(obj)
{
}

CSpooky::~CSpooky()
{
}

void CSpooky::Start()
{
	CCharacter::Start();
}

bool CSpooky::Init()
{
	if (!CCharacter::Init())
		return false;


	CreateAnimation();
	AddAnimation("SPOOKY_IDLE", true, 1.f);


	AddAnimation("SPOOKY_UP", false, 0.5f);
	AddAnimationNotify<CSpooky>("SPOOKY_UP", 5, this, &CSpooky::MoveEnd);
	SetAnimationEndNotify<CSpooky>("SPOOKY_UP", this, &CSpooky::MoveEnd);


	AddAnimation("SPOOKY_DOWN", false, 0.5f);

	AddAnimationNotify<CSpooky>("SPOOKY_DOWN", 25, this, &CSpooky::MoveEnd);
	SetAnimationEndNotify<CSpooky>("SPOOKY_DOWN", this, &CSpooky::MoveEnd);


	AddAnimation("SPOOKY_LEFT", false, 0.5f);

	AddAnimationNotify<CSpooky>("SPOOKY_LEFT", 15, this, &CSpooky::MoveEnd);
	SetAnimationEndNotify<CSpooky>("SPOOKY_LEFT", this, &CSpooky::MoveEnd);


	AddAnimation("SPOOKY_RIGHT", false, 0.5f);

	AddAnimationNotify<CSpooky>("SPOOKY_RIGHT", 25, this, &CSpooky::MoveEnd);
	SetAnimationEndNotify<CSpooky>("SPOOKY_RIGHT", this, &CSpooky::MoveEnd);

	return true;
}

void CSpooky::Update(float DeltaTime)
{
	CCharacter::Update(DeltaTime);
}

void CSpooky::PostUpdate(float DeltaTime)
{
	CCharacter::PostUpdate(DeltaTime);
}

void CSpooky::Collision(float DeltaTime)
{
	CCharacter::Collision(DeltaTime);
}

void CSpooky::Render(HDC hDC)
{
	CCharacter::Render(hDC);
}

CSpooky* CSpooky::Clone()
{
	return new CSpooky(*this);
}

void CSpooky::MoveUp(float DeltaTime)
{
	ChangeAnimation("SPOOKY_UP");

	Vector2 Pos = Vector2(m_Pos.x, 210.f);

	m_Pos = Pos;

	CCharacter::MoveUp(DeltaTime);
}

void CSpooky::MoveDown(float DeltaTime)
{
	ChangeAnimation("SPOOKY_DOWN");

	Vector2 Pos = Vector2(m_Pos.x, 370.f);

	m_Pos = Pos;

	CCharacter::MoveDown(DeltaTime);
}

void CSpooky::MoveLeft(float DeltaTime)
{
	ChangeAnimation("SPOOKY_LEFT");

	CCharacter::MoveLeft(DeltaTime);
}

void CSpooky::MoveRight(float DeltaTime)
{
	ChangeAnimation("SPOOKY_RIGHT");

	CCharacter::MoveRight(DeltaTime);
}

void CSpooky::MoveEnd()
{
	ChangeAnimation("SPOOKY_IDLE");

	Vector2 Pos = Vector2(m_Pos.x, 250.f);

	m_Pos = Pos;
}
