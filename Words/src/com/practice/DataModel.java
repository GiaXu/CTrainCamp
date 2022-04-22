package com.practice;

import com.practice.config.DBConfig;
import com.practice.controller.DBController;

import java.sql.*;
import java.util.ArrayList;
import java.util.UUID;

public class DataModel {

    static class DBConnection {

        public static Connection createConnection(String url, String databaseName, String userName, String password){
            String fullUrl = String.format("%s/%s", url, databaseName);
            //fullUrl = "jdbc:mysql://localhost:3306/Users"
            Connection conn = null;
            try{
                conn = DriverManager.getConnection(fullUrl, userName, password);
            }catch (SQLException e){
                createDatabase(url, databaseName, userName, password);
                try{
                    conn = DriverManager.getConnection(fullUrl, userName, password);
                }catch (SQLException ex){
                    ex.printStackTrace();
                }
            }
            return conn;
        }

        private static void createDatabase(String url, String databaseName, String userName, String password){
            String sql = String.format("CREATE DATABASE IF NOT EXISTS %s", databaseName);

            try{
                Connection conn = DriverManager.getConnection(url, userName, password);
                PreparedStatement stmt = conn.prepareStatement(sql);
                stmt.execute();
                conn.close();
            } catch (Exception e){
                e.printStackTrace();
            }
        }
    }

    private Connection mUsersConnection = null;
    private Connection mProjectConnection = null;

    private static DataModel sDataModel = null;
    private static final int VERSION_USERS = 1;
    private static boolean sUserInitOK = false;
    private static boolean sProjectInitOK = false;

    public static DataModel getInstance(){
        if (null == sDataModel){
            sDataModel = new DataModel();
        }

        return sDataModel;
    }

    public static void releaseInstance(){
        if (null != sDataModel){
            sDataModel.release();
            sDataModel = null;
        }
    }

    private DataModel()
    {
        mUsersConnection = DBConnection.createConnection(DBConfig.DATABASE_URL,
                "Users",
                DBConfig.DATABASE_USERNAME,
                DBConfig.DATABASE_PASSWORD);

        sUserInitOK = initUsersTable();
    }


    private boolean initUsersTable(){
        try{
            String sql = "CREATE TABLE IF NOT EXISTS Version (version INT PRIMARY KEY)";
            Statement stmt = mUsersConnection.createStatement();
            stmt.execute(sql);

            String sql_user = "CREATE TABLE IF NOT EXISTS Users (user_hash VARCHAR(255) PRIMARY KEY,db_path VARCHAR(255))";
            Statement stat = mUsersConnection.createStatement();
            stat.execute(sql_user);

            int aVersion = getUsersTableVersion();
            if (0 == aVersion){
                setUsersTableVersion();
            }

            return true;

        } catch (SQLException e){
            e.printStackTrace();
        }

        return false;
    }


    public int getUsersTableVersion(){
        try{
            String sql = "SELECT version FROM Version";
            Statement stmt = mUsersConnection.createStatement();
            if (stmt.execute(sql)){
                ResultSet rs = stmt.getResultSet();
                if (rs.next()){
                    return rs.getInt(1);
                }
                rs.close();
            }
        } catch (SQLException e){
            e.printStackTrace();
        }

        return 0; //invalid value
    }


    private void setUsersTableVersion(){
        try{
            String sql = String.format("INSERT INTO Version(version) VALUES(%d)", VERSION_USERS);
            Statement stmt = mUsersConnection.createStatement();
            stmt.execute(sql);
        }catch (SQLException e){
            e.printStackTrace();
        }
    }


    private boolean initProjectTable(){
        try{
            String sql_version = "CREATE TABLE IF NOT EXISTS Version (version INT PRIMARY KEY)";
            Statement stmt = mProjectConnection.createStatement();
            stmt.execute(sql_version);

            String sql_words = "CREATE TABLE IF NOT EXISTS Words (word VARCHAR(255) PRIMARY KEY, " +
                    "frequency INT, familiarity INT, voice VARCHAR(255), Chinese VARCHAR(255))";
            Statement stat = mProjectConnection.createStatement();
            stat.execute(sql_words);

            String sql_source = "CREATE TABLE IF NOT EXISTS Source (word VARCHAR(255), source VARCHAR(255), " +
                    "frequency INT, PRIMARY KEY(word, source))";
            Statement stet = mProjectConnection.createStatement();
            stet.execute(sql_source);


            int aVersion = getProjectTableVersion();
            if (0 == aVersion){
                setProjectTableVersion();
            }

            return true;

        } catch (SQLException e){
            e.printStackTrace();
        }

        return false;
    }


    public int getProjectTableVersion(){
        try{
            String sql = "SELECT version FROM Version";
            Statement stmt = mProjectConnection.createStatement();
            if (stmt.execute(sql)){
                ResultSet rs = stmt.getResultSet();
                if (rs.next()){
                    return rs.getInt(1);
                }
                rs.close();
            }
        } catch (SQLException e){
            e.printStackTrace();
        }

        return 0; //invalid value
    }


