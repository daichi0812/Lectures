package p4;

class A{
	int a, b;
	
	A(int i, int j){
		a = i;
		b = j;
	}
	
	A(){
		this(10, 20);
	}
}

class B extends A {
	int a, c, d;
	
	B(int i, int j, int k, int l, int m){
		super(i, j);
		a = k;
		c = l;
		d = m;
	}
	
	B(){
		this(10, 20, 15, 30, 40);
	}
	
	int getSuperA() {
		return super.a;
	}
}

class C extends B {
	int a, c, e;
	
	C(){
		a = 50;
		c = 60;
		e = 70;
	}
	
	/*int getSuperA() {
		return super.a;
	}*/
	
	int getSuperC() {
		return super.c;
	}
}

public class InheritTest {
	
	public static void main(String[] args) {
		C instC = new C();
		B instB = new B();
		
		System.out.printf("For the instance of class C\n");
		System.out.printf("a = %d, b = %d, c = %d, d = %d, e = %d\n", instC.a, instC.b, instC.c, instC.d, instC.e);
		System.out.printf("Super.a = %d, super.c = %d\n", instC.getSuperA(), instC.getSuperC());
		
		System.out.printf("For the instance of class B\n");
		System.out.printf("a = %d, b = %d, c = %d, d = %d\n", instB.a, instB.b, instB.c, instB.d);
		System.out.printf("super.a = %d\n", instB.getSuperA());

	}

}
