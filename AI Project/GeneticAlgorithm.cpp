#include "GeneticAlgorithm.h"

GeneticAlgorithm::GeneticAlgorithm()
{
	m_Val = 0;
	m_ChromosomeLength = 10;
	m_ChromosomeQuantity = 10;
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
	m_CurrentLevel.resize(_1DLevel[1] + 1, std::vector<int>(_1DLevel[0] + 1));				// Change the size of current level based on the first 2 values within the level array
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
	// Loop for quanitity
	for (int j = 0; j < m_ChromosomeQuantity; j++)
	{	
		// Loop for Length and add numbers
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
	// Create a loop that occurs indefinately, this way it will continue until it reaches the end
	while (m_AlwaysFalse == false)
	{
	// Increment the generations and apply changes based on which generation we are at
		m_GenerationCount++;
		// Every 1,000 generations, we extend the chromosomes length
		if ((m_GenerationCount % 100) == 0)
		{
			std::cout << m_GenerationCount << std::endl;
			for (int i = 0; i < m_Chromosomes.size(); i++)
			{
				m_RandomNumber.seed(std::random_device()());
				std::uniform_int_distribution<std::mt19937::result_type> m_Distribute(0, 7);
				m_Chromosomes[i].push_back(m_Distribute(m_RandomNumber));
				m_TempChromosomes[0].push_back(0);
				m_TempChromosomes[1].push_back(0);
			}
			m_ChromosomeLength++;
		}
		// Every 10,000 generations, we also add 1 new chromosome
		if ((m_GenerationCount % 1000) == 0)
		{
			GenerateOneChromosome();
		}
		// Every 100,000 generations, we erase the first half of every chromosome and randomise it, this stops the chromsomes from stagnating. This number can be increased if it's too harsh
		if ((m_GenerationCount % 10000) == 0)
		{
			RestoreBalance();
		}
		// Loop for the amount of chromosomes
		for (int i = 0; i < m_ChromosomeQuantity; i++)
		{
			// Reset to start location
			m_CurrentLocation = m_StartLocation;
			// Ensure that the code doesn't think the chromosome has reached the end
			m_ChromosomeFinished = false;
			// Run through the chromosomes to check if they reach the end
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
			// Set the chromosome length away and calcualte the fitness
			m_ChromosomeLengthAway[i][0] = abs(m_EndLocation[0] - m_CurrentLocation[0]);
			m_ChromosomeLengthAway[i][1] = abs(m_EndLocation[1] - m_CurrentLocation[1]);
			CalculateFitness(i);
		}
		// Update/ Breed all Chromosomes
		for (int i = 0; i < (m_ChromosomeQuantity / 2); i++)
		{
			UpdateChromosomes();
		}
		// Mutate all Chromosomes
		for (int i = 0; i < m_ChromosomeQuantity; i++)
		{
			MutateChromosomes(i);
		}
		
	}
}

void GeneticAlgorithm::UpdateChromosomes()
{
	// Select Parents
	m_Parent1 = BreedSelector();
	m_Parent2 = BreedSelector();
	// Generate random float 0.0 - 1.1
	m_SwapValue = (double)rand() / (RAND_MAX + 1.0);
	// If the random number is high enough, breed
	if (m_SwapValue > m_SwapRate)
	{
		// Add The first half of each chromosome
		for (int i = 0; i < m_ChromosomeLength / 2; i++)
		{
			m_TempChromosomes[0][i] = m_Chromosomes[m_Parent1][i];
			m_TempChromosomes[1][i] = m_Chromosomes[m_Parent2][i];
		}
		// Add the second half of each chromosome
		for (int i = (m_ChromosomeLength / 2); i < m_ChromosomeLength; i++)
		{
			m_TempChromosomes[0][i] = m_Chromosomes[m_Parent2][i];
			m_TempChromosomes[1][i] = m_Chromosomes[m_Parent1][i];
		}
		// Add the swapped chromosomes
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
	// Fitness = 1/Length away+1, Calcualted below
	m_ChromosomeFitness[_i] = (1 / (float)(m_ChromosomeLengthAway[_i][0] + m_ChromosomeLengthAway[_i][1] + 1));
	// Check if all fitness' have been calculated
	if (_i == (m_ChromosomeQuantity - 1))
	{
		// Reset total fitness
		m_TotalFitness = 0;
		// Add all the fitnesses together
		for (int i = 0; i < m_ChromosomeQuantity; i++)
		{
			m_TotalFitness += m_ChromosomeFitness[i];
		}
		// Set the chance to breed
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
	// Create a random percentage
	m_Percentage = (double)rand() / (RAND_MAX + 1.0);
	// Loop for chromosomes
	for (int i = 0; i < m_ChromosomeQuantity; i++)
	{
		// Check if the correct chromosome has been found, break if it has
		if (m_ChanceToBreed[i] >= m_Percentage)
		{
			return i;
			break;
		}
	}
}

void GeneticAlgorithm::MutateChromosomes(int _i)
{
	// Loop for the chromosome length
	for (int i = 0; i < m_ChromosomeLength; i++)
	{
		// Create a random value to decide if we should mutate
		m_MutationValue = (double)rand() / (RAND_MAX + 1.0);
		// If we should, act
		if (m_MutationValue <= m_MutationRate)
		{
			// Create a new random move and replace
			m_RandomNumber.seed(std::random_device()());
			std::uniform_int_distribution<std::mt19937::result_type> m_Distribute(0, 7);
			m_Chromosomes[_i][i] = m_Distribute(m_RandomNumber);
		}
	}
}

void GeneticAlgorithm::GeneticAlgorithmLoop()
{
	// Create the chromosomes
	CreateChromosomes();
	// Test the chromosomes
	m_FinalChromosome = TestChromosomes();
	// Clear the screen to remove debris numbers
	system("CLS");
	// Draw the map again
	Draw();
	// Output all the final values
	std::cout << "The Chromosome ";
	for (int i = 0; i < m_ChromosomeLength; i++)
	{
		std::cout << m_FinalChromosome[i] << " ";
	}
	std::cout << "has successfully reached the end at generation " << m_GenerationCount << "!" << std::endl;
	// Reset everything
	Reset();
}

void GeneticAlgorithm::GenerateOneChromosome()
{
	// Add another space to the chromosomes
	m_Chromosomes.push_back(std::vector<int>(0));
	// Loop for full length
	for (int i = 0; i < m_ChromosomeLength; i++)
	{																									// Key: (Compass) 0 = N, 1 = NE, 2 = E, 3 = SE, 4 = S, 5 = SW, 6 = W, 7 = NW
		// Add random numbers
		m_RandomNumber.seed(std::random_device()());
		std::uniform_int_distribution<std::mt19937::result_type> m_Distribute(0, 7);
		m_Chromosomes[m_Chromosomes.size()-1].push_back(m_Distribute(m_RandomNumber));									// Add a random integer from 0 - 7
	}
}

void GeneticAlgorithm::RestoreBalance()
{
	// Take half of the chromosomes
	for (int i = 0; i < m_Chromosomes.size() / 2; i++)
	{
		// Take their full length and randomise the value
		for (int j = 0; j < m_ChromosomeLength; j++)
		{
			m_RandomNumber.seed(std::random_device()());
			std::uniform_int_distribution<std::mt19937::result_type> m_Distribute(0, 7);
			m_Chromosomes[i][j] = m_Distribute(m_RandomNumber);
		}
	}
}

void GeneticAlgorithm::Reset()
{
	// Refresh everything
	m_ChromosomeMovesTaken.clear();
	m_CurrentLevel.clear();
	m_ChromosomeLengthAway.clear();
	m_ChromosomeFitness.clear();
	m_ChanceToBreed.clear();
	m_FinalChromosome.clear();
	m_ChromosomeLength = 10;
	m_ChromosomeQuantity = 10;
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
