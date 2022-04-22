package com.practice.gui;

import com.practice.controller.DBController;
import javafx.application.Platform;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.control.cell.CheckBoxTableCell;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Priority;
import javafx.scene.layout.StackPane;
import javafx.scene.text.Text;
import javafx.stage.Stage;
import javafx.util.Callback;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;

public class MainWindow {
    private final int PREFERRED_WIDTH = 1024;
    private final int PREFERRED_HEIGHT = 768;
    private StackPane mStackPanel;

    private BorderPane mInputPanel;
    private TextField mInputTitle;
    private TextArea mInputContent;

    private BorderPane mDBViewPanel;
    private Button mBtnBackToInput;
    private Button mBtnDelete;
    private RadioButton mRadioRecent;
    private RadioButton mRadioAll;

    private final ProgressIndicator mPI;

    private TableView<DBController.WordItem> mDBTableView;
    private int mSelectedItemCount = 0;

    private ChangeListener<Boolean> mCheckBoxCellListener = (observableValue, aBoolean, t1) ->
    {
        if (t1) {
            mSelectedItemCount += 1;
        } else {
            mSelectedItemCount -= 1;
        }
        mSelectedItemCount = Math.max(0, mSelectedItemCount);
        mBtnDelete.setDisable(0 == mSelectedItemCount);
    };

    private void addListenerToDataSource(List<DBController.WordItem> dataSource) {
        for (DBController.WordItem item : dataSource) {
            item.getSelected().addListener(mCheckBoxCellListener);
        }
    }

    private void removeListenerFromDataSource(List<DBController.WordItem> dataSource) {
        for (DBController.WordItem item : dataSource) {
            item.getSelected().removeListener(mCheckBoxCellListener);
        }
    }

    private MainWindow(Stage primaryStage) {
        final double rem = new Text("").getLayoutBounds().getHeight();
        mPI = new ProgressIndicator();
        mPI.setVisible(false);

        initInputPanel(rem);

        initDBViewPanel(rem);

        mStackPanel = new StackPane();
        mStackPanel.setAlignment(Pos.CENTER);
        mStackPanel.getChildren().addAll(mInputPanel, mDBViewPanel, mPI);

        Scene scene = new Scene(mStackPanel);

        primaryStage.setScene(scene);
        primaryStage.setTitle("Words");

        return;
    }

    private void initInputPanel(double rem) {
        mInputPanel = new BorderPane();

        mInputTitle = new TextField();

        HBox titleBar = new HBox(10.0);
        titleBar.setAlignment(Pos.CENTER);
        titleBar.getChildren().add(new Label("Title"));
        titleBar.getChildren().add(mInputTitle);
        titleBar.setPadding(new Insets(rem * 0.8));
        HBox.setHgrow(mInputTitle, Priority.ALWAYS);

        mInputContent = new TextArea();
        mInputContent.setPadding(new Insets(rem * 0.8));
        mInputContent.wrapTextProperty().set(true);

        Button btnSubmit = new Button("Submit");
        btnSubmit.setDefaultButton(true);
        btnSubmit.setDisable(true);

        btnSubmit.setOnAction(event -> {
            showProgressIndicator();
            new Thread(() -> {
                DBController.getInstance().submit(mInputTitle.getText(), mInputContent.getText(), (() -> {
                    Platform.runLater(() -> {
                        mInputPanel.setVisible(false);
                        mInputTitle.setText("");
                        mInputContent.setText("");
                        mDBViewPanel.setVisible(true);
                        mBtnDelete.setDisable(true);
                        mRadioRecent.setSelected(true);
                        mRadioRecent.requestFocus();
                        hideProgressIndicator();
                    });
                }));
            }).start();
        });

        Button btnSkip = new Button("Skip");

        btnSkip.setOnAction(event -> {
            mInputPanel.setVisible(false);
            mInputTitle.setText("");
            mInputContent.setText("");
            mDBViewPanel.setVisible(true);
            mBtnDelete.setDisable(true);
            mRadioAll.setSelected(true);
            mRadioAll.requestFocus();
        });

        mInputContent.textProperty().addListener((arg0, oldValue, newValue) -> {
            btnSubmit.setDisable(mInputContent.getText().trim().isEmpty());
        });

        HBox InputPanelBottomBar = new HBox(200.0);
        InputPanelBottomBar.setPadding(new Insets(rem * 0.8));
        InputPanelBottomBar.setAlignment(Pos.CENTER);
        InputPanelBottomBar.getChildren().addAll(btnSubmit, btnSkip);

        mInputPanel.setTop(titleBar);
        mInputPanel.setCenter(mInputContent);
        mInputPanel.setBottom(InputPanelBottomBar);

        mInputPanel.setPrefSize(PREFERRED_WIDTH, PREFERRED_HEIGHT);
    }

