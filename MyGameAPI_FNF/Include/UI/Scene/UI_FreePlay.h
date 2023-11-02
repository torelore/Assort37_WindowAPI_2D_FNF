#pragma once

#include "../UIWindow.h"

class CUI_FreePlay :
	public CUIWindow
{
	friend class CScene;

private:
	CUI_FreePlay();
	virtual ~CUI_FreePlay();

private:
	int			m_Score;
	float		m_Time;


private :
	class CTextWidget*				m_ScoreTextWidget;
	std::vector<class CTextWidget*>	m_vecSongListTextWidget;

	Vector2 m_WhiteSpaceFixed;

	std::vector<std::wstring>		m_vecTextFileName;

private :
	class CNumberWidget*			m_ScoreNumberWidget;
	std::vector<std::wstring>		m_vecNumberFileName;

public :
	void SetScore(int Score) {
		m_Score = Score;
	}

	void SetWhiteSpace(float x, float y) {
		m_WhiteSpaceFixed.x = x;
		m_WhiteSpaceFixed.y = y;
	}

	void SetWhiteSpace(Vector2 vecWhiteSpace) {
		m_WhiteSpaceFixed.x = vecWhiteSpace.x;
		m_WhiteSpaceFixed.y = vecWhiteSpace.y;
	}

	Vector2 GetWhiteSpace() const {
		return m_WhiteSpaceFixed;
	}

	void ResetTime() {
		m_Time = 0.f;
	}

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);

public :
	void AddVecTextWidget(const std::string& SongName);
	std::string GetNowSelectedSongName() const;
	int GetNowSelectedSongNum() const;
};
