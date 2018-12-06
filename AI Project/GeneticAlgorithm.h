#include <vector>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <sstream>
#include <array>

class GeneticAlgorithm 
{
private:
	std::vector<std::vector<int>> m_CurrentLevel;
	int m_TempChrome1;
	int m_TempChrome2;
	int m_ChromosomeQuantity;
	int m_ChromosomeLength;
	bool m_ChromosomeFinished;
	std::array<int, 2> m_StartLocation;
	std::array<int, 2> m_EndLocation;
	std::array<int, 2> m_CurrentLocation;
	int m_Val;
	int m_LevelNumber;
	std::vector<std::vector<int>> m_Chromosomes;
	std::vector<int> m_ChromosomeMovesTaken;
	std::vector<std::vector<int>> m_ChromosomeLengthAway;
	std::vector<float> m_ChromosomeFitness;

public:
	GeneticAlgorithm();
	void FullyLoadLevel(std::vector<int> _1DLevel);
	void Draw();
	void CreateChromosomes();
	void TestChromosomes();
	void UpdateChromosomes();
	void CalculateDirections(int _i, int _j);
};