    private void initDBViewPanel(double rem) {
        mDBViewPanel = new BorderPane();

        mDBViewPanel.setPrefSize(PREFERRED_WIDTH, PREFERRED_HEIGHT);
        mDBViewPanel.setPadding(new Insets(0.8 * rem));

        ObservableList<DBController.WordItem> dataSource = FXCollections.observableArrayList(new ArrayList<>());
        mDBTableView = new TableView<>();
        mDBTableView.setItems(dataSource);
        mDBTableView.editableProperty().set(true);
        TableColumn<DBController.WordItem, String> column0 = new TableColumn<>("Word");
        column0.setCellValueFactory(new PropertyValueFactory<>("word"));
        column0.setMinWidth(200.0);

        TableColumn<DBController.WordItem, Integer> column1 = new TableColumn<>("Count");
        column1.setCellValueFactory(new PropertyValueFactory<>("frequency"));

        TableColumn<DBController.WordItem, Boolean> columnX = new TableColumn<>("Selected");
        columnX.setCellValueFactory(param -> param.getValue().getSelected());
        columnX.setCellFactory(CheckBoxTableCell.forTableColumn(columnX));

        mDBTableView.getColumns().setAll(columnX, column0, column1);

        mDBViewPanel.setCenter(mDBTableView);

        ToggleGroup aRadioGroup = new ToggleGroup();

        mRadioRecent = new RadioButton("Recent");
        mRadioRecent.setToggleGroup(aRadioGroup);
        mRadioAll = new RadioButton("All");
        mRadioAll.setToggleGroup(aRadioGroup);

        mBtnBackToInput = new Button("Back");
        mBtnBackToInput.setOnAction(event -> {
            mDBViewPanel.setVisible(false);
            mRadioAll.setSelected(false);
            mRadioRecent.setSelected(false);
            mInputPanel.setVisible(true);
        });

        aRadioGroup.selectedToggleProperty().addListener(new ChangeListener<Toggle>() {
            @Override
            public void changed(ObservableValue<? extends Toggle> observableValue, Toggle toggle, Toggle t1) {
                Object selectedToggle = aRadioGroup.getSelectedToggle();
                if (selectedToggle == mRadioRecent) {
                    showProgressIndicator();
                    mBtnDelete.setDisable(true);
                    new Thread(() -> {
                        DBController.getInstance().queryRecent(listOfWords -> {
                            removeListenerFromDataSource(dataSource);
                            addListenerToDataSource(listOfWords);
                            Platform.runLater(() -> {
                                dataSource.clear();
                                dataSource.addAll(listOfWords);
                                hideProgressIndicator();
                            });
                        });
                    }).start();
                } else if (selectedToggle == mRadioAll) {
                    showProgressIndicator();
                    mBtnDelete.setDisable(true);
                    new Thread(() -> {
                        DBController.getInstance().queryAll(listOfWords -> {
                            removeListenerFromDataSource(dataSource);
                            addListenerToDataSource(listOfWords);
                            Platform.runLater(() -> {
                                dataSource.clear();
                                dataSource.addAll(listOfWords);
                                hideProgressIndicator();
                            });
                        });
                    }).start();

                }
            }
        });

        mBtnDelete = new Button("Delete");

        HBox DBPanelBottomBar = new HBox(100.0f);
        DBPanelBottomBar.setPadding(new Insets(rem * 0.8));
        DBPanelBottomBar.setAlignment(Pos.CENTER);
        DBPanelBottomBar.getChildren().addAll(mBtnBackToInput, mRadioRecent, mRadioAll, mBtnDelete);

        mBtnDelete.setOnAction(event -> {
            showProgressIndicator();
            mBtnDelete.setDisable(true);
            DBPanelBottomBar.setDisable(true);
            mDBTableView.setEditable(false);
            final boolean isRecentSelected = mRadioRecent.isSelected();
            new Thread(() -> {
                HashSet<String> aSet = new HashSet<>();
                for (DBController.WordItem item : dataSource) {
                    if (item.getSelected().get()) {
                        aSet.add(item.getWord());
                    }
                }
                DBController aDB = DBController.getInstance();
                if (isRecentSelected) {
                    aDB.deleteRecentWords(aSet, () -> {
                        aDB.queryRecent(listOfWords ->
                        {
                            removeListenerFromDataSource(dataSource);
                            addListenerToDataSource(listOfWords);
                            Platform.runLater(() ->
                            {
                                dataSource.clear();
                                dataSource.addAll(listOfWords);
                                DBPanelBottomBar.setDisable(false);
                                mDBTableView.setEditable(true);
                                hideProgressIndicator();
                            });

                        });
                    });
                } else {
                    aDB.deleteWords(aSet, () -> {
                        aDB.queryAll(listOfWords ->
                        {
                            removeListenerFromDataSource(dataSource);
                            addListenerToDataSource(listOfWords);
                            Platform.runLater(() ->
                            {
                                dataSource.clear();
                                dataSource.addAll(listOfWords);
                                DBPanelBottomBar.setDisable(false);
                                mDBTableView.setEditable(true);
                                hideProgressIndicator();
                            });
                        });
                    });
                }
            }).start();
        });

        mDBViewPanel.setBottom(DBPanelBottomBar);
        mDBViewPanel.setVisible(false);
    }

    private void showProgressIndicator() {
        mPI.setVisible(true);
    }

    private void hideProgressIndicator() {
        mPI.setVisible(false);
    }

    public static MainWindow create(Stage primaryStage) {
        return new MainWindow(primaryStage);
    }
}
