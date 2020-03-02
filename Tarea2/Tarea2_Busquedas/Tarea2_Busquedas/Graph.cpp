#include "Graph.h"

// funcion para ver si el grafo esta vacio.
bool Graph::Empty() {
	if (first == NULL) {
		return true;
	}
	else {
		return false;
	}
}

// funcion para saber la cantidad de nodos que hay en el grafo(tamano).
int Graph::Size() {
	int size = 0;
	Node *it; // creacion del iterador para recorrer el grafo.
	it = first;
	// recorre el grafo con el iterador
	while (it != NULL) {
		size++;
		it = it->next;
	}
	// regresa el tamano
	return size;
}

// funcion para buscar un nodo de acuerdo a su ID
Node* Graph::GetNode(int ID) {
	Node *it;
	it = first;
	// recorre el grafo
	while (it != NULL) {
		// le va preguntando a cada nodo si su ID es el mismo que tu le diste si lo es te regresa el nodo si no sigue con el siguiente
		if (it->ID == ID) {
			return it;
		}
		it = it->next;
	}
	// si ningun nodo lo era regresa NULL
	return NULL;
}

// Insertar nuevos nodos en el fondo de la lista
void Graph::AddNode(int ID) {
	Node* newNode = new Node;
	// el nuevo nodo tiene un ID, el siguiente esta vacio porque es el ultimo y por el momento no tienen conexiones.
	newNode->ID = ID;
	newNode->next = NULL;
	newNode->ady = NULL;

	// si el grafo esta vacio simplemente pone el nodo en el first
	if (Empty()) {
		first = newNode;
	}else{
		Node *it;
		it = first;
		// Si el nodo no esta vacio recorred el grafo hasta el ultimo nodo existente y le dices que el siguiente nodo va a ser el nuevo nodo.
		while (it->next != NULL) {
			it = it->next;
		}
		it->next = newNode;
	}
}

// Agrega una nueva conexion entre 2 nodos del grafo. 
void Graph::AddEdge(Node* parent, Node* son, int weight) {
	Edge* newEdge = new Edge;
	// Las conexiones tienen 3 variable. El "costo" del camino, de donde viene y a donde va.
	newEdge->weight = weight;
	newEdge->next = NULL;
	newEdge->ady = NULL;

	// creamos un auxiliar para iterar sobre Edge.
	Edge *it;

	// it se vuelve el primer edge que tenga el padre, si el padre no tiene ninguna conexion esto va a ser igual a null 
	it = parent->ady;

	// si it es null entonces el padre no tiene conexiones aun y simplemente lo unes a un Edge y luego ese Edge lo unes a otro Nodo para crear la conexion
	if (it == NULL) {
		parent->ady = newEdge;
		newEdge->ady = son;
	}
	// si no es null entonces recorres la lista de conexiones que tiene ese nodo y en la ultima haces una nueva
	else {
		// recorres las edges simplemente hasta llegar a la ultima
		while (it->next != NULL) {
			it = it->next;
		}
		it->next = newEdge;
		newEdge->ady = son;
	}
	
}

// Crea una lista de adyacencia recorriendo todos los nodos y cada vez que entra a un nodo recorre sus conexiones y las regresa.
void Graph::PrintGraph() {
	Node *NodeIt;
	Edge *EdgeIt;

	NodeIt = first;
	// Recorres los nodos.
	while (NodeIt != NULL) {
		// Imprimes el ID del nodo.
		cout << NodeIt->ID << "->";
		EdgeIt = NodeIt->ady;
		// Recorres las conexiones.
		while (EdgeIt != NULL) {
			// Imprimes el ID de todas las conexiones.
			cout << EdgeIt->ady->ID << "->";
			EdgeIt = EdgeIt->next;
		}
		NodeIt = NodeIt->next;
		cout << endl;
	}
}

// funcion para eliminar a todo el grafo.
void Graph::DeleteGraph() {
	Node *it;

	// vas recorriendo todo el grafo, moviendo first y eliminando it
	while (first != NULL) {
		it = first;
		first = first->next;
		delete(it);
	}
}

