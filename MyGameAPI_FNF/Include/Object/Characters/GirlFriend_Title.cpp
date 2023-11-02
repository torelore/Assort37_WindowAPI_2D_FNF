#include "GirlFriend_Title.h"

CGirlFriend_Title::CGirlFriend_Title()
{
}

CGirlFriend_Title::CGirlFriend_Title(const CGirlFriend_Title& obj)
{
}

CGirlFriend_Title::~CGirlFriend_Title()
{
}

void CGirlFriend_Title::Start()
{
}

bool CGirlFriend_Title::Init()
{
	if (!CCharacter::Init())
		return false;

	SetPos(525.f, 0.f);

	CreateAnimation();
	AddAnimation("GF_DANCE_TITLE", true, 1.f);

	return true;
}

void CGirlFriend_Title::Update(float DeltaTime)
{
	CCharacter::Update(DeltaTime);
}

void CGirlFriend_Title::PostUpdate(float DeltaTime)
{
	CCharacter::PostUpdate(DeltaTime);
}

void CGirlFriend_Title::Render(HDC hDC)
{
	CCharacter::Render(hDC);
}

CGirlFriend_Title* CGirlFriend_Title::Clone()
{
	return new CGirlFriend_Title(*this);
}
