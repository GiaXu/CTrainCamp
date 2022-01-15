public class Employee {
    private String m_name;
    private int m_age;
    private double m_id;

    Employee(){
    }
    Employee(String name,int age,double id){
        m_name = name;
        m_age = age;
        m_id = id;
    }
    public String getM_name(){
        return m_name;
    }
    public void setM_name(String name){
        m_name = name;
    }
    public String getDetails(){
        return m_name +"\t"+ m_age +"\t"+  m_id;
    }
}

class Manager extends Employee{
    private String m_name;
    private int m_age;
    private double m_id;
    private String m_vehicle;

    Manager(){
    }
    Manager(String name,int age,double id,String vehicle){
        m_name = name;
        m_age = age;
        m_id = id;
        m_vehicle = vehicle;
    }
    public String getDetails(){
        return m_name +"\t"+ m_age +"\t"+  m_id +"\t"+ m_vehicle;
    }


}