// Funcion para eliminar las conexiones de los nodos en el grafo.
void Graph::DeleteEdge(Node *parent, Node *son) {
	bool found = false;
	Edge *it;

	it = parent->ady;

	// Si no tiene conexiones el nodo
	if (it == NULL) {
		cout << "El nodo padre no tiene ninguna conexion." << endl;
	}
	// Si la 1ra conexion es la conexion que estas buscando primero lugar el nodo con la siguiente conexion y luego eliminar la conexion
	else if(it->ady == son) {
		parent->ady = it->next;
		delete(it);
	}
	else {
		while (it != NULL) {
			if (it->ady == son) {
				found = true;
				before->next = it->next;
				delete(it);
				break;
			}
			before = it;
			it = it->next;
		}
		if (found == false) {
			cout << "No existe la conexion entre esos 2 nodos." << endl;
		}
	}
}

// Funcion para eliminar nodos
void Graph::DeleteNode(Node *node) {
	Node *NodeIt;
	Edge *EdgeIt;

	NodeIt = first;

	//Eliminar el nodo se divide en 2 partes la primera es eliminar todas las conexiones a este
	//Se recorren todos los nodos
	while (NodeIt != NULL) {
		EdgeIt = NodeIt->ady;
		//Se recorren todas las conexiones de esos nodos
		while (EdgeIt != NULL) {
			//Si encuentra una conexion la borra.
			if (EdgeIt->ady == node) {
				DeleteEdge(NodeIt, EdgeIt->ady);
				break;
			}
			EdgeIt = EdgeIt->next;
		}
		NodeIt = NodeIt->next;
	}

	// La segunda parte es eliminar el nodo
	NodeIt = first;
	//Si el nodo es el primero simplemente hacemos que el 2do nodo se convierta en el nuevo first y eliminamos el nodo
	if (first == node) {
		first = first->next;
		delete(NodeIt);
	}
	// Si no es el primer nodo entonces lo encontramos, linkeamos el anterior nodo a este con el siguiente y luego lo eliminamos.
	else {
		while (NodeIt != node) {
			NodeBefore = NodeIt;
			NodeIt = NodeIt->next;
		}
		NodeBefore->next = NodeIt->next;
		delete(NodeIt);
	}
}

// BFS:
// 1.- Se coloca el first en una queue
// 2.- Mientras la queue no este vacia recorrerla y cada vez que cambies de nodo agarrar el nuevo nodo
// 3.- Con el nodo actual si no habia sido visitado lo visitas y lo agregas a una lista de visitados
// 4.- Para cada nodo que tiene conexion con el nodo actual y que no ha sido visitado agregarlo a la queue de nodos que vas a visitar.
void Graph::BFS(Node* search) {
	// bool para ir marcando a los que ya visitaste
	bool visited;
	Node* it;
	queue<Node*> que;
	list<Node*> visitedList;
	list<Node*>::iterator i;
	
	// El primer nodo por el cual vas a empezar el recorrido es la root
	que.push(first);
	// Mientras la lista de nodos por visitar no este vacia:
	while (!que.empty()) {
		visited = false;
		// cada vez que haces el ciclo while haces que it sea igual al nodo de hasta adelante del que
		it = que.front();
		// lo sacas del queue porque ya lo vas a revisar
		que.pop();

		// recorres toda la lista de nodos que ya visitaste y si it esta en la lista ya no lo visitas
		for (i = visitedList.begin(); i != visitedList.end(); i++) {
			if (*i == it) {
				visited = true;
			}
		}
		// en caso de que it no este en la lista de nodos visitados continuas
		if (visited == false) {
			// como it no estaba visitado lo agregas a la lista 
			cout << it->ID << ", ";
			// si it era el nodo que estabas buscando paras el while para salir de la funcion
			if (it == search) {
				break;
			}
			// agregas el nodo a la lista de visitados para que no vuelvas a pasar por el
			visitedList.push_back(it);

			Edge* EdgeIt;
			EdgeIt = it->ady;
			// haces un while para revisar todas las conexiones que tiene ese nodo y poder agregarlas al que
			while (EdgeIt != NULL) {
				// recorres la lista de conexiones para ver que ninguno de los nodos que estan ahi esten en la lista de visitados
				for (i = visitedList.begin(); i != visitedList.end(); i++) {
					if (EdgeIt->ady == *i) {
						visited = true;
					}
				}
				// si no habia sido visitado el nodo lo agregas al que
				if (visited == false) {
					que.push(EdgeIt->ady);
				}
				// avanzas en la lista de conexiones
				EdgeIt = EdgeIt->next;
			}
		}
	}
}

