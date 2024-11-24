package p5;
import java.io.*; //necessary to use InputStreamReader and BufferedReader

public class KeyboardInputTest {

	public static void main(String[] args) {
		try {//try block is required because InputStreamReader and BufferedReader throw exceptions
			//InputStreamReader sr = new InputStreamReader(System.in);
			//BufferedReader br = new BufferedReader(sr);
			BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
			String s;
			do {
				//Click the console pane of Eclipse and enter arbitrary strings
				System.out.print("Input strings: ");
				s = br.readLine();
				System.out.printf("%s/n", s);
			}while(!s.equals("exit"));	//enter "exit" to break this loop
			br.close();
			//sr.close();
			System.out.println("terminated");
		}catch(Exception e) {	//catch block is required to catch an exception thrown by the reader classes
			System.out.println("Exception: " + e);
			e.printStackTrace();
		}
	}

}
