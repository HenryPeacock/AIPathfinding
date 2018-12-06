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
	// Initialising the variables
	int levelToLoad;
	int algorithmChoice;
	std::vector<int> theLevel;
	UserInput userInput;
	GeneticAlgorithm geneticAlgorithm;

	// Choosing the algorithm
	algorithmChoice = userInput.Menu();

	// Loading the levels
	FileLoader levelLoader(userInput.GetLevelQuantity());
	levelLoader.LoadFiles();
	levelLoader.LoadLevels();

	// Choosing the algorithm
	if (algorithmChoice == 1)
	{
		// Complete level loading and initialise the genetic algorithm
		levelToLoad = userInput.GetLevelToLoad();
		theLevel = levelLoader.ReturnLevel(levelToLoad);
		geneticAlgorithm.FullyLoadLevel(theLevel);
		geneticAlgorithm.Draw();
		
		// Completing the genetic algorithm
		geneticAlgorithm.CreateChromosomes();
		geneticAlgorithm.TestChromosomes();
		
	}
	else if (algorithmChoice == 2)
	{
		std::cout << "A* Choice placeholder" << std::endl;
	}
	else
	{
		throw std::exception();
	}

	
	system("PAUSE");
	return 0;
}