// DFS:
// Se coloca el vertice origen en una pila
// Mientras la pila no este vacia:
//		Desplegar un vertice, sera el vertice actual
//	Si el vertice actual no ha sido visitado
//		Se "Procesa" el vertice actual
//		Se coloca el vertice actual en la lista de visitados
//	Para cada vertice que el vertice actual tiene como destino y que no ha sido visitado:
//		Aplicar el vertice.
void Graph::DFS(Node* search) {
	// bool para ir marcando a los que ya visitaste
	bool visited;
	Node* it;
	stack<Node*> stack;
	list<Node*> NodeList;
	list<Node*>::iterator i;

	// El primer nodo por el cual vas a empezar el recorrido es la root
	stack.push(first);

	// Mientras la lista de nodos por visitar no este vacia:
	while (!stack.empty()) {
		visited = false;
		// cada vez que haces el ciclo while haces que it sea igual al nodo de hasta arriba del stack
		it = stack.top();
		// lo sacas del stack porque ya lo vas a revisar
		stack.pop();


		// recorres toda la lista de nodos que ya visitaste y si it esta en la lista ya no lo visitas
		for (i = NodeList.begin(); i != NodeList.end(); i++) {
			if (*i == it) {
				visited = true;
			}

		}
		// en caso de que it no este en la lista de nodos visitados continuas
		if (visited == false) {
			// Como no estaba lo imprimes
			cout << it->ID << ", ";
			// si it era el nodo que estabas buscando paras el while para salir de la funcion
			if (it == search) {
				break;
			}
			// agregas el nodo a la lista de visitados para que no vuelvas a pasar por el
			NodeList.push_back(it);

			Edge* EdgeIt;
			EdgeIt = it->ady;

			// haces un while para revisar todas las conexiones que tiene ese nodo y poder agregarlas al stack
			while (EdgeIt != NULL) {
				// recorres la lista de conexiones para ver que ninguno de los nodos que estan ahi esten en la lista de visitados
				for (i = NodeList.begin(); i != NodeList.end(); i++) {
					if (*i == EdgeIt->ady) {
						visited = true;
					}
					// si no habia sido visitado el nodo lo agregas al stack
					if (visited == false) {
						stack.push(EdgeIt->ady);
					}
				}
				// avanzas en la lista de conexiones
				EdgeIt = EdgeIt->next;
			}
		}
	}
}

// busqueda de profundidad limitada
// 1.- Determinar el vértice donde la búsqueda debe empezar y asignar la máxima profundidad
// 2.- Comprobar si el vértice actual es el estado objetivo
//		Si no : No hacer nada
//		Si sí : devolver
// 3.-Comprueba si el vértice actual está dentro de la profundidad máxima
//		Si no : No hacer nada
//		Si sí :
//			Expandir el vértice y guardar todos sus sucesores en una pila
//			Llamar a BPL recursivamente para todos los vértices de la pila y volver al paso 2
void Graph::LimitedSearch(Node* search, int maxDeep) {
	// bool para ir marcando a los que ya visitaste
	bool visited;
	Node* it;
	stack<Node*> stack;
	list<Node*> NodeList;
	list<Node*>::iterator i;

	// El primer nodo por el cual vas a empezar el recorrido es la root
	stack.push(first);

	visited = false;
	// cada vez que haces el ciclo while haces que it sea igual al nodo de hasta arriba del stack
	it = stack.top();
	// lo sacas del stack porque ya lo vas a revisar
	stack.pop();


	// recorres toda la lista de nodos que ya visitaste y si it esta en la lista ya no lo visitas
	for (i = NodeList.begin(); i != NodeList.end(); i++) {
		if (*i == it) {
			visited = true;
		}

	}
	// en caso de que it no este en la lista de nodos visitados continuas
	if (visited == false) {
		// Como no estaba lo imprimes
		cout << it->ID << ", ";
		// si it era el nodo que estabas buscando paras el while para salir de la funcion
		if (it != search) {
			// agregas el nodo a la lista de visitados para que no vuelvas a pasar por el
			NodeList.push_back(it);

			Edge* EdgeIt;
			EdgeIt = it->ady;

			// haces un while para revisar todas las conexiones que tiene ese nodo y poder agregarlas al stack
			while (EdgeIt != NULL) {
				// recorres la lista de conexiones para ver que ninguno de los nodos que estan ahi esten en la lista de visitados
				for (i = NodeList.begin(); i != NodeList.end(); i++) {
					if (*i == EdgeIt->ady) {
						visited = true;
					}
					// si no habia sido visitado el nodo lo agregas al stack
					if (visited == false) {
						stack.push(EdgeIt->ady);
					}
				}
				// avanzas en la lista de conexiones
				EdgeIt = EdgeIt->next;
			}
		}
	}
	LimitedSearch(stack.top(), search, maxDeep - 1, stack, NodeList);
}

