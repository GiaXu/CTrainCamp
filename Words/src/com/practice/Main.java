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
/*
        String a = "Q?A!Z,w,s,x\\E.d/C";
        String LowerCase = a.toLowerCase();
        String replace = LowerCase.replaceAll("(?!\")\\p{Punct}", " ");
        String[] words = replace.split("\\s");
        for(String w:words){
            System.out.println(w);
        }
*/

        return;
    }
}
