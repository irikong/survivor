#pragma once
#include <random>

class Random
{
public:
	static void Init();
	static int GetIntRange(int min, int max);
	static float GetFloatRange(float min, float max);

private:
	static std::random_device rd;
	static std::mt19937 generator;
};

