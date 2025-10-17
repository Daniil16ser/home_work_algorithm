#include <iostream>
#include "graph.h"
#include <stack>

using graph::Vertex;


enum class Colors {
  White,
  Gray,
  Black
};

void GoDfs(const graph::Graph& g, std::vector<Colors>& colors, Vertex v){
  switch (colors[v]) {
  case Colors::White:
    std::cout << "I'm seing " << v << std::endl;
    colors[v] = Colors::Gray;
    for (Vertex w : g.GetAdjacents(v))
      GoDfs(g, colors, w);
    colors[v] = Colors::Black;
    break;
  case Colors::Gray:
    std::cout << "I'm seeing incoming cycle at " << v << std::endl;
    break;
  case Colors::Black:
    std::cout << "I'm seeing completed point " << v << std::endl;
    break;
  }
}

void Dfs(const graph::Graph& g) {
  std::vector<Colors> colors(g.size());
  for (Vertex i = 0; i < colors.size(); ++i) {
    if(colors[i] == Colors::White)
      GoDfs(g, colors, i);
  }
}





void firstDFS(const graph::Graph& g, Vertex v, std::vector<Colors>& colors, std::stack<Vertex>& stack) {
    colors[v] = Colors::Gray;
    
    for (Vertex neighbor : g.GetAdjacents(v)) {
        if (colors[neighbor] == Colors::White) {
            firstDFS(g, neighbor, colors, stack);
        }
    }
    
    colors[v] = Colors::Black;
    stack.push(v);  
}


void secondDFS(const graph::Graph& reversed_g, Vertex v, std::vector<Colors>& colors) {
    colors[v] = Colors::Gray;
    
    for (Vertex neighbor : reversed_g.GetAdjacents(v)) {
        if (colors[neighbor] == Colors::White) {
            secondDFS(reversed_g, neighbor, colors);
        }
    }
    
    colors[v] = Colors::Black;
}

graph::Graph buildReversedGraph(const graph::Graph& g) {
    graph::Graph reversed_g(g.size());
    
    for (Vertex v = 0; v < g.size(); ++v) {
        for (Vertex neighbor : g.GetAdjacents(v)) {
            reversed_g.AddEdge(neighbor, v);
        }
    }
    
    return reversed_g;
}

size_t strong_connection_count(const graph::Graph& g) {
    if (g.empty()) return 0;
    

    std::vector<Colors> colors(g.size(), Colors::White);
    std::stack<Vertex> stack;
    
    for (Vertex v = 0; v < g.size(); ++v) {
        if (colors[v] == Colors::White) {
            firstDFS(g, v, colors, stack);
        }
    }
    

    graph::Graph reversed_g = buildReversedGraph(g);
    
    colors.assign(g.size(), Colors::White);
    size_t count = 0;
    
    while (!stack.empty()) {
        Vertex v = stack.top();
        stack.pop();
        
        if (colors[v] == Colors::White) {
            ++count; 
            secondDFS(reversed_g, v, colors);
        }
    }
    
    return count;
}




int main() {
    graph::Graph g(5);
    g.AddEdge(0, 1);
    g.AddEdge(1, 2);
    g.AddEdge(2, 0);
    g.AddEdge(1, 3);
    g.AddEdge(3, 4);
    g.AddEdge(4, 3);
    
    size_t count = strong_connection_count(g);
    std::cout << "Number of strongly connected components: " << count << std::endl;

    
    return 0;
}
