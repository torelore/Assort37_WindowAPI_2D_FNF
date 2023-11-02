#pragma once

#include "../Scene.h"
#include "../../Object/ComboFont.h"
#include "../../Object/EffectTiming.h"

class CScene_GamePlay : 
	public CScene
{
public :
	CScene_GamePlay();
	CScene_GamePlay(const CScene_GamePlay& scene);
	virtual ~CScene_GamePlay();

public:
	virtual bool Init();

private :
	int				m_Score;
	int				m_NoteCount;
	int				m_NoteMissCount;
	float			m_Rating;
	int				m_Combo;
	int				m_MaxCombo;
	CEffectTiming*	m_NoteRate;
	CComboFont*		m_ComboFont;

private :
	std::string			m_NowSongName;
	ESong_Difficulty	m_NowSongDifficulty;
	bool				m_IsGameStop;
	bool				m_IsStoryMode;

private :
	std::string m_SongNameVoice;
	std::string m_SongNameInst;

public :
	void AddScore(int Score) {
		m_Score += Score;
	}

	void AddNoteMissCount() {
		m_NoteMissCount++;
	}

	void AddCombo() {
		m_Combo++;

		if (m_Combo > m_MaxCombo)
			m_MaxCombo = m_Combo;
	}

	void ResetCombo() {
		m_Combo = 0;
	}

	void SetRate(float Rate) {
		m_Rating = Rate;
	}

	void SetRate() {
		m_Rating = 100.f - (((float)m_NoteMissCount / (float)m_NoteCount) * 100.f);
	}

	bool IsStoryMode() const {
		return m_IsStoryMode;
	}

private:
	void LoadAnimationSequence();
	void LoadAnimationSequence_Daddy();
	void LoadAnimationSequence_Mom();
	void LoadAnimationSequence_Monster();
	void LoadAnimationSequence_Pico();
	void LoadAnimationSequence_Spooky();
	void LoadAnimationSequence_Senpai();
	void LoadAnimationSequence_Parents();

private :
	void LoadSound();
	void LoadSong(const std::string Name);

public :
	void PlaySong();
	void ResumeSong();
	void PauseSong();
	void StopSong();
	bool SetSongInfo(const std::string& Name, const ESong_Difficulty& Difficulty, bool IsStoryMode = false);
	void ComboEffect(const ENote_Rate& Rate);
	GameScore GameOver();
	GameScore GameEnd();
	void EnterPressed();
};

