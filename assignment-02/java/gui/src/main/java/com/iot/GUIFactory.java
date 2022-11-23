package com.iot;


import javafx.scene.control.Slider;

import java.util.ArrayList;
import java.util.List;

import javafx.scene.chart.LineChart;

import javafx.scene.control.ComboBox;
import javafx.scene.text.Text;


public interface GUIFactory {

    ComboBox<String> createSelector(ArrayList<String> options);
    Text createText(String text);
    LineChart<Number,Number> createLineChart();
    void populateChart(ArrayList<Float> data);
    Slider createSlider();

    
}
