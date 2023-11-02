#include "UI_GameEndRate.h"
#include "../../GameManager.h"
#include "../../Scene/SceneManager.h"
#include "../../Scene/Scene/Scene_FreePlay.h"
#include "../../Scene/Scene/Scene_ModeSelect.h"
#include "../../Scene/Scene/Scene_GamePlay.h"
#include "../UIImage.h"
#include "../TextWidget.h"
#include "../NumberWidget.h"

CUI_GameEndRate::CUI_GameEndRate() :
	m_IsStoryMode(false),
	m_Time(0.f),
	m_IsLeftSelected(true),
	m_IsLeftMove(false),
	m_SongName(""),
	m_Difficulty(ESong_Difficulty::Normal)
{
}

CUI_GameEndRate::~CUI_GameEndRate()
{
}

bool CUI_GameEndRate::Init()
{
	Resolution	RS = CGameManager::GetInst()->GetResolution();

	// Alphabet & Number Bmp Texture Setting
	for (int i = 0; i < 26; ++i)
	{
		TCHAR	FileName[256] = {};

		wsprintf(FileName, TEXT("Alphabet/%d.bmp"), i + 65);

		m_vecTextFileName.push_back(FileName);
	}

	for (int i = 0; i < 10; ++i)
	{
		TCHAR	FileName[256] = {};

		wsprintf(FileName, TEXT("Number/%d.bmp"), i + 48);

		m_vecNumberFileName.push_back(FileName);
	}


	// SCORE Text Setting
	m_ScoreTextWidget = CreateWidget<CTextWidget>("ScoreText");

	m_ScoreTextWidget->SetTexture("Alphabet", m_vecTextFileName);

	for (int i = 0; i < 26; ++i)
		m_ScoreTextWidget->SetTextureColorKey(255, 0, 255, i);

	m_ScoreTextWidget->SetPos(350.f, 300.f);
	m_ScoreTextWidget->SetText("Score");


	// Rate Text Setting
	m_ScoreTextWidget = CreateWidget<CTextWidget>("RateText");

	m_ScoreTextWidget->SetTexture("Alphabet", m_vecTextFileName);

	for (int i = 0; i < 26; ++i)
		m_ScoreTextWidget->SetTextureColorKey(255, 0, 255, i);

	m_ScoreTextWidget->SetPos(350.f, 400.f);
	m_ScoreTextWidget->SetText("Rate");


	// Combo Text Setting
	m_ScoreTextWidget = CreateWidget<CTextWidget>("MaxText");

	m_ScoreTextWidget->SetTexture("Alphabet", m_vecTextFileName);

	for (int i = 0; i < 26; ++i)
		m_ScoreTextWidget->SetTextureColorKey(255, 0, 255, i);

	m_ScoreTextWidget->SetPos(150.f, 500.f);
	m_ScoreTextWidget->SetText("MAX");


	// Combo Text Setting
	m_ScoreTextWidget = CreateWidget<CTextWidget>("ComboText");

	m_ScoreTextWidget->SetTexture("Alphabet", m_vecTextFileName);

	for (int i = 0; i < 26; ++i)
		m_ScoreTextWidget->SetTextureColorKey(255, 0, 255, i);

	m_ScoreTextWidget->SetPos(350.f, 500.f);
	m_ScoreTextWidget->SetText("Combo");


	// Retry Text Setting
	m_ScoreTextWidget = CreateWidget<CTextWidget>("RetryText");

	m_ScoreTextWidget->SetTexture("Alphabet", m_vecTextFileName);

	for (int i = 0; i < 26; ++i)
		m_ScoreTextWidget->SetTextureColorKey(255, 0, 255, i);

	m_ScoreTextWidget->SetPos(200.f, 600.f);

	if (m_IsStoryMode)
		m_ScoreTextWidget->SetText("Next");
	else
		m_ScoreTextWidget->SetText("Retry");

	m_vecButtonListTextWidget.push_back(m_ScoreTextWidget);


	// Exit Text Setting
	m_ScoreTextWidget = CreateWidget<CTextWidget>("ExitText");

	m_ScoreTextWidget->SetTexture("Alphabet", m_vecTextFileName);

	for (int i = 0; i < 26; ++i)
		m_ScoreTextWidget->SetTextureColorKey(255, 0, 255, i);

	m_ScoreTextWidget->SetPos(900.f, 600.f);
	
	m_ScoreTextWidget->SetText("Exit");

	m_vecButtonListTextWidget.push_back(m_ScoreTextWidget);

	return true;
}

void CUI_GameEndRate::Update(float DeltaTime)
{
	CUIWindow::Update(DeltaTime);

	m_Time += DeltaTime;

	if (m_IsLeftSelected) {
		Vector2 Pos = m_vecButtonListTextWidget[0]->GetPos();
		
		if (Pos.x >= 250.f)
			m_IsLeftMove = true;
		else if (Pos.x <= 150.f)
			m_IsLeftMove = false;

		if (m_IsLeftMove)
			Pos.x -= 0.1f;
		else
			Pos.x += 0.1f;

		m_vecButtonListTextWidget[0]->SetPos(Pos.x, Pos.y);
	}
	else {

		Vector2 Pos = m_vecButtonListTextWidget[1]->GetPos();

		if (Pos.x >= 950.f)
			m_IsLeftMove = true;
		else if (Pos.x <= 850.f)
			m_IsLeftMove = false;

		if (m_IsLeftMove)
			Pos.x -= 0.1f;
		else
			Pos.x += 0.1f;

		m_vecButtonListTextWidget[1]->SetPos(Pos.x, Pos.y);
	}

}


