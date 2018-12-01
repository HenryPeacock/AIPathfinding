#include <vector>
#include <iostream>
#include <stdlib.h>

class GeneticAlgorithm;

class GeneticAlgorithm 
{
private:
	std::vector<std::vector<int>> m_CurrentLevel;
	int m_Val;
	int m_LevelNumber;

public:
	GeneticAlgorithm();
	void FullyLoadLevel(std::vector<int> _1DLevel);
	void Draw();
};
