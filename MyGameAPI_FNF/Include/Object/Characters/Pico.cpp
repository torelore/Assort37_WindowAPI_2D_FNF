#include "Pico.h"

CPico::CPico()
{
}

CPico::CPico(const CPico& obj) :
	CCharacter(obj)
{
}

CPico::~CPico()
{
}

void CPico::Start()
{
    CCharacter::Start();
}

bool CPico::Init()
{
	if (!CCharacter::Init())
		return false;


	CreateAnimation();
	AddAnimation("PICO_IDLE", true, 0.8f);


	AddAnimation("PICO_UP", false, 0.5f);
	AddAnimationNotify<CPico>("PICO_UP", 14, this, &CPico::MoveEnd);
	SetAnimationEndNotify<CPico>("PICO_UP", this, &CPico::MoveEnd);


	AddAnimation("PICO_DOWN", false, 0.5f);

	AddAnimationNotify<CPico>("PICO_DOWN", 11, this, &CPico::MoveEnd);
	SetAnimationEndNotify<CPico>("PICO_DOWN", this, &CPico::MoveEnd);


	AddAnimation("PICO_LEFT", false, 0.5f);

	AddAnimationNotify<CPico>("PICO_LEFT", 17, this, &CPico::MoveEnd);
	SetAnimationEndNotify<CPico>("PICO_LEFT", this, &CPico::MoveEnd);


	AddAnimation("PICO_RIGHT", false, 0.5f);

	AddAnimationNotify<CPico>("PICO_RIGHT", 17, this, &CPico::MoveEnd);
	SetAnimationEndNotify<CPico>("PICO_RIGHT", this, &CPico::MoveEnd);

	return true;
}

void CPico::Update(float DeltaTime)
{
	CCharacter::Update(DeltaTime);
}

void CPico::PostUpdate(float DeltaTime)
{
	CCharacter::PostUpdate(DeltaTime);
}

void CPico::Collision(float DeltaTime)
{
	CCharacter::Collision(DeltaTime);
}

void CPico::Render(HDC hDC)
{
	CCharacter::Render(hDC);
}

CPico* CPico::Clone()
{
	return new CPico(*this);
}

void CPico::MoveUp(float DeltaTime)
{
	ChangeAnimation("PICO_UP");

	CCharacter::MoveUp(DeltaTime);
}

void CPico::MoveDown(float DeltaTime)
{
	ChangeAnimation("PICO_DOWN");

	CCharacter::MoveDown(DeltaTime);
}

void CPico::MoveLeft(float DeltaTime)
{
	ChangeAnimation("PICO_LEFT");

	CCharacter::MoveLeft(DeltaTime);
}

void CPico::MoveRight(float DeltaTime)
{
	ChangeAnimation("PICO_RIGHT");

	CCharacter::MoveRight(DeltaTime);
}

void CPico::MoveEnd()
{
	ChangeAnimation("PICO_IDLE");
}
