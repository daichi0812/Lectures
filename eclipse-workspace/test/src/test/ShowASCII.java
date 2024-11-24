package test;

public class ShowASCII {

	public static void main(String[] args) {
		
		int i, code;
		
		for(code=33, i=1; code<127; code++, i++) {
			System.out.printf("\'%c\'(%3d)", (char)code, code);
			System.out.printf((i%5==0)? "\n":" ");
			
		}
		System.out.println("");
	}

}
