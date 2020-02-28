using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DibujaLinea : MonoBehaviour
{
    public Material color;
    LineRenderer line;

    // Start is called before the first frame update
    void Start()
    {
        if(transform.parent != null)
        {
            line = gameObject.AddComponent<LineRenderer>();
            line.widthMultiplier = 0.1f;
            line.material = color;
            line.SetPosition(0, transform.position);
            line.SetPosition(1, transform.parent.transform.position);
        }
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
