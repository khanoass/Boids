#pragma once

#include <random>

namespace Random
{

	static int nextInt(int min, int max)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> distribution(min, max);

		int rnd = distribution(gen);

		return rnd;
	}

	static float nextFloat(float min, float max)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<> distribution(min, max);

		float rnd = distribution(gen);

		return rnd;
	}

	static double nextDouble(double min, double max)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<> distribution(min, max);

		double rnd = distribution(gen);

		return rnd;
	}

}