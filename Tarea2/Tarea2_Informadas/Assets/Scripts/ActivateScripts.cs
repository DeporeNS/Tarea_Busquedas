using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ActivateScripts : MonoBehaviour
{
    public GameObject PlayerManager;

    public void StartScriptAnchura()
    {
        PlayerManager.GetComponent<Dijkstra>().enabled = true;
    }

    public void StartScriptProfundidad()
    {
        PlayerManager.GetComponent<AEstrella>().enabled = true;
    }

    public void StartScriptProfundidadLimitada()
    {
        PlayerManager.GetComponent<Heuristica>().enabled = true;
    }
}