void Graph::LimitedSearch(Node* root, Node* search, int maxDeep, stack<Node*> stackNode, list<Node*> NodeList) {
	// bool para ir marcando a los que ya visitaste
	bool visited;
	Node* it;
	list<Node*>::iterator i;
	stack<Node*> stack2;

	// El primer nodo por el cual vas a empezar el recorrido es la root
	stackNode.push(root);

	if (maxDeep >= 0) {
		while (!stackNode.empty()) {
			visited = false;
			// cada vez que haces el ciclo while haces que it sea igual al nodo de hasta arriba del stack
			it = stackNode.top();
			// lo sacas del stack porque ya lo vas a revisar
			stackNode.pop();

			// recorres toda la lista de nodos que ya visitaste y si it esta en la lista ya no lo visitas
			for (i = NodeList.begin(); i != NodeList.end(); i++) {
				if (*i == it) {
					visited = true;
				}

			}
			// en caso de que it no este en la lista de nodos visitados continuas
			if (visited == false) {
				// Como no estaba lo imprimes
				cout << it->ID << ", ";
				// si it era el nodo que estabas buscando paras el while para salir de la funcion
				if (it == search) {
					endFunction = true;
					break;
				}
				// agregas el nodo a la lista de visitados para que no vuelvas a pasar por el
				NodeList.push_back(it);

				Edge* EdgeIt;
				EdgeIt = it->ady;

				// haces un while para revisar todas las conexiones que tiene ese nodo y poder agregarlas al stack
				while (EdgeIt != NULL) {
					// recorres la lista de conexiones para ver que ninguno de los nodos que estan ahi esten en la lista de visitados
					for (i = NodeList.begin(); i != NodeList.end(); i++) {
						if (*i == EdgeIt->ady) {
							visited = true;
						}
						// si no habia sido visitado el nodo lo agregas al stack
						if (visited == false) {
							stack2.push(EdgeIt->ady);
						}
					}
					// avanzas en la lista de conexiones
					EdgeIt = EdgeIt->next;
				}
			}
		}
		if (endFunction == false) {
			LimitedSearch(stack2.top(), search, maxDeep - 1, stack2, NodeList);
		}
	}
	else if (endFunction == true) {
		endFunction = false;
	}
	else {
		cout << "  --  No se encontro el nodo";
	}
}

// busqueda de profundidad iterativa
// BPI(raíz, objetivo)
// {
// 	profundidad = 0
// 		repetir
//	{
//	  resultado = BPL(raíz, objetivo, profundidad)
//	  Si(resultado es una solución)
//		devolver resultado
//	  profundidad = profundidad + 1
//	}
// }
void Graph::IterativeSearch(Node* search, int maxDeep) {
	// bool para ir marcando a los que ya visitaste
	bool visited;
	int originalMaxDeep = maxDeep;
	Node* it;
	stack<Node*> stack;
	list<Node*> NodeList;
	list<Node*>::iterator i;

	// El primer nodo por el cual vas a empezar el recorrido es la root
	stack.push(first);

	visited = false;
	// cada vez que haces el ciclo while haces que it sea igual al nodo de hasta arriba del stack
	it = stack.top();
	// lo sacas del stack porque ya lo vas a revisar
	stack.pop();


	// recorres toda la lista de nodos que ya visitaste y si it esta en la lista ya no lo visitas
	for (i = NodeList.begin(); i != NodeList.end(); i++) {
		if (*i == it) {
			visited = true;
		}

	}
	// en caso de que it no este en la lista de nodos visitados continuas
	if (visited == false) {
		// Como no estaba lo imprimes
		cout << it->ID << ", ";
		// si it era el nodo que estabas buscando paras el while para salir de la funcion
		if (it != search) {
			// agregas el nodo a la lista de visitados para que no vuelvas a pasar por el
			NodeList.push_back(it);

			Edge* EdgeIt;
			EdgeIt = it->ady;

			// haces un while para revisar todas las conexiones que tiene ese nodo y poder agregarlas al stack
			while (EdgeIt != NULL) {
				// recorres la lista de conexiones para ver que ninguno de los nodos que estan ahi esten en la lista de visitados
				for (i = NodeList.begin(); i != NodeList.end(); i++) {
					if (*i == EdgeIt->ady) {
						visited = true;
					}
					// si no habia sido visitado el nodo lo agregas al stack
					if (visited == false) {
						stack.push(EdgeIt->ady);
					}
				}
				// avanzas en la lista de conexiones
				EdgeIt = EdgeIt->next;
			}
		}
	}
	IterativeSearch(stack.top(), search, maxDeep - 1, stack, NodeList, originalMaxDeep);
}

