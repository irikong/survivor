#include "Random.h"

void Random::Init()
{
	generator.seed(rd());
}

int Random::GetIntRange(int min, int max)
{
	std::uniform_int_distribution<int> dist(min, max);
	return dist(generator);
}

float Random::GetFloatRange(float min, float max)
{
	std::uniform_real_distribution<float> dist(min, max);
	return dist(generator);
}

std::random_device Random::rd;
std::mt19937 Random::generator;
