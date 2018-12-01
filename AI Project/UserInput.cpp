#include "UserInput.h"

UserInput::UserInput()
{
	m_Correct = FALSE;
}

int UserInput::GetLevelQuantity()
{
	// Requesting level amount with data validation
	std::cout << "How many Levels do you want to load? (Maximum 5) ";
	while (m_Correct == FALSE)																							// Loop when the input is invalid
	{
		std::getline(std::cin, m_TempLevelQuantity);																		// Take User Input as string
		std::stringstream convert(m_TempLevelQuantity);																	// Convert to String Stream
		std::cout << std::endl;
		if (convert >> m_LevelQuantity && !(convert >> m_TempLevelQuantity) && m_LevelQuantity <= 5 && m_LevelQuantity > 0)		// Test if it is an integer, and if it's between 1 and 5
		{
			m_LevelQuantity = std::stoi(m_TempLevelQuantity);																// Convert string to int and store
			return m_LevelQuantity;																							// Exit loop
		}
		else
		{
			std::cin.clear();																							// Clear the user input
			std::cerr << "Please enter an integer of between 1 and 5: ";												// Output the error message
		}
	}
}

int UserInput::GetLevelToLoad()
{
	// Requesting which level to apply the genetic algorithm to with data validation
	std::cout << "Which level do you want to apply the genetic algorithm to? ";
	while (m_Correct == FALSE)																							// Loop when the input is invalid
	{
		std::getline(std::cin, m_TempLevelQuantity);																		// Take User Input as string
		std::stringstream convert(m_TempLevelQuantity);																	// Convert to String Stream
		std::cout << std::endl;
		if (convert >> m_LevelQuantity && !(convert >> m_TempLevelQuantity) && m_LevelQuantity <= 5 && m_LevelQuantity > 0)		// Test if it is an integer, and if it's between 1 and 5
		{
			m_LevelQuantity = std::stoi(m_TempLevelQuantity);																// Convert string to int and store
			return m_LevelQuantity;																							// Exit loop
		}
		else
		{
			std::cin.clear();																							// Clear the user input
			std::cerr << "Please enter an integer: ";												// Output the error message
		}
	}
}
