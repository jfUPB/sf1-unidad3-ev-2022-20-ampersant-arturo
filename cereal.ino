#include <Wire.h>

int MPU_ADDR = 0x68; // I2C address of the MPU-6050
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ,X,Y,Z;

void setup()
{
    Serial.begin(115200);
    // Wire.setPins(21, 22);
    Wire.begin(21, 22); // sda, scl, clock speed
    Wire.beginTransmission(MPU_ADDR);
    Wire.write(0x6B); // PWR_MGMT_1 register
    Wire.write(0);    // set to zero (wakes up the MPU−6050)
    int status = Wire.endTransmission(true);

    printf("status: %d\n", status);

    Serial.println("Setup complete");
}

void loop()
{
    Wire.beginTransmission(MPU_ADDR);
    Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H)
    Wire.endTransmission(true);
    // Wire.beginTransmission(MPU_ADDR);

    Wire.requestFrom(MPU_ADDR, 6); // request a total of 14 registers

    AcX = Wire.read() << 8 | Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
    AcY = Wire.read() << 8 | Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
    AcZ = Wire.read() << 8 | Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)

    // Serial.write ( (uint8_t *) ( (&AcX) ) + 1,1);
    // Serial.write ( (uint8_t *) ( (&AcX) ),1);

    if (Serial.available())
    {
        if (Serial.read() == 's')
        {
            
            X = map(AcX,20000,0,0,90);
            Y = map(AcY,0,20000,0,90);
            //X = map(AcZ,0,20000,0,90);

            Serial.write((uint8_t *)&X, 2);
            Serial.write((uint8_t *)&Y, 2);
            //Serial.write((uint8_t *)&Z, 2);

            
        }
    }
}

/*
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
                        Y =0;
                    }
                    
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
*/