package p5;
import java.io.*;
import org.apache.commons.lang3.*;

public class ReadFile {

	public static void main(String[] args) {
		try {
			FileReader fr = new FileReader(args[0]);
			BufferedReader br = new BufferedReader(fr);
			
			String s, token[];
			while((s = br.readLine()) != null) {
				token = StringUtils.split(s);
				for(int i = 0; i < token.length; i++) {
					System.out.println(token[i]);
				}
			}
			br.close();
			fr.close();
		}catch(Exception e) {
			System.out.println("Exception: " + e);
			e.printStackTrace();
		}

	}

}
