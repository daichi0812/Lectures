package p12;

public class ExceptionTest {
	private double[] data;
	
	ExceptionTest(){
		int num_elements = 5;
		
		data = new double[num_elements];
	}
	
	double getElement(int i) {
		return data[i];
	}

	public static void main(String[] args) {
		ExceptionTest ex = new ExceptionTest();
		
		System.out.println("Before exception");
		ex.getElement(10);
		System.out.println("After exception");

	}

}