    private void setProjectTableVersion(){
        try{
            String sql = String.format("INSERT INTO Version(version) VALUES(%d)", VERSION_USERS);
            Statement stmt = mProjectConnection.createStatement();
            stmt.execute(sql);
        }catch (SQLException e){
            e.printStackTrace();
        }
    }


    public void insertWord(String word, int values){
        try{
            int count = checkFrequency(word);
            Statement stat = mProjectConnection.createStatement();
            if(0 == count) {
                String insert = String.format("INSERT INTO Words(word) VALUES('%s')", word);
                stat.execute(insert);
            }
            String setFrequency = String.format("UPDATE Words SET frequency = '%d' WHERE word='%s'", values, word);
            stat.execute(setFrequency);

        }catch (SQLException e){
            e.printStackTrace();
        }
    }

    public ArrayList<DBController.WordItem> getWords(){
        ArrayList<DBController.WordItem> aResult = new ArrayList<>();
        try{
            String getaWord = String.format("SELECT word,frequency FROM Words ORDER BY frequency DESC");
            Statement stat = mProjectConnection.createStatement();
            if(stat.execute(getaWord)){
                ResultSet re = stat.getResultSet();
                while (re.next()){
                    String aWord = re.getString(1);
                    int aFre = re.getInt(2);
                   aResult.add(new DBController.WordItem(aWord, aFre));
                }
                re.close();
            }

        }catch (SQLException e){
            e.printStackTrace();
        }

        return aResult;
    }

    public int checkFrequency(String word){
        try{
            String checkFre = String.format("SELECT frequency FROM Words WHERE word = '%s'",word);
            Statement stat = mProjectConnection.createStatement();
            if(stat.execute(checkFre)){
                ResultSet re = stat.getResultSet();
                if(re.next()){
                    int count = re.getInt(1);

                    return count;
                }
            }

        }catch(SQLException e){
            e.printStackTrace();
        }

        return 0;
    }

    public void deleteWord(String word){
        try{
            if(0 == checkFrequency(word)){
                return;
            }
            String deleteWord = String.format("DELETE FROM Words WHERE word = '%s'",word);
            Statement stat = mProjectConnection.createStatement();
            stat.execute(deleteWord);

        }catch (SQLException e){
            e.printStackTrace();
        }
    }

    private boolean checkDuplicates(String userHashCode){
        try{
            String checkDup = String.format("SELECT COUNT(user_hash) FROM Users WHERE user_hash = '%s'",userHashCode);
            Statement stat = mUsersConnection.createStatement();
            if(stat.execute(checkDup)){
                ResultSet re = stat.getResultSet();
                if(re.next()){
                    int count = re.getInt(1);
                    return 0 != count;
                }
            }

        }catch (SQLException e){
            e.printStackTrace();
        }

        return false;
    }

    public String signUp(String userHashCode){

        boolean check = checkDuplicates(userHashCode);
        if(check){
            return null;      //user already exists
        }
        try {
            String newDBName = UUID.randomUUID().toString().toLowerCase().replace("-", "");
            String sql = String.format("INSERT INTO Users(user_hash, db_path) VALUES('%s','%s')", userHashCode, newDBName);
            Statement stmt = mUsersConnection.createStatement();
            stmt.execute(sql);

            mProjectConnection = DBConnection.createConnection(DBConfig.DATABASE_URL,
                    newDBName,
                    DBConfig.DATABASE_USERNAME,
                    DBConfig.DATABASE_PASSWORD);

            sProjectInitOK = initProjectTable();

            return newDBName;

        } catch (SQLException e){
            e.printStackTrace();
        }

        return null;
    }

    public String logIn(String userHashCode){

        boolean check = checkDuplicates(userHashCode);
        if(check) {
            try {
                String sql = String.format("SELECT db_path FROM Users WHERE user_hash = '%s'", userHashCode);
                Statement stat = mUsersConnection.createStatement();
                if (stat.execute(sql)) {
                    ResultSet rs = stat.getResultSet();
                   if (rs.next()) {
                        String pro = rs.getString(1);

                        if(null != mProjectConnection){
                            mProjectConnection.close();
                        }
                        mProjectConnection = DBConnection.createConnection(DBConfig.DATABASE_URL,
                                pro,
                                DBConfig.DATABASE_USERNAME,
                                DBConfig.DATABASE_PASSWORD);
                        return pro;
                    }
                    rs.close();
                }

            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
            return null;
    }

    private void release(){
        if (null != mUsersConnection){
            try {
                mUsersConnection.close();
            }catch (SQLException e){
                e.printStackTrace();
            } finally {
                mUsersConnection = null;
            }
        }

        sUserInitOK = false;
    }
}

