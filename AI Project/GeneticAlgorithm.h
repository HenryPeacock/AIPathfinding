#include <vector>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <sstream>
#include <array>
#include <random>

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
	int m_Parent1;
	int m_Parent2;
	float m_AreaChoice;
	float m_TotalFitness;
	float m_Percentage;
	float m_SwapRate;
	float m_SwapValue;
	float m_MutationRate;
	float m_MutationValue;
	int m_GenerationCount;
	bool m_AlwaysFalse;
	std::vector<int> m_FinalChromosome;
	std::vector<std::vector<int>> m_Chromosomes;
	std::vector<std::vector<int>> m_TempChromosomes;
	std::vector<int> m_ChromosomeMovesTaken;
	std::vector<std::vector<int>> m_ChromosomeLengthAway;
	std::vector<float> m_ChromosomeFitness;
	std::vector<float> m_ChanceToBreed;
	std::mt19937 m_RandomNumber;

public:
	GeneticAlgorithm();
	void FullyLoadLevel(std::vector<int> _1DLevel);
	void Draw();
	void CreateChromosomes();
	std::vector<int> TestChromosomes();
	void UpdateChromosomes();
	void CalculateDirections(int _i, int _j);
	void CalculateFitness(int _i);
	int BreedSelector();
	void MutateChromosomes(int _i);
	void GeneticAlgorithmLoop();
	void GenerateOneChromosome();
	void RestoreBalance();
	void Reset();
};
