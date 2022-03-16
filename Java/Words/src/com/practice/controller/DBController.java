package com.practice.controller;

import com.practice.DataModel;

import javax.xml.crypto.Data;
import java.math.BigInteger;
import java.nio.charset.StandardCharsets;
import java.security.MessageDigest;

public class DBController
{
    static private DBController sController = null;

    static final private String SALT = "4117EAF8-444D-4517-88E5-8C815D58E6B7";
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

    public boolean submit(String title, String content){
        try {
            String lowerTitle = title.toLowerCase();
            String reLtitle = lowerTitle.replaceAll("(?!\")\\p{Punct}", " ");

            String Lcontent = content.toLowerCase();
            String reLcontent = Lcontent.replaceAll("(?!\")\\p{Punct}", " ");

            String Words = reLtitle.concat(" " + reLcontent);
            String[] Awords = Words.split("\\s");

            for (String w : Awords) {
                DataModel adata = DataModel.getInstance();
                adata.insertWord(w);
            }
                return true;

        }catch (Exception e){
            e.printStackTrace();
        }

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
