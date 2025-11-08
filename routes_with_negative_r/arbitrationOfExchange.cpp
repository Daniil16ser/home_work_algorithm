#include <vector>
#include <iostream>
#include <cmath>
#include <limits>
#include <algorithm>

using Vertex = size_t;

struct Edge
{
    Vertex to;
    float rate;
};

using Graph = std::vector<std::vector<Edge>>;

std::vector<Vertex> find_arbitrage_cycle(const Graph& graph, Vertex start)
{
    std::vector<float> dist(graph.size(), std::numeric_limits<float>::infinity());
    std::vector<Vertex> backtrace(graph.size(), -1);

    dist[start] = 0;

    for (Vertex i = 0; i < graph.size() - 1; ++i) 
    {
        for (Vertex from = 0; from < graph.size(); ++from)
        {
            if (dist[from] == std::numeric_limits<float>::infinity())
            {
                continue;
            }

            for (const Edge& e : graph[from])
            {
                float new_dist = dist[from] - std::log(e.rate);
                if (new_dist < dist[e.to])
                {
                    dist[e.to] = new_dist;
                    backtrace[e.to] = from;
                }
            }
        }
    }

    for (Vertex from = 0; from < graph.size(); ++from)
    {
        if (dist[from] == std::numeric_limits<float>::infinity())
        {
            continue;
        }

        for (const Edge& e : graph[from])
        {
            float new_dist = dist[from] - std::log(e.rate);
            if (new_dist < dist[e.to])
            {
                std::vector<Vertex> cycle;
                std::vector<bool> visited(graph.size(), false);

                Vertex current = e.to;

                while (!visited[current])
                {
                    visited[current] = true;
                    current = backtrace[current];
                }

                Vertex cycle_start = current;
                cycle.push_back(cycle_start);
                current = backtrace[cycle_start];

                while (current != cycle_start)
                {
                    cycle.push_back(current);
                    current = backtrace[current];
                }

                cycle.push_back(cycle_start);
                std::reverse(cycle.begin(), cycle.end());
                return cycle;
            }
        }
    }

    return {};
}