package p4;

// an abstract class to store base (底辺) and height (高さ) of a figure
abstract class Shape{
	double base;
	double height;
	Shape(double b, double h){
		base = b; height = h;
	}
	// an abstract method to be implemented in a subclass
	abstract double getArea();
}

class Rectangle extends Shape{	// a subclass of Shape for rectangle
	Rectangle(double b, double h){
		super(b, h);	//Calling the constructor of the superclass Shape
	}
	double getArea() {	//actual implementation of the method getArea()
		return base * height;
	}
}

class Triangle extends Shape{	//a subclass of Shape for triangle
	Triangle(double b, double h){
		super(b, h);	//Calling the constructor of the superclass Shape
	}
	double getArea() {	//actual implementation of the method getArea()
		return base * height * 0.5;
	}
}

public class AreaTest {

	public static void main(String[] args) {
		Rectangle rect = new Rectangle(2.0, 5.0);
		Triangle tri = new Triangle(2.0, 5.0);
		System.out.printf("Area of the base %.1f, height %.1g rectangle: %.1f\n", rect.base, rect.height, rect.getArea());
		System.out.printf("Area of the base %.1f, height %.1f triangle: %.1f\n", tri.base, tri.height, tri.getArea());
		
		System.out.println("Class: " + rect.getClass() + " Superclass: " + rect.getClass().getSuperclass());
		System.out.println("Class: " + tri.getClass() + " Superclass: " + tri.getClass().getSuperclass());

	}

}
