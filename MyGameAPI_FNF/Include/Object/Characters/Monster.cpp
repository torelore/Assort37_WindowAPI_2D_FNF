#include "Monster.h"

CMonster::CMonster()
{
}

CMonster::CMonster(const CMonster& obj) :
	CCharacter(obj)
{
}

CMonster::~CMonster()
{

}

void CMonster::Start()
{
	CCharacter::Start();
}

bool CMonster::Init()
{
	if (!CCharacter::Init())
		return false;


	CreateAnimation();
	AddAnimation("MONSTER_IDLE", true, 0.8f);


	AddAnimation("MONSTER_UP", false, 0.5f);
	AddAnimationNotify<CMonster>("MONSTER_UP", 5, this, &CMonster::MoveEnd);
	SetAnimationEndNotify<CMonster>("MONSTER_UP", this, &CMonster::MoveEnd);


	AddAnimation("MONSTER_DOWN", false, 0.5f);

	AddAnimationNotify<CMonster>("MONSTER_DOWN", 7, this, &CMonster::MoveEnd);
	SetAnimationEndNotify<CMonster>("MONSTER_DOWN", this, &CMonster::MoveEnd);


	AddAnimation("MONSTER_LEFT", false, 0.5f);

	AddAnimationNotify<CMonster>("MONSTER_LEFT", 1, this, &CMonster::MoveEnd);
	SetAnimationEndNotify<CMonster>("MONSTER_LEFT", this, &CMonster::MoveEnd);


	AddAnimation("MONSTER_RIGHT", false, 0.5f);

	AddAnimationNotify<CMonster>("MONSTER_RIGHT", 19, this, &CMonster::MoveEnd);
	SetAnimationEndNotify<CMonster>("MONSTER_RIGHT", this, &CMonster::MoveEnd);

	return true;
}

void CMonster::Update(float DeltaTime)
{
	CCharacter::Update(DeltaTime);
}

void CMonster::PostUpdate(float DeltaTime)
{
	CCharacter::PostUpdate(DeltaTime);
}

void CMonster::Collision(float DeltaTime)
{
	CCharacter::Collision(DeltaTime);
}

void CMonster::Render(HDC hDC)
{
	CCharacter::Render(hDC);
}

CMonster* CMonster::Clone()
{
	return new CMonster(*this);
}

void CMonster::MoveUp(float DeltaTime)
{
	ChangeAnimation("MONSTER_UP");

	CCharacter::MoveUp(DeltaTime);
}

void CMonster::MoveDown(float DeltaTime)
{
	ChangeAnimation("MONSTER_DOWN");

	CCharacter::MoveDown(DeltaTime);
}

void CMonster::MoveLeft(float DeltaTime)
{
	ChangeAnimation("MONSTER_LEFT");

	CCharacter::MoveLeft(DeltaTime);
}

void CMonster::MoveRight(float DeltaTime)
{
	ChangeAnimation("MONSTER_RIGHT");

	CCharacter::MoveRight(DeltaTime);
}

void CMonster::MoveEnd()
{
	ChangeAnimation("MONSTER_IDLE");
}
