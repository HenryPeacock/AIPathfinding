#pragma once
#include <string>
#include <sstream>
#include <iostream>
#include <Windows.h>

class UserInput 
{
private:
	bool m_Correct;
	int m_LevelQuantity;
	int m_LevelChoice;
	int m_MenuChoice;
	std::string m_TempLevelQuantity;

public:
	UserInput();
	int GetLevelQuantity();
	int GetLevelToLoad();
	int Menu();
};