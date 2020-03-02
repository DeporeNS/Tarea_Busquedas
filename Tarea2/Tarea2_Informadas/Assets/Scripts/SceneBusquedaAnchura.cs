using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class SceneBusquedaAnchura : MonoBehaviour
{
    public void DijkstraScene()
    {
        SceneManager.LoadScene("Dijkstra");
    }

    public void AEstrellaScene()
    {
        SceneManager.LoadScene("AEstrella");
    }

    public void HeuristicaScene()
    {
        SceneManager.LoadScene("Heuristica");
    }

    public void MenuScene()
    {
        SceneManager.LoadScene("Menu");
    }
}
