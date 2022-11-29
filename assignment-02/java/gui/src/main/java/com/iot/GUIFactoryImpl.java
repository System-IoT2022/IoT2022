package com.iot;

import java.util.ArrayList;
import java.util.List;

import javafx.collections.FXCollections;
import javafx.stage.Screen;
import javafx.scene.control.Slider;
import javafx.scene.transform.Rotate;
import javafx.scene.chart.LineChart;
import javafx.scene.chart.NumberAxis;
import javafx.scene.chart.XYChart;
import javafx.scene.control.ComboBox;
import javafx.geometry.Insets;

public class GUIFactoryImpl implements GUIFactory {

    public GUIFactoryImpl() {
        super();

    }

    @Override
    public ComboBox<String> createSelector(List<String> options) {

        ComboBox<String> b = new ComboBox<>();
        b.setItems(FXCollections.observableArrayList(options));
        return b;
    }

    @Override
    public LineChart<Number, Number> createLineChart() {

        final NumberAxis xAxis = new NumberAxis();
        final NumberAxis yAxis = new NumberAxis();
        // setup x axis
        xAxis.setLabel("time");
        xAxis.setAutoRanging(true);
        xAxis.setForceZeroInRange(false);
        // setup y axis
        yAxis.setLabel("metres");
        yAxis.setAutoRanging(true);
        yAxis.setForceZeroInRange(false);
        // creating the chart
        LineChart<Number, Number> chart = new LineChart<Number, Number>(xAxis, yAxis);
        // setup linechart and insert data
        chart.setTitle("Water Level");

        return chart;
    }

    // TODO: Fix warning
    @Override
    public Slider createSlider() {

        Slider slider = new Slider(0, 100, 0);
        slider.setCenterShape(true);
        slider.setShowTickMarks(true);
        slider.setShowTickLabels(false);
        slider.setMajorTickUnit(0.25);
        slider.setBlockIncrement(1.0);
        slider.setRotate(90.0);
        slider.setMinWidth(Screen.getPrimary().getBounds().getHeight() * 0.3);
        slider.setMaxWidth(Screen.getPrimary().getBounds().getHeight());
        slider.setRotationAxis(Rotate.Z_AXIS);
        slider.setPadding(new Insets(0));
        return slider;
    }

    @Override
    public XYChart.Series<Number, Number> populateChart(ArrayList<Float> newData,
            XYChart.Series<Number, Number> oldSerie) {
        XYChart.Series<Number, Number> newSerie = new XYChart.Series<>();
        int last = (int) oldSerie.getData().get(oldSerie.getData().size() - 1).getXValue(); // ottengo un Number, lo
                                                                                            // casto a int
        int oldLen = oldSerie.getData().size();
        if (oldSerie.getData().size() > 50) {
            // tolgo i primi n valori presenti nella serie per la quantita di dati mostrati
            for (int i = newData.size(); i < oldLen; i++, last++) {
                newSerie.getData().add(oldSerie.getData().get(i));
            }
        } else {
            newSerie.getData().addAll(oldSerie.getData());
        }
        for (Float item : newData) {
            newSerie.getData().add(new XYChart.Data<>(last, item.floatValue()));
            last++;
        }
        return newSerie;
    }
}
