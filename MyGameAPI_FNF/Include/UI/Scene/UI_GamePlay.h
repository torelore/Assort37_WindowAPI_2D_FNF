#pragma once
#include "../UIWindow.h"
#include "../UIImage.h"
#include "../../Object/Note.h"

class CUI_GamePlay :
	public CUIWindow
{
	friend class CScene;

private:
	CUI_GamePlay();
	virtual ~CUI_GamePlay();

private:
	float	m_Time;
	bool	m_Start;
	bool	m_Pause;
	bool	m_End;
	int		m_CountDown;

	CUIImage* m_CountDownImage;

	SongInfo			m_SongInfo;
	int					m_NoteCount;
	std::list<NoteInfo> m_listNoteInfo;
	ESong_Difficulty	m_Difficulty;
	std::list<CSharedPtr<CNote>> m_listLeftNote;
	std::list<CSharedPtr<CNote>> m_listUpNote;
	std::list<CSharedPtr<CNote>> m_listDownNote;
	std::list<CSharedPtr<CNote>> m_listRightNote;

public :
	CNote* GetLeftFirstNote() const {
		if (m_listLeftNote.empty())
			return nullptr;

		return m_listLeftNote.front();
	}

	void PopLeftFirstNote() {
		if(!m_listLeftNote.empty())
			m_listLeftNote.pop_front();
	}

	CNote* GetUpFirstNote() const {
		if (m_listUpNote.empty())
			return nullptr;

		return m_listUpNote.front();
	}

	void PopUpFirstNote() {
		if (!m_listUpNote.empty())
			m_listUpNote.pop_front();
	}

	CNote* GetDownFirstNote() const {
		if (m_listDownNote.empty())
			return nullptr;

		return m_listDownNote.front();
	}

	void PopDownFirstNote() {
		if (!m_listDownNote.empty())
			m_listDownNote.pop_front();
	}

	CNote* GetRightFirstNote() const {
		if (m_listRightNote.empty())
			return nullptr;

		return m_listRightNote.front();
	}

	void PopRightFirstNote() {
		if (!m_listRightNote.empty())
			m_listRightNote.pop_front();
	}

	void SetPause() {
		m_Pause = true;
	}

	void SetResume() {
		m_Pause = false;
	}

public :
	void SetSongInfo(SongInfo& Info, const ESong_Difficulty& Difficulty);

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
};

