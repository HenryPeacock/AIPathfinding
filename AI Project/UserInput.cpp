#include "UserInput.h"

UserInput::UserInput()
{
	m_Correct = FALSE;
}

int UserInput::GetLevelQuantity()
{
	// Requesting level amount with data validation
	std::cout << "How many Levels do you want to load? (Maximum 5) ";
	while (m_Correct == FALSE)																									// Loop when the input is invalid
	{
		std::getline(std::cin, m_TempLevelQuantity);																			// Take User Input as string
		std::stringstream convert(m_TempLevelQuantity);																			// Convert to String Stream
		std::cout << std::endl;
		if (convert >> m_LevelQuantity && !(convert >> m_TempLevelQuantity) && m_LevelQuantity <= 5 && m_LevelQuantity > 0)		// Test if it is an integer, and if it's between 1 and 5
		{
			m_LevelQuantity = std::stoi(m_TempLevelQuantity);																	// Convert string to int and store
			return m_LevelQuantity;																								// Exit loop
		}
		else
		{
			std::cin.clear();																							// Clear the user input
			std::cerr << "Please enter an integer between 1 and 5: ";												// Output the error message
		}
	}
}

int UserInput::GetLevelToLoad()
{
	// Requesting which level to apply the genetic algorithm to with data validation
	std::cout << "Which level do you want to apply the algorithm to? ";
	while (m_Correct == FALSE)																									// Loop when the input is invalid
	{	
		std::getline(std::cin, m_TempLevelQuantity);																			// Take User Input as string
		std::stringstream convert(m_TempLevelQuantity);																			// Convert to String Stream
		std::cout << std::endl;
		if (convert >> m_LevelChoice && !(convert >> m_TempLevelQuantity) && m_LevelChoice <= m_LevelQuantity && m_LevelChoice > 0)		// Test if it is an integer, and if it's between 1 and previous choice
		{
			m_LevelChoice = std::stoi(m_TempLevelQuantity);																	// Convert string to int and store
			return m_LevelChoice;																								// Exit loop
		}
		else
		{
			std::cin.clear();																									// Clear the user input
			std::cerr << "Please enter an integer within the range: ";																			// Output the error message
		}
	}
}

int UserInput::Menu()
{
	// Output the menu messages
	std::cout << "Welcome to the Mouthbourne Intelligent Computer Games pathfinding algorithm tester. " << std::endl;
	std::cout << "Which algorithm do you want to test? " << std::endl << "1: Genetic Algorithm" << std::endl << "2: A* Pathfinding" << std::endl;
	while (m_Correct == FALSE)																									// Loop when the input is invalid
	{
		std::getline(std::cin, m_TempLevelQuantity);																			// Take User Input as string
		std::stringstream convert(m_TempLevelQuantity);																			// Convert to String Stream
		std::cout << std::endl;
		if (convert >> m_MenuChoice && !(convert >> m_TempLevelQuantity) && m_MenuChoice <= 2 && m_MenuChoice > 0)		// Test if it is an integer, and if it's between 1 or 2
		{
			m_MenuChoice = std::stoi(m_TempLevelQuantity);																	// Convert string to int and store
			return m_MenuChoice;																								// Exit loop
		}
		else
		{
			std::cin.clear();																									// Clear the user input
			std::cerr << "Please enter an integer within the range: ";																			// Output the error message
		}
	}
}

bool UserInput::Continue()
{
	// Output the reset message
	std::cout << "Do you want to test another level (1 = Yes, 2 = No) " << std::endl;
	while (m_Correct == FALSE)																									// Loop when the input is invalid
	{
		std::getline(std::cin, m_TempLevelQuantity);																			// Take User Input as string
		std::stringstream convert(m_TempLevelQuantity);																			// Convert to String Stream
		std::cout << std::endl;
		if (convert >> m_ResetChoice && !(convert >> m_TempLevelQuantity) && m_ResetChoice <= 2 && m_ResetChoice > 0)		// Test if it is an integer, and if it's between 1 or 2
		{
			m_ResetChoice = std::stoi(m_TempLevelQuantity);																	// Convert string to int and store																													// Exit loop
			if (m_ResetChoice == 1)
			{
				return false;																								// Continue if they wish
			}
			else
			{
				return true;																								// Otherwise, exit
			}
		}
		else
		{
			std::cin.clear();																									// Clear the user input
			std::cerr << "Please enter an integer within the range: ";																			// Output the error message
		}
	}
	return false;
}
