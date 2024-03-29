package com.practice.gui;

import com.practice.controller.DBController;
import javafx.application.Application;
import javafx.application.Platform;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.stage.Stage;

import java.util.*;

public class MyApplication extends Application
{
    private Stage mLoginWindow = null;
    private Stage mSignupWindow = null;
    private MainWindow mMainWindow = null;

    @Override
    public void start(Stage primaryStage) throws Exception
    {
        while( WindowStates.State.STATE_QUIT != WindowStates.state
                && WindowStates.State.STATE_WORKING != WindowStates.state)
        {
            switch( WindowStates.state ){
                case STATE_LOGIN:
                {
                    if (null == mLoginWindow) {
                        mLoginWindow = new LoginWindowBuilder().create();
                    }
                    mLoginWindow.showAndWait();
                }
                break;

                case STATE_SIGNUP:
                {
                    if (null == mSignupWindow) {
                        mSignupWindow = new SignupWindowBuilder().create();
                    }
                    mSignupWindow.showAndWait();
                }
                break;

                default:
                    break;
            } // switch

        } // while

        if (WindowStates.State.STATE_WORKING == WindowStates.state) {
            mMainWindow = MainWindow.create(primaryStage);
            primaryStage.show();
        } else {
            DBController.release();
            Platform.exit();
        }
    }
}
