#pragma once

#include <random>

namespace rf
{
	namespace Random
	{

		static int getInt(int min, int max)
		{
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<> distribution(min, max);

			int rnd = distribution(gen);

			return rnd;
		}

		static float getFloat(float min, float max)
		{
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_real_distribution<> distribution(min, max);

			float rnd = distribution(gen);

			return rnd;
		}

		static double getDouble(double min, double max)
		{
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_real_distribution<> distribution(min, max);

			double rnd = distribution(gen);

			return rnd;
		}

		static float getAngle()
		{
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_real_distribution<> distribution(0, 360);

			float rnd = distribution(gen);

			return rnd;
		}

	}
}