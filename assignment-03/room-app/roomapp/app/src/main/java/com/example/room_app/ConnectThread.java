package com.example.room_app;

import android.annotation.SuppressLint;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.util.Log;

import java.io.IOException;
import java.util.UUID;
import java.util.function.Consumer;

class ConnectThread extends Thread {
    private final BluetoothSocket mmSocket;
    private final BluetoothDevice mmDevice;
    private final BluetoothAdapter bluetoothAdapter;
    private UUID btuuid;


    @SuppressLint("MissingPermission")
    public ConnectThread(BluetoothDevice device, BluetoothAdapter btAdapter) {
        // Use a temporary object that is later assigned to mmSocket
        // because mmSocket is final.
        BluetoothSocket tmp = null;
        mmDevice = device;
        bluetoothAdapter = btAdapter;
         btuuid = device.getUuids()[0].getUuid();

        try {
            // Get a BluetoothSocket to connect with the given BluetoothDevice.
            // MY_UUID is the app's UUID string, also used in the server code. not anymore
            tmp = device.createInsecureRfcommSocketToServiceRecord(btuuid);
        } catch (IOException e) {
            Log.e(C.TAG, "Socket's create() method failed", e);
        }
        mmSocket = tmp;

    }

    @SuppressLint("MissingPermission")
    public void run() {
        // Cancel discovery because it otherwise slows down the connection.
        bluetoothAdapter.cancelDiscovery();
        try {
            // Connect to the remote device through the socket. This call blocks
            // until it succeeds or throws an exception.
            mmSocket.connect();
            Log.i(C.TAG, "Connected to" + mmDevice.getName());
        } catch (IOException connectException) {
            // Unable to connect; close the socket and return.
            try {
                mmSocket.close();
            } catch (IOException closeException) {
                Log.e(C.TAG, "Could not close the client socket", closeException);
            }
            return;
        }

        // The connection attempt succeeded. Perform work associated with
        // the connection in a separate thread
    }

    // Closes the client socket and causes the thread to finish.
    public void cancel() {
        try {
            mmSocket.close();
        } catch (IOException e) {
            Log.e(C.TAG, "Could not close the client socket", e);
        }
    }

    public BluetoothSocket getSocket(){
        return this.mmSocket;
    }
}