void Graph::IterativeSearch(Node* root, Node* search, int maxDeep, stack<Node*> stackNode, list<Node*> NodeList, int originalMaxDeep) {
	// bool para ir marcando a los que ya visitaste
	bool visited;
	Node* it;
	list<Node*>::iterator i;
	stack<Node*> stack2;

	// El primer nodo por el cual vas a empezar el recorrido es la root
	stackNode.push(root);

	if (maxDeep >= 0) {
		while (!stackNode.empty()) {
			visited = false;
			// cada vez que haces el ciclo while haces que it sea igual al nodo de hasta arriba del stack
			it = stackNode.top();
			// lo sacas del stack porque ya lo vas a revisar
			stackNode.pop();

			// recorres toda la lista de nodos que ya visitaste y si it esta en la lista ya no lo visitas
			for (i = NodeList.begin(); i != NodeList.end(); i++) {
				if (*i == it) {
					visited = true;
				}

			}
			// en caso de que it no este en la lista de nodos visitados continuas
			if (visited == false) {
				// Como no estaba lo imprimes
				cout << it->ID << ", ";
				// si it era el nodo que estabas buscando paras el while para salir de la funcion
				if (it == search) {
					endFunction = true;
					break;
				}
				// agregas el nodo a la lista de visitados para que no vuelvas a pasar por el
				NodeList.push_back(it);

				Edge* EdgeIt;
				EdgeIt = it->ady;

				// haces un while para revisar todas las conexiones que tiene ese nodo y poder agregarlas al stack
				while (EdgeIt != NULL) {
					// recorres la lista de conexiones para ver que ninguno de los nodos que estan ahi esten en la lista de visitados
					for (i = NodeList.begin(); i != NodeList.end(); i++) {
						if (*i == EdgeIt->ady) {
							visited = true;
						}
						// si no habia sido visitado el nodo lo agregas al stack
						if (visited == false) {
							stack2.push(EdgeIt->ady);
						}
					}
					// avanzas en la lista de conexiones
					EdgeIt = EdgeIt->next;
				}
			}
		}
		if (endFunction == false) {
			IterativeSearch(stack2.top(), search, maxDeep - 1, stack2, NodeList, originalMaxDeep);
		}
	}
	else if (endFunction == true) {

	}
	else{
		IterativeSearch(search, originalMaxDeep * 2);
	}
}

//busqueda de profundidad bidireccional
void Graph::BidirectionalSearch(Node* search) {

}

// busqueda evadiendo estados repetidos
void Graph::AvoidingStates(Node* search) {
	// bool para ir marcando a los que ya visitaste
	bool visited;
	Node* it;
	queue<Node*> que;
	list<Node*> visitedList;
	list<Node*>::iterator i;

	// El primer nodo por el cual vas a empezar el recorrido es la root
	que.push(first);
	// Mientras la lista de nodos por visitar no este vacia:
	while (!que.empty()) {
		visited = false;
		// cada vez que haces el ciclo while haces que it sea igual al nodo de hasta adelante del que
		it = que.front();
		// lo sacas del queue porque ya lo vas a revisar
		que.pop();

		// recorres toda la lista de nodos que ya visitaste y si it esta en la lista ya no lo visitas
		for (i = visitedList.begin(); i != visitedList.end(); i++) {
			if (*i == it) {
				visited = true;
			}
		}
		// en caso de que it no este en la lista de nodos visitados continuas
		if (visited == false) {
			// como it no estaba visitado lo agregas a la lista 
			cout << it->ID << ", ";
			// si it era el nodo que estabas buscando paras el while para salir de la funcion
			if (it == search) {
				break;
			}
			// agregas el nodo a la lista de visitados para que no vuelvas a pasar por el
			visitedList.push_back(it);

			Edge* EdgeIt;
			EdgeIt = it->ady;
			// haces un while para revisar todas las conexiones que tiene ese nodo y poder agregarlas al que
			while (EdgeIt != NULL) {
				// recorres la lista de conexiones para ver que ninguno de los nodos que estan ahi esten en la lista de visitados
				for (i = visitedList.begin(); i != visitedList.end(); i++) {
					if (EdgeIt->ady == *i) {
						visited = true;
					}
				}
				// si no habia sido visitado el nodo lo agregas al que
				if (visited == false) {
					que.push(EdgeIt->ady);
				}
				// avanzas en la lista de conexiones
				EdgeIt = EdgeIt->next;
			}
		}
	}
}

