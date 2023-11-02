#pragma once

#include "../UIWindow.h"

class CUI_GameEndRate :
	public CUIWindow
{
	friend class CScene;

private:
	CUI_GameEndRate();
	virtual ~CUI_GameEndRate();

private:
	class CTextWidget*				m_ScoreTextWidget;
	std::vector<class CTextWidget*>	m_vecButtonListTextWidget;

	std::vector<std::wstring>		m_vecTextFileName;

private:
	class CNumberWidget*			m_ScoreNumberWidget;
	std::vector<std::wstring>		m_vecNumberFileName;

private :
	bool		m_IsStoryMode;
	float		m_Time;
	bool		m_IsLeftSelected;
	bool		m_IsLeftMove;

private :
	std::string			m_SongName;
	ESong_Difficulty	m_Difficulty;

public :
	void SetIsStroyMode() {
		m_IsStoryMode = true;
	}

	void SetIsLeftSelect() {
		m_IsLeftSelected = true;
	}

	bool GetIsLeftSelected() const {
		return m_IsLeftSelected;
	}

	void SetIsRightSelect() {
		m_IsLeftSelected = false;
	}

	bool GetIsStoryMode() const {
		return m_IsStoryMode;
	}

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);

public :
	void SetGameRate(const GameScore& GameScore);
	void GameRetry();
	void GameNext();
	void GameExit();
};

