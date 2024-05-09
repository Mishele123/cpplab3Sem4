
#include "header.h"
#include <iostream>


int main()
{
    setlocale(LC_ALL, "ru");

	Graph<int, double> graph;


    graph.add_vertex(0);
    graph.add_vertex(1);
    graph.add_vertex(2);
    graph.add_vertex(3);

    
    graph.add_edge(0, 1, 2.0);
    graph.add_edge(0, 3, 2.0);
    graph.add_edge(1, 2, 3.0);
    graph.add_edge(2, 3, 3.0);
    graph.add_edge(3, 0, 5.0);
    graph.add_edge(0, 2, 4.0);

    graph.walk(0);

    graph.shortest_path(0, 2);

    graph.print_edges(graph.edges(1));
    std::cout << "Degree for 1 = " << graph.degree(1) << std::endl;

    std::cout << graph.remove_vertex(2) << std::endl;
    std::cout << graph.has_edge({2, 3, 1.0}) << std::endl;


	return 0;
}