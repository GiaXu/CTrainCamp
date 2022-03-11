package com.practice;


import com.practice.gui.MyApplication;

public class Main extends MyApplication {

    public static void main(String[] args) {
	// Register MYSQL connectorJ
        try{
            Class.forName("com.mysql.cj.jdbc.Driver").newInstance();
        }catch (Exception ex){
            ex.printStackTrace();
        }

        DataModel aDataModel = DataModel.getInstance();
        int usersVersion = aDataModel.getUsersTableVersion();

        launch(args);
/*
        aDataModel.signUp("Xujiaqi22222");
        aDataModel.signUp("Wangsiqi");
        aDataModel.logIn("Xujiaqi22222");
        aDataModel.logIn("Wangsiqi");


 */
        DataModel.releaseInstance();

        return;
    }
}
