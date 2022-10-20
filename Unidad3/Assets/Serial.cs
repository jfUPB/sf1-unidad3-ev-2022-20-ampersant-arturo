using System;
using UnityEngine;
using System.IO.Ports;
using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;

enum TaskState
{
    INIT,
    WAIT_COMMANDS
}
public class Serial : MonoBehaviour
{
    private static TaskState taskState = TaskState.INIT;
    private SerialPort _serialPort;
    private byte[] buffer = new byte[4];
    private byte[] bufX = new byte[2];
    private byte[] bufY = new byte[2];
    
    private byte bufZ;
    private Vector3 vector3;
    private UInt16 X, Y, Z;
    void Start()
    {
        _serialPort = new SerialPort();
        _serialPort.PortName = "/dev/ttyACM0";
        _serialPort.BaudRate = 115200;
        _serialPort.DtrEnable = true;
        _serialPort.NewLine = "\n";
        _serialPort.Open();
        Debug.Log("Open Serial Port");
    }

    void Update()
    {
        switch (taskState)
        {
            case TaskState.INIT:
                taskState = TaskState.WAIT_COMMANDS;
                Debug.Log("WAIT COMMANDS");
                break;
            case TaskState.WAIT_COMMANDS:
                _serialPort.Write("s");
                if(_serialPort.BytesToRead >= 4)
                {
                    _serialPort.Read(buffer,0,4);
                    //Debug.Log(System.BitConverter.ToUInt16(buffer,0));
                    
                    bufX[0] = buffer[0]; bufX[1] = buffer[1];
                    bufY[0] = buffer[2]; bufY[1] = buffer[3];
                    //Debug.Log(System.BitConverter.ToUInt16(bufY,0));
                    X = System.BitConverter.ToUInt16(bufX, 0);
                    Y = System.BitConverter.ToUInt16(bufY, 0);
                    if (X > 90)
                    {
                        X = 90;
                    }
                    if (Y > 90)
                    {
                        Y = 0;
                    }

                    transform.eulerAngles = new Vector3((float)Y,0,(float)X);
                    //Debug.Log(System.BitConverter.ToUInt16(bufY,0));
                }
               break;
            
            default:
                Debug.Log("State Error");
                break;
        }
    }
    
}

//if(AcX < 0 || AcX > 20)