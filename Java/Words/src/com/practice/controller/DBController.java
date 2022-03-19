package com.practice.controller;

import com.mysql.cj.conf.BooleanProperty;
import com.mysql.cj.conf.IntegerProperty;
import com.mysql.cj.conf.StringProperty;
import com.practice.DataModel;
import javafx.beans.property.SimpleBooleanProperty;
import javafx.beans.property.SimpleIntegerProperty;
import javafx.beans.property.SimpleStringProperty;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableBooleanValue;
import javafx.beans.value.ObservableValue;
import javafx.util.Pair;

import java.math.BigInteger;
import java.nio.charset.StandardCharsets;
import java.security.MessageDigest;
import java.util.*;
import java.util.function.Consumer;

public class DBController
{
    static private DBController sController = null;

    static final private String SALT = "4117EAF8-444D-4517-88E5-8C815D58E6B7";

    private final ArrayList<WordItem> mRecentInsertWords = new ArrayList<>();

    public static class WordItem{
        private String word;
        private int frequency;
        private SimpleBooleanProperty selected = new SimpleBooleanProperty(false);

        public String getWord() { return word; }
        public void setWord(String value) { word = value; }

        public int getFrequency(){ return frequency; }
        public void setFrequency(int value){ frequency = value;}

        public ObservableBooleanValue getSelected(){ return selected; }
        public void setSelected(Boolean value){ selected.set(value);}

        public WordItem(String _word, int _frequency){
            setWord(_word);
            setFrequency(_frequency);

            getSelected().addListener(new ChangeListener<Boolean>()
            {
                @Override
                public void changed(ObservableValue<? extends Boolean> observableValue, Boolean aBoolean, Boolean t1)
                {

                }
            });
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

    public boolean submit(String title, String content, Runnable callback){
	try {
            //String lowerTitle = title.toLowerCase();
            //String reLtitle = lowerTitle.replaceAll("(?!_-)\\p{Punct}", " ");

            String Lcontent = content.toLowerCase();
            String reLcontent = Lcontent.replaceAll("(?!_-)\\p{Punct}", " ");

            String[] aWords = reLcontent.split("\\s");

            DataModel aData = DataModel.getInstance();

            //insert aWords into wordsMap
            HashMap<String,Integer> wordsMap = new HashMap<>();

            for (String aWord : aWords) {
                if(wordsMap.containsKey(aWord)){
                    int frequency = wordsMap.get(aWord);
                    wordsMap.put(aWord, frequency + 1);
                }
                else {
                    wordsMap.put(aWord, 1);
                }
            }

            for (String w :wordsMap.keySet()) {
                int fre = wordsMap.get(w);
                aData.insertWord(w,fre);
            }

            // update UI
            mRecentInsertWords.clear();
            for (Map.Entry<String, Integer> anItem : wordsMap.entrySet()) {
                mRecentInsertWords.add( new WordItem(anItem.getKey(), anItem.getValue()));
            }

            callback.run();
            return true;

        }catch (Exception e){
            e.printStackTrace();
            return false;
        }
    }

    public void queryAll(Consumer<List<WordItem>> callback){
        // query all records here:
        ArrayList<WordItem> aResult = new ArrayList<>();
        aResult.add(new WordItem("Hello", 100));
        aResult.add(new WordItem("This", 99));
        aResult.add(new WordItem("is", 98));
        aResult.add(new WordItem("all", 98));
        aResult.add(new WordItem("words", 98));

        callback.accept(aResult);
    }

    public void queryRecent(Consumer<List<WordItem>> callback){
        ArrayList<WordItem> aCopy = new ArrayList<>();
        for (WordItem item : mRecentInsertWords) {
            aCopy.add( new WordItem(item.getWord(), item.getFrequency()));
        }
        callback.accept(aCopy);
    }

    public void deleteWords(Set<String> words, Runnable onCompleted){
        // delete words here:

        onCompleted.run();
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
