#include "Senpai.h"

CSenpai::CSenpai()
{
}

CSenpai::CSenpai(const CSenpai& obj) :
	CCharacter(obj)
{
}

CSenpai::~CSenpai()
{

}

void CSenpai::Start()
{
	CCharacter::Start();
}

bool CSenpai::Init()
{
	if (!CCharacter::Init())
		return false;


	CreateAnimation();
	AddAnimation("SENPAI_IDLE", true, 0.8f);


	AddAnimation("SENPAI_UP", false, 0.5f);
	AddAnimationNotify<CSenpai>("SENPAI_UP", 5, this, &CSenpai::MoveEnd);
	SetAnimationEndNotify<CSenpai>("SENPAI_UP", this, &CSenpai::MoveEnd);


	AddAnimation("SENPAI_DOWN", false, 0.5f);

	AddAnimationNotify<CSenpai>("SENPAI_DOWN", 7, this, &CSenpai::MoveEnd);
	SetAnimationEndNotify<CSenpai>("SENPAI_DOWN", this, &CSenpai::MoveEnd);


	AddAnimation("SENPAI_LEFT", false, 0.5f);

	AddAnimationNotify<CSenpai>("SENPAI_LEFT", 1, this, &CSenpai::MoveEnd);
	SetAnimationEndNotify<CSenpai>("SENPAI_LEFT", this, &CSenpai::MoveEnd);


	AddAnimation("SENPAI_RIGHT", false, 0.5f);

	AddAnimationNotify<CSenpai>("SENPAI_RIGHT", 19, this, &CSenpai::MoveEnd);
	SetAnimationEndNotify<CSenpai>("SENPAI_RIGHT", this, &CSenpai::MoveEnd);

	return true;
}

void CSenpai::Update(float DeltaTime)
{
	CCharacter::Update(DeltaTime);
}

void CSenpai::PostUpdate(float DeltaTime)
{
	CCharacter::PostUpdate(DeltaTime);
}

void CSenpai::Collision(float DeltaTime)
{
	CCharacter::Collision(DeltaTime);
}

void CSenpai::Render(HDC hDC)
{
	CCharacter::Render(hDC);
}

CSenpai* CSenpai::Clone()
{
	return new CSenpai(*this);
}

void CSenpai::MoveUp(float DeltaTime)
{
	ChangeAnimation("SENPAI_UP");

	CCharacter::MoveUp(DeltaTime);
}

void CSenpai::MoveDown(float DeltaTime)
{
	ChangeAnimation("SENPAI_DOWN");

	CCharacter::MoveDown(DeltaTime);
}

void CSenpai::MoveLeft(float DeltaTime)
{
	ChangeAnimation("SENPAI_LEFT");

	CCharacter::MoveLeft(DeltaTime);
}

void CSenpai::MoveRight(float DeltaTime)
{
	ChangeAnimation("SENPAI_RIGHT");

	CCharacter::MoveRight(DeltaTime);
}

void CSenpai::MoveEnd()
{
	ChangeAnimation("SENPAI_IDLE");
}
