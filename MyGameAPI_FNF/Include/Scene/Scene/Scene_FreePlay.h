#pragma once

#include "../Scene.h"
#include "../../Object/Text/Button_Diffi_Arrow.h"

class CScene_FreePlay :
	public CScene
{
	friend class CSceneManager;

private:
	CScene_FreePlay();
	virtual ~CScene_FreePlay();

public:
	virtual bool Init();

private :
	std::vector<std::string>	m_vecSongName;
	ESong_Difficulty			m_SongDifficuly;

public :
	void SetSongDifficulty(ESong_Difficulty Difficulty) {
		m_SongDifficuly = Difficulty;
	}

private :
	CButton_Diffi_Arrow* LeftArrow;
	CButton_Diffi_Arrow* RightArrow;

private:
	void LoadAnimationSequence();
	void LoadSound();

public :
	void EnterPressed();
	void UpPressed(float DeltaTime);
	void DownPressed(float DeltaTime);
	void LeftPressed(float DeltaTime);
	void RightPressed(float DeltaTime);
};

