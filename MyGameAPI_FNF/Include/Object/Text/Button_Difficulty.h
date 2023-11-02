#pragma once

#include "../GameObject.h"

class CButton_Difficulty :
	public CGameObject
{
	friend class CScene;

protected:
	CButton_Difficulty();
	CButton_Difficulty(const CButton_Difficulty& obj);
	virtual ~CButton_Difficulty();

private:
	ESong_Difficulty		m_Difficulty;

public :
	void SetSongDifficulty(const ESong_Difficulty& Difficulty) {
		m_Difficulty = Difficulty;
	}

	ESong_Difficulty GetDifficulty() const {
		return m_Difficulty;
	}

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC);
	virtual CButton_Difficulty* Clone();
	virtual bool ButtonScene(float InputTime);

public :
	void EnterPressed(float DeltaTime);
	void UpPressed(float DeltaTime);
	void DownPressed(float DeltaTime);
	void LeftPressed(float DeltaTime);
	void RightPressed(float DeltaTime);
};

