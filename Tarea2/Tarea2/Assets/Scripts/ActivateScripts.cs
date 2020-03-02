using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ActivateScripts : MonoBehaviour
{
    public GameObject PlayerManager;

    public void StartScriptAnchura()
    {
        PlayerManager.GetComponent<BusquedaAnchura>().enabled = true;
    }

    public void StartScriptProfundidad()
    {
        PlayerManager.GetComponent<BusquedaProfundidad>().enabled = true;
    }

    public void StartScriptProfundidadLimitada()
    {
        PlayerManager.GetComponent<BusquedaProfundidadLimitada>().enabled = true;
    }

    public void StartScriptProfundidadIterativa()
    {
        PlayerManager.GetComponent<BusquedaIterativaProfundidad>().enabled = true;
    }

    public void StartScriptProfundidadBidireccional()
    {
        PlayerManager.GetComponent<BusquedaBidireccional>().enabled = true;
    }

    public void StartScriptProfundidadBidireccionalFin()
    {
        PlayerManager.GetComponent<BusquedaBidireccionalFin>().enabled = true;
    }

    public void StartScriptEvitandoEstados()
    {
        PlayerManager.GetComponent<EvitandoEstados>().enabled = true;
    }
}
