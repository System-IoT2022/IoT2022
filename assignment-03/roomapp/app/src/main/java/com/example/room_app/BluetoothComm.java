package com.example.room_app;

import android.bluetooth.BluetoothSocket;
import android.graphics.Color;
import android.util.Log;

import java.io.IOException;
import java.io.OutputStream;
import java.nio.charset.StandardCharsets;

public class BluetoothComm {
    private BluetoothSocket btSocket;
    private OutputStream bluetoothOutputStream;

    public BluetoothComm(BluetoothSocket socket){
        btSocket = socket;
    }
    private void manageConnectedSocket(BluetoothSocket socket) {
        try {
            bluetoothOutputStream = socket.getOutputStream();
            Log.i(C.TAG, "Connection successful!");
        } catch (IOException e) {
            Log.e(C.TAG, "Error occurred when creating output stream", e);
        }

    }

    private void sendMessage(String message) {
        new Thread(() -> {
            try {
                bluetoothOutputStream.write(message.getBytes(StandardCharsets.UTF_8));
                ledState = !ledState;
                //runOnUiThread(() -> remoteButton.setBackgroundColor(ledState? Color.GREEN : Color.RED));
            } catch (IOException e) {
                e.printStackTrace();
            }
        }).start();
    }

    public String rcvMessage(){

        return "";
    }
}
