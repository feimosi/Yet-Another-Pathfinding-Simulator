#pragma once
#include "DataMatrix.h"
#include "Coordinates.h"
#include <vector>
namespace yaps{
    class Graph{
    DataMatrix<float> &data;
    private:
        std::vector<Coordinates> path;
        Coordinates findEndPoint();
        Coordinates findStartPoint();
        int twoDtoOneD(Coordinates);
        Coordinates reconstruct_path(std::vector<Coordinates>, Coordinates);
        std::vector<Coordinates> adjacentPoints(Coordinates);
        double heuristic_cost(Coordinates, Coordinates);

    public:
        Graph(DataMatrix<float> &);
        Coordinates findPath();
        Coordinates findPath(Coordinates);
        Coordinates findPath(Coordinates, Coordinates);
        double cost(Coordinates, Coordinates);

        void getPath(std::vector<Coordinates>&);
        ~Graph();
};
}