void CUI_GameEndRate::SetGameRate(const GameScore& GameScore)
{
	m_SongName = GameScore.SongName;
	m_Difficulty = GameScore.Difficulty;


	// SongName Text Setting
	m_ScoreTextWidget = CreateWidget<CTextWidget>("SongNameText");

	m_ScoreTextWidget->SetTexture("Alphabet", m_vecTextFileName);

	for (int i = 0; i < 26; ++i)
		m_ScoreTextWidget->SetTextureColorKey(255, 0, 255, i);

	m_ScoreTextWidget->SetPos(400.f, 50.f);
	m_ScoreTextWidget->SetText(GameScore.SongName);

	// SongDifficulty TextSetting
	m_ScoreTextWidget = CreateWidget<CTextWidget>("SongDifficultyText");

	m_ScoreTextWidget->SetTexture("Alphabet", m_vecTextFileName);

	for (int i = 0; i < 26; ++i)
		m_ScoreTextWidget->SetTextureColorKey(255, 0, 255, i);

	m_ScoreTextWidget->SetPos(500.f, 125.f);

	std::string Diificulty = "";

	switch (GameScore.Difficulty)
	{
	case ESong_Difficulty::Easy:
		Diificulty = "Easy";
		break;
	case ESong_Difficulty::Normal:
		Diificulty = "Normal";
		break;
	case ESong_Difficulty::Hard:
		Diificulty = "Hard";
		break;
	}

	m_ScoreTextWidget->SetText(Diificulty);


	if (GameScore.Rate == EGame_Rate::Failed) {
		// Clear Or GameOver Text Setting
		m_ScoreTextWidget = CreateWidget<CTextWidget>("GameText");

		m_ScoreTextWidget->SetTexture("Alphabet", m_vecTextFileName);

		for (int i = 0; i < 26; ++i)
			m_ScoreTextWidget->SetTextureColorKey(255, 0, 255, i);

		m_ScoreTextWidget->SetPos(400.f, 200.f);
		m_ScoreTextWidget->SetText("GAME");

		m_ScoreTextWidget = CreateWidget<CTextWidget>("OverText");

		m_ScoreTextWidget->SetTexture("Alphabet", m_vecTextFileName);

		for (int i = 0; i < 26; ++i)
			m_ScoreTextWidget->SetTextureColorKey(255, 0, 255, i);

		m_ScoreTextWidget->SetPos(700.f, 200.f);
		m_ScoreTextWidget->SetText("Over");
	}
	else {
		// Clear Or GameOver Text Setting
		m_ScoreTextWidget = CreateWidget<CTextWidget>("ClearText");

		m_ScoreTextWidget->SetTexture("Alphabet", m_vecTextFileName);

		for (int i = 0; i < 26; ++i)
			m_ScoreTextWidget->SetTextureColorKey(255, 0, 255, i);

		m_ScoreTextWidget->SetPos(500.f, 200.f);
		m_ScoreTextWidget->SetText("Clear");
	}


	// SCORE Value Setting
	m_ScoreNumberWidget = CreateWidget<CNumberWidget>("ScoreValue");

	m_ScoreNumberWidget->SetTexture("Number", m_vecNumberFileName);

	for (int i = 0; i < 10; ++i)
		m_ScoreNumberWidget->SetTextureColorKey(255, 0, 255, i);

	m_ScoreNumberWidget->SetPos(700.f, 300.f);
	m_ScoreNumberWidget->SetNumber(GameScore.Score);


	// Rate Text Setting
	m_ScoreTextWidget = CreateWidget<CTextWidget>("GameText");

	m_ScoreTextWidget->SetTexture("Alphabet", m_vecTextFileName);

	for (int i = 0; i < 26; ++i)
		m_ScoreTextWidget->SetTextureColorKey(255, 0, 255, i);

	m_ScoreTextWidget->SetPos(700.f, 400.f);

	std::string Rate = "";

	switch (GameScore.Rate)
	{
	case EGame_Rate::Great:
		Rate = "Great";
		break;
	case EGame_Rate::Sick:
		Rate = "Sick";
		break;
	case EGame_Rate::Good:
		Rate = "Good";
		break;
	case EGame_Rate::Meh:
		Rate = "Meh";
		break;
	case EGame_Rate::Failed:
		Rate = "Failed";
		break;
	}

	m_ScoreTextWidget->SetText(Rate);


	// MaxCombo Value Setting
	m_ScoreNumberWidget = CreateWidget<CNumberWidget>("ScoreValue");

	m_ScoreNumberWidget->SetTexture("Number", m_vecNumberFileName);

	for (int i = 0; i < 10; ++i)
		m_ScoreNumberWidget->SetTextureColorKey(255, 0, 255, i);

	m_ScoreNumberWidget->SetPos(700.f, 500.f);
	m_ScoreNumberWidget->SetNumber(GameScore.MaxCombo);

}

void CUI_GameEndRate::GameRetry()
{
	CSceneManager::GetInst()->CreateScene<CScene_GamePlay>(m_SongName, m_Difficulty);
}

void CUI_GameEndRate::GameNext()
{
}

void CUI_GameEndRate::GameExit()
{
	if (m_IsStoryMode) {
		CSceneManager::GetInst()->CreateScene<CScene_ModeSelect>();
	}
	else {
		CSceneManager::GetInst()->CreateScene<CScene_FreePlay>();
	}
}
