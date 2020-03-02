using System.Collections;
using System.Collections.Generic;
using UnityEngine;

// Mi heuristica es solo tomar al hijo con el menos valor
public class Heuristica : MonoBehaviour
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
    int saveEdge; // guardar el numero de la conexion
    bool flag;

    private void Start()
    {
        que = new List<Node>();

        que.Add(root); // empiezas con la root dentro de la lista
        bool foundIt = false;

        // mientras la lista tenga elementos
        while (que.Count != 0)
        {
            flag = true;
            //agrega los hijos de la root a la que
            for (int i = 0; i < que[0].ady.Count; i++)
            {
                // Recorres tu lista de conexiones
                for (int j = 0; j < listEdge.Count; j++)
                {
                    // Esto sirve para localizar de tu lista de conexiones cuales son la que unen al root con sus hijos
                    if (listEdge[j].parent.ID == que[0].ID && listEdge[j].son.ID == que[0].ady[i].ID)
                    {
                        // si ya encontraste el objetivo haces foundIt true
                        if (que[0].ady[i].ID == goal.ID)
                        {
                            foundIt = true;
                        }
                        if (flag == true)
                        {
                            que.Add(que[0].ady[i]);
                            saveEdge = j;
                            flag = false;
                        } 
                        else if (listEdge[j].cost < listEdge[saveEdge].cost)
                        {
                            que.RemoveAt(1);
                            que.Add(que[0].ady[i]);
                            saveEdge = j;
                        }
                    }
                }
            }

            // Aqui se calcula dijkstra. 
            // Recorres todos los nodos que tienes en el que
            for (int i = 0; i < que.Count; i++)
            {
                // Recorres tu lista de conexiones
                for (int j = 0; j < listEdge.Count; j++)
                {
                    // Esto sirve para localizar de tu lista de conexiones cuales son la que unen al root con sus hijos
                    if (listEdge[j].parent.ID == que[0].ID && listEdge[j].son.ID == que[i].ID)
                    {
                        // funcion dijkstra
                        currentCost = listEdge[j].cost + que[0].totalCost;
                        // cambio el costo total si es mayor que el current cost
                        if (currentCost < que[i].totalCost)
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
