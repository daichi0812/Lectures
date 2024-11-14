package p7;
import java.io.*;

public class FileListTest {

	public static void main(String[] args) {
		
		File dir = new File(args[0]);
		File [] files = dir.listFiles();
		for(File file: files) {
			System.out.println(file.toString());
		}

	}

}