//Teniendo un grafo dirigido ponderado de N nodos no aislados, sea x el nodo inicial.Un vector D de tamaño N guardará al final 
//del algoritmo las distancias desde x hasta el resto de los nodos.
//
//Inicializar todas las distancias en D con un valor infinito relativo, ya que son desconocidas al principio, exceptuando la de x, 
//que se debe colocar en 0, debido a que la distancia de x a x sería 0.
//
//Sea a = x(Se toma a como nodo actual.)
//
//Se recorren todos los nodos adyacentes de a, excepto los nodos marcados.Se les llamará nodos no marcados vi.
//Para el nodo actual, se calcula la distancia tentativa desde dicho nodo hasta sus vecinos con la siguiente fórmula : dt(vi) = Da + d(a, vi).Es decir, 
//la distancia tentativa del nodo ‘vi’ es la distancia que actualmente tiene el nodo en el vector D más la distancia desde dicho nodo ‘a’(el actual) hasta el nodo vi.
//Si la distancia tentativa es menor que la distancia almacenada en el vector, entonces se actualiza el vector con esta distancia tentativa.Es decir, si dt(vi) < Dvi → Dvi = dt(vi)
//
//	Se marca como completo el nodo a.
//	Se toma como próximo nodo actual el de menor valor en D(puede hacerse almacenando los valores en una cola de prioridad) y se regresa al paso 3, mientras existan nodos no marcados.
//	Una vez terminado al algoritmo, D estará completamente lleno.
void Graph::Dijkstra(Node* search) {
	// bool para ir marcando a los que ya visitaste
	bool visited;
	Node* it;
	queue<Node*> que;
	list<Node*> visitedList;
	list<Node*>::iterator i;

	// El primer nodo por el cual vas a empezar el recorrido es la root
	que.push(first);
	// Mientras la lista de nodos por visitar no este vacia:
	while (!que.empty()) {
		visited = false;
		// cada vez que haces el ciclo while haces que it sea igual al nodo de hasta adelante del que
		it = que.front();
		// lo sacas del queue porque ya lo vas a revisar
		que.pop();

		// recorres toda la lista de nodos que ya visitaste y si it esta en la lista ya no lo visitas
		for (i = visitedList.begin(); i != visitedList.end(); i++) {
			if (*i == it) {
				visited = true;
			}
		}
		// en caso de que it no este en la lista de nodos visitados continuas
		if (visited == false) {
			// como it no estaba visitado lo agregas a la lista 
			cout << it->ID << ", ";
			// si it era el nodo que estabas buscando paras el while para salir de la funcion
			if (it == search) {
				break;
			}
			// agregas el nodo a la lista de visitados para que no vuelvas a pasar por el
			visitedList.push_back(it);

			Edge* EdgeIt;
			EdgeIt = it->ady;
			// haces un while para revisar todas las conexiones que tiene ese nodo y poder agregarlas al que
			while (EdgeIt != NULL) {
				// recorres la lista de conexiones para ver que ninguno de los nodos que estan ahi esten en la lista de visitados
				for (i = visitedList.begin(); i != visitedList.end(); i++) {
					if (EdgeIt->ady == *i) {
						visited = true;
					}
				}
				// si no habia sido visitado el nodo lo agregas al que
				if (visited == false) {
					que.push(EdgeIt->ady);
				}
				// avanzas en la lista de conexiones
				EdgeIt = EdgeIt->next;
			}
		}
	}
}