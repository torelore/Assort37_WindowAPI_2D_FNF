#pragma once

#include "../GameInfo.h"
#include "Scene.h"
#include "Scene/Scene_GamePlay.h"
#include "Scene/Scene_GameEndRate.h"

class CSceneManager
{
private:
	CSceneManager();
	~CSceneManager();

private:
	CScene* m_Scene;
	CScene* m_NextScene;

public:
	CScene* GetScene()
	{
		return m_Scene;
	}

public:
	bool Init();
	bool Update(float DeltaTime);
	bool PostUpdate(float DeltaTime);
	bool Collision(float DeltaTime);
	bool Render(HDC hDC);

private:
	bool ChangeScene();

private:
	static CSceneManager* m_Inst;

public:
	static CSceneManager* GetInst()
	{
		if (!m_Inst)
			m_Inst = new CSceneManager;

		return m_Inst;
	}

	static void DestroyInst()
	{
		SAFE_DELETE(m_Inst);
	}

public:
	template <typename T>
	bool CreateScene()
	{
		m_NextScene = new T;

		if (!m_NextScene->Init())
		{
			SAFE_DELETE(m_NextScene);
			return false;
		}

		return true;
	}

	template <typename T>
	bool CreateScene(const std::string& SongName, const ESong_Difficulty& Difficulty, bool IsStoryMode = false)
	{
		m_NextScene = new T;

		if (!m_NextScene->Init())
		{
			SAFE_DELETE(m_NextScene);
			return false;
		}

		if (((CScene_GamePlay*)m_NextScene)->SetSongInfo(SongName, Difficulty, IsStoryMode))
			return false;

		return true;
	}

	template <typename T>
	bool CreateScene(const GameScore& GameScore, bool IsStoryMode = false)
	{
		m_NextScene = new T;

		if (!m_NextScene->Init())
		{
			SAFE_DELETE(m_NextScene);
			return false;
		}

		((CScene_GameEndRate*)m_NextScene)->SetGameRate(GameScore);

		if (IsStoryMode)
			((CScene_GameEndRate*)m_NextScene)->IsStoryMode();

		return true;
	}
};

