#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <Windows.h>

class FileLoader;

class FileLoader
{
private:
	char m_PlaceHolder;
	char m_LegalChars[10];
	bool m_IsLoaded;
	int m_Val;
	int m_LevelQuantity;
	std::vector<char> m_TempLevel;
	std::vector<int> m_CurrentLevel;
	std::vector<std::vector<int>> m_LevelMatrix;
	std::ifstream m_LevelFiles[5];

public:
	FileLoader(int _LQ);
	void LoadFiles();
	void LoadLevels();
	std::vector<int> ReturnLevel(int _LevelNumber);
};