#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <queue>
#include <list>
#include <stack>

using namespace std;

class Edge; // Se declara el edge al principio para poder meter atributos de esta clase a Node

class Node {
	Node* next; // apuntador al siguiete Nodo
	Edge* ady; // apuntador al edge adyacente, el edge sirve como la coneccion entre 2 nodos
	int ID; // identificador de los Nodos
	friend class Graph; // clase amiga para que pueda usar los atributos de la clase grafo
};

class Edge {
	Edge* next; // Apuntador a la siguiente Edge
	Node* ady; // apuntador al Nodo Adyacente
	int weight; // Caunto cuesta cada camino para las busquedas informadas
	friend class Graph;
};

class Graph
{
private:
	Edge* before; // edge before para algunas funciones
	Node* NodeBefore; // nodo before para algunas funciones
	Node* first = NULL; // primer nodo del grafo
	bool endFunction = false;
public:
	bool Empty(); // Sirve para preguntar si el grafo se encuentra vacio 
	int Size(); // Para saber el tamano del grafo
	Node* GetNode(int ID); // funcion que te regresa el un nodo de acuerdo a su ID
	void AddEdge(Node *parent, Node *son, int weight); // Creacion de la conexion entre los nodos.
	void AddNode(int ID); // anade nodo con su respectivo ID
	void PrintGraph(); // Crea una lista de adyacencia recorriendo todos los nodos y cada vez que entra a un nodo recorre sus conexiones y las regresa.
	void DeleteEdge(Node *parent, Node *son); // elemina las conexiones entre los nodos.
	void DeleteGraph(); // para liberar la memoria de todo el grafo.
	void DeleteNode(Node *node); // Funcion para eliminar un nodo

	// Busquedas no informadas
	void BFS(Node* search); // para hacer una busqueda por anchura
	void DFS(Node* search); // para hacer una busqueda por profundidad
	void LimitedSearch(Node* search, int maxDeep); // busqueda de profundidad limitada
	void LimitedSearch(Node* root, Node* search, int maxDeep, stack<Node*> stack, list<Node*> NodeList);
	void IterativeSearch(Node* search, int maxDeep); // busqueda de profundidad iterativa
	void IterativeSearch(Node* root, Node* search, int maxDeep, stack<Node*> stack, list<Node*> NodeList, int originalMaxDeep);
	void BidirectionalSearch(Node* search); //busqueda de profundidad bidireccional
	void AvoidingStates(Node* search); // busqueda evadiendo estados repetidos

	//Busquedas informadas
	void Dijkstra(Node* search); // busqueda informada de dijkstra
};

#endif // GRAPH_H