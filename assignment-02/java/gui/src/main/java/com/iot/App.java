package com.iot;

import javafx.application.Application;
import javafx.application.Platform;
import javafx.collections.FXCollections;
import javafx.collections.ObservableFloatArray;
import javafx.collections.ObservableList;
import javafx.scene.Scene;
import javafx.stage.Screen;
import javafx.stage.Stage;
import javafx.scene.control.Slider;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.HBox;
import javafx.scene.transform.Rotate;
import javafx.scene.chart.LineChart;
import javafx.scene.chart.NumberAxis;
import javafx.scene.chart.XYChart;
import javafx.scene.chart.XYChart.Series;
import javafx.scene.control.ComboBox;
import javafx.geometry.Insets;
import javafx.geometry.Pos;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Enumeration;
import java.util.Timer;
import java.util.TimerTask;
import jssc.*;

import com.iot.GUIFactoryImpl;

/**
 * JavaFX App
 */
public class App extends Application {
    
   
    
    
    
    @Override
    public void start(Stage stage) throws Exception {
        final Timer clockTimer = new Timer();
        ArrayList baud = new ArrayList<>();

        GUIFactoryImpl p = new GUIFactoryImpl();

        
        baud.add("4800");
        baud.add("9500");
        baud.add("14400");
        ArrayList<String> port = new ArrayList<>();
       
        for (String string : SerialPortList.getPortNames()) {
            port.add(string);
        }


        String[] com = {"COM1","COM2","COM3"}; 
        
        final ComboBox<String> baudRateComboBox = p.createSelector(baud);
        final ComboBox<String> portComboBox = p.createSelector(port);
        
        //di default seleziono gli elementi in 0,0: elementi vuoti
        final SerialParser console = new SerialParser(portComboBox.getItems().get(0).toString(), 
                                                        Integer.valueOf( baudRateComboBox.getItems().get(0).toString()));
        // Creates a slider
        Slider slider = p.createSlider();
        LineChart chart = p.createLineChart();
        HBox selectors = new HBox();
        selectors.getChildren().add(portComboBox);
        selectors.getChildren().add(baudRateComboBox);
        
        BorderPane root= new BorderPane(chart,selectors,null,null,slider); //center,top,right,bottom,left
        root.setAlignment(slider, Pos.CENTER_LEFT);
        
        Scene scene = new Scene(root, 1000, 1000); 
        // add Scene to the frame
        stage.setScene(scene);
        stage.show();
        
        //time driven event check
        clockTimer.scheduleAtFixedRate(new TimerTask() {
            @Override
           public void run() { 
                /*
                * Calculates the time in base 10 time and calls the 4 methods
                * to set the GUI display.
                * 
                 * In a constant while loop in order to continuously update
                 * the GUI.
                 */
                
                Platform.runLater(new Runnable() {
                    @Override  public void run() {
                        /*methods to execute every n seconds */
                    }
                });
            }
        }, 0, 1000  // Sleep for 8.64 seconds since that is how long it is between
        );              
}




// public Series updateChart(float value){
        
        
// }
    

private String[] consolePrintSerialPorts(){
    String[] portNames = SerialPortList.getPortNames();
		for (int i = 0; i < portNames.length; i++){
		    System.out.println(portNames[i]);
		}
        return portNames;
}

    
    

    public static void main(String[] args) {
        launch();
    }

}