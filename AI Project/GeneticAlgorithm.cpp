#include "GeneticAlgorithm.h"

GeneticAlgorithm::GeneticAlgorithm()
{
	int m_Val = 0;
	m_ChromosomeLength = 20;
	m_ChromosomeQuantity = 20;
	m_Chromosomes.resize(m_ChromosomeQuantity, std::vector<int>(0));
}

void GeneticAlgorithm::FullyLoadLevel(std::vector<int> _1DLevel)
{
	m_CurrentLevel.resize(_1DLevel[0], std::vector<int>(_1DLevel[1]));						// Change the size of current level based on the first 2 values within the level array
	m_Val = 0;
	// Loop to load the requested level
	for (int j = 0; j < m_CurrentLevel.size(); j++)											// Loops for the x size of the level
	{
		for (int k = 0; k < m_CurrentLevel[j].size(); k++)									// Loops for the y size of the level
		{
			m_CurrentLevel[j][k] = _1DLevel[m_Val + 2];										// Loads the values into the correct part of currentLevel
			if (_1DLevel[m_Val + 2] == 2)													// Save the start location
			{
				m_StartLocation[0] = j;
				m_StartLocation[1] = k;
			}
			else if (_1DLevel[m_Val + 2] == 3)												// Save the end location
			{
				m_EndLocation[0] = j;
				m_EndLocation[1] = k;
			}
			m_Val++;																		// Increments val
		}
	}
}

void GeneticAlgorithm::Draw()
{
	system("CLS");																									// First, clear the screen 
	std::cout << "Key: " << std::endl << "0 = Empty Space \n1 = Wall \n2 = Start \n3 = Finish \n" << std::endl;		// Output the key
	
	// Looping to output 
	for (int i = 0; i < m_CurrentLevel.size(); i++)																	// Loop the rows first
	{
		std::cout << " ";
		for (int j = 0; j < m_CurrentLevel[i].size(); j++)															// Then loop for each column
		{
			std::cout << "----";																					// Output the row lines
		}
		std::cout << "-" << std::endl;																				// 1 extra line must always be added for the row lines to fit
		std::cout << " | ";																							// Add the first column line
		for (int j = 0; j < m_CurrentLevel[i].size(); j++)															// Then loop again for each column
		{
			std::cout << m_CurrentLevel[i][j] << " | ";																// Output the level followed by the column lines
		}
		std::cout << std::endl;																						// Change to next line
		if (i == (m_CurrentLevel.size() - 1))																		// If we are on the last line, print the final row line
		{
			std::cout << " ";
			for (int j = 0; j < m_CurrentLevel[i].size(); j++)														// Again, loop fro each column
			{
				std::cout << "----";																				// Output the lines
			}
			std::cout << "-" << std::endl;																			// Add the 1 extra line
		}
	}
}

void GeneticAlgorithm::CreateChromosomes()
{
	srand(time(NULL));
	for (int j = 0; j < m_ChromosomeQuantity; j++)
	{
		for (int i = 0; i < m_ChromosomeLength; i++)
		{																			// Key: (Compass) 0 = N, 1 = NE, 2 = E, 3 = SE, 4 = S, 5 = SW, 6 = W, 7 = NW
			m_Chromosomes[j].push_back(rand() % 8);									// Add a random integer from 0 - 7
		}
	}
}

void GeneticAlgorithm::TestChromosomes()
{
	for (int i = 0; i < m_ChromosomeQuantity; i++)
	{
		for (int j = 0; j < m_ChromosomeLength; j++)
		{

		}
	}
}

void GeneticAlgorithm::UpdateChromosomes()
{

}
