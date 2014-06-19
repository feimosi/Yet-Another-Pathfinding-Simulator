#pragma once

namespace yaps{
    class Graph {
    private:
        DataMatrix<float> &data;
        std::vector<Coordinates> path;
        Coordinates findEndPoint();
        Coordinates findStartPoint();
        int twoDtoOneD(Coordinates);
        void reconstruct_path(std::vector<Coordinates>, Coordinates);
        std::vector<Coordinates> adjacentPoints(Coordinates);
        double heuristic_cost(Coordinates, Coordinates);
        double cost(Coordinates, Coordinates);

    public:
        Graph(DataMatrix<float> &);
        Coordinates findPath();
        Coordinates findPath(Coordinates);
        Coordinates findPath(Coordinates, Coordinates);
        std::vector<Coordinates> &getPath() { return path; }
        ~Graph();
    };
}
