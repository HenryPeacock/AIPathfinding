#include "GeneticAlgorithm.h"

GeneticAlgorithm::GeneticAlgorithm()
{
	m_Val = 0;
	m_ChromosomeLength = 20;
	m_ChromosomeQuantity = 20;
	m_Chromosomes.resize(m_ChromosomeQuantity, std::vector<int>(0));
	m_TempChromosomes.resize(2, std::vector<int>(m_ChromosomeLength));
	m_ChromosomeFinished = false;
	m_ChromosomeFitness.resize(m_ChromosomeQuantity);
	m_ChanceToBreed.resize(m_ChromosomeQuantity);
	m_SwapRate = 0.7;
	m_ChromosomeLengthAway.resize(m_ChromosomeQuantity, std::vector<int>(2));
	m_MutationRate = 0.01;
	m_GenerationCount = 0;
	m_FinalChromosome.resize(m_ChromosomeLength);
	m_AlwaysFalse = false;
	srand(time((unsigned)NULL));
}

void GeneticAlgorithm::FullyLoadLevel(std::vector<int> _1DLevel)
{
	m_CurrentLevel.resize(_1DLevel[1] + 1, std::vector<int>(_1DLevel[0] + 1));						// Change the size of current level based on the first 2 values within the level array
	m_Val = 0;
	// Loop to load the requested level
	for (int j = 1; j < m_CurrentLevel.size(); j++)											// Loops for the x size of the level
	{
		for (int k = 1; k < m_CurrentLevel[j].size(); k++)									// Loops for the y size of the level
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
	for (int i = 1; i < m_CurrentLevel.size(); i++)																	// Loop the rows first
	{
		std::cout << " ";
		for (int j = 1; j < m_CurrentLevel[i].size(); j++)															// Then loop for each column
		{
			std::cout << "----";																					// Output the row lines
		}
		std::cout << "-" << std::endl;																				// 1 extra line must always be added for the row lines to fit
		std::cout << " | ";																							// Add the first column line
		for (int j = 1; j < m_CurrentLevel[i].size(); j++)															// Then loop again for each column
		{
			std::cout << m_CurrentLevel[i][j] << " | ";																// Output the level followed by the column lines
		}
		std::cout << std::endl;																						// Change to next line
		if (i == (m_CurrentLevel.size() - 1))																		// If we are on the last line, print the final row line
		{
			std::cout << " ";
			for (int j = 1; j < m_CurrentLevel[i].size(); j++)														// Again, loop fro each column
			{
				std::cout << "----";																				// Output the lines
			}
			std::cout << "-" << std::endl;																			// Add the 1 extra line
		}
	}
}

void GeneticAlgorithm::CreateChromosomes()
{
	for (int j = 0; j < m_ChromosomeQuantity; j++)
	{
		for (int i = 0; i < m_ChromosomeLength; i++)
		{																									// Key: (Compass) 0 = N, 1 = NE, 2 = E, 3 = SE, 4 = S, 5 = SW, 6 = W, 7 = NW
			m_RandomNumber.seed(std::random_device()());
			std::uniform_int_distribution<std::mt19937::result_type> m_Distribute(0, 7);
			m_Chromosomes[j].push_back(m_Distribute(m_RandomNumber));									// Add a random integer from 0 - 7
		}
	}
}

std::vector<int> GeneticAlgorithm::TestChromosomes()
{
	while (m_AlwaysFalse == false)
	{
		for (int i = 0; i < m_ChromosomeQuantity; i++)
		{
			m_GenerationCount++;
			m_CurrentLocation = m_StartLocation;
			m_ChromosomeFinished = false;
			for (int j = 0; j < m_ChromosomeLength; j++)
			{
				CalculateDirections(i, j);
				if (m_ChromosomeFinished == true)
				{
					return m_Chromosomes[i];
				}
				else if (j == m_ChromosomeLength - 1)
				{
					m_ChromosomeMovesTaken.push_back(j + 1);
				}
			}
			m_ChromosomeLengthAway[i][0] = abs(m_EndLocation[0] - m_CurrentLocation[0]);
			m_ChromosomeLengthAway[i][1] = abs(m_EndLocation[1] - m_CurrentLocation[1]);
			CalculateFitness(i);
		}
		for (int i = 0; i < (m_ChromosomeQuantity / 2); i++)
		{
			UpdateChromosomes();
		}
		for (int i = 0; i < m_ChromosomeQuantity; i++)
		{
			MutateChromosomes(i);
		}
		if ((m_GenerationCount % 1000) == 0)
		{
			std::cout << m_GenerationCount << std::endl;
		}
	}
}

void GeneticAlgorithm::UpdateChromosomes()
{
	m_Parent1 = BreedSelector();
	m_Parent2 = BreedSelector();
	m_SwapValue = (double)rand() / (RAND_MAX + 1.0);
	if (m_SwapValue > m_SwapRate)
	{
		for (int i = 0; i < m_ChromosomeLength / 2; i++)
		{
			m_TempChromosomes[0][i] = m_Chromosomes[m_Parent1][i];
			m_TempChromosomes[1][i] = m_Chromosomes[m_Parent2][i];
		}
		for (int i = (m_ChromosomeLength / 2); i < m_ChromosomeLength; i++)
		{
			m_TempChromosomes[0][i] = m_Chromosomes[m_Parent2][i];
			m_TempChromosomes[1][i] = m_Chromosomes[m_Parent1][i];
		}
		for (int i = 0; i < m_ChromosomeLength; i++)
		{
			m_Chromosomes[m_Parent1][i] = m_TempChromosomes[0][i];
			m_Chromosomes[m_Parent2][i] = m_TempChromosomes[0][i];
		}
	}
}

void GeneticAlgorithm::CalculateDirections(int _i, int _j)
{
	// North
	if ((m_Chromosomes[_i][_j] == 0) && ((m_CurrentLocation[0] - 1) > 0))
		{
			if (m_CurrentLevel[m_CurrentLocation[0] - 1][m_CurrentLocation[1]] == 3)
			{
				m_ChromosomeFinished = true;
			}
			else if ((m_CurrentLevel[m_CurrentLocation[0] - 1][m_CurrentLocation[1]] != 1))
			{
				m_CurrentLocation[0] -= 1;
			}

		}
	// North East
	else if ((m_Chromosomes[_i][_j] == 1) && ((m_CurrentLocation[0] - 1) > 0) && ((m_CurrentLocation[1] + 1) < m_CurrentLevel[0].size()))
		{
			if (m_CurrentLevel[m_CurrentLocation[0] - 1][m_CurrentLocation[1] + 1] == 3)
			{
				m_ChromosomeFinished = true;
			}
			else if ((m_CurrentLevel[m_CurrentLocation[0] - 1][m_CurrentLocation[1] + 1] != 1))
			{
				m_CurrentLocation[0] -= 1;
				m_CurrentLocation[1] += 1;
			}
		}
	// East
	else if ((m_Chromosomes[_i][_j] == 2) && ((m_CurrentLocation[1] + 1) < m_CurrentLevel[0].size()))
		{
			if (m_CurrentLevel[m_CurrentLocation[0]][m_CurrentLocation[1] + 1] == 3)
			{
				m_ChromosomeFinished = true;
			}
			else if ((m_CurrentLevel[m_CurrentLocation[0]][m_CurrentLocation[1] + 1] != 1))
			{
				m_CurrentLocation[1] += 1;
			}
		}
	// South East
	else if ((m_Chromosomes[_i][_j] == 3) && ((m_CurrentLocation[0] + 1) < m_CurrentLevel.size()) && ((m_CurrentLocation[1] + 1) < m_CurrentLevel[0].size()))
		{
			if (m_CurrentLevel[m_CurrentLocation[0] + 1][m_CurrentLocation[1] + 1] == 3)
			{
				m_ChromosomeFinished = true;
			}
			else if ((m_CurrentLevel[m_CurrentLocation[0] + 1][m_CurrentLocation[1] + 1] != 1))
			{
				m_CurrentLocation[0] += 1;
				m_CurrentLocation[1] += 1;
			}
		}
	// South
	else if ((m_Chromosomes[_i][_j] == 4) && ((m_CurrentLocation[0] + 1) < m_CurrentLevel.size()))
		{
			if (m_CurrentLevel[m_CurrentLocation[0] + 1][m_CurrentLocation[1]] == 3)
			{
				m_ChromosomeFinished = true;
			}
			else if ((m_CurrentLevel[m_CurrentLocation[0] + 1][m_CurrentLocation[1]] != 1))
			{
				m_CurrentLocation[0] += 1;
			}
		}
	// South West
	else if ((m_Chromosomes[_i][_j] == 5) && ((m_CurrentLocation[0] + 1) < m_CurrentLevel.size()) && ((m_CurrentLocation[1] - 1) > 0))
		{
			if (m_CurrentLevel[m_CurrentLocation[0] + 1][m_CurrentLocation[1] - 1] == 3)
			{
				m_ChromosomeFinished = true;
			}
			else if ((m_CurrentLevel[m_CurrentLocation[0] + 1][m_CurrentLocation[1] - 1] != 1))
			{
				m_CurrentLocation[0] += 1;
				m_CurrentLocation[1] -= 1;
			}
		}
	// West
	else if ((m_Chromosomes[_i][_j] == 6) && ((m_CurrentLocation[1] - 1) > 0))
		{
			if (m_CurrentLevel[m_CurrentLocation[0]][m_CurrentLocation[1] - 1] == 3)
			{
				m_ChromosomeFinished = true;
			}
			else if ((m_CurrentLevel[m_CurrentLocation[0]][m_CurrentLocation[1] - 1] != 1))
			{
				m_CurrentLocation[1] -= 1;
			}
		}
	// North West
	else if ((m_Chromosomes[_i][_j] == 7) && ((m_CurrentLocation[1] - 1) > 0) && ((m_CurrentLocation[0] - 1) > 0))
		{
			if (m_CurrentLevel[m_CurrentLocation[0] - 1][m_CurrentLocation[1] - 1] == 3)
			{
				m_ChromosomeFinished = true;
			}
			else if ((m_CurrentLevel[m_CurrentLocation[0] - 1][m_CurrentLocation[1] - 1] != 1))
			{
				m_CurrentLocation[0] -= 1;
				m_CurrentLocation[1] -= 1;
			}
		}
}

void GeneticAlgorithm::CalculateFitness(int _i)
{
	// Fitness = 1/Length away+1
	m_ChromosomeFitness[_i] = (1 / (float)(m_ChromosomeLengthAway[_i][0] + m_ChromosomeLengthAway[_i][1] + 1));
	if (_i == (m_ChromosomeQuantity - 1))
	{
		m_TotalFitness = 0;
		for (int i = 0; i < m_ChromosomeQuantity; i++)
		{
			m_TotalFitness += m_ChromosomeFitness[i];
		}
		for (int i = 0; i < m_ChromosomeQuantity; i++)
		{
			m_ChanceToBreed[i] = (m_ChromosomeFitness[i] / m_TotalFitness);
			if (i > 0)
			{
				m_ChanceToBreed[i] += m_ChanceToBreed[i - 1];
			}
		}
	}
}

int GeneticAlgorithm::BreedSelector()
{
	m_Percentage = (double)rand() / (RAND_MAX + 1.0);
	for (int i = 0; i < m_ChromosomeQuantity; i++)
	{
		if (m_ChanceToBreed[i] >= m_Percentage)
		{
			return i;
			break;
		}
	}
}

void GeneticAlgorithm::MutateChromosomes(int _i)
{
	for (int i = 0; i < m_ChromosomeLength; i++)
	{
		m_MutationValue = (double)rand() / (RAND_MAX + 1.0);
		if (m_MutationValue <= m_MutationRate)
		{
			m_RandomNumber.seed(std::random_device()());
			std::uniform_int_distribution<std::mt19937::result_type> m_Distribute(0, 7);
			m_Chromosomes[_i][i] = m_Distribute(m_RandomNumber);
		}
	}
}

void GeneticAlgorithm::GeneticAlgorithmLoop()
{
	CreateChromosomes();
	m_FinalChromosome = TestChromosomes();
	std::cout << "The Chromosome ";
	for (int i = 0; i < m_ChromosomeLength; i++)
	{
		std::cout << m_FinalChromosome[i] << " ";
	}
	std::cout << "has successfully reached the end!" << std::endl;
}
