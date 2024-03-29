package com.example.room_app;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;

import android.Manifest;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.os.Build;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.SeekBar;
import android.widget.Switch;

import android.annotation.SuppressLint;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothManager;
import android.bluetooth.BluetoothSocket;

import com.google.android.material.slider.Slider;

import java.io.IOException;
import java.io.OutputStream;
import java.nio.charset.StandardCharsets;
import java.util.ArrayList;
import java.util.List;


public class MainActivity extends AppCompatActivity {

    private static final int REQUEST_ENABLE_BT = 1234;
    private static final int REQUEST_PERMISSION_CONNECT = 758;
    private static final int REQUEST_PERMISSION_SCAN = 759;
    private static final int LEGACY_REQUEST_PERMISSION_BLUETOOTH = 555;
    private static final int REQUEST_PERMISSION_ADMIN = 556;
    public static final String X_BLUETOOTH_DEVICE_EXTRA = "X_BLUETOOTH_DEVICE_EXTRA";
    private final  String BT_NAME = "isi00";

    private Button remoteButton;
    private SeekBar curtainSlider;
    private boolean lightOn;


    //bluetooth vars
    private BluetoothAdapter btAdapter;
    private List<BluetoothDevice> scannedDevices = new ArrayList<>();
    private List<String> scannedNameList = new ArrayList<>();
    private List<BluetoothDevice> pairedDevices = new ArrayList<>();
    private List<String> pairedNameList = new ArrayList<>();
    private ConnectThread btConnection;
    private BluetoothDevice arduinoDev;
    private BluetoothSocket arduinoSocket;
    private OutputStream btOutStream;
    private ConnectThread serialBT;



