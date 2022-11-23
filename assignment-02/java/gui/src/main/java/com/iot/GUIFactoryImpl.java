package com.iot;

import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.List;

import javafx.collections.FXCollections;
import javafx.stage.Screen;
import javafx.scene.control.Slider;
import javafx.scene.text.Text;
import javafx.scene.transform.Rotate;
import javafx.scene.chart.LineChart;
import javafx.scene.chart.NumberAxis;
import javafx.scene.control.ComboBox;
import javafx.geometry.Insets;


public class GUIFactoryImpl implements GUIFactory{
    

    public GUIFactoryImpl(){
        super();
       
    }

    @Override
    public ComboBox<String> createSelector(ArrayList<String> options) {
        // TODO Auto-generated method stub
        
        ComboBox<String> b = new ComboBox();    
        b.setItems(FXCollections.observableArrayList(options));
        return b;
    }

    @Override
    public Text createText(String text) {
        Text t = new Text(text);
        return t;
    }

    @Override
    public LineChart<Number,Number> createLineChart() {
        
        final NumberAxis xAxis = new NumberAxis();
        final NumberAxis yAxis = new NumberAxis();
        //setup x axis
        xAxis.setLabel("time");
        xAxis.setAutoRanging(true);
        xAxis.setForceZeroInRange(false);
        //setup y axis
        yAxis.setLabel("metres");
        yAxis.setAutoRanging(true);
        yAxis.setForceZeroInRange(false);
        //creating the chart
       LineChart<Number,Number> chart = 
        new LineChart<Number,Number>(xAxis,yAxis);        
        //setup linechart and insert data
        chart.setTitle("Water Level"); 

        return chart;
    }

    @Override
    public Slider createSlider() {
        // TODO Auto-generated method stub
        Slider slider = new Slider(0, 100, 0); 
        slider.setCenterShape(true);    
        slider.setShowTickMarks(true);         
        slider.setShowTickLabels(false);         
        slider.setMajorTickUnit(0.25);         
        slider.setBlockIncrement(1.0);  
        slider.setRotate(90.0);
        slider.setMinWidth(Screen.getPrimary().getBounds().getHeight()*0.3);
        slider.setMaxWidth(Screen.getPrimary().getBounds().getHeight());      
        slider.setRotationAxis(Rotate.Z_AXIS);
        slider.setPadding(new Insets(0));
        return slider;
    }

    @Override
    public void populateChart(ArrayList<Float> data) {
        // TODO Auto-generated method stub
        
    }

    
}
