abstract class A {
        public abstract void f();
        public void g(){
            System.out.println("Hello!");
        }
}

class B extends A {
    public void f(){
        System.out.println("Hi!");
    }
}

interface Shape{
    public abstract double computeArea();
}

class Rect implements Shape{
    private double width;
    private double height;

    Rect(){}
    Rect(double width,double height){
        this.height = height;
        this.width = width;
    }

    public double getWidth(){
        return width;
    }

    public double getHeight(){
        return height;
    }

    public void setWidth(double width){
        this.width = width;
    }

    public void setHeight(double height){
        this.height = height;
    }

    public double computeArea(){
        return width * height;
    }

    public void printf(){
        System.out.println("The area is "+computeArea());
    }
}






