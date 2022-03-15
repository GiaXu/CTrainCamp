package com.practice.controller;

import com.mysql.cj.conf.IntegerProperty;
import com.mysql.cj.conf.StringProperty;
import com.practice.DataModel;
import javafx.beans.property.SimpleIntegerProperty;
import javafx.beans.property.SimpleStringProperty;

import java.math.BigInteger;
import java.nio.charset.StandardCharsets;
import java.security.MessageDigest;
import java.util.ArrayList;
import java.util.List;
import java.util.function.Consumer;

public class DBController
{
    static private DBController sController = null;

    static final private String SALT = "4117EAF8-444D-4517-88E5-8C815D58E6B7";

    public static class WordItem{
        private String word;
        private int frequency;

        public String getWord() { return word; }
        public void setWord(String value) { word = value; }

        public int getFrequency(){ return frequency; }
        public void setFrequency(int value){ frequency = value;}

        public WordItem(String _word, int _frequency){
            setWord(_word);
            setFrequency(_frequency);
        }
    };

    private DBController(){
        DataModel aDataModel = DataModel.getInstance();
        // Connect to Users database
    }

    private String makeHash(String userName, String password){
        String source = userName + password + SALT;
        byte[] buffer = source.getBytes(StandardCharsets.UTF_8);
        try
        {
            MessageDigest md = MessageDigest.getInstance("MD5");
            byte[] hashedCode = md.digest(buffer);
            return String.format("%032x", new BigInteger(1, hashedCode));
        }
        catch (Exception e){
            e.printStackTrace();
            return null;
        }
    }

    public boolean login(String userName, String password){
        try {
            String hashCode = makeHash(userName, password);

            DataModel aDataModel = DataModel.getInstance();
            String check = aDataModel.logIn(hashCode);
            if(null == check)
            {
                return false;
            }
            return true;

        }catch (Exception e){
            e.printStackTrace();
        }
        return false;
    }

    public boolean signup(String userName, String password){
        try {
            String hashCode = makeHash(userName, password);

            DataModel aDataModel = DataModel.getInstance();
            String check = aDataModel.signUp(hashCode);
            if(null == check)
            {
                return false;
            }
            return true;

        }catch (Exception e){
            e.printStackTrace();
        }
        return false;
    }

    public boolean submit(String title, String content, Consumer<List<WordItem>> callback){
        ArrayList<WordItem> aResult = new ArrayList();
        aResult.add(new WordItem("hello",100));
        aResult.add(new WordItem("world", 101));
        callback.accept(aResult);
        return false;
    }

    private void close(){
        // disconnect from databases
        DataModel.releaseInstance();
    }

    static public DBController getInstance(){
        if (null == sController) {
            sController = new DBController();
        }

        return sController;
    }

    static public void release(){
        if (null != sController){
            sController.close();
            sController = null;
        }
    }
}
