package com.iot;

import javafx.scene.control.Slider;

import java.util.ArrayList;
import java.util.List;

import javafx.scene.chart.LineChart;
import javafx.scene.chart.XYChart;
import javafx.scene.control.ComboBox;
import javafx.scene.text.Text;

public interface GUIFactory {

    ComboBox<String> createSelector(List<String> options);

    LineChart<Number, Number> createLineChart();

    XYChart.Series<Number, Number> populateChart(ArrayList<Float> data, XYChart.Series<Number, Number> serie);

    Slider createSlider();

}
