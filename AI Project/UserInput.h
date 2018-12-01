#pragma once
#include <string>
#include <sstream>
#include <iostream>
#include <Windows.h>

class UserInput;

class UserInput 
{
private:
	bool m_Correct;
	int m_LevelQuantity;
	std::string m_TempLevelQuantity;

public:
	UserInput();
	int GetLevelQuantity();
	int GetLevelToLoad();
};