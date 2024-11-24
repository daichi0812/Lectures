package p5;
import java.io.*;

public class WriteFile {

	public static void main(String[] args) {
		try {
			BufferedReader br = new BufferedReader(new FileReader(args[0]));
			BufferedWriter bw = new BufferedWriter(new FileWriter(args[1]));
			
			String s;
			while((s = br.readLine()) != null) {
				System.out.println(s);
				bw.write(s);
				bw.newLine();
			}
			bw.close();
			br.close();
		}
		catch(Exception e) {
			System.out.println("Exception: " + e);
			e.printStackTrace();
		}

	}

}
