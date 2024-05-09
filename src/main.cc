
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
    graph.add_edge(1, 4, 2.0);
    graph.add_edge(2, 3, 1.0);
    graph.add_edge(3, 4, 3.0);
    graph.add_edge(4, 1, 5.0);

    graph.print_edges(graph.edges(1));

    std::cout << graph.remove_vertex(2) << std::endl;
    std::cout << graph.has_edge({2, 3, 1.0}) << std::endl;


	return 0;
}