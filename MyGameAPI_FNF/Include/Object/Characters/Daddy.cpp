#include "Daddy.h"

CDaddy::CDaddy()
{
}

CDaddy::CDaddy(const CDaddy& obj) :
	CCharacter(obj)
{
}

CDaddy::~CDaddy()
{

}

void CDaddy::Start()
{
	CCharacter::Start();
}

bool CDaddy::Init()
{
	if (!CCharacter::Init())
		return false;


	CreateAnimation();
	AddAnimation("DADDY_IDLE", true, 0.8f);


	AddAnimation("DADDY_UP", false, 0.5f);
	AddAnimationNotify<CDaddy>("DADDY_UP", 5, this, &CDaddy::MoveEnd);
	SetAnimationEndNotify<CDaddy>("DADDY_UP", this, &CDaddy::MoveEnd);


	AddAnimation("DADDY_DOWN", false, 0.5f);

	AddAnimationNotify<CDaddy>("DADDY_DOWN", 7, this, &CDaddy::MoveEnd);
	SetAnimationEndNotify<CDaddy>("DADDY_DOWN", this, &CDaddy::MoveEnd);


	AddAnimation("DADDY_LEFT", false, 0.5f);

	AddAnimationNotify<CDaddy>("DADDY_LEFT", 1, this, &CDaddy::MoveEnd);
	SetAnimationEndNotify<CDaddy>("DADDY_LEFT", this, &CDaddy::MoveEnd);


	AddAnimation("DADDY_RIGHT", false, 0.5f);

	AddAnimationNotify<CDaddy>("DADDY_RIGHT", 19, this, &CDaddy::MoveEnd);
	SetAnimationEndNotify<CDaddy>("DADDY_RIGHT", this, &CDaddy::MoveEnd);

	return true;
}

void CDaddy::Update(float DeltaTime)
{
	CCharacter::Update(DeltaTime);
}

void CDaddy::PostUpdate(float DeltaTime)
{
	CCharacter::PostUpdate(DeltaTime);
}

void CDaddy::Collision(float DeltaTime)
{
	CCharacter::Collision(DeltaTime);
}

void CDaddy::Render(HDC hDC)
{
	CCharacter::Render(hDC);
}

CDaddy* CDaddy::Clone()
{
	return new CDaddy(*this);
}

void CDaddy::MoveUp(float DeltaTime)
{
	ChangeAnimation("DADDY_UP");

	Vector2 Pos = Vector2(m_Pos.x, -5.f);

	m_Pos = Pos;

	CCharacter::MoveUp(DeltaTime);
}

void CDaddy::MoveDown(float DeltaTime)
{
	ChangeAnimation("DADDY_DOWN");

	Vector2 Pos = Vector2(m_Pos.x, 80.f);

	m_Pos = Pos;

	CCharacter::MoveDown(DeltaTime);
}

void CDaddy::MoveLeft(float DeltaTime)
{
	ChangeAnimation("DADDY_LEFT");

	CCharacter::MoveLeft(DeltaTime);
}

void CDaddy::MoveRight(float DeltaTime)
{
	ChangeAnimation("DADDY_RIGHT");

	Vector2 Pos = Vector2(m_Pos.x, 20.f);

	m_Pos = Pos;

	CCharacter::MoveRight(DeltaTime);
}

void CDaddy::MoveEnd()
{
	ChangeAnimation("DADDY_IDLE");

	Vector2 Pos = Vector2(m_Pos.x, 50.f);

	m_Pos = Pos;
}
