package test;

public class ShowASCII2 {

	public static void main(String[] args) {

		int i=1, code=33;
		
		while(code<127) {
			System.out.printf("\'%c\'(%3d)", (char)code, code);
			if(i%5==0)System.out.println ("");
			else System.out.print(" ");
			code++;
			i++;
		}
		System.out.println("");

	}

}
