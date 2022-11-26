module com.iot {
    requires javafx.controls;
    requires javafx.fxml;
    requires jssc;
    
    opens com.iot to javafx.fxml;
    exports com.iot;
}
