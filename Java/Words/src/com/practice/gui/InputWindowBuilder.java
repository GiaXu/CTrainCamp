package com.practice.gui;

import com.practice.controller.DBController;
import javafx.beans.InvalidationListener;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableStringValue;
import javafx.beans.value.ObservableValue;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Node;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.layout.*;
import javafx.scene.text.Text;
import javafx.stage.Stage;

import java.awt.*;
import java.util.ArrayList;

public final class InputWindowBuilder
{
    private static final int PREFERRED_WIDTH = 1024;
    private static final int PREFERRED_HEIGHT = 768;

    public BorderPane createDataPanel( ObservableList<DBController.WordItem> dataSource){
        final double rem = new Text("").getLayoutBounds().getHeight();

        BorderPane dataPanel = new BorderPane();
        dataPanel.setPrefSize(PREFERRED_WIDTH, PREFERRED_HEIGHT);
        dataPanel.setPadding(new Insets(0.8 * rem));

        TableView<DBController.WordItem> tableView = new TableView<>();
        tableView.setItems(dataSource);

        TableColumn<DBController.WordItem, String> column0 = new TableColumn<>("Word");
        column0.setCellValueFactory(new PropertyValueFactory<DBController.WordItem, String>("word"));

        TableColumn<DBController.WordItem, Integer> column1 = new TableColumn<>("Count");
        column1.setCellValueFactory(new PropertyValueFactory<DBController.WordItem, Integer>("frequency"));

        tableView.getColumns().setAll(column0, column1);

        dataPanel.setCenter(tableView);

        HBox bottomBar = new HBox(10.0f);
        bottomBar.setPadding(new Insets(rem * 0.8));
        bottomBar.setAlignment(Pos.CENTER);
        bottomBar.getChildren().add(new Button("Test"));

        dataPanel.setBottom(bottomBar);

        return dataPanel;
    }

    public Stage create(Stage primaryStage, ObservableList<DBController.WordItem> dataSource){
        final double rem = new Text("").getLayoutBounds().getHeight();

        BorderPane dataPanel = createDataPanel(dataSource);
        dataPanel.setVisible(false);

        BorderPane inputPanel = new BorderPane();

        TextField titleTF = new TextField();

        HBox titleBar = new HBox(10.0);
        titleBar.setAlignment(Pos.CENTER);
        titleBar.getChildren().add(new Label("Title"));
        titleBar.getChildren().add(titleTF);
        titleBar.setPadding(new Insets(rem * 0.8));
        HBox.setHgrow(titleTF, Priority.ALWAYS );

        TextArea contentTA = new TextArea();
        contentTA.setPadding(new Insets( rem * 0.8));
        contentTA.wrapTextProperty().set(true);

        Button btnSubmit = new Button("Submit");
        btnSubmit.setDefaultButton(true);

        btnSubmit.setOnAction(event ->{
            DBController.getInstance().submit(titleTF.getText(),contentTA.getText(),(listOfWords ->{
                inputPanel.setVisible(false);
                dataPanel.setVisible(true);
                dataSource.clear();
                dataSource.addAll(listOfWords);
            }));
        });

        HBox bottomBar = new HBox(10.0);
        bottomBar.setPadding(new Insets(rem * 0.8));
        bottomBar.setAlignment(Pos.CENTER);
        bottomBar.getChildren().add(btnSubmit);


        inputPanel.setTop(titleBar);
        inputPanel.setCenter(contentTA);
        inputPanel.setBottom(bottomBar);

        inputPanel.setPrefSize(PREFERRED_WIDTH, PREFERRED_HEIGHT);

        StackPane mainPanel = new StackPane();
        mainPanel.setAlignment(Pos.CENTER);
        mainPanel.getChildren().add(inputPanel);
        mainPanel.getChildren().add(dataPanel);

        Scene scene = new Scene(mainPanel);

        primaryStage.setScene(scene);
        primaryStage.setTitle("Words");
        return primaryStage;
    }
}