    private boolean bluetoothEnabled = false;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        lightOn=false;
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);


        remoteButton = (Button) findViewById(R.id.remoteButton);
        remoteButton.setOnClickListener(new OnClickListener() {
            @SuppressLint("MissingPermission")
            @Override
            public void onClick(View v) {
                String message="";
                //serial.sendMessage(message);
                if(lightOn){
                  message = "light:0 \n";
                    lightOn=false;
                }else{
                     message = "light:1 \n";
                    lightOn=true;
                }
                try {
                    btOutStream = arduinoSocket.getOutputStream();
                    Log.i(C.TAG, "Connection successful!");
                    Log.i(C.TAG, (arduinoSocket.isConnected()?"true":"false"));
                    Log.i(C.TAG, message);
                    btOutStream.write(message.getBytes(StandardCharsets.UTF_8));
                } catch (IOException e) {
                    Log.e(C.TAG, "Error occurred when creating output stream", e);
                    checkPairedDevices();
                    connectArduino(BT_NAME);
                }
            }
        });

        curtainSlider = (SeekBar) findViewById(R.id.curtainBar);
       curtainSlider.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
           @Override
           public void onProgressChanged(SeekBar seekBar, int i, boolean b) {

           }

           @Override
           public void onStartTrackingTouch(SeekBar seekBar) {

           }

           @Override
           public void onStopTrackingTouch(SeekBar seekBar) {
               try {
                   String message = "servo:" + curtainSlider.getProgress() + "\n";
                   btOutStream = arduinoSocket.getOutputStream();
                   Log.i(C.TAG, "Connection successful!");
                   Log.i(C.TAG, (arduinoSocket.isConnected()?"true":"false"));
                   Log.i(C.TAG, message);
                   btOutStream.write(message.getBytes(StandardCharsets.UTF_8));
               } catch (IOException e) {
                   Log.e(C.TAG, "Error occurred when creating output stream", e);
                   checkPairedDevices();
                   connectArduino(BT_NAME);
               }
           }
       });
    }
    @Override
    protected void onStart() {
        btAdapter = getSystemService(BluetoothManager.class).getAdapter();
        if (btAdapter == null) {
            displayError("Bluetooth not supported!");
            finish();
        }
        super.onStart();
        checkPermissionAndEnableBluetooth();
        checkPairedDevices();
        connectArduino("isi00");
        //verify correctness of connection

    }
    @Override
    protected void onResume() {
        super.onResume();
        if (Build.VERSION.SDK_INT < Build.VERSION_CODES.S){
            if (ActivityCompat.checkSelfPermission(this, Manifest.permission.BLUETOOTH) != PackageManager.PERMISSION_GRANTED) {
                //do not ask for permissions on resume otherwise you will get in a loop!
                displayError("Please grant legacy permissions first");
            }else{
                //  todo:check arduino connected
            }
        } else {
            if (ActivityCompat.checkSelfPermission(this, Manifest.permission.BLUETOOTH_CONNECT) != PackageManager.PERMISSION_GRANTED) {
                //do not ask for permissions on resume otherwise you will get in a loop!
                displayError("Please grant permissions first");
            } else{
                //  todo:check arduino connected
            }
        }
    }
    @Override
    protected void onStop() {
        try {
            btConnection.cancel();
            arduinoSocket.close();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        super.onStop();
    }
    /* ================== PERMISSION MANAGEMENT ========================== */
    private void checkPermissionAndEnableBluetooth(){
        if (Build.VERSION.SDK_INT < Build.VERSION_CODES.S){
            if (ActivityCompat.checkSelfPermission(this, Manifest.permission.BLUETOOTH) != PackageManager.PERMISSION_GRANTED
                    || ActivityCompat.checkSelfPermission(this, Manifest.permission.ACCESS_FINE_LOCATION) != PackageManager.PERMISSION_GRANTED
            ) {
                requestPermissions(new String[]{Manifest.permission.BLUETOOTH, Manifest.permission.ACCESS_FINE_LOCATION}, LEGACY_REQUEST_PERMISSION_BLUETOOTH);
            } else {
                if (!btAdapter.isEnabled()) {
                    Intent enableBtIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
                    //noinspection deprecation
                    startActivityForResult(enableBtIntent, REQUEST_ENABLE_BT);
                } else {
                    //this.remoteButton.setEnabled(true);

                }
            }
        } else {
            if (ActivityCompat.checkSelfPermission(this, Manifest.permission.BLUETOOTH_CONNECT) != PackageManager.PERMISSION_GRANTED) {
                requestPermissions(new String[]{Manifest.permission.BLUETOOTH_CONNECT}, REQUEST_PERMISSION_CONNECT);
            } else {
                if (!btAdapter.isEnabled()) {
                    Intent enableBtIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
                    //noinspection deprecation
                    startActivityForResult(enableBtIntent, REQUEST_ENABLE_BT);
                } else {
                    //this.remoteButton.setEnabled(true);
                }
            }
        }
    }

    @SuppressLint("MissingPermission")
    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);
        switch (requestCode) {
            case REQUEST_PERMISSION_CONNECT:
                Log.i(C.TAG, "REQUEST_PERMISSION_CONNECT");
                // If request is cancelled, the result arrays are empty.
                if (grantResults.length > 0 && grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                    //go back to enabling bluetooth
                    checkPermissionAndEnableBluetooth();
                } else {
                    //note, since android 11 permissions are asked only twice to the user.
                    // You should avoid terminating your app and instead maybe redirect the user to the settings to enable the permission manually
                    displayError("You need to grant bluetooth connection permissions to use this app");
                }
                break;
            case REQUEST_PERMISSION_SCAN:
                Log.i(C.TAG, "scan");
                break;
            case REQUEST_PERMISSION_ADMIN:
                Log.i(C.TAG, "admin");
                if (grantResults.length > 0 && grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                    //go back at scanning after receiving the permission
                    //startScanning();
                } else {
                    displayError( "You need to grant bluetooth scan permission to use this feature");
                }
                break;
            case LEGACY_REQUEST_PERMISSION_BLUETOOTH:
                Log.i(C.TAG, "bluetooth");
                if(grantResults.length > 1 && grantResults[0] == PackageManager.PERMISSION_GRANTED && grantResults[1] == PackageManager.PERMISSION_GRANTED)
                    logMessage("legacy ok");
                checkPermissionAndEnableBluetooth();
                break;
            default:
                logMessage("result of unknown activity request");
        }
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, @Nullable Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        switch (requestCode) {
            case REQUEST_ENABLE_BT:
                if(resultCode == RESULT_OK) {
                    this.remoteButton.setEnabled(true);
                } else {
                    displayError("You need to enable bluetooth to use the app");
                }
                break;
            default:
                //logMessage("result of unknown activity request");
        }
    }
    /* ================== LOGGING AND ERROR HANDLING ========================== */

    private void displayError(String s) {
        Log.e(C.TAG, s);
    }

    private void logMessage(String message){
        Log.i(C.TAG, message);
    }

    //* ============== BLUETOOTH CONNECTION =======================*/
    private final BroadcastReceiver receiver = new BroadcastReceiver() {
        public void onReceive(Context context, Intent intent) {
            String action = intent.getAction();
            if (BluetoothDevice.ACTION_FOUND.equals(action)) {
                BluetoothDevice device = intent.getParcelableExtra(BluetoothDevice.EXTRA_DEVICE);
                onBluetoothDeviceFound(device);
            }
        }
    };
    @SuppressLint("MissingPermission")
    private void onBluetoothDeviceFound(BluetoothDevice device) {
        this.scannedDevices.add(device);
        if(device.getName()!= null){
            this.scannedNameList.add(device.getName());
        } else {
            this.scannedNameList.add(device.getAddress());
        }
    }

    @SuppressLint("MissingPermission")
    private void checkPairedDevices(){
        pairedDevices.clear();
        pairedNameList.clear();
        pairedDevices.addAll(btAdapter.getBondedDevices());
        if (pairedDevices.size() > 0) {
            // There are paired devices. Get the name and address of each paired device.
            for (BluetoothDevice device : pairedDevices) {
                if(device.getName()!= null){
                    this.pairedNameList.add(device.getName());
                } else {
                    this.pairedNameList.add(device.getAddress());
                }
            }
        }
    }
    @SuppressLint("MissingPermission")
    private void connectArduino(String name){
        Log.i(C.TAG, "CONNECTING");
        for(BluetoothDevice dev : pairedDevices){
            if(dev.getName().equals(name)){
                arduinoDev=dev;
            }
        }

        Log.i(C.TAG, "BT_FOUND-ARDUINO" + arduinoDev);
        btConnection = new ConnectThread(arduinoDev, btAdapter);
        btConnection.run();
        arduinoSocket = btConnection.getSocket();
    }
}