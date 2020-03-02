using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DibujaLinea : MonoBehaviour
{
    public Material color;
    public Node thisNode;
    LineRenderer line;
    GameObject obj;
    public GameObject Empty;

    // Start is called before the first frame update
    void Start()
    {
        for (int i = 0; i < thisNode.ady.Count; i++)
        {
            obj = Instantiate(Empty, transform.position, transform.rotation);
            line = obj.AddComponent<LineRenderer>();
            line.widthMultiplier = 0.1f;
            line.material = color;
            line.SetPosition(1, transform.position);
            line.SetPosition(0, thisNode.ady[i].transform.position);
        }
    }
}
