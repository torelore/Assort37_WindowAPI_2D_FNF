
#include "ComboFont.h"
#include "Note.h"
#include "../Scene/Scene.h"
#include "../Collision/ColliderBox.h"

CComboFont::CComboFont()
{
	m_ObjType = EObject_Type::Effect;
	m_DirX = 0.f;
	m_SpeedX = 0.f;
}

CComboFont::CComboFont(const CComboFont& obj) :
	CGameObject(obj)
{
	m_ObjType = obj.m_ObjType;
	m_DirX = obj.m_DirX;
	m_SpeedX = obj.m_SpeedX;
}

CComboFont::~CComboFont()
{
}

void CComboFont::Start()
{
	CGameObject::Start();
}

bool CComboFont::Init()
{
	if (!CGameObject::Init())
		return false;

	SetPivot(0.5f, 0.5f);

	SetGravityAccel(30.f);
	SetPhysicsSimulate(true);
	SetJumpVelocity(50.f);
	Jump();

	CWidgetComponent* Widget = CreateWidgetComponent("ComboFont");

	m_NumberWidget = Widget->CreateWidget<CNumberWidget>("ComboFont");
	m_NumberWidget->SetIsScore(false);

	std::vector<std::wstring>	vecNumberFileName;

	for (int i = 0; i < 10; ++i)
	{
		TCHAR	FileName[256] = {};

		wsprintf(FileName, TEXT("Number/%d.bmp"), i + 48);

		vecNumberFileName.push_back(FileName);
	}

	m_NumberWidget->SetTexture("ComboFont", vecNumberFileName);

	for (int i = 0; i < 10; ++i)
	{
		m_NumberWidget->SetTextureColorKey(255, 0, 255, i);
	}

	SetLifeTime(0.3f);

	return true;
}

void CComboFont::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	Move(Vector2(m_DirX * m_SpeedX * DeltaTime, 0.f));
}

void CComboFont::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CComboFont::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CComboFont::Render(HDC hDC)
{
	CGameObject::Render(hDC);
}

CComboFont* CComboFont::Clone()
{
	return new CComboFont(*this);
}
