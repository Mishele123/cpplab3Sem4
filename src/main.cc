
#include "header.h"
#include <iostream>


int main()
{

	Graph<int, double> graph;


    graph.add_vertex(1);
    graph.add_vertex(2);
    graph.add_vertex(3);
    graph.add_vertex(4);

    
    graph.add_edge(1, 2, 1.0);
    graph.add_edge(1, 3, 2.0);
    graph.add_edge(2, 3, 1.0);
    graph.add_edge(3, 4, 3.0);
    graph.add_edge(4, 1, 5.0);

    std::cout << graph.remove_vertex(2) << std::endl;

	return 0;
}