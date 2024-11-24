// 15822108 情報テクノロジー学科 堀田大智
package task11_1;

import java.io.*;

public class Vector {
	
	private double[] data;
	
	Vector(int columns) {
		data = new double[columns];
	}
	
	double get(int i) {
		return data[i];
	}
	
	void set(int i, double num) {
		data[i] = num;
	}
	
	 void show() {
		for(int i = 0; i < data.length; i++) {
			System.out.printf(data[i] + " ");
		}
		System.out.println();
	}
	
	void show(String description) {
		System.out.println(description);
		show();
	}
	
	void writeToFile(String filename) {
		writeToFile(filename, false);
	}
	
	void writeToFile(String filename, boolean append) {
		try {
			StringBuilder builder = new StringBuilder();
			for (int i = 0; i < data.length; i++) {
					builder.append(data[i] + "");
					if (i < data.length - 1)
						builder.append(" ");
					else
						builder.append("\r\n");
			}
			BufferedWriter writer;
			if (append) {
				writer = new BufferedWriter(new FileWriter(filename, true)); 
			} else {
				writer = new BufferedWriter(new FileWriter(filename)); 
			}

			writer.write(builder.toString());
			writer.close();
		} catch (IOException e) {
			System.out.println(e);
			System.exit(1);
		}

	}

	public static void main(String[] args) {
		// TODO Auto-generated method stub

	}

}
