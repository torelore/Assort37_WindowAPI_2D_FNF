#pragma once

#include "../Ref.h"

class CSongData :
    public CRef
{
    friend class CResourceManager;

private:
    CSongData();
    ~CSongData();

private :
    std::unordered_map<std::string, SongInfo*>	m_mapSongInfo;

public :
    bool LoadAllSongData();
    bool LoadJsonFullPath(const std::string& Name, const std::string& FullPath, const ESong_Difficulty& Difficulty = ESong_Difficulty::Normal);

    std::unordered_map<std::string, SongInfo*> GetMapSongData() const {
        return m_mapSongInfo;
    }


private :
	const TCHAR* StringToTchar(std::string& Name) {

		// 기존 string 사이즈
		size_t Size = strlen(Name.c_str());
		size_t ConvertSize = 0;

		wchar_t* tString = new wchar_t[Size];

		mbstowcs_s(&ConvertSize, tString, Size, Name.c_str(), _TRUNCATE);

		return (TCHAR*)tString;
	}

public :
    SongInfo* FindSongInfo(const std::string& Name) const {

        auto iter = m_mapSongInfo.find(Name);

        return iter->second;
    }

};

