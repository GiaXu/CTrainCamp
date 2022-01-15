import javax.swing.JFrame;

public class MyFirstFrame extends JFrame{
    public static void main(String args[]){
        MyFirstFrame frame = new MyFirstFrame();
        frame.setVisible(true);
    }
    public MyFirstFrame(){
        super();
        setTitle("利用JFrame创建的窗体");
        setBounds(100,100,500,375);
        getContentPane().setLayout(null);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setVisible(true);
    }
}
