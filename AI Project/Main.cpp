#include <iostream>
#include <Windows.h>
#include <math.h>
#include <cmath>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "UserInput.h"
#include "FileLoader.h"
#include "GeneticAlgorithm.h"

int main()
{
	int levelToLoad;
	std::vector<int> theLevel;
	UserInput userInput;
	FileLoader levelLoader(userInput.GetLevelQuantity());
	GeneticAlgorithm geneticAlgorithm;

	levelLoader.LoadFiles();
	levelLoader.LoadLevels();
	levelToLoad = userInput.GetLevelToLoad();
	theLevel = levelLoader.ReturnLevel(levelToLoad);
	geneticAlgorithm.FullyLoadLevel(theLevel);
	geneticAlgorithm.Draw();


	system("PAUSE");
	return 0;
}