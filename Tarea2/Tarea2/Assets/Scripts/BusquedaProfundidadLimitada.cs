﻿// Basado en el tutorial de https://www.youtube.com/watch?v=10CeI4cU-Ck
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BusquedaProfundidadLimitada : MonoBehaviour
{
    // 1.- Anade el nodo raiz al queue y marcalo como visitado.
    // 2.- Avanza en el queue siempre y cuando no este vacio.
    //      a.- Obten y remueve el nodo de hasta arriva del queue(current).
    //      b.- Para cada hijo no visitado del nodo actual hacer lo siguiente, solo si esta a cierta distancia de la root original:
    //              I.- Marcarlo como visitado.
    //              II.- Checar si es el nodo objetivo y si lo es regresarlo.
    //              III.- Si no es el nodo objetivo agregarlo al queue
    // 4.- Hacer un swap del primero y del ultimo nodo para que la busqueda siga a profundida y no a anchura
    // 5.- Si la queue esta vacia entonces el nodo objetivo no esta

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
            if (que[0].transform.parent.parent != gameObject.transform)
            {
                // Buscar a sus hijos.
                for (int i = 0; i < que[0].transform.childCount; i++)
                {
                    // Ver si los hijos son el objetivo.
                    if (que[0].transform.GetChild(i).gameObject == goal)
                    {
                        Debug.Log("Ya se encontro el nodo objetivo.");
                        foundIt = true;
                        break;
                    }

                    // Anadiendo a los hijos despues de comprobar que no se encuenta el goal y dibujandolos de verde.
                    que.Add(que[0].transform.GetChild(i).gameObject);
                    timer++;
                    StartCoroutine(ExampleCoroutine(que[0].transform.GetChild(i).GetComponent<MeshRenderer>(), inQue, timer));

                }
            }

            // Remover el nodo explorado.
            timer++;
            StartCoroutine(ExampleCoroutine(que[0].GetComponent<MeshRenderer>(), explored, timer));
            que.RemoveAt(0);
            // Swap del primero y del ultimo nodo para que la busqueda siga a profundida y no a anchura
            Swap(que, 0, que.Count - 1);


            // Parar el ciclo while si se encuentra el objetivo.
            if (foundIt)
            {
                StartCoroutine(ExampleCoroutine(goal.GetComponent<MeshRenderer>(), goalNode, timer));
                break;
            }
        }

        // Si no se encontro el nodo objetivo.
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

    // Funcion para cambiar de lugar 2 nodos en la lista.
    public static void Swap<GameObject>(List<GameObject> list, int indexA, int indexB)
    {
        GameObject tmp = list[indexA];
        list[indexA] = list[indexB];
        list[indexB] = tmp;
    }
}

// Basado en el tutorial de https://www.youtube.com/watch?v=10CeI4cU-Ck
