#include "UI_FreePlay.h"
#include "../../GameManager.h"
#include "../UIImage.h"
#include "../TextWidget.h"
#include "../NumberWidget.h"

CUI_FreePlay::CUI_FreePlay()
{
	m_Score = 0;
	m_Time = 0.f;

	m_WhiteSpaceFixed = Vector2(UI_FREEPLAY_SONG_X, UI_FREEPLAY_SONG_Y);
}

CUI_FreePlay::~CUI_FreePlay()
{
}

bool CUI_FreePlay::Init()
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
	m_ScoreTextWidget = CreateWidget<CTextWidget>("Alphabet");

	m_ScoreTextWidget->SetTexture("Alphabet", m_vecTextFileName);

	for (int i = 0; i < 26; ++i)
		m_ScoreTextWidget->SetTextureColorKey(255, 0, 255, i);

	m_ScoreTextWidget->SetPos(775.f, 25.f);
	m_ScoreTextWidget->SetText("Score");


	// SCORE Value Setting
	m_ScoreNumberWidget = CreateWidget<CNumberWidget>("Number");

	m_ScoreNumberWidget->SetTexture("Number", m_vecNumberFileName);

	for (int i = 0; i < 10; ++i)
		m_ScoreNumberWidget->SetTextureColorKey(255, 0, 255, i);

	m_ScoreNumberWidget->SetPos(1000.f, 25.f);
	m_ScoreNumberWidget->SetNumber(0);

	return true;
}

void CUI_FreePlay::Update(float DeltaTime)
{
	CUIWindow::Update(DeltaTime);

	m_Time += DeltaTime;

	size_t Size = m_vecSongListTextWidget.size();

	for (size_t i = 0; i < Size; i++) {
		Vector2 Pos = Vector2(m_WhiteSpaceFixed.x + i * UI_FREEPLAY_SONG_MOVE_X, m_WhiteSpaceFixed.y + i * UI_FREEPLAY_SONG_MOVE_Y);

		m_vecSongListTextWidget[i]->SetPos(Pos);
	}
}

void CUI_FreePlay::AddVecTextWidget(const std::string& SongName)
{
	CTextWidget* TextWidget = CreateWidget<CTextWidget>("Alphabet");

	TextWidget->SetTexture("Alphabet", m_vecTextFileName);

	for (int i = 0; i < 26; ++i)
		TextWidget->SetTextureColorKey(255, 0, 255, i);

	TextWidget->SetText(SongName);

	m_vecSongListTextWidget.push_back(TextWidget);
}

std::string CUI_FreePlay::GetNowSelectedSongName() const
{
	size_t Size = m_vecSongListTextWidget.size();

	for (size_t i = 0; i < Size; i++)
		if (m_vecSongListTextWidget[i]->GetPos().y == UI_FREEPLAY_SONG_Y)
			return m_vecSongListTextWidget[i]->GetText();

	return "";
}

int CUI_FreePlay::GetNowSelectedSongNum() const
{
	size_t Size = m_vecSongListTextWidget.size();

	for (size_t i = 0; i < Size; i++)
		if (m_vecSongListTextWidget[i]->GetPos().y == UI_FREEPLAY_SONG_Y)
			return (int)i;

	return 0;
}

