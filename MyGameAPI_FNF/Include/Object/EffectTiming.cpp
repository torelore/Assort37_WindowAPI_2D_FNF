
#include "EffectTiming.h"
#include "Note.h"
#include "../Scene/Scene.h"
#include "../Collision/ColliderBox.h"

CEffectTiming::CEffectTiming()
{
	m_ObjType = EObject_Type::Effect;
	m_DirX = 0.f;
	m_SpeedX = 0.f;
}

CEffectTiming::CEffectTiming(const CEffectTiming& obj) :
	CGameObject(obj)
{
	m_ObjType = obj.m_ObjType;
	m_DirX = obj.m_DirX;
	m_SpeedX = obj.m_SpeedX;
}

CEffectTiming::~CEffectTiming()
{
}

void CEffectTiming::Start()
{
	CGameObject::Start();

	SetAnimationEndNotify<CEffectTiming>("SICK", this, &CEffectTiming::AnimationFinish);
	SetAnimationEndNotify<CEffectTiming>("GOOD", this, &CEffectTiming::AnimationFinish);
	SetAnimationEndNotify<CEffectTiming>("BAD", this, &CEffectTiming::AnimationFinish);
	SetAnimationEndNotify<CEffectTiming>("SHIT", this, &CEffectTiming::AnimationFinish);
}

bool CEffectTiming::Init()
{
	if (!CGameObject::Init())
		return false;

	SetPivot(0.5f, 0.5f);

	SetGravityAccel(30.f);
	SetPhysicsSimulate(true);
	SetJumpVelocity(50.f);
	Jump();

	CreateAnimation();

	AddAnimation("SICK", false, 0.3f);
	AddAnimation("GOOD", false, 0.3f);
	AddAnimation("BAD", false, 0.3f);
	AddAnimation("SHIT", false, 0.3f);

	return true;
}

void CEffectTiming::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	Move(Vector2(m_DirX * m_SpeedX * DeltaTime, 0.f));
}

void CEffectTiming::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CEffectTiming::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CEffectTiming::Render(HDC hDC)
{
	CGameObject::Render(hDC);
}

CEffectTiming* CEffectTiming::Clone()
{
	return new CEffectTiming(*this);
}

void CEffectTiming::AnimationFinish()
{
	Destroy();
}

void CEffectTiming::SetNoteRate(const ENote_Rate& Rate)
{
	switch (Rate)
	{
	case ENote_Rate::Bad:
		ChangeAnimation("BAD");
		break;
	case ENote_Rate::Good:
		ChangeAnimation("GOOD");
		break;
	case ENote_Rate::Sick:
		ChangeAnimation("SICK");
		break;
	case ENote_Rate::Shit:
		ChangeAnimation("SHIT");
		break;
	}
}
