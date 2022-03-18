package com.practice.gui;

import com.practice.controller.DBController;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.collections.ObservableList;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Priority;
import javafx.scene.layout.StackPane;
import javafx.scene.text.Text;
import javafx.stage.Stage;

public class MainWindow
{
    private final int PREFERRED_WIDTH = 1024;
    private final int PREFERRED_HEIGHT = 768;
    private StackPane mStackPanel;

    private final BorderPane mInputPanel;
    private final TextField mInputTitle;
    private final TextArea mInputContent;

    private final BorderPane mDBViewPanel;
    private final Button mBtnBackToInput;
    private final Button mBtnDelete;
    private final RadioButton mRadioRecent;
    private final RadioButton mRadioAll;

    private final TableView<DBController.WordItem> mDBTableView;

    private MainWindow(Stage primaryStage, ObservableList<DBController.WordItem> dataSource){
        final double rem = new Text("").getLayoutBounds().getHeight();

        // create database view panel
        mInputPanel = new BorderPane();
        mDBViewPanel = new BorderPane();

        mDBViewPanel.setPrefSize(PREFERRED_WIDTH, PREFERRED_HEIGHT);
        mDBViewPanel.setPadding(new Insets(0.8 * rem));

        mDBTableView = new TableView<>();
        mDBTableView.setItems(dataSource);

        TableColumn<DBController.WordItem, String> column0 = new TableColumn<>("Word");
        column0.setCellValueFactory(new PropertyValueFactory<DBController.WordItem, String>("word"));
        column0.setMinWidth(200.0);

        TableColumn<DBController.WordItem, Integer> column1 = new TableColumn<>("Count");
        column1.setCellValueFactory(new PropertyValueFactory<DBController.WordItem, Integer>("frequency"));

        mDBTableView.getColumns().setAll(column0, column1);

        mDBViewPanel.setCenter(mDBTableView);

        mBtnBackToInput = new Button("Back");
        mBtnBackToInput.setOnAction(event -> {
            mDBViewPanel.setVisible(false);
            mInputPanel.setVisible(true);
        });

        ToggleGroup aRadioGroup = new ToggleGroup();

        mRadioRecent = new RadioButton("Recent");
        mRadioRecent.setToggleGroup(aRadioGroup);
        mRadioAll = new RadioButton("All");
        mRadioAll.setToggleGroup(aRadioGroup);

        aRadioGroup.selectedToggleProperty().addListener(new ChangeListener<Toggle>()
        {
            @Override
            public void changed(ObservableValue<? extends Toggle> observableValue, Toggle toggle, Toggle t1)
            {
                Object selectedToggle = aRadioGroup.getSelectedToggle();
                if (selectedToggle == mRadioRecent) {
                    DBController.getInstance().queryRecent(listOfWords ->{
                        dataSource.clear();
                        dataSource.addAll(listOfWords);
                    });
                } else if (selectedToggle == mRadioAll) {
                    DBController.getInstance().queryAll(listOfWords ->{
                        dataSource.clear();
                        dataSource.addAll(listOfWords);
                    });
                }
            }
        });

        mBtnDelete = new Button("Delete");

        HBox DBPanelBottomBar = new HBox(100.0f);
        DBPanelBottomBar.setPadding(new Insets(rem * 0.8));
        DBPanelBottomBar.setAlignment(Pos.CENTER);
        DBPanelBottomBar.getChildren().addAll(mBtnBackToInput, mRadioRecent, mRadioAll, mBtnDelete);

        mDBViewPanel.setBottom(DBPanelBottomBar);
        mDBViewPanel.setVisible(false);

        // create input panel

        mInputTitle = new TextField();

        HBox titleBar = new HBox(10.0);
        titleBar.setAlignment(Pos.CENTER);
        titleBar.getChildren().add(new Label("Title"));
        titleBar.getChildren().add(mInputTitle);
        titleBar.setPadding(new Insets(rem * 0.8));
        HBox.setHgrow(mInputTitle, Priority.ALWAYS );

        mInputContent = new TextArea();
        mInputContent.setPadding(new Insets( rem * 0.8));
        mInputContent.wrapTextProperty().set(true);

        Button btnSubmit = new Button("Submit");
        btnSubmit.setDefaultButton(true);

        btnSubmit.setOnAction(event ->{
            DBController.getInstance().submit(mInputTitle.getText(),mInputContent.getText(),(listOfWords ->{
                mInputPanel.setVisible(false);
                mInputTitle.setText("");
                mInputContent.setText("");
                mDBViewPanel.setVisible(true);
                mBtnDelete.setDisable(true);
                mRadioRecent.setSelected(true);
                mRadioRecent.requestFocus();
            }));
        });

        Button btnSkip = new Button("Skip");

        btnSkip.setOnAction(event ->{
            DBController.getInstance().queryAll(listOfWords ->{
                mInputPanel.setVisible(false);
                mInputTitle.setText("");
                mInputContent.setText("");
                mDBViewPanel.setVisible(true);
                mBtnDelete.setDisable(true);
                mRadioAll.setSelected(true);
                mRadioAll.requestFocus();
            });
        });

        HBox InputPanelBottomBar = new HBox(200.0);
        InputPanelBottomBar.setPadding(new Insets(rem * 0.8));
        InputPanelBottomBar.setAlignment(Pos.CENTER);
        InputPanelBottomBar.getChildren().addAll(btnSubmit, btnSkip);

        mInputPanel.setTop(titleBar);
        mInputPanel.setCenter(mInputContent);
        mInputPanel.setBottom(InputPanelBottomBar);

        mInputPanel.setPrefSize(PREFERRED_WIDTH, PREFERRED_HEIGHT);

        mStackPanel = new StackPane();
        mStackPanel.setAlignment(Pos.CENTER);
        mStackPanel.getChildren().add(mInputPanel);
        mStackPanel.getChildren().add(mDBViewPanel);

        Scene scene = new Scene(mStackPanel);

        primaryStage.setScene(scene);
        primaryStage.setTitle("Words");

        return;
    }

    public static MainWindow create(Stage primaryStage, ObservableList<DBController.WordItem> dataSource){
        return new MainWindow(primaryStage, dataSource);
    }
}
