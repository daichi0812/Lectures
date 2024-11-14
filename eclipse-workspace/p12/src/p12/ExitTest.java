package p12;

public class ExitTest {
	
	static void callExit() {
		System.out.println("Before System.exit()");
		System.exit(0);
		System.out.println("After System,exit()");
	}

	public static void main(String[] args) {
		System.out.println("Before callExit()");
		callExit();
		System.out.println("After callExit()");

	}

}
