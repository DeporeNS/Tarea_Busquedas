#include <iostream>
#include "Graph.h"

int main()
{
	// Inicializa el grafo
	Graph graph;

	// Creacion de los nodos.
	graph.AddNode(1);
	graph.AddNode(2);
	graph.AddNode(3);
	graph.AddNode(4);
	graph.AddNode(5);
	graph.AddNode(6);
	graph.AddNode(7);
	graph.AddNode(8);
	graph.AddNode(9);
	graph.AddNode(10);
	graph.AddNode(11);
	graph.AddNode(12);
	graph.AddNode(13);
	graph.AddNode(14);
	graph.AddNode(15);

	// Creacion de las conexiones entre nodos.
	graph.AddEdge(graph.GetNode(1), graph.GetNode(2), 200); // 1
	graph.AddEdge(graph.GetNode(1), graph.GetNode(3), 50); // 2
	graph.AddEdge(graph.GetNode(1), graph.GetNode(4), 100); // 3
	graph.AddEdge(graph.GetNode(2), graph.GetNode(5), 150); // 4
	graph.AddEdge(graph.GetNode(2), graph.GetNode(6), 80); // 5
	graph.AddEdge(graph.GetNode(5), graph.GetNode(6), 10); // 6
	graph.AddEdge(graph.GetNode(6), graph.GetNode(7), 150); // 7
	graph.AddEdge(graph.GetNode(7), graph.GetNode(8), 170); // 8
	graph.AddEdge(graph.GetNode(7), graph.GetNode(10), 200); // 9
	graph.AddEdge(graph.GetNode(9), graph.GetNode(7), 500); // 10
	graph.AddEdge(graph.GetNode(3), graph.GetNode(9), 100); // 11
	graph.AddEdge(graph.GetNode(10), graph.GetNode(11), 110); // 12
	graph.AddEdge(graph.GetNode(10), graph.GetNode(14), 90); // 13
	graph.AddEdge(graph.GetNode(10), graph.GetNode(15), 100); // 14
	graph.AddEdge(graph.GetNode(12), graph.GetNode(10), 100); // 15
	graph.AddEdge(graph.GetNode(12), graph.GetNode(14), 150); // 16
	graph.AddEdge(graph.GetNode(12), graph.GetNode(13), 250); // 17
	graph.AddEdge(graph.GetNode(13), graph.GetNode(15), 70); // 18
	graph.AddEdge(graph.GetNode(4), graph.GetNode(12), 250); // 19
	graph.AddEdge(graph.GetNode(14), graph.GetNode(15), 50); // 20
	graph.AddEdge(graph.GetNode(8), graph.GetNode(10), 120); // 21
	graph.AddEdge(graph.GetNode(9), graph.GetNode(12), 20); // 22

	// Imprime el grafo
	cout << "El grafo es:" << endl;
	graph.PrintGraph();
	cout << endl; 	cout << endl;
	
	// Busqueda por anchura
	cout << "Encuentra el nodo 10 buscandolo por anchura." << endl;
	graph.BFS(graph.GetNode(10));
	cout << endl; 	cout << endl;

	// Busqueda por profundidad
	cout << "Encuentra el nodo 10 buscandolo por profundidad." << endl;
	graph.DFS(graph.GetNode(10));
	cout << endl; 	cout << endl;

	// Busqueda por profundidad limitada
	cout << "Encuentra el nodo 10 buscandolo por profundidad limitada con limite de 2." << endl;
	graph.LimitedSearch(graph.GetNode(10), 2);
	cout << endl; 	cout << endl;

	// Busqueda Iterativa en profundidad
	cout << "Encuentra el nodo 10 buscandolo por profundidad iterativa con limite de 2 y expandiendo el limite *2." << endl;
	graph.IterativeSearch(graph.GetNode(10), 2);
	cout << endl; 	cout << endl;

	// Busqueda Bidireccional
	cout << "Encuentra el nodo 10 buscandolo por busqueda bidireccional." << endl;
	graph.BidirectionalSearch(graph.GetNode(10));
	cout << endl; 	cout << endl;

	// Busqueda evitando los estados repetidos
	cout << "Encuentra el nodo 10 buscandolo por estados repetidos." << endl;
	graph.AvoidingStates(graph.GetNode(10));
	cout << endl; 	cout << endl;

	// Busqueda Dijkstra
	cout << "Encuentra la ruta mas rapida al nodo 10 con dijkstra." << endl;
	graph.Dijkstra(graph.GetNode(10));
	cout << endl; 	cout << endl;
}