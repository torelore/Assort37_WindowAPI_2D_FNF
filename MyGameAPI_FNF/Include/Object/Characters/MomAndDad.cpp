#include "MomAndDad.h"

CMomAndDad::CMomAndDad()
{
}

CMomAndDad::CMomAndDad(const CMomAndDad& obj) :
	CCharacter(obj)
{
}

CMomAndDad::~CMomAndDad()
{

}

void CMomAndDad::Start()
{
	CCharacter::Start();
}

bool CMomAndDad::Init()
{
	if (!CCharacter::Init())
		return false;


	CreateAnimation();
	AddAnimation("MOMANDDAD_IDLE", true, 0.8f);


	AddAnimation("MOMANDDAD_UP", false, 0.5f);
	AddAnimationNotify<CMomAndDad>("MOMANDDAD_UP", 5, this, &CMomAndDad::MoveEnd);
	SetAnimationEndNotify<CMomAndDad>("MOMANDDAD_UP", this, &CMomAndDad::MoveEnd);


	AddAnimation("MOMANDDAD_DOWN", false, 0.5f);

	AddAnimationNotify<CMomAndDad>("MOMANDDAD_DOWN", 7, this, &CMomAndDad::MoveEnd);
	SetAnimationEndNotify<CMomAndDad>("MOMANDDAD_DOWN", this, &CMomAndDad::MoveEnd);


	AddAnimation("MOMANDDAD_LEFT", false, 0.5f);

	AddAnimationNotify<CMomAndDad>("MOMANDDAD_LEFT", 1, this, &CMomAndDad::MoveEnd);
	SetAnimationEndNotify<CMomAndDad>("MOMANDDAD_LEFT", this, &CMomAndDad::MoveEnd);


	AddAnimation("MOMANDDAD_RIGHT", false, 0.5f);

	AddAnimationNotify<CMomAndDad>("MOMANDDAD_RIGHT", 19, this, &CMomAndDad::MoveEnd);
	SetAnimationEndNotify<CMomAndDad>("MOMANDDAD_RIGHT", this, &CMomAndDad::MoveEnd);

	return true;
}

void CMomAndDad::Update(float DeltaTime)
{
	CCharacter::Update(DeltaTime);
}

void CMomAndDad::PostUpdate(float DeltaTime)
{
	CCharacter::PostUpdate(DeltaTime);
}

void CMomAndDad::Collision(float DeltaTime)
{
	CCharacter::Collision(DeltaTime);
}

void CMomAndDad::Render(HDC hDC)
{
	CCharacter::Render(hDC);
}

CMomAndDad* CMomAndDad::Clone()
{
	return new CMomAndDad(*this);
}

void CMomAndDad::MoveUp(float DeltaTime)
{
	ChangeAnimation("MOMANDDAD_UP");

	CCharacter::MoveUp(DeltaTime);
}

void CMomAndDad::MoveDown(float DeltaTime)
{
	ChangeAnimation("MOMANDDAD_DOWN");

	CCharacter::MoveDown(DeltaTime);
}

void CMomAndDad::MoveLeft(float DeltaTime)
{
	ChangeAnimation("MOMANDDAD_LEFT");

	CCharacter::MoveLeft(DeltaTime);
}

void CMomAndDad::MoveRight(float DeltaTime)
{
	ChangeAnimation("MOMANDDAD_RIGHT");

	CCharacter::MoveRight(DeltaTime);
}

void CMomAndDad::MoveEnd()
{
	ChangeAnimation("MOMANDDAD_IDLE");
}
