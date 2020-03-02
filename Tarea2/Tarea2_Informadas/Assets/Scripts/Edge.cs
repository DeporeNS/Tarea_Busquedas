using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Edge : MonoBehaviour
{
    public int cost;
    public Node parent;
    public Node son;

    //Clase edge para las conexiones entre los nodos, tiene parent y son que representan origen y destino y un costo del camino
    public Edge()
    {
        cost = 0;
        parent = null;
        son = null;
    }

}