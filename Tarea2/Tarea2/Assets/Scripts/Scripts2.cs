using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Scripts2 : MonoBehaviour
{
    public GameObject PlayerManager;

    public void StartScriptProfundidadBidireccionalFin()
    {
        PlayerManager.GetComponent<BusquedaBidireccionalFin>().enabled = true;
    }
}

