package com.iot;

import java.util.ArrayList;

import java.util.Timer;
import java.util.TimerTask;

import javafx.application.Application;
import javafx.application.Platform;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;

import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.chart.LineChart;
import javafx.scene.chart.XYChart;
import javafx.scene.control.ComboBox;
import javafx.scene.control.Label;
import javafx.scene.control.Slider;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.stage.Screen;
import javafx.stage.Stage;
import jssc.SerialPortList;

/**
 * JavaFX App
 */
public class App extends Application {

    private SerialCommChannel console;
    XYChart.Series<Number, Number> series;
    SerialParser parser;
    GUIFactoryImpl p;
    float valveOpeningDegrees; // apertura della valvola in gradi
    String state; // stato di arduino: 0=normal, 1=pre-alarm , 2= alarm
    String smartLight;
    long start;

    @Override
    public void start(Stage stage) throws Exception {
        // TODO: aggiungere label per indicare stato e PIR,

        console = null;
        final Timer clockTimer = new Timer();
        final Label stateLabel, lightLabel, valveLabel;
        ArrayList<String> rawData = new ArrayList<>();

        valveOpeningDegrees = 0;
        state = "unknown";
        smartLight = "unknown";

        parser = new SerialParser();
        p = new GUIFactoryImpl();
        series = new XYChart.Series<>();

        ArrayList<String> port = new ArrayList<>();
        for (String string : SerialPortList.getPortNames()) {
            port.add(string);
        }
        stateLabel = new Label("state");
        stateLabel.setScaleX(2);
        stateLabel.setScaleY(2);

        lightLabel = new Label("SmartLight");
        lightLabel.setScaleX(2);
        lightLabel.setScaleY(2);

        valveLabel = new Label("valve");

        final ComboBox<String> portComboBox = p.createSelector(port);

        // check for presence of com port
        portComboBox.getSelectionModel().selectedItemProperty()
                .addListener(new ChangeListener<String>() {
                    public void changed(ObservableValue<? extends String> observable,
                            String oldValue, String newValue) {
                        System.out.println("Port selected: " + newValue);
                        try {
                            if (console != null) {
                                console.close();
                                console = new SerialCommChannel(newValue, 9600);
                            } else {
                                console = new SerialCommChannel(newValue, 9600);
                            }
                            // console = updateChannel(console,pt ,b );

                        } catch (Exception e) {
                            System.out.println("Exception: " + e.toString());
                        }
                    }
                });

        series.setName("water");
        series.getData().add(new XYChart.Data<>(0, 0));

        // Creates a slider
        Slider slider = p.createSlider();

        slider.valueProperty().addListener(new ChangeListener<Number>() {

            @Override
            public void changed(ObservableValue<? extends Number> arg0, Number arg1, Number newVal) {

                if (state.equals("alarm")) {
                    valveOpeningDegrees = newVal.floatValue();
                    valveOpeningDegrees = valveOpeningDegrees * (float) 1.8;

                    valveLabel.setText(String.format("%.2f", valveOpeningDegrees));
                    console.sendMsg("valve-" + valveOpeningDegrees);
                }

            }

        });
        VBox slid = new VBox(slider, valveLabel);
        slid.setSpacing(150);
        slid.setAlignment(Pos.CENTER);

        LineChart<Number, Number> chart = p.createLineChart();
        chart.getData().add(series);
        chart.setAnimated(false);
        chart.setCreateSymbols(false);

        HBox selectors = new HBox();
        selectors.getChildren().add(portComboBox);
        selectors.getChildren().add(stateLabel);
        selectors.getChildren().add(lightLabel);
        selectors.setSpacing(50);

        BorderPane root = new BorderPane(chart, selectors, null, null, slid); // center,top,right,bottom,left
        BorderPane.setAlignment(slid, Pos.CENTER_LEFT);

        Scene scene = new Scene(root, 800, 600);
        // add Scene to the frame
        stage.setScene(scene);
        stage.show();

        // time driven event
        clockTimer.scheduleAtFixedRate(new TimerTask() {
            @Override
            public void run() {
                Platform.runLater(new Runnable() {
                    @Override
                    public void run() {
                        /* methods to execute every n milliseconds */
                        // System.out.println("UPDATE");
                        rawData.clear();
                        try {
                            rawData.addAll(console.retiriveMessages());

                        } catch (Exception e) {

                            System.out.println("error in serial communiation: no port selected");
                        }
                        series = p.populateChart(parser.getNewChartData(rawData), series);
                        chart.getData().clear();
                        chart.getData().add(series);
                        // ottengo stato
                        state = parser.getState(rawData, state);
                        stateLabel.setText(state);
                        // ottengo smart light
                        smartLight = parser.getSmartLight(rawData, smartLight);
                        lightLabel.setText(smartLight);
                    }
                });
            }
        }, 0, 1000 // Sleep for 1 seconds since that is how long it is between
        );

    }

    @Override
    public void stop() {
        if (console != null) {
            console.close();
        }
        System.out.println("console closed");
        // Save file
        System.exit(0);
    }

    public static void main(String[] args) {
        launch(args);
    }

}
