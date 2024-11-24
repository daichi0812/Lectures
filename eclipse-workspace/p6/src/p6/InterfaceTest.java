package p6;

interface In1{		//Definition of interface In1
	int v1 = 10;	//Constrant (modifier "public static final" is omi
	void showMessage1();	//Abstract method (modifier "public abstract" is omitted)
}

interface In2{
	int v2 = 20;
	void showMessage2();
}

interface In1ext extends In1, In2{
	int v1ext = 100;
	void showMessage1ext();
}

class InClass implements In1, In2{		//Implementation of In1
	public void showMessage1() {	//Mofidier "public" must be specified
		System.out.println("showMessage of InClass");
	}
	
	public void showMessage2() {
		System.out.println("showMesssage2 of InClass");
	}
	public void showMessage() {
		System.out.println("showMessage of InClass");
	}
}

class InClassExt implements In1ext{
	public void showMessage1() {
		System.out.println("showMessage1 of InClassExt");
	}
	public void showMessage1ext() {
		System.out.println("ShowMessage1ext of InClassExt");
	}
	public void showMessage2() {
		System.out.println("showMessage2 of InClassExt");
	}
}

class BaseClass{
	void showMessage() {
		System.out.println("showMessage of BaseClass");
	}
}

public class InterfaceTest {

	public static void main(String[] args) {
		InClass in0bj = new InClass();
		System.out.println("Constant of In1: " + In1.v1);
		in0bj.showMessage1();
		
		System.out.println("Constant of In2: " + In2.v2);
		in0bj.showMessage2();
		
		InClassExt inExt0bj = new InClassExt();
		System.out.println("Constant v1 of In1ext: " + In1ext.v1);
		System.out.println("Constant v1ext of In1ext: " + In1ext.v1ext);
		inExt0bj.showMessage1();
		inExt0bj.showMessage1ext();
		
		System.out.println("Constant v2 of In1ext: " + In1ext.v2);
		inExt0bj.showMessage2();
		
		in0bj.showMessage();
		
		// Reference through a reference type variable of an interface
		In1 in1Var = new InClass();
		in1Var.showMessage1();
		if(in1Var instanceof InClass) {
			System.out.println("Instance of InClass");
		}
		else {
			System.out.println("Instance of InClassExt");
		}
		in1Var = inExt0bj;
		in1Var.showMessage1();
		if(in1Var instanceof InClass) {
			System.out.println("Instance of InClass");
		}
		else {
			System.out.println("Instance of InClassExt");
		}
	}

}
