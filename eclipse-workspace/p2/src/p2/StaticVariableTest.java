package p2;

public class StaticVariableTest {
	int instance_var;
	static int static_var;
	final static int static_constant = 1000;

	public static void main(String[] args) {
		StaticVariableTest instance1 = new StaticVariableTest();
		StaticVariableTest instance2 = new StaticVariableTest();
		
		instance1.instance_var = 10;
		instance2.instance_var = 20;
		StaticVariableTest.static_var = 100;
		System.out.println("instance1.instance_var = " + instance1.instance_var);
		System.out.println("instance2.instance_Var = " + instance2.instance_var);
		System.out.println("static_var = " + StaticVariableTest.static_var);
		System.out.println("static_constant = " + StaticVariableTest.static_constant);
		
		instance1.instance_var += 10;
		instance2.instance_var *= 20;
		StaticVariableTest.static_var = 200;
		System.out.println("instance1.instance_var = " + instance1.instance_var);
		System.out.println("instance2.instance_var = " + instance2.instance_var);
		System.out.println("static_var = " + StaticVariableTest.static_var);
		System.out.println("static_constant = " + StaticVariableTest.static_constant);

	}

}
