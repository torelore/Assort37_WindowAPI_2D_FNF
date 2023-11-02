#include "UI_GamePlay.h"
#include "../../Object/Note.h"
#include "../../Scene/SceneManager.h"
#include "../../Scene/Scene.h"
#include "../../Scene/SceneResource.h"
#include "../../Scene/Camera.h"
#include "../../Scene/Scene/Scene_GamePlay.h"

CUI_GamePlay::CUI_GamePlay() 
{
	m_Time = 0.f;
	m_Difficulty = ESong_Difficulty::Normal;
	m_NoteCount = 0;
	m_Start = false;
	m_Pause = false;
	m_End = false;
	m_CountDown = 0;
	m_CountDownImage = nullptr;
}

CUI_GamePlay::~CUI_GamePlay()
{
	{
		auto    iter = m_SongInfo.NotesList[m_Difficulty].begin();
		auto    iterEnd = m_SongInfo.NotesList[m_Difficulty].end();

		for (; iter != iterEnd; ++iter)
			m_SongInfo.NotesList[m_Difficulty].erase(iter);
	}
}

void CUI_GamePlay::SetSongInfo(SongInfo& Info, const ESong_Difficulty& Difficulty)
{
	m_SongInfo = Info;
	m_Difficulty = Difficulty;

	m_listNoteInfo = m_SongInfo.NotesList.find(m_Difficulty)->second;
}

bool CUI_GamePlay::Init()
{
	return true;
}

void CUI_GamePlay::Update(float DeltaTime)
{
	if (m_Pause)
		return;

	CUIWindow::Update(DeltaTime);

	m_Time += DeltaTime;

	if (m_End && m_Time >= 5.f) {
		GameScore GC = ((CScene_GamePlay*)m_Scene)->GameEnd();

		bool IsStoryMode = ((CScene_GamePlay*)m_Scene)->IsStoryMode();

		CSceneManager::GetInst()->CreateScene<CScene_GameEndRate>(GC, IsStoryMode);
		return;
	}

	if (m_listNoteInfo.empty()) {
		if(!m_End)
			m_Time = 0.f;
		
		m_End = true;
		
		return;
	}

	if (m_Time >= 5.5f && !m_Start) {
		m_CountDownImage->Destroy();
		m_Start = true;
		m_Time = 0.f;
		((CScene_GamePlay*)m_Scene)->PlaySong();
	}
	else if (!m_Start) { // CountDown
		if (m_Time >= 3.5f && m_CountDown == 0) {
			m_CountDownImage = CreateWidget<CUIImage>("ReadyImage");
			m_CountDownImage->SetTexture("ReadyImage", TEXT("ready.bmp"));
			m_CountDownImage->SetTextureColorKey(255, 0, 255);
			m_CountDownImage->SetPos(261.5f, 178.f);

			((CScene_GamePlay*)m_Scene)->GetSceneResource()->SoundPlay("intro3");
			m_CountDown++;
		}
		if (m_Time >= 4.f && m_CountDown == 1) {
			((CScene_GamePlay*)m_Scene)->GetSceneResource()->SoundPlay("intro2");
			m_CountDown++;
		}
		else if (m_Time >= 4.5f && m_CountDown == 2) {
			m_CountDownImage->Destroy();

			m_CountDownImage = CreateWidget<CUIImage>("SetImage");
			m_CountDownImage->SetTexture("SetImage", TEXT("set.bmp"));
			m_CountDownImage->SetTextureColorKey(255, 0, 255);
			m_CountDownImage->SetPos(289.f, 199.f);

			((CScene_GamePlay*)m_Scene)->GetSceneResource()->SoundPlay("intro1");
			m_CountDown++;
		}
		else if (m_Time >= 5.f && m_CountDown == 3) {
			m_CountDownImage->Destroy();

			m_CountDownImage = CreateWidget<CUIImage>("GoImage");
			m_CountDownImage->SetTexture("GoImage", TEXT("go.bmp"));
			m_CountDownImage->SetTextureColorKey(255, 0, 255);
			m_CountDownImage->SetPos(361.f, 145.f);

			((CScene_GamePlay*)m_Scene)->GetSceneResource()->SoundPlay("introGo");
			m_CountDown++;
		}

		return;
	}

	NoteInfo NoteInfo = m_listNoteInfo.front();

	if ((m_Time + 1.f) * 1000.f >= (int)NoteInfo.NoteTime) {
		CSharedPtr<CNote> Note;

		float NoteX = 0.f;
		std::string NoteOwn = "";
		std::string NoteName = "";

		bool NoteOwner = (bool)NoteInfo.NoteOwner;

		if (NoteOwner) {
			NoteX = NOTE_MY_X;
			NoteOwn = "PlayerNote";
		}
		else {
			NoteX = NOTE_ENEMY_X;
			NoteOwn = "EnenyNote";
		}

		switch (NoteInfo.NoteType)
		{
		case ENote_Type::Left:
			Note = m_Scene->CreateObject<CNote>("LEFT_NOTE", NoteOwn, Vector2(NoteX, NOTE_START_Y));
			Note->ChangeAnimation("LEFT_NOTE");
			Note->SetNoteOwner(NoteInfo.NoteOwner);
			Note->SetNoteType(NoteInfo.NoteType);
	
			if(NoteOwner)
				m_listLeftNote.push_back(Note);
			break;
		case ENote_Type::Down:
			Note = m_Scene->CreateObject<CNote>("DOWN_NOTE", NoteOwn, Vector2(NoteX + 120.f, NOTE_START_Y));
			Note->ChangeAnimation("DOWN_NOTE");
			Note->SetNoteOwner(NoteInfo.NoteOwner);
			Note->SetNoteType(NoteInfo.NoteType);

			if (NoteOwner)
				m_listDownNote.push_back(Note);
			break;
		case ENote_Type::Up:
			Note = m_Scene->CreateObject<CNote>("UP_NOTE", NoteOwn, Vector2(NoteX + 240.f, NOTE_START_Y));
			Note->ChangeAnimation("UP_NOTE");
			Note->SetNoteOwner(NoteInfo.NoteOwner);
			Note->SetNoteType(NoteInfo.NoteType);

			if (NoteOwner)
				m_listUpNote.push_back(Note);
			break;
		case ENote_Type::Right:
			Note = m_Scene->CreateObject<CNote>("RIGHT_NOTE", NoteOwn, Vector2(NoteX + 360.f, NOTE_START_Y));
			Note->ChangeAnimation("RIGHT_NOTE");
			Note->SetNoteOwner(NoteInfo.NoteOwner);
			Note->SetNoteType(NoteInfo.NoteType);

			if (NoteOwner)
				m_listRightNote.push_back(Note);
			break;
		}

		m_listNoteInfo.pop_front();
	}
}