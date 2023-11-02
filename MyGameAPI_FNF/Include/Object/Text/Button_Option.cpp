#include "Button_Option.h"

CButton_Option::CButton_Option()
{
	m_IsSelected = false;
}

CButton_Option::CButton_Option(const CButton_Option& obj)
{
}

CButton_Option::~CButton_Option()
{
}

void CButton_Option::Start()
{
	CGameObject::Start();
}

bool CButton_Option::Init()
{
	if (!CGameObject::Init())
		return false;

	CreateAnimation();

	AddAnimation("OPTION_BASIC", true, 0.3f);
	AddAnimation("OPTION_WHITE", true, 0.3f);


	return true;
}

void CButton_Option::Update(float DeltaTime)
{
	if (m_IsSelected) {
		ChangeAnimation("OPTION_WHITE");
	}
	else {
		ChangeAnimation("OPTION_BASIC");
	}

	CGameObject::Update(DeltaTime);
}

void CButton_Option::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CButton_Option::Render(HDC hDC)
{
	CGameObject::Render(hDC);
}

CButton_Option* CButton_Option::Clone()
{
	return new CButton_Option(*this);
}
