#include "LogoBumpin.h"

CLogoBumpin::CLogoBumpin()
{
}

CLogoBumpin::CLogoBumpin(const CLogoBumpin& obj) :
	CGameObject(obj)
{
}

CLogoBumpin::~CLogoBumpin()
{
}

void CLogoBumpin::Start()
{
	CGameObject::Start();
}

bool CLogoBumpin::Init()
{
	if (!CGameObject::Init())
		return false;
	
	SetPos(-125.f, -100.f);

	CreateAnimation();
	AddAnimation("LOGO_BUMFIN", true, 0.5f);

	return true;
}

void CLogoBumpin::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CLogoBumpin::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CLogoBumpin::Render(HDC hDC)
{
	CGameObject::Render(hDC);
}

CLogoBumpin* CLogoBumpin::Clone()
{
	return new CLogoBumpin(*this);
}