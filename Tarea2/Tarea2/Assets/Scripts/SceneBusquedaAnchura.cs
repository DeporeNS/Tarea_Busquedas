using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class SceneBusquedaAnchura : MonoBehaviour
{
    public void BFSScene()
    {
        SceneManager.LoadScene("BusquedaAnchura");
    }

    public void DFSScene()
    {
        SceneManager.LoadScene("BusquedaProfundidad");
    }

    public void LimitadaScene()
    {
        SceneManager.LoadScene("BusquedaProfundidadLimitada");
    }

    public void IterativaScene()
    {
        SceneManager.LoadScene("BusquedaIterativaProfundidad");
    }

    public void BidireccionalScene()
    {
        SceneManager.LoadScene("BusquedaBidireccional");
    }

    public void EvitandoEstadosScene()
    {
        SceneManager.LoadScene("EvitandoEstados");
    }

    public void MenuScene()
    {
        SceneManager.LoadScene("Menu");
    }
}
