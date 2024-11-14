package p3;

public class ArgumentCheck {
	int diff;
	
	void addValue(int v) {
		v = v + diff;
		System.out.println("Value of v in addValue: " + v);
	}
	
	void addValues(int [] u) {
		for(int i = 0; i < u.length; i++) {
			u[i] += diff;
			System.out.printf("Value of %d-th value of array u in addValues: %d\n", i, u[i]);
		}
	}

	public static void main(String[] args) {
		ArgumentCheck test = new ArgumentCheck();
		test.diff = 2;
		int v = 10;
		int [] u = {1, 2, 3, 4, 5};
		
		System.out.println("Value of v in main: " + v);
		test.addValue(v);
		System.out.println("Value of v in main: " + v);
		
		for(int i = 0; i < u.length; i++)
			System.out.printf("Value of %d-th value of array u in main: %d\n", i, u[i]);
		test.addValues(u);;
		for(int i = 0; i < u.length; i++)
			System.out.printf("Value of %d-th value of array u in main: %d\n", i, u[i]);
	}

}
