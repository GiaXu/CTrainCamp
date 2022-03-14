package com.practice.gui;

import com.practice.controller.DBController;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Pane;
import javafx.scene.layout.Priority;
import javafx.scene.text.Text;
import javafx.stage.Stage;

public final class InputWindowBuilder
{
    private static final int MESSAGE_X = 75;
    private static final int MESSAGE_Y = 100;
    private static final int PREFERRED_WIDTH = 1024;
    private static final int PREFERRED_HEIGHT = 768;

    public Stage create(Stage primaryStage){
        final double rem = new Text("").getLayoutBounds().getHeight();
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
            DBController.getInstance().submit(titleTF.getText(), contentTA.getText());
        });

        HBox bottomBar = new HBox(10.0);
        bottomBar.setPadding(new Insets(rem * 0.8));
        bottomBar.setAlignment(Pos.CENTER);
        bottomBar.getChildren().add(btnSubmit);

        BorderPane inputPanel = new BorderPane();
        inputPanel.setTop(titleBar);
        inputPanel.setCenter(contentTA);
        inputPanel.setBottom(bottomBar);

        inputPanel.setPrefSize(PREFERRED_WIDTH, PREFERRED_HEIGHT);

        Scene scene = new Scene(inputPanel);

        primaryStage.setScene(scene);
        primaryStage.setTitle("Words");
        return primaryStage;
    }
}
