#include "FileLoader.h"

FileLoader::FileLoader(int _LQ)
{
	for (int i = 0; i < 10; i++)
	{
		m_LegalChars[i] = (i + 48);
	}
	m_IsLoaded = FALSE;
	m_Val = 0;
	m_LevelQuantity = _LQ;
	// Resize the level matrix based on how many files the user wishes to load
	m_LevelMatrix.resize(m_LevelQuantity, std::vector<int>(0));
}

void FileLoader::LoadFiles()
{
	// Loading Files
	for (int j = 0; j < m_LevelQuantity; j++)
	{
		std::stringstream ss;						// Create stringstream
		ss << "level" << j + 1 << ".txt";			// Merge level file format with current iteration
		m_LevelFiles[j].open(ss.str().c_str());		// Open the level file into the current iteration of the level files array
		if (m_LevelFiles[j].is_open() == false)		// Check that the file has sucessfully opened, if not throw an exception
		{
			throw std::exception();
		}
	}
}

void FileLoader::LoadLevels()
{
	// Validating the level files and saving to a final level matrix
	for (int l = 0; l < m_LevelQuantity; l++)														// Loop for all levels
	{
		m_TempLevel.clear();																		// Clear the temporary level vector
		while (m_LevelFiles[l].get(m_PlaceHolder))													// Load the file into the temporary level vector
		{
			m_TempLevel.push_back(m_PlaceHolder);
		}
		for (int i = 0; i < (m_TempLevel.size()); i++)												// Loop to the size of the temporary level vector
		{
			for (int j = 0; j < 10; j++)															// Loop 10 times to check against all legal characters (numbers 1 to 10, declared on line 89)
			{
				m_IsLoaded = FALSE;																	// Set the load check to 0
				if (m_TempLevel[i] == m_LegalChars[j])												// Test whether the current space is a legal character
				{
					for (int k = 0; k < 10; k++)													// Loop 10 times to check if the next character is a number, this tests whether we are taking a 2 digit number
					{
						if ((i + 2) < m_TempLevel.size())											// Check that we are remaining within the array size to avoid vertex errors 
						{
							if (m_TempLevel[i + 2] == m_LegalChars[k])								// Check if the next character (2 away due to file loading format) is a number
							{
								std::stringstream css;												// Create stringstream
								css << (m_TempLevel[i] - 48) << (m_TempLevel[i + 2] - 48);			// Concatenate numbers
								m_Val = atoi(css.str().c_str());									// Convert to integer
								m_LevelMatrix[l].push_back(m_Val);									// Save in level matrix
								i += 3;																// Increment i
								m_IsLoaded = TRUE;													// Avoid the number being saved again
							}
						}
					}
					if (m_IsLoaded == FALSE)														// Test if a 2 digit number was loaded
					{
						m_LevelMatrix[l].push_back(m_TempLevel[i] - 48);							// Save in level matrix
					}

				}

			}
		}
	}
}

std::vector<int> FileLoader::ReturnLevel(int _LevelNumber)
{
	for (int i = 0; i < m_LevelMatrix[_LevelNumber - 1].size(); i++)
	{
		m_CurrentLevel.push_back(m_LevelMatrix[_LevelNumber - 1][i]);
	}
	return m_CurrentLevel;					
}
