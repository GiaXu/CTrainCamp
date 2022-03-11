package com.practice.controller;

import java.math.BigInteger;
import java.nio.charset.StandardCharsets;
import java.security.MessageDigest;

public class DBController
{
    static private DBController sController = null;

    static final private String SALT = "4117EAF8-444D-4517-88E5-8C815D58E6B7";
    private DBController(){
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
        String hashCode = makeHash(userName, password);
        return false;
    }

    public boolean signup(String userName, String password){
        String hashCode = makeHash(userName, password);
        return false;
    }

    private void close(){
        // disconnect from databases
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
