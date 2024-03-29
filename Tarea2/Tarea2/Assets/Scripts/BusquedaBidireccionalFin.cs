﻿// Basado en el tutorial de https://www.youtube.com/watch?v=10CeI4cU-Ck
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BusquedaBidireccionalFin : MonoBehaviour
{
    // 1.- Anade el nodo raiz al queue y marcalo como visitado.
    // 2.- Avanza en el queue siempre y cuando no este vacio.
    //      a.- Obten y remueve el nodo de hasta arriva del queue(current).
    //      b.- Para cada padre no visitado del nodo actual hacer lo siguiente:
    //              I.- Marcarlo como visitado.
    //              II.- Checar si es el nodo objetivo y si lo es regresarlo.
    //              III.- Si no es el nodo objetivo agregarlo al queue
    // 4.- Si la queue esta vacia entonces el nodo objetivo no esta

    public Material explored;
    public Material inQue;
    public Material goalNode;

    public GameObject goal;

    List<GameObject> que;
    int timer = 0;

    // Start is called before the first frame update
    void Start()
    {
        que = new List<GameObject>();

        que.Add(gameObject);
        gameObject.GetComponent<MeshRenderer>().material = inQue;
        bool foundIt = false;

        while (que.Count != 0)
        {
            // Ver si el papa ya fue visitado
            if (que[0].transform.parent.gameObject.tag == "visited1")
            {
                Debug.Log("Ya se encontro el nodo objetivo.");
                goal = que[0].transform.parent.gameObject;
                foundIt = true;
                break;
            }

            que[0].transform.parent.gameObject.transform.tag = "visited2";

            // Anadiendo a los padres despues de comprobar que no se encuenta el goal y dibujandolos de verde.
            que.Add(que[0].transform.parent.gameObject);
            timer++;
            StartCoroutine(ExampleCoroutine(que[0].transform.parent.GetComponent<MeshRenderer>(), inQue, timer));

            // Remover el nodo explorado.
            timer++;
            StartCoroutine(ExampleCoroutine(que[0].GetComponent<MeshRenderer>(), explored, timer));
            que.RemoveAt(0);


            // Parar el ciclo while si se encuentra el objetivo.
            if (foundIt)
            {
                StartCoroutine(ExampleCoroutine(goal.GetComponent<MeshRenderer>(), goalNode, timer));
                break;
            }
        }

        // Si no se encontro el nodo objetivo.ss
        if (!foundIt)
        {
            Debug.Log("No se encontro el nodo objetivo.");
        }
    }

    // Funcion para hacer la coroutine, es decir para que el juego no se realice de manera instantanea
    IEnumerator ExampleCoroutine(MeshRenderer mesh, Material newMat, int delay)
    {
        yield return new WaitForSeconds(delay);
        mesh.material = newMat;
    }
}

// Basado en el tutorial de https://www.youtube.com/watch?v=10CeI4cU-Ck