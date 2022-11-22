package com.example;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Screen;
import javafx.stage.Stage;
import javafx.stage.Window;
import javafx.scene.control.Slider;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Pane;
import javafx.scene.transform.Rotate;
import javafx.scene.chart.LineChart;
import javafx.scene.chart.NumberAxis;
import javafx.scene.chart.XYChart;
import javafx.geometry.Insets;
import javafx.geometry.Pos;

import java.io.IOException;

/**
 * JavaFX App
 */
public class App extends Application {

    @Override
    public void start(Stage stage) throws IOException {
        
        //creo dataset grafico
        final NumberAxis xAxis = new NumberAxis();
        final NumberAxis yAxis = new NumberAxis();
        xAxis.setLabel("time");
        xAxis.setAutoRanging(true);
        xAxis.setForceZeroInRange(false);
        
        yAxis.setLabel("metres");
        yAxis.setAutoRanging(true);
        yAxis.setForceZeroInRange(false);
        //creating the chart
        final LineChart<Number,Number> lineChart = 
                new LineChart<Number,Number>(xAxis,yAxis);
                
        lineChart.setTitle("Water Level");   
        
        XYChart.Series series = new XYChart.Series();       
        series.setName("water");

        //utilizzare recuperare da serial!!!!
        series.getData().add(new XYChart.Data(0, 23));
        series.getData().add(new XYChart.Data(1, 23));
        series.getData().add(new XYChart.Data(2, 14));
        series.getData().add(new XYChart.Data(3, 15));

        // Creates a slider
        
        Slider slider = new Slider(0, 100, 0); 
        slider.setCenterShape(true);    
        slider.setShowTickMarks(true);         
        slider.setShowTickLabels(true);         
        slider.setMajorTickUnit(0.25);         
        slider.setBlockIncrement(1.0);  
        slider.setRotate(90.0);
        slider.setMinWidth(Screen.getPrimary().getBounds().getHeight()*0.3);
        slider.setMaxWidth(Screen.getPrimary().getBounds().getHeight());      
        slider.setRotationAxis(Rotate.Z_AXIS);
        slider.setPadding(new Insets(0));
        


        // set title of the frame
        stage.setTitle("Slider Sample");
        lineChart.getData().add(series);
        lineChart.autosize();
        lineChart.applyCss();
        
        
        BorderPane root= new BorderPane();
        root.setCenter(lineChart);
        root.setLeft(slider);
        root.setPadding(new Insets(0.0));
        root.setAlignment(slider, Pos.CENTER_LEFT);

        Scene scene = new Scene(root, 800, 800); 
        // add Scene to the frame
        stage.setScene(scene);
        stage.show();
    }

    

    public static void main(String[] args) {
        launch();
    }

}
