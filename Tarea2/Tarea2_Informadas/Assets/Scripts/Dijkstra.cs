using System.Collections;
using System.Collections.Generic;
using UnityEngine;

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
public class Dijkstra : MonoBehaviour
{
    //public Material explored;
    //public Material inQue;
    //public Material goalNode;

    public Node goal; // el objetivo
    public Node root; // donde empieza

    List<Node> que;

    //public List<Node> listNode;
    public List<Edge> listEdge; // lista de conexiones
    int currentCost; // lista del costo que se tiene hasta el momento

    private void Start()
    {
        que = new List<Node>();

        que.Add(root); // empiezas con la root dentro de la lista
        bool foundIt = false;

        // mientras la lista tenga elementos
        while(que.Count != 0)
        {
            //agrega los hijos de la root a la que
            for(int i = 0;  i < que[0].ady.Count; i++)
            {
                // si ya encontraste el objetivo haces foundIt true
                if(que[0].ady[i].ID == goal.ID)
                {
                    foundIt = true;
                }
                que.Add(que[0].ady[i]);
            }

            // Aqui se calcula dijkstra. 
            // Recorres todos los nodos que tienes en el que
            for(int i = 0; i < que.Count; i++)
            {
                // Recorres tu lista de conexiones
                for(int j = 0; j < listEdge.Count; j++)
                {
                    // Esto sirve para localizar de tu lista de conexiones cuales son la que unen al root con sus hijos
                    if(listEdge[j].parent.ID == que[0].ID && listEdge[j].son.ID == que[i].ID)
                    {
                        // funcion dijkstra
                        currentCost = listEdge[j].cost + que[0].totalCost;
                        // cambio el costo total si es mayor que el current cost
                        if(currentCost < que[i].totalCost)
                        {
                            que[i].totalCost = currentCost;
                        }
                    }
                }
            }
            // remueves la root
            que.RemoveAt(0);
        }
    }
}
