#include "gtest/gtest.h"
#include "Simulator.h"
#include "Simulator.cpp"
#include "InputCollector.cpp"
#include "Fuzzifier.cpp"
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
	simulator.initialise("data.txt");
}

TEST(SimulatorTest, approximateData) {
	Simulator simulator(5, 5);
	simulator.initialise("data.txt");
	simulator.run();
}