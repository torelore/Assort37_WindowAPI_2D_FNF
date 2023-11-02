#include "Button_FreePlay.h"
#include "../../Scene/Scene/Scene_FreePlay.h"
#include "../../Scene/SceneManager.h"
#include "../../Scene/Scene/Scene_ModeSelect.h"
#include "../../Input.h"

CButton_FreePlay::CButton_FreePlay()
{
}

CButton_FreePlay::CButton_FreePlay(const CButton_FreePlay& obj)
{
}

CButton_FreePlay::~CButton_FreePlay()
{
}

void CButton_FreePlay::Start()
{
	CGameObject::Start();
}

bool CButton_FreePlay::Init()
{
	CreateAnimation();

	AddAnimation("FREE_PLAY_BASIC", true, 0.3f);
	AddAnimation("FREE_PLAY_WHITE", true, 0.3f);

	return true;
}

void CButton_FreePlay::Update(float DeltaTime)
{
	if (m_IsSceneEnd && (m_Time - m_InputTIme) > 1.f)
		CSceneManager::GetInst()->CreateScene<CScene_FreePlay>();

	m_Time += DeltaTime;

	if (m_IsSelected)
		ChangeAnimation("FREE_PLAY_WHITE");
	else
		ChangeAnimation("FREE_PLAY_BASIC");

	CGameObject::Update(DeltaTime);
}

void CButton_FreePlay::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CButton_FreePlay::Render(HDC hDC)
{
	CGameObject::Render(hDC);
}

CButton_FreePlay* CButton_FreePlay::Clone()
{
	return new CButton_FreePlay(*this);
}

bool CButton_FreePlay::ButtonScene(float InputTime)
{
	m_InputTIme = InputTime;
	m_IsSceneEnd = true;

	return false;
}
