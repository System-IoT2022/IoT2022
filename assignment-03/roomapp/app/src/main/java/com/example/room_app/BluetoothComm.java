package com.example.room_app;

import android.bluetooth.BluetoothSocket;
public class BluetoothComm {
    private BluetoothSocket btSocket;

    public BluetoothComm(BluetoothSocket socket){
        btSocket = socket;
    }

    public void sendMsg(String message){

    }

    public String rcvMessage(){

        return "";
    }
}
