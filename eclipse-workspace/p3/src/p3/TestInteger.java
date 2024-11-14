package p3;

public class TestInteger {

	public static void main(String[] args) {
		int v = 5;
		
		String s = Integer.toString(v);
		System.out.println("v = " + s);
		System.out.println("v = " + v); //implicit conversion
		
		Integer U = 100; //boxing conversion
		int u = U.intValue();
		System.out.println("u = " + u);
		u = U; //unboxing coversion
		System.out.println("u = " + u);
		u = Integer.valueOf("123"); 	//atoi()( (unboxing conversion)
		u += 100;
		System.out.println("u = " + u);
	}
}
