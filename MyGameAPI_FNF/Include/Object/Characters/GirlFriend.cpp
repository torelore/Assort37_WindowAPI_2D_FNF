#include "GirlFriend.h"
#include "../../Scene/Scene.h"

CGirlFriend::CGirlFriend()
{
}

CGirlFriend::CGirlFriend(const CGirlFriend& obj)
{
}

CGirlFriend::~CGirlFriend()
{
}

void CGirlFriend::Start()
{
	CCharacter::Start();
}

bool CGirlFriend::Init()
{
	if (!CCharacter::Init())
		return false;


	CreateAnimation();
	AddAnimation("GF_DANCING", true, 1.f);


	AddAnimation("GF_FEAR", false, 0.8f);
	AddAnimationNotify<CGirlFriend>("GF_FEAR", 5, this, &CGirlFriend::MoveEnd);
	SetAnimationEndNotify<CGirlFriend>("GF_FEAR", this, &CGirlFriend::MoveEnd);


	AddAnimation("GF_UP", false, 1.f);
	AddAnimationNotify<CGirlFriend>("GF_UP", 7, this, &CGirlFriend::MoveEnd);
	SetAnimationEndNotify<CGirlFriend>("GF_UP", this, &CGirlFriend::MoveEnd);


	AddAnimation("GF_DOWN", false, 1.f);
	AddAnimationNotify<CGirlFriend>("GF_DOWN", 20, this, &CGirlFriend::MoveEnd);
	SetAnimationEndNotify<CGirlFriend>("GF_DOWN", this, &CGirlFriend::MoveEnd);


	AddAnimation("GF_LEFT", false, 1.f);
	AddAnimationNotify<CGirlFriend>("GF_LEFT", 15, this, &CGirlFriend::MoveEnd);
	SetAnimationEndNotify<CGirlFriend>("GF_LEFT", this, &CGirlFriend::MoveEnd);


	AddAnimation("GF_RIGHT", false, 1.f);
	AddAnimationNotify<CGirlFriend>("GF_RIGHT", 20, this, &CGirlFriend::MoveEnd);
	SetAnimationEndNotify<CGirlFriend>("GF_RIGHT", this, &CGirlFriend::MoveEnd);

	return true;
}

void CGirlFriend::Update(float DeltaTime)
{
	m_Time += DeltaTime;

	CCharacter::Update(DeltaTime);
}

void CGirlFriend::PostUpdate(float DeltaTime)
{
	CCharacter::PostUpdate(DeltaTime);
}

void CGirlFriend::Collision(float DeltaTime)
{
	CCharacter::Collision(DeltaTime);
}

void CGirlFriend::Render(HDC hDC)
{
	CCharacter::Render(hDC);
}

CGirlFriend* CGirlFriend::Clone()
{
	return new CGirlFriend(*this);
}

void CGirlFriend::MoveUp(float DeltaTime)
{
	ChangeAnimation("GF_UP");

	CCharacter::MoveUp(DeltaTime);
}

void CGirlFriend::MoveDown(float DeltaTime)
{
	ChangeAnimation("GF_DOWN");

	CCharacter::MoveDown(DeltaTime);
}

void CGirlFriend::MoveLeft(float DeltaTime)
{
	ChangeAnimation("GF_LEFT");

	CCharacter::MoveLeft(DeltaTime);
}

void CGirlFriend::MoveRight(float DeltaTime)
{
	ChangeAnimation("GF_RIGHT");

	CCharacter::MoveRight(DeltaTime);
}

void CGirlFriend::MoveEnd()
{
	ChangeAnimation("GF_DANCING");
}
