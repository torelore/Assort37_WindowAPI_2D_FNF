#include "Button_StoryMode.h"
#include "../../Scene/Scene/Scene_StoryMode.h"
#include "../../Resource/ResourceManager.h"
#include "../../Scene/SceneManager.h"
#include "../../Scene/Scene/Scene_GamePlay.h"
#include "../../Scene/Scene/Scene_ModeSelect.h"
#include "../../Input.h"


CButton_StoryMode::CButton_StoryMode()
{
}

CButton_StoryMode::CButton_StoryMode(const CButton_StoryMode& obj)
{
}

CButton_StoryMode::~CButton_StoryMode()
{
}

void CButton_StoryMode::Start()
{
	CGameObject::Start();
	CInput::GetInst()->SetCallback<CButton_StoryMode>("Enter", KeyState_Down, this, &CButton_StoryMode::EnterPressed);
	CInput::GetInst()->SetCallback<CButton_StoryMode>("MoveUp", KeyState_Down, this, &CButton_StoryMode::UpPressed);
	CInput::GetInst()->SetCallback<CButton_StoryMode>("MoveDown", KeyState_Down, this, &CButton_StoryMode::DownPressed);
}

bool CButton_StoryMode::Init()
{
	if (!CGameObject::Init())
		return false;

	CreateAnimation();

	AddAnimation("STORY_MODE_BASIC", true, 0.3f);
	AddAnimation("STORY_MODE_WHITE", true, 0.3f);

	return true;
}

void CButton_StoryMode::Update(float DeltaTime)
{
	if (m_IsSceneEnd && (m_Time - m_InputTIme) > 1.f) {

		//std::string SongName = CResourceManager::GetInst()->GetStoryModeSongName();

		CSceneManager::GetInst()->CreateScene<CScene_GamePlay>("Tutorial", ESong_Difficulty::Easy, true);

		return;
	}

	m_Time += DeltaTime;

	if (m_IsSelected)
		ChangeAnimation("STORY_MODE_WHITE");
	else
		ChangeAnimation("STORY_MODE_BASIC");

	CGameObject::Update(DeltaTime);
}

void CButton_StoryMode::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CButton_StoryMode::Render(HDC hDC)
{
	CGameObject::Render(hDC);
}

CButton_StoryMode* CButton_StoryMode::Clone()
{
	return new CButton_StoryMode(*this);
}

bool CButton_StoryMode::ButtonScene(float InputTime)
{
	m_InputTIme = InputTime;
	m_IsSceneEnd = true;

	// 현재 CScene_GamePlay이지만, CScene_StoryMode로 바뀌어야함
	//if (m_IsSelected)
	//	CSceneManager::GetInst()->CreateScene<CScene_GamePlay>();

	return false;
}

void CButton_StoryMode::EnterPressed(float DeltaTime)
{
	((CScene_ModeSelect*)m_Scene)->EnterPressed();
}

void CButton_StoryMode::UpPressed(float DeltaTime)
{
	((CScene_ModeSelect*)m_Scene)->UpPressed();
}

void CButton_StoryMode::DownPressed(float DeltaTime)
{
	((CScene_ModeSelect*)m_Scene)->DownPressed();
}

