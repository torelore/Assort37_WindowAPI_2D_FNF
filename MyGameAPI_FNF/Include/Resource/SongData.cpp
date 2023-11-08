#include "SongData.h"
#include "../PathManager.h"

CSongData::CSongData()
{
}

CSongData::~CSongData()
{
}

bool CSongData::LoadAllSongData()
{
	const TCHAR* JsonPath = CPathManager::GetInst()->FindPath(JSON_PATH)->Path;
	const std::wstring JsonWPath(JsonPath);
	
	std::string Path(JsonWPath.begin(), JsonWPath.end());
	std::string Filter = "*";
	std::string fullPath = Path + Filter;
	
	std::vector<std::string> JsonList;
	
	_finddata_t  fd;
	intptr_t handle = _findfirst(fullPath.c_str(), &fd);
	
	if (handle == -1)
		return false;

	int result = 0;

	do {
		std::string Song = fd.name;
		
		if (Song == "." || Song == "..") {
			result = _findnext(handle, &fd);
			continue;
		}
		else {
			result = _findnext(handle, &fd);
		}

		std::string EasyFullPath = Path + Song + "\\" + Song + "-easy.json";
		LoadJsonFullPath(Song, EasyFullPath, ESong_Difficulty::Easy);

		std::string NormalFullPath = Path + Song + "\\" + Song + ".json";
		LoadJsonFullPath(Song, NormalFullPath, ESong_Difficulty::Normal);

		std::string HardFullPath = Path + Song + "\\" + Song + "-hard.json";
		LoadJsonFullPath(Song, HardFullPath, ESong_Difficulty::Hard);


	} while (result != -1);

	_findclose(handle);

	return true;
}

bool CSongData::LoadJsonFullPath(const std::string& Name, const std::string& FullPath, const ESong_Difficulty& Difficulty)
{
	std::ifstream json_dir(FullPath);

	Json::CharReaderBuilder builder;
	builder["collectComments"] = false;

	Json::Value value;
	JSONCPP_STRING errs;

	bool ok = parseFromStream(builder, json_dir, &value, &errs);

	if (ok) { // 읽어온 json을 형식에 따라 처리
		SongInfo* Info = new SongInfo;

		Info->SongName = value["song"]["song"].asString();

		std::list<NoteInfo> NotesList;

		size_t Size = value["song"]["notes"].size();

		for (int i = 0; i < Size; i++) {
			bool isOwnPlayer = value["song"]["notes"][i]["mustHitSection"].asBool();
			int bpm = value["song"]["notes"][i]["bpm"].asInt();

			int NotesCount = value["song"]["notes"][i]["sectionNotes"].size();

			if (NotesCount == 0)
				continue;

			for (int j = 0; j < NotesCount; j++) {

				ENote_Type direction = ENote_Type::Left;

				if (value["song"]["notes"][i]["sectionNotes"][j][1] == 1)
					direction = ENote_Type::Down;

				if (value["song"]["notes"][i]["sectionNotes"][j][1] == 2)
					direction = ENote_Type::Up;

				if (value["song"]["notes"][i]["sectionNotes"][j][1] == 3)
					direction = ENote_Type::Right;

				float	Timing = value["song"]["notes"][i]["sectionNotes"][j][0].asFloat();
				float	LongNote = value["song"]["notes"][i]["sectionNotes"][j][2].asFloat();

				NoteInfo Note = NoteInfo(direction, Timing, (ENote_Owner)isOwnPlayer, bpm, LongNote);

				NotesList.push_back(Note);
			}
		}

		auto iter = m_mapSongInfo.begin();
		auto iterEnd = m_mapSongInfo.end();

		bool isNew = true;

		for (; iter != iterEnd; iter++) {
			if (iter->first == Info->SongName) {
				isNew = false;
				break;
			}
		}

		if (isNew) {
			Info->NotesList.insert(std::make_pair(Difficulty, NotesList));
			m_mapSongInfo.insert(std::make_pair(Info->SongName, Info));
		}
		else {
			m_mapSongInfo.find(Info->SongName)->second->NotesList.insert(std::make_pair(Difficulty, NotesList));
		}
	}

	return true;
}
