#include "GeneticAlgorithm.h"

GeneticAlgorithm::GeneticAlgorithm()
{
	int m_Val = 0;
}

void GeneticAlgorithm::FullyLoadLevel(std::vector<int> _1DLevel)
{
	m_CurrentLevel.resize(_1DLevel[0], std::vector<int>(_1DLevel[1]));
	m_Val = 0;
	for (int j = 0; j < m_CurrentLevel.size(); j++)											// Loops for the x size of the level
	{
		for (int k = 0; k < m_CurrentLevel[j].size(); k++)									// Loops for the y size of the level
		{
			m_CurrentLevel[j][k] = _1DLevel[m_Val + 2];										// Loads the values into the correct part of currentLevel
			m_Val++;																			// Increments val
		}
	}
}

void GeneticAlgorithm::Draw()
{
	system("CLS");
	std::cout << "Key: " << std::endl << "0 = Empty Space \n1 = Wall \n2 = Start \n3 = Finish \n" << std::endl;
	for (int i = 0; i < m_CurrentLevel.size(); i++)
	{
		for (int j = 0; j < m_CurrentLevel[i].size(); j++)
		{
			std::cout << " " << m_CurrentLevel[i][j];
		}
		std::cout << std::endl;
	}
}
