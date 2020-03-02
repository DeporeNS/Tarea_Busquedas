using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Node : MonoBehaviour
{
    public int totalCost;
    public int ID;
    public List<Node> ady;

    // Clase nodo, tiene una lista de adyacencia, un costo total de lo que te ha costado llegar a el 
    // y una lista de adyacencia que es una lista de sus hijos
    public Node()
    {
        totalCost = 9999;
        ID = 0;
        ady = null;
    }
}