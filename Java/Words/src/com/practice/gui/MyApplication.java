package com.practice.gui;

import com.practice.controller.DBController;
import javafx.application.Application;
import javafx.application.Platform;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Pane;
import javafx.scene.text.Text;
import javafx.stage.Stage;
import javafx.stage.StageStyle;

public class MyApplication extends Application
{
    private static final int MESSAGE_X = 75;
    private static final int MESSAGE_Y = 100;
    private static final int PREFERRED_WIDTH = 300;
    private static final int PREFERRED_HEIGHT = 200;

    private Stage mLoginWindow = null;
    private Stage mSignupWindow = null;
    private Stage mMainWindow = null;

    enum State{
        STATE_LOGIN,
        STATE_SIGNUP,
        STATE_WORKING,
        STATE_QUIT
    }

    private State mState = State.STATE_LOGIN;

    private Stage createLoginWindow(){
        final double rem = new Text("").getLayoutBounds().getHeight();
        final GridPane aGridPanel = new GridPane();
        aGridPanel.setPadding(new Insets(0.8 * rem));

        final Label userNameLabel = new Label("User name:");
        userNameLabel.setPadding(new Insets(0.8 * rem));
        final Label passwordLabel = new Label("Password:");
        passwordLabel.setPadding(new Insets(0.8 * rem));
        final TextField userName = new TextField();
        final TextField password = new TextField();

        final Button btnSignup = new Button("Signup");
        btnSignup.setDisable(true);
        final Button btnLogin = new Button("Login");
        btnLogin.setDisable(true);

        userName.textProperty().addListener((arg0, oldValue, newValue) ->{
            boolean btnDisabled = userName.getText().trim().isEmpty() || password.getText().trim().isEmpty();
            btnLogin.setDisable(btnDisabled);
            btnSignup.setDisable(btnDisabled);
        });

        password.textProperty().addListener((arg0, oldValue, newValue) ->{
            boolean btnDisabled = userName.getText().trim().isEmpty() || password.getText().trim().isEmpty();
            btnLogin.setDisable(btnDisabled);
            btnSignup.setDisable(btnDisabled);
        });

        btnLogin.setOnAction(event -> {
            if (!DBController.getInstance().login(userName.getText().trim(), password.getText().trim())) {
                Alert aDialog = new Alert(Alert.AlertType.ERROR, "Incorrect user name or password");
                aDialog.showAndWait();
            } else {
                mState = State.STATE_WORKING;
                btnLogin.getScene().getWindow().hide();
            }
        });

        btnSignup.setOnAction(event -> {
            mState = State.STATE_SIGNUP;
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
            mState = State.STATE_QUIT;
        });

        stage.setOnShowing(event -> {
            userName.setText("");
            password.setText("");
        });

        return stage;
    }

    private Stage createSignupWindow(){
        final double rem = new Text("").getLayoutBounds().getHeight();
        final GridPane aGridPanel = new GridPane();
        aGridPanel.setPadding(new Insets(0.8 * rem));

        final Label userNameLabel = new Label("User name:");
        userNameLabel.setPadding(new Insets(0.8 * rem));
        final Label passwordLabel = new Label("Password:");
        passwordLabel.setPadding(new Insets(0.8 * rem));
        final TextField userName = new TextField();
        final TextField password = new TextField();

        final Button btnSignup = new Button("Signup");
        btnSignup.setDisable(true);
        final Button btnCancel = new Button("Cancel");

        userName.textProperty().addListener((arg0, oldValue, newValue) ->{
            boolean btnDisabled = userName.getText().trim().isEmpty() || password.getText().trim().isEmpty();
            btnSignup.setDisable(btnDisabled);
        });

        password.textProperty().addListener((arg0, oldValue, newValue) ->{
            boolean btnDisabled = userName.getText().trim().isEmpty() || password.getText().trim().isEmpty();
            btnSignup.setDisable(btnDisabled);
        });

        btnSignup.setOnAction(event -> {
            if (!DBController.getInstance().signup(userName.getText().trim(), password.getText().trim())) {
                Alert aDialog = new Alert(Alert.AlertType.ERROR, "Signup failed.");
                aDialog.showAndWait();
            } else {
                mState = State.STATE_LOGIN;
                btnCancel.getScene().getWindow().hide();
            }
        });

        btnCancel.setOnAction(event -> {
            mState = State.STATE_LOGIN;
            btnCancel.getScene().getWindow().hide();
        });

        final HBox buttons = new HBox(0.8 * rem);
        buttons.getChildren().addAll(btnCancel, btnSignup);
        buttons.setAlignment(Pos.CENTER);
        buttons.setPadding(new Insets(0.8 * rem));

        aGridPanel.add(userNameLabel, 0, 0);
        aGridPanel.add(userName, 1, 0);
        aGridPanel.add(passwordLabel, 0, 1);
        aGridPanel.add(password, 1, 1);
        aGridPanel.add(buttons, 0, 2, 2, 1);
        final Scene scene = new Scene(aGridPanel);

        final Stage stage = new Stage();
        stage.setTitle("Signup ...");
        stage.setResizable(false);
        stage.initStyle(StageStyle.UTILITY);

        stage.setScene(scene);

        stage.setOnCloseRequest(event -> {
            mState = State.STATE_QUIT;
        });

        stage.setOnShowing(event -> {
            userName.setText("");
            password.setText("");
        });

        return stage;
    }

    private Stage createMainWindow(Stage primaryStage){
        Text message = new Text(MESSAGE_X, MESSAGE_Y, "Not a Hello World program");

        Pane root = new Pane(message); root.setPrefSize(PREFERRED_WIDTH, PREFERRED_HEIGHT);

        Scene scene = new Scene(root);

        primaryStage.setScene(scene);
        primaryStage.setTitle("NotHelloWorld");
        return primaryStage;
    }

    @Override
    public void start(Stage primaryStage) throws Exception
    {
        while( State.STATE_QUIT != mState && State.STATE_WORKING != mState)
        {
            switch( mState ){
                case STATE_LOGIN:
                {
                    if (null == mLoginWindow) {
                        mLoginWindow = createLoginWindow();
                    }
                    mLoginWindow.showAndWait();
                }
                break;

                case STATE_SIGNUP:
                {
                    if (null == mSignupWindow) {
                        mSignupWindow = createSignupWindow();
                    }
                    mSignupWindow.showAndWait();
                }
                break;

                default:
                    break;
            } // switch

        } // while

        if (State.STATE_WORKING == mState) {
            mMainWindow = createMainWindow(primaryStage);
            mMainWindow.show();
        } else {
            DBController.release();
            Platform.exit();
        }
    }
}
