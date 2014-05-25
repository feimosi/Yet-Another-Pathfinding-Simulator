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

TEST(FuzzyControlSystem, sailStraightFast) {
    FuzzyControlSystem fcs(1, 3, 5, 45, 60);
    std::vector<float> front = { 6, 5, 6 },
        left = {5, 4, 3},
        right = {3, 2, 2};
    fcs.run(front, left, right);
    ASSERT_NEAR(fcs.getAngle(), -45 / 4, 5);
    ASSERT_NEAR(fcs.getSpeed(), 60, 10);
}

TEST(FuzzyControlSystem, sailLeft) {
    FuzzyControlSystem fcs(1, 3, 5, 45, 60);
    std::vector<float> front = { 3, 4, 4 },
        left = { 6, 5, 5 },
        right = { 3, 3, 3 };
    fcs.run(front, left, right);
    ASSERT_NEAR(fcs.getAngle(), -20, 5);
    ASSERT_NEAR(fcs.getSpeed(), 50, 10);
}

TEST(FuzzyControlSystem, sailRight) {
    FuzzyControlSystem fcs(1, 3, 5, 45, 60);
    std::vector<float> front = { 2, 2, 3 },
        left = { 2, 3, 3 },
        right = { 4, 3, 4 };
    fcs.run(front, left, right);
    ASSERT_NEAR(fcs.getAngle(), 45 /2, 5);
    ASSERT_NEAR(fcs.getSpeed(), 30, 10);
}

TEST(FuzzyControlSystem, sailRightSlowly) {
    FuzzyControlSystem fcs(1, 3, 5, 45, 60);
    std::vector<float> front = { 2, 2, 1 },
        left = { 1, 2, 1 },
        right = { 3, 3, 4 };
    fcs.run(front, left, right);
    ASSERT_NEAR(fcs.getAngle(), 35, 5);
    ASSERT_NEAR(fcs.getSpeed(), 20, 10);
}