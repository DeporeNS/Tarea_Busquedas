using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class NumberAssigner : MonoBehaviour
{
    private Node node;
    public GameObject NodeObj;

    private void Start()
    {
        node = NodeObj.GetComponent<Node>();
    }
    private void Update()
    {
        GetComponent<UnityEngine.UI.Text>().text = node.totalCost.ToString();
    }
}
