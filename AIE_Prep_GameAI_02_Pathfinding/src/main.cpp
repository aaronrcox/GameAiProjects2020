
#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#include "raygui.h"

#include "Application.h"

#include <functional>

#include <iostream>
#include "Graph.h"

void TestGraph()
{
    // setup
    Graph<char, int> graph;
    auto a = graph.AddNode('A');
    auto b = graph.AddNode('B');
    auto c = graph.AddNode('C');
    auto d = graph.AddNode('D');
    auto e = graph.AddNode('E');
    auto f = graph.AddNode('F');
    auto g = graph.AddNode('G');
    auto h = graph.AddNode('H');
    auto i = graph.AddNode('I');
    auto j = graph.AddNode('J');

    graph.AddEdge(a, b, 0); graph.AddEdge(b, a, 0);     
    graph.AddEdge(a, c, 0); graph.AddEdge(c, a, 0);     
    graph.AddEdge(c, d, 0); graph.AddEdge(d, c, 0);     
    graph.AddEdge(d, f, 99); graph.AddEdge(f, d, 99);
    graph.AddEdge(d, e, 0); graph.AddEdge(e, d, 0);     
    graph.AddEdge(e, g, 0); graph.AddEdge(g, e, 0);     
    graph.AddEdge(f, g, 0); graph.AddEdge(g, f, 0);     
    graph.AddEdge(f, h, 0); graph.AddEdge(h, f, 0);     
    graph.AddEdge(e, i, 99); graph.AddEdge(i, e, 99);     
    graph.AddEdge(i, h, 0); graph.AddEdge(h, i, 0);     
    graph.AddEdge(e, j, 0); graph.AddEdge(j, e, 0);

    auto isGoalNode = [=](Graph<char, int>::Node* node) { 
        return node == i;
    };
    std::list<Graph<char, int>::Node*> path;

    if (graph.FindPath(a, isGoalNode, path))
    {
        std::cout << "Path found" << std::endl;
    }


    /*
    graph.ForEachBFS(f, [](Graph<char,int>::Node* node) {
        std::cout << node->data << std::endl;
        return false;
    });

    std::cout << "------------" << std::endl;

    graph.ForEachDFS(f, [](Graph<char, int>::Node* node) {
        std::cout << node->data << std::endl;
        return false;
    });
    */
}


int main(int argc, char* argv[])
{
    // TestGraph();

     {
         Application app(800, 450);
         app.Run();
     }
    
    return 0;
}

