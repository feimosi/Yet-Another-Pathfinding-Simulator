#include "Graph.h"
#include "stdafx.h"


using namespace yaps;

Graph::Graph(DataMatrix<float> &riverBottomRef) : data(riverBottomRef) {}


Coordinates Graph::findPath()
{
    return findPath(findStartPoint(), findEndPoint());
}

Coordinates Graph::findPath(Coordinates StartPoint)
{
    return findPath(StartPoint, findEndPoint());
}

Coordinates Graph::findPath(Coordinates start, Coordinates endpoint)
{
    double score_dis;
    bool contains;

    PriorityQueue<Coordinates> openset ;
    std::set<Coordinates> closed;

    std::vector<double> dokladne_odleglosci(data.getHeight() * data.getWidth());
    std::vector<double> h_odleglosci(data.getHeight() * data.getWidth());
    std::vector<Coordinates> previous(data.getHeight() * data.getWidth());

    std::fill (previous.begin(), previous.end(), Coordinates(-1, -1));
    std::fill (dokladne_odleglosci.begin(), dokladne_odleglosci.end(),0);
    std::fill (h_odleglosci.begin(), h_odleglosci.end(), 0);

    h_odleglosci.at(0) = dokladne_odleglosci[twoDtoOneD(start)] + heuristic_cost(start, endpoint);
    openset.add(start, 0);

    Coordinates current;
    while(!openset.isEmpty())
    {
        current = *openset.removeHighestPrior();
        if (current.x == endpoint.x && current.y == endpoint.y) reconstruct_path(previous, endpoint);
        closed.insert(current);

        for (Coordinates neighbor: adjacentPoints(current))
        {
            if (closed.count(neighbor) > 0) continue;
            score_dis = dokladne_odleglosci[twoDtoOneD(current)] + cost(current, neighbor);
            contains = openset.contains(neighbor);

            if (!contains || score_dis < dokladne_odleglosci[twoDtoOneD(neighbor)])
            {
                previous.at(twoDtoOneD(neighbor)) = current;
                dokladne_odleglosci[twoDtoOneD(neighbor)] = score_dis;
                h_odleglosci[twoDtoOneD(neighbor)] = score_dis + heuristic_cost(neighbor, endpoint);
                openset.changePrior(neighbor, score_dis);
                if (!contains)
                {
                   openset.add(neighbor, score_dis);
                }
            }
        }
    }
    return endpoint;
}

double Graph::heuristic_cost(Coordinates start, Coordinates endpoint)
{
    int dx = std::abs(start.x - endpoint.x);
    int dy = std::abs(start.y - endpoint.y);
    return  (dx + dy);
}

double Graph::cost(Coordinates p1, Coordinates p2)
{
    int dx = p1.x - p2.x;
    int dy = p1.y - p2.y;
    double mod;
    if(p1.x < data.getWidth() && p2.x < data.getWidth() && p1.y < data.getHeight() && p2.y < data.getHeight())
    {
        mod = (data[p1.y][p1.x] + data[p2.y][p2.x]) / 10;

    }
    if (dx == 0 || dy == 0) return 1 - mod;
    else return 1.41 - mod;

}

Coordinates Graph::reconstruct_path(std::vector<Coordinates> previous, Coordinates node)
{
    if (previous[twoDtoOneD(node)] == Coordinates(-1, -1)) return node;
    path.push_back(node);
    reconstruct_path(previous, previous[twoDtoOneD(node)]);

}

Coordinates Graph::findEndPoint()  //REPAIR
{
    float value = 0;
    int start_index;
    int end_index;
    bool flag;

    for (int i = 0; i < data.getWidth(); i++)
    {
        if (data[0][i] > value)
        {
            start_index = i;
            value = data[0][i];
            flag = true;

        }
        if (flag && data[0][i] < value)
        {
            end_index = i;
            flag = false;

        }
    }
    return Coordinates( (end_index + start_index) / 2, 0);
}

Coordinates Graph::findStartPoint()  //REPAIR
{
    float value = 0;
    int start_index;
    int end_index;
    bool flag;
    for (int i = 0; i < data.getWidth(); i++)
    {
        if (data[data.getHeight() - 1][i] > value)
        {
            start_index = i;
            value = data[data.getHeight() - 1][i];
            flag = true;
        }
        if (flag && data[data.getHeight() - 1][i] < value)
        {
            end_index = i;
            flag = false;
        }
    }
    return Coordinates( (end_index + start_index) / 2, data.getHeight() - 1);
}

int Graph::twoDtoOneD(Coordinates cor)
{
    return (cor.x + cor.y * data.getWidth());
}

std::vector<Coordinates> Graph::adjacentPoints(Coordinates reference_point)
{
    int rx = reference_point.x;
    int ry = reference_point.y;
    std::vector<Coordinates> result;
    for(int x = -1; x <= 1; x++)
        for(int y = -1; y <= 1; y++)
        {
            if (rx + x >= 0 && rx + x < data.getWidth() - 1 && ry + y >= 0 && ry + y < data.getHeight() - 1
                && !(x == 0 && y == 0)) result.push_back(Coordinates(rx + x, ry + y));
        }
    return result;

}

void Graph::getPath(std::vector<Coordinates>& var)
{
    var = path;
}

Graph::~Graph()
{
}
    //dtor
