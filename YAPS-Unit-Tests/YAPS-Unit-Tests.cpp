#include "gtest/gtest.h"
#include "Simulator.h"
#include "Simulator.cpp"
#include "InputCollector.cpp"
#include "Fuzzifier.cpp"
#include "ApproximationEngine.cpp"
#include "RouteScheduler.cpp"

using namespace yaps;

TEST(DataMatrixTest, insertAndGetValue) {
	DataMatrix<float> array(2, 2);
	array[0][0] = 20.f;
	ASSERT_EQ(array[0][0], 20);
	ASSERT_EQ(array[1][1], 0);
	ASSERT_ANY_THROW(array[4][0]);
	ASSERT_ANY_THROW(array[0][6]);
}

TEST(SimulatorTest, readDataFromFile) {
	Simulator simulator(4, 4);
	simulator.initialise("data.txt");
	simulator.run();
	simulator.printCurrentData();
}