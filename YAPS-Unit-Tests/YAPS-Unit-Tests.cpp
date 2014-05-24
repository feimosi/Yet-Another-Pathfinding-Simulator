#include "stdafx.h"
#include "gtest/gtest.h"
#include "Simulator.cpp"
#include "InputCollector.cpp"
#include "FuzzyControlSystem.cpp"
#include "ApproximationEngine.cpp"
#include "RouteScheduler.cpp"

using namespace yaps;

TEST(DataMatrixTest, insertAndGetValue) {
	DataMatrix<float> array(3, 3);
	array[0][0] = 20.f;
	array[2][2] = 15.8f;
	array[1][2] = .8f;
	ASSERT_EQ(array[0][0], 20);
	ASSERT_EQ(array[2][2], 15.8f);
	ASSERT_EQ(array[1][2], .8f);
}

TEST(DataMatrixTest, referToOutOfBoundIndex) {
	DataMatrix<float> array(2, 2);
	ASSERT_ANY_THROW(array[2][2]);
	ASSERT_ANY_THROW(array[100][0]);
	ASSERT_ANY_THROW(array[0][100]);
	ASSERT_ANY_THROW(array[200][200]);
}

TEST(SimulatorTest, readDataFromFile) {
	Simulator simulator(5, 5);
	ASSERT_TRUE(simulator.initialise("data.txt"));
	ASSERT_FALSE(simulator.initialise("fake.txt.txt"));
}

TEST(SimulatorTest, runTest) {
	Simulator simulator(5, 5);
	ASSERT_TRUE(simulator.initialise("data.txt"));
	ASSERT_NO_THROW(simulator.run());
}

TEST(ApproximationEngine, runWithNoData) {
	DataMatrix<float> data(10, 10);
	ApproximationEngine approx(data);
	approx.approximate();
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			ASSERT_EQ(data[i][j], NULL);
}