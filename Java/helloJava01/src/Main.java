import javax.imageio.plugins.bmp.BMPImageWriteParam;
import java.util.Scanner;
import javax.swing.JFrame;

public class Main {

    public static void main(String[] args){
        final int x = 5;
/*
        System.out.println("Hello Java!");
        System.out.println("My name is Floria");
        System.out.println("answer is:"+(x+7));

        Student s = new Student("Floria",19);
        System.out.println("Student :");
        System.out.println(s.getDetails());
*/
        /*
        Employee p = new Employee("David",19,1001);
        System.out.println("Employee :");
        System.out.println(p.getDetails());

        Employee a = new Manager("Lucas",20,1005,"BMW");
        System.out.println("Manager :");
        System.out.println(a.getDetails());



        System.out.println(x>=2);
        double e = 1.0;
        double b = 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1;
        System.out.println(e==b);
        System.out.println(Math.abs(e-b) < 1e-6);
*/
        /*
        Scanner in = new Scanner(System.in);
        System.out.println("Please input your age: ");
        System.out.println("Your age is : " + in.nextInt());

        System.out.println("You are in a great age,please enjoy it!");

        System.out.println("How time flies!");

        System.out.println("Have you remember your goal?");


        B b=new B();
        b.f();
        b.g();
        Rect j=new Rect(6,8);
        j.printf();
        Shape q=new Rect(2,7);
        System.out.println("The area of q is  "+q.computeArea());

 */
        MyFirstFrame t;

    }
}

class Student{
    private String m_name;
    private int m_age;
    Student(){
    }
    Student(String name,int age){
        m_name = name;
        m_age = age;
    }
    public String getM_name(){
        return m_name;
    }
    public void setM_name(String name){
        m_name = name;
    }
    public String getDetails(){
        return m_name +"\t"+  m_age;
    }

}



