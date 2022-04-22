package com.practice.gui;

import com.practice.controller.DBController;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.HBox;
import javafx.scene.text.Text;
import javafx.stage.Stage;
import javafx.stage.StageStyle;

public final class LoginWindowBuilder {
    public Stage create() {
        final double rem = new Text("").getLayoutBounds().getHeight();
        final GridPane aGridPanel = new GridPane();
        aGridPanel.setPadding(new Insets(0.8 * rem));

        final Label userNameLabel = new Label("User name:");
        userNameLabel.setPadding(new Insets(0.8 * rem));
        final Label passwordLabel = new Label("Password:");
        passwordLabel.setPadding(new Insets(0.8 * rem));
        final TextField userName = new TextField();
        final PasswordField password = new PasswordField();

        final Button btnSignup = new Button("Signup");
        btnSignup.setDisable(false);
        final Button btnLogin = new Button("Login");
        btnLogin.setDisable(true);

        userName.textProperty().addListener((arg0, oldValue, newValue) -> {
            boolean btnDisabled = userName.getText().trim().isEmpty() || password.getText().trim().isEmpty();
            btnLogin.setDisable(btnDisabled);
        });

        password.textProperty().addListener((arg0, oldValue, newValue) -> {
            boolean btnDisabled = userName.getText().trim().isEmpty() || password.getText().trim().isEmpty();
            btnLogin.setDisable(btnDisabled);
        });

        btnLogin.setDefaultButton(true);
        btnLogin.setOnAction(event -> {
            if (!DBController.getInstance().login(userName.getText().trim(), password.getText().trim())) {
                Alert aDialog = new Alert(Alert.AlertType.ERROR, "Incorrect user name or password");
                aDialog.showAndWait();
            } else {
                WindowStates.state = WindowStates.State.STATE_WORKING;
                btnLogin.getScene().getWindow().hide();
            }
        });

        btnSignup.setOnAction(event -> {
            WindowStates.state = WindowStates.State.STATE_SIGNUP;
            btnSignup.getScene().getWindow().hide();
        });

        final HBox buttons = new HBox(0.8 * rem);
        buttons.getChildren().addAll(btnSignup, btnLogin);
        buttons.setAlignment(Pos.CENTER);
        buttons.setPadding(new Insets(0.8 * rem));

        aGridPanel.add(userNameLabel, 0, 0);
        aGridPanel.add(userName, 1, 0);
        aGridPanel.add(passwordLabel, 0, 1);
        aGridPanel.add(password, 1, 1);
        aGridPanel.add(buttons, 0, 2, 2, 1);
        final Scene scene = new Scene(aGridPanel);

        final Stage stage = new Stage();
        stage.setTitle("Please login ...");
        stage.setResizable(false);
        stage.initStyle(StageStyle.UTILITY);

        stage.setScene(scene);

        stage.setOnCloseRequest(event -> {
            WindowStates.state = WindowStates.State.STATE_QUIT;
        });

        stage.setOnShowing(event -> {
            userName.setText("");
            password.setText("");
        });

        return stage;
    }
}
