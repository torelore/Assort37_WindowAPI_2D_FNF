#include "Mom.h"

CMom::CMom()
{
}

CMom::CMom(const CMom& obj) :
	CCharacter(obj)
{
}

CMom::~CMom()
{
}

void CMom::Start()
{
	CCharacter::Start();
}

bool CMom::Init()
{
	if (!CCharacter::Init())
		return false;


	CreateAnimation();
	AddAnimation("MOM_IDLE", true, 1.f);


	AddAnimation("MOM_UP", false, 0.5f);
	AddAnimationNotify<CMom>("MOM_UP", 15, this, &CMom::MoveEnd);
	SetAnimationEndNotify<CMom>("MOM_UP", this, &CMom::MoveEnd);


	AddAnimation("MOM_DOWN", false, 0.5f);

	AddAnimationNotify<CMom>("MOM_DOWN", 15, this, &CMom::MoveEnd);
	SetAnimationEndNotify<CMom>("MOM_DOWN", this, &CMom::MoveEnd);


	AddAnimation("MOM_LEFT", false, 0.5f);

	AddAnimationNotify<CMom>("MOM_LEFT", 10, this, &CMom::MoveEnd);
	SetAnimationEndNotify<CMom>("MOM_LEFT", this, &CMom::MoveEnd);


	AddAnimation("MOM_RIGHT", false, 0.5f);

	AddAnimationNotify<CMom>("MOM_RIGHT", 10, this, &CMom::MoveEnd);
	SetAnimationEndNotify<CMom>("MOM_RIGHT", this, &CMom::MoveEnd);

	return true;
}

void CMom::Update(float DeltaTime)
{
    CCharacter::Update(DeltaTime);
}

void CMom::PostUpdate(float DeltaTime)
{
    CCharacter::PostUpdate(DeltaTime);
}

void CMom::Collision(float DeltaTime)
{
    CCharacter::Collision(DeltaTime);
}

void CMom::Render(HDC hDC)
{
    CCharacter::Render(hDC);
}

CMom* CMom::Clone()
{
    return new CMom(*this);
}

void CMom::MoveUp(float DeltaTime)
{
    ChangeAnimation("MOM_UP");

	Vector2 Pos = Vector2(m_Pos.x, 20.f);

	m_Pos = Pos;

    CCharacter::MoveUp(DeltaTime);
}

void CMom::MoveDown(float DeltaTime)
{
    ChangeAnimation("MOM_DOWN");

	Vector2 Pos = Vector2(m_Pos.x, 280.f);

	m_Pos = Pos;

    CCharacter::MoveDown(DeltaTime);
}

void CMom::MoveLeft(float DeltaTime)
{
    ChangeAnimation("MOM_LEFT");

	Vector2 Pos = Vector2(m_Pos.x, 70.f);

	m_Pos = Pos;

    CCharacter::MoveLeft(DeltaTime);
}

void CMom::MoveRight(float DeltaTime)
{
    ChangeAnimation("MOM_RIGHT");

	Vector2 Pos = Vector2(m_Pos.x, 120.f);

	m_Pos = Pos;

    CCharacter::MoveRight(DeltaTime);
}

void CMom::MoveEnd()
{
    ChangeAnimation("MOM_IDLE");

	Vector2 Pos = Vector2(m_Pos.x, 50.f);

	m_Pos = Pos;
